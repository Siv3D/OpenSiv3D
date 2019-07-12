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
# include <opencv2/videoio.hpp>

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

	//struct WebcamData
	//{
	//	cv::VideoCapture m_capture;

	//	Size m_resolution = Size(0, 0);

	//	cv::Mat_<cv::Vec3b> m_frame;

	//	Image m_image;

	//	std::thread m_thread;

	//	std::atomic<WebcamState> m_state = WebcamState::None;

	//	std::mutex m_imageMutex;

	//	std::atomic<int32> m_newFrameCount = 0;

	//	static void OnRunning(WebcamData& webcam);

	//	~WebcamData();

	//	bool open(size_t index);

	//	bool isOpened() const;

	//	void initResolution();

	//	bool setResolution(const Size& resolution);

	//	bool retrieve();

	//	void release();

	//	const Size& getResolution() const;

	//	bool start();

	//	void stop();

	//	bool hasNewFrame() const;

	//	bool getFrame(Image& image);

	//	bool getFrame(DynamicTexture& texture);
	//};

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
