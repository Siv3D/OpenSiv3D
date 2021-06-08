//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
		bool isReady();

		void cancel();

		[[nodiscard]]
		const HTTPResponse& getResponse();

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
		std::mutex m_mutex;

		HTTPProgress m_progress_internal;

		int m_wgetHandle = 0;
		//
		////

		URL m_url;

		HTTPResponse m_response;
	};
}