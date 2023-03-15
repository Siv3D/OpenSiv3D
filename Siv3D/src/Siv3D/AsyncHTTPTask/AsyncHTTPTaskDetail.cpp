//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Common.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FileSystem.hpp>
# include "AsyncHTTPTaskDetail.hpp"

# define CURL_STATICLIB
# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/curl/curl.h>
# else
#	include <curl/curl.h>
# endif

namespace s3d
{
	namespace detail
	{
		static size_t WriteAsyncCallback(const char* ptr, const size_t size, const size_t nmemb, IWriter* pWriter)
		{
			const size_t size_bytes = (size * nmemb);

			pWriter->write(ptr, size_bytes);

			return size_bytes;
		}

		static size_t HeaderAsyncCallback(const char* buffer, const size_t size, const size_t nitems, std::string* userData)
		{
			const size_t size_bytes = (size * nitems);

			userData->append(buffer, size_bytes);

			return size_bytes;
		}

		static int ProgressCallback(AsyncHTTPTaskDetail* progress, const curl_off_t dlTotal, const curl_off_t dlNow, const curl_off_t ulTotal, const curl_off_t ulNow)
		{
			progress->updateProgress(dlTotal, dlNow, ulTotal, ulNow);

			if (progress->isAborted())
			{
				return CURLE_ABORTED_BY_CALLBACK;
			}

			return 0;
		}
	}

	AsyncHTTPTaskDetail::AsyncHTTPTaskDetail() {}

	AsyncHTTPTaskDetail::AsyncHTTPTaskDetail(const URLView url, const HashTable<String, String>& headers, const FilePathView path)
		: m_url{ url }
	{
		m_writer.open(path);

		m_headers = headers;

		m_task = Async(&AsyncHTTPTaskDetail::runGet, this);
	}

	AsyncHTTPTaskDetail::AsyncHTTPTaskDetail(const URLView url, const HashTable<String, String>& headers, const void* src, const size_t size, const FilePathView path)
		: m_url{ url }
	{
		m_writer.open(path);

		m_headers = headers;

		m_blob.create(src, size);

		m_task = Async(&AsyncHTTPTaskDetail::runPost, this);
	}

	AsyncHTTPTaskDetail::~AsyncHTTPTaskDetail()
	{
		if (getStatus() == HTTPAsyncStatus::Downloading)
		{
			m_abort = true;

			m_task.wait();
		}
	}

	bool AsyncHTTPTaskDetail::isEmpty() const noexcept
	{
		return m_url.isEmpty();
	}

	bool AsyncHTTPTaskDetail::isReady() const
	{
		return m_task.isReady();
	}

	void AsyncHTTPTaskDetail::cancel()
	{
		if (m_task.isValid())
		{
			m_abort = true;

			m_task.wait();
		}
	}

	const HTTPResponse& AsyncHTTPTaskDetail::getResponse()
	{
		if (m_task.isReady())
		{
			m_response = m_task.get();
		}

		return m_response;
	}

	HTTPAsyncStatus AsyncHTTPTaskDetail::getStatus()
	{
		std::lock_guard lock{ m_mutex };

		return m_progress_internal.status;
	}

	void AsyncHTTPTaskDetail::setStatus(const HTTPAsyncStatus status)
	{
		std::lock_guard lock{ m_mutex };

		m_progress_internal.status = status;
	}

	HTTPProgress AsyncHTTPTaskDetail::getProgress()
	{
		std::lock_guard lock{ m_mutex };

		return m_progress_internal;
	}

	void AsyncHTTPTaskDetail::updateProgress(const int64 dlTotal, const int64 dlNow, const int64 ulTotal, const int64 ulNow)
	{
		std::lock_guard lock{ m_mutex };

		m_progress_internal.downloaded_bytes = static_cast<int64>(dlNow);
		m_progress_internal.uploaded_bytes = static_cast<int64>(ulNow);

		if (dlTotal)
		{
			m_progress_internal.download_total_bytes = static_cast<int64>(dlTotal);
		}

		if (ulTotal)
		{
			m_progress_internal.upload_total_bytes = static_cast<int64>(ulTotal);
		}
	}

	bool AsyncHTTPTaskDetail::isAborted() const
	{
		return m_abort;
	}

	void AsyncHTTPTaskDetail::close()
	{
		m_writer.close();

		m_headers.clear();

		m_blob.release();
	}

