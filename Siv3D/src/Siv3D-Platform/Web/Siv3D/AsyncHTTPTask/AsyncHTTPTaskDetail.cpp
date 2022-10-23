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
		static void OnLoadCallBack(unsigned requestID, void* userData, const char* locatedFileName)
		{
			auto& httpTask = *static_cast<AsyncHTTPTaskDetail*>(userData);

			httpTask.updateResponseStatus("HTTP/1.1 200 Ok\n");
			httpTask.setStatus(HTTPAsyncStatus::Succeeded);
			httpTask.resolveResponse();

			EM_ASM("setTimeout(function() { _siv3dMaybeAwake(); }, 0)");
		}

		static void OnErrorCallback(unsigned requestID, void* userData, int statusCode)
		{
			auto& httpTask = *static_cast<AsyncHTTPTaskDetail*>(userData);

			httpTask.updateResponseStatus(U"HTTP/1.1 {} Unknown\n"_fmt(statusCode).toUTF8());
			httpTask.setStatus(HTTPAsyncStatus::Failed);
			httpTask.resolveResponse();

			EM_ASM("setTimeout(function() { _siv3dMaybeAwake(); }, 0)");
		}

		static void ProgressCallback(unsigned requestID, void* userData, int percentComplete)
		{
			auto& httpTask = *static_cast<AsyncHTTPTaskDetail*>(userData);

			httpTask.updateProgress(0, percentComplete, 0, 0);
		}
	}

	AsyncHTTPTaskDetail::AsyncHTTPTaskDetail() {}

	AsyncHTTPTaskDetail::AsyncHTTPTaskDetail(const URLView url, const FilePathView path)
		: m_url{ url }
	{
		run(path);
	}

	AsyncHTTPTaskDetail::~AsyncHTTPTaskDetail()
	{
		if (getStatus() == HTTPAsyncStatus::Downloading)
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
		return m_progress_internal.status == HTTPAsyncStatus::Succeeded;
	}

	void AsyncHTTPTaskDetail::cancel()
	{
		if (m_wgetHandle != 0)
		{
			::emscripten_async_wget2_abort(m_wgetHandle);
			m_wgetHandle = 0;

			m_progress_internal.status = HTTPAsyncStatus::Canceled;
		}
	}

	const HTTPResponse& AsyncHTTPTaskDetail::getResponse()
	{
		return m_response;
	}

	void AsyncHTTPTaskDetail::resolveResponse()
	{
		m_promise.set_value(m_response);
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

	void AsyncHTTPTaskDetail::run(FilePathView path)
	{
		setStatus(HTTPAsyncStatus::Downloading);

		const std::string urlUTF8 = m_url.toUTF8();

		m_wgetHandle = ::emscripten_async_wget2(
			urlUTF8.c_str(), path.toUTF8().c_str(), 
			"GET", "", 
			this, detail::OnLoadCallBack, detail::OnErrorCallback, detail::ProgressCallback);
	}
}