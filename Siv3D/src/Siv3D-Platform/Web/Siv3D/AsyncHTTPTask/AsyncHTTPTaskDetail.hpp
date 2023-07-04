//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <atomic>
# include <mutex>
# include <Siv3D/Common.hpp>
# include <Siv3D/AsyncTask.hpp>
# include <Siv3D/URLView.hpp>
# include <Siv3D/URL.hpp>
# include <Siv3D/HTTPResponse.hpp>
# include <Siv3D/HTTPAsyncStatus.hpp>
# include <Siv3D/HTTPProgress.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/AsyncHTTPTask.hpp>

namespace s3d
{
	class AsyncHTTPTaskDetail
	{
	public:

		SIV3D_NODISCARD_CXX20
		AsyncHTTPTaskDetail();

		SIV3D_NODISCARD_CXX20
		AsyncHTTPTaskDetail(URLView url, const HashTable<String, String>& headers, FilePathView path);

		SIV3D_NODISCARD_CXX20
		AsyncHTTPTaskDetail(StringView method, URLView url, const HashTable<String, String>& headers, FilePathView path);

		~AsyncHTTPTaskDetail();

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		bool isReady() const;

		void send(Optional<std::string_view> body);

		void cancel();

		void setRequestHeader(StringView name, StringView value);

		[[nodiscard]]
		const HTTPResponse& getResponse();

		void resolveResponse(const HTTPResponse&);

		[[nodiscard]]
		HTTPAsyncStatus getStatus();

		void setStatus(HTTPAsyncStatus status);

		[[nodiscard]]
		HTTPProgress getProgress();

		void updateProgress(int64 dlTotal, int64 dlNow, int64 ulTotal, int64 ulNow);

		void updateResponseStatus(std::string_view response);

		[[nodiscard]]
		bool isAborted() const;

		[[nodiscard]]
		AsyncTask<HTTPResponse> CreateAsyncTask();

	private:

		////
		//
		std::promise<HTTPResponse> m_promise;

		std::mutex m_mutex;

		HTTPProgress m_progress_internal;

		int m_wgetHandle = 0;
		//
		////

		String m_method;
		
		URL m_url;

		AsyncTask<HTTPResponse> m_task;

		HTTPResponse m_response;
	};
}