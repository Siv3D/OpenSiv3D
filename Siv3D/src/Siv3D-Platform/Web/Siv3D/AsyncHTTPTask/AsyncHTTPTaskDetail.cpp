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

# include <emscripten/emscripten.h>

namespace s3d
{
	namespace detail
	{
		__attribute__((import_name("siv3dCreateXMLHTTPRequest")))
		extern int32 siv3dCreateXMLHTTPRequest();

		__attribute__((import_name("siv3dSetXMLHTTPRequestWriteBackFile")))
		extern void siv3dSetXMLHTTPRequestWriteBackFile(int32 id, const char* fileName);

		__attribute__((import_name("siv3dSetXMLHTTPRequestCallback")))
		extern void siv3dSetXMLHTTPRequestCallback(int32 id, void(*callback)(int32, void*), void* userData);

		__attribute__((import_name("siv3dSetXMLHTTPRequestErrorCallback")))
		extern void siv3dSetXMLHTTPRequestErrorCallback(int32 id, void(*callback)(int32, void*), void* userData);

		__attribute__((import_name("siv3dSetXMLHTTPRequestProgressCallback")))
		extern void siv3dSetXMLHTTPRequestProgressCallback(int32 id, void(*callback)(int32, void*, int32, int32), void* userData);
	
		__attribute__((import_name("siv3dSetXMLHTTPRequestRequestHeader")))
		extern void siv3dSetXMLHTTPRequestRequestHeader(int32 id, const char* name, const char* value);

		__attribute__((import_name("siv3dGetXMLHTTPRequestResponseHeaders")))
		extern char* siv3dGetXMLHTTPRequestResponseHeaders(int32 id);

		__attribute__((import_name("siv3dSendXMLHTTPRequest")))
		extern void siv3dSendXMLHTTPRequest(int32 id, const char* data);

		__attribute__((import_name("siv3dOpenXMLHTTPRequest")))
		extern void siv3dOpenXMLHTTPRequest(int32 id, const char* method, const char* url);

		__attribute__((import_name("siv3dAbortXMLHTTPRequest")))
		extern void siv3dAbortXMLHTTPRequest(int32 id);

		__attribute__((import_name("siv3dDeleteXMLHTTPRequest")))
		extern void siv3dDeleteXMLHTTPRequest(int32 id);

		static void OnLoadCallBack(int32 requestID, void* userData)
		{
			char* responseHeader = siv3dGetXMLHTTPRequestResponseHeaders(requestID);
			HTTPResponse response{ std::string(responseHeader) };
			::free(responseHeader);

			auto& httpTask = *static_cast<AsyncHTTPTaskDetail*>(userData);

			httpTask.setStatus(HTTPAsyncStatus::Succeeded);
			httpTask.resolveResponse(response);

			EM_ASM("setTimeout(function() { _siv3dMaybeAwake(); }, 0)");
		}

		static void OnErrorCallback(int32 requestID, void* userData)
		{
			char* responseHeader = siv3dGetXMLHTTPRequestResponseHeaders(requestID);
			HTTPResponse response{ std::string(responseHeader) };
			::free(responseHeader);
			auto& httpTask = *static_cast<AsyncHTTPTaskDetail*>(userData);

			httpTask.setStatus(HTTPAsyncStatus::Failed);
			httpTask.resolveResponse(response);

			EM_ASM("setTimeout(function() { _siv3dMaybeAwake(); }, 0)");
		}

		static void ProgressCallback(int32 requestID, void* userData, int dlTotal, int dlNow)
		{
			auto& httpTask = *static_cast<AsyncHTTPTaskDetail*>(userData);

			httpTask.updateProgress(dlTotal, dlNow, 0, 0);
		}
	}

	AsyncHTTPTaskDetail::AsyncHTTPTaskDetail() {}

	AsyncHTTPTaskDetail::AsyncHTTPTaskDetail(URLView url, FilePathView path)
		: AsyncHTTPTaskDetail(U"GET", url, path) {}

	AsyncHTTPTaskDetail::AsyncHTTPTaskDetail(StringView method, URLView url, FilePathView path)
		: m_url{ url }
	{
		m_wgetHandle = detail::siv3dCreateXMLHTTPRequest();

		detail::siv3dOpenXMLHTTPRequest(m_wgetHandle, method.toUTF8().data(), url.toUTF8().data());
		detail::siv3dSetXMLHTTPRequestWriteBackFile(m_wgetHandle, path.toUTF8().data());
	}

	AsyncHTTPTaskDetail::~AsyncHTTPTaskDetail()
	{
		if (m_wgetHandle != 0)
		{
			cancel();
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
		if (m_wgetHandle != 0)
		{
			detail::siv3dAbortXMLHTTPRequest(m_wgetHandle);
			detail::siv3dDeleteXMLHTTPRequest(m_wgetHandle);
			m_wgetHandle = 0;

			m_progress_internal.status = HTTPAsyncStatus::Canceled;
		}
	}

	void AsyncHTTPTaskDetail::setRequestHeader(StringView name, StringView value)
	{
		detail::siv3dSetXMLHTTPRequestRequestHeader(m_wgetHandle, name.toUTF8().data(), value.toUTF8().data());
	}

	const HTTPResponse& AsyncHTTPTaskDetail::getResponse()
	{
		if (m_task.isReady())
		{
			m_response = m_task.get();
		}

		return m_response;
	}

	void AsyncHTTPTaskDetail::resolveResponse(const HTTPResponse& response)
	{
		// CreateAsyncTask で作成した AsyncTask を resolved 状態にする
		{
			m_promise.set_value(response);
		}

		// m_task を resolved 状態にする
		{
			std::promise<HTTPResponse> resolvedPromise;
		
			resolvedPromise.set_value(response);
			m_task = resolvedPromise.get_future();
		}
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
		return m_progress_internal.status == HTTPAsyncStatus::Canceled;
	}

	void AsyncHTTPTaskDetail::updateResponseStatus(std::string_view response)
	{
		m_response = HTTPResponse(std::string(response));
	}

	void AsyncHTTPTaskDetail::send(Optional<std::string_view> body)
	{
		setStatus(HTTPAsyncStatus::Downloading);

		detail::siv3dSetXMLHTTPRequestCallback(m_wgetHandle, &detail::OnLoadCallBack, this);
		detail::siv3dSetXMLHTTPRequestErrorCallback(m_wgetHandle, &detail::OnErrorCallback, this);
		detail::siv3dSetXMLHTTPRequestProgressCallback(m_wgetHandle, &detail::ProgressCallback, this);

		if (body)
		{
			detail::siv3dSendXMLHTTPRequest(m_wgetHandle, body->data());
		}
		else
		{
			detail::siv3dSendXMLHTTPRequest(m_wgetHandle, nullptr);
		}
	}

	AsyncTask<HTTPResponse> AsyncHTTPTaskDetail::CreateAsyncTask()
	{
		return m_promise.get_future();
	}
}