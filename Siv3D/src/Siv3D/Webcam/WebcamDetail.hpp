//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <atomic>
# include <thread>
# include <Siv3D/Webcam.hpp>
# include <Siv3D/Image.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(5054)
# include <opencv2/videoio.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	enum class WebcamState
	{
		None,

		Ready,

		Active,

		Stop,

		HasError,
	};

	class Webcam::WebcamDetail
	{
	private:

		bool m_initialized = false;

		int32 m_index = 0;

		cv::VideoCapture m_capture;

		Size m_currentResolution = Size(0, 0);

		std::thread m_thread;

		std::atomic<WebcamState> m_state = WebcamState::None;

		cv::Mat_<cv::Vec3b> m_frame;

		std::mutex m_imageMutex;

		Image m_image;

		std::atomic<int32> m_newFrameCount = 0;

		bool open();

		static void OnRunning(WebcamDetail& webcam);

	public:

		WebcamDetail();

		WebcamDetail(size_t index);

		~WebcamDetail();

		bool isAvailable();

		bool start();

		void stop();

		bool isActive() const;

		size_t index() const;

		Size getResolution() const;

		bool setResolution(const Size& resolution);

		bool hasNewFrame() const;

		bool getFrame(Image& image);

		bool getFrame(DynamicTexture& texture);
	};
}
