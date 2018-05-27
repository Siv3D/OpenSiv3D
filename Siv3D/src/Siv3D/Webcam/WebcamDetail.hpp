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
# include <opencv2/videoio.hpp>

namespace s3d
{
	class Webcam::WebcamDetail
	{
	private:

		size_t m_index = 0;

		bool m_available = false;

		Size m_resolution = Size(0, 0);

		cv::VideoCapture m_capture;

		//std::thread m_thread;

	public:

		WebcamDetail(size_t index);

		~WebcamDetail();

		bool isAvailable() const;

		bool start();

		void stop();

		bool isActive() const;

		size_t index() const;

		Size getResolution() const;

		void setResolution(const Size& size);
	};
}
