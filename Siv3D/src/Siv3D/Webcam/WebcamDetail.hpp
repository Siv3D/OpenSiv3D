//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "IWebcam.hpp"
# include <Siv3D/Webcam.hpp>
# include <Siv3D/Image.hpp>
# include <opencv2/videoio.hpp>

namespace s3d
{
	enum class WebcamState
	{
		None,

		Ready,

		Active,

		Pause,

		Stop,

		HasError,
	};

	struct WebcamData
	{
		cv::VideoCapture m_capture;

		Size m_resolution = Size(0, 0);

		cv::Mat_<cv::Vec3b> m_frame;

		Image m_image;

		std::thread m_thread;

		std::atomic<WebcamState> m_state = WebcamState::None;

		std::mutex m_imageMutex;

		std::atomic<int32> m_newFrameCount = 0;

		static void OnRunning(WebcamData& webcam, const int32 index);

		~WebcamData();

		bool open(size_t index);

		void initResolution();

		bool setResolution(const Size& resolution);

		bool retrieve();

		void release();

		const Size& getResolution() const;

		bool start(int32 index);

		void stop();

		bool hasNewFrame() const;

		bool getFrame(Image& image);

		bool getFrame(DynamicTexture& texture);
	};

	class Webcam::WebcamDetail
	{
	private:

		size_t m_index = 0;

		bool m_available = false;

		bool m_isActive = false;

		WebcamData m_webcam;

	public:

		WebcamDetail(size_t index);

		~WebcamDetail();

		bool isAvailable() const;

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
