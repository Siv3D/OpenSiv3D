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
# include <Siv3D/Webcam.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>

namespace s3d
{
	class Webcam::WebcamDetail
	{
	public:

		WebcamDetail();

		~WebcamDetail();

		bool open(uint32 cameraIndex);

		void close();

		bool isOpen();

		bool start();

		bool isActive() const;

		uint32 cameraIndex() const;

		Size getResolution() const;

		bool setResolution(const Size& resolution);

		bool hasNewFrame();

		bool getFrame(Image& image);

		bool getFrame(DynamicTexture& texture);

	private:

		cv::VideoCapture m_capture;

		uint32 m_cameraIndex = 0;

		std::thread m_thread;

		Size m_captureResolution = Size{ 0, 0 };

		cv::Mat_<cv::Vec3b> m_frame;

		std::atomic<bool> m_abort = { false };

		//////
		//
		std::mutex m_imageMutex;

		Image m_image;

		int32 m_newFrameCount = 0;
		//
		//////

		static void Run(WebcamDetail& webcam);
	};
}