	HTTPResponse AsyncHTTPTaskDetail::runGet()
	{
		if (not m_writer)
		{
			setStatus(HTTPAsyncStatus::Failed);
			return{};
		}

		::CURL* curl = ::curl_easy_init();
		{
			if (not curl)
			{
				setStatus(HTTPAsyncStatus::Failed);
				close();
				return{};
			}
		}

		// ヘッダの追加
		::curl_slist* header_slist = nullptr;
		{
			for (auto&& [key, value] : m_headers)
			{
				const std::string header = (key.toUTF8() + ": " + value.toUTF8());
				header_slist = ::curl_slist_append(header_slist, header.c_str());
			}
		}

		setStatus(HTTPAsyncStatus::Downloading);

		const std::string urlUTF8 = m_url.toUTF8();
		::curl_easy_setopt(curl, ::CURLOPT_URL, urlUTF8.c_str());
		::curl_easy_setopt(curl, ::CURLOPT_FOLLOWLOCATION, 1L);
		::curl_easy_setopt(curl, ::CURLOPT_HTTPHEADER, header_slist);
		::curl_easy_setopt(curl, ::CURLOPT_WRITEFUNCTION, detail::WriteAsyncCallback);
		::curl_easy_setopt(curl, ::CURLOPT_WRITEDATA, &m_writer);
		::curl_easy_setopt(curl, ::CURLOPT_XFERINFOFUNCTION, detail::ProgressCallback);
		::curl_easy_setopt(curl, ::CURLOPT_XFERINFODATA, this);
		::curl_easy_setopt(curl, ::CURLOPT_NOPROGRESS, 0L);

		// レスポンスヘッダーの設定
		std::string responseHeader;
		{
			::curl_easy_setopt(curl, ::CURLOPT_HEADERFUNCTION, detail::HeaderAsyncCallback);
			::curl_easy_setopt(curl, ::CURLOPT_HEADERDATA, &responseHeader);
		}

		const ::CURLcode result = ::curl_easy_perform(curl);
		::curl_easy_cleanup(curl);
		::curl_slist_free_all(header_slist);

		const FilePath saveFilePath = m_writer.path();

		close();

		if (result != ::CURLE_OK)
		{
			LOG_FAIL(U"curl failed (CURLcode: {})"_fmt(FromEnum(result)));

			if (result == ::CURLE_ABORTED_BY_CALLBACK)
			{
				setStatus(HTTPAsyncStatus::Canceled);
			}
			else
			{
				setStatus(HTTPAsyncStatus::Failed);
			}

			FileSystem::Remove(saveFilePath);

			return{};
		}

		setStatus(HTTPAsyncStatus::Succeeded);

		return HTTPResponse{ responseHeader };
	}

	HTTPResponse AsyncHTTPTaskDetail::runPost()
	{
		if (not m_writer)
		{
			setStatus(HTTPAsyncStatus::Failed);
			return{};
		}

		::CURL* curl = ::curl_easy_init();
		{
			if (not curl)
			{
				setStatus(HTTPAsyncStatus::Failed);
				close();
				return{};
			}
		}

		// ヘッダの追加
		::curl_slist* header_slist = nullptr;
		{
			for (auto&& [key, value] : m_headers)
			{
				const std::string header = (key.toUTF8() + ": " + value.toUTF8());
				header_slist = ::curl_slist_append(header_slist, header.c_str());
			}
		}

		setStatus(HTTPAsyncStatus::Downloading);

		const std::string urlUTF8 = m_url.toUTF8();
		::curl_easy_setopt(curl, ::CURLOPT_URL, urlUTF8.c_str());
		::curl_easy_setopt(curl, ::CURLOPT_FOLLOWLOCATION, 1L);
		::curl_easy_setopt(curl, ::CURLOPT_HTTPHEADER, header_slist);
		::curl_easy_setopt(curl, ::CURLOPT_POST, 1L);
		::curl_easy_setopt(curl, ::CURLOPT_POSTFIELDS, const_cast<char*>(static_cast<const char*>(static_cast<const void*>(m_blob.data()))));
		::curl_easy_setopt(curl, ::CURLOPT_POSTFIELDSIZE, static_cast<long>(m_blob.size_bytes()));
		::curl_easy_setopt(curl, ::CURLOPT_WRITEFUNCTION, detail::WriteAsyncCallback);
		::curl_easy_setopt(curl, ::CURLOPT_WRITEDATA, &m_writer);
		::curl_easy_setopt(curl, ::CURLOPT_XFERINFOFUNCTION, detail::ProgressCallback);
		::curl_easy_setopt(curl, ::CURLOPT_XFERINFODATA, this);
		::curl_easy_setopt(curl, ::CURLOPT_NOPROGRESS, 0L);

		// レスポンスヘッダーの設定
		std::string responseHeader;
		{
			::curl_easy_setopt(curl, ::CURLOPT_HEADERFUNCTION, detail::HeaderAsyncCallback);
			::curl_easy_setopt(curl, ::CURLOPT_HEADERDATA, &responseHeader);
		}

		const ::CURLcode result = ::curl_easy_perform(curl);
		::curl_easy_cleanup(curl);
		::curl_slist_free_all(header_slist);

		const FilePath saveFilePath = m_writer.path();

		close();

		if (result != ::CURLE_OK)
		{
			LOG_FAIL(U"curl failed (CURLcode: {})"_fmt(FromEnum(result)));

			if (result == ::CURLE_ABORTED_BY_CALLBACK)
			{
				setStatus(HTTPAsyncStatus::Canceled);
			}
			else
			{
				setStatus(HTTPAsyncStatus::Failed);
			}

			FileSystem::Remove(saveFilePath);

			return{};
		}

		setStatus(HTTPAsyncStatus::Succeeded);

		return HTTPResponse{ responseHeader };
	}
}
