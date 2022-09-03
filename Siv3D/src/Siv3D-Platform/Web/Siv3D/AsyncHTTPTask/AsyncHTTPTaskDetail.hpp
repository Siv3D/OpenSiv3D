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
			AsyncHTTPTaskDetail(URLView url, FilePathView path);

		~AsyncHTTPTaskDetail();

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		bool isReady() const;

		void cancel();

		[[nodiscard]]
		const HTTPResponse& getResponse();

		void resolveResponse();

		[[nodiscard]]
		HTTPAsyncStatus getStatus();

		void setStatus(HTTPAsyncStatus status);

		[[nodiscard]]
		HTTPProgress getProgress();

		void updateProgress(int64 dlTotal, int64 dlNow, int64 ulTotal, int64 ulNow);

		void updateResponseStatus(std::string_view response);

		[[nodiscard]]
		bool isAborted() const;

	private:

		void run(FilePathView path);

		////
		//
		std::promise<HTTPResponse> m_promise;

		std::mutex m_mutex;

		HTTPProgress m_progress_internal;

		int m_wgetHandle = 0;
		//
		////

		URL m_url;

		HTTPResponse m_response;

		friend AsyncTask<HTTPResponse> Platform::Web::SimpleHTTP::CreateAsyncTask(AsyncHTTPTask& httpTask);
	};
}