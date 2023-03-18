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
# include <Siv3D/PseudoThread/PseudoThread.hpp>
# include <Siv3D/VideoCapture/FrameBufferUnpacker.hpp>
# include <Siv3D/VideoCapture/VideoCapture.hpp>

namespace s3d
{
	class Webcam::WebcamDetail
	{
	public:

		WebcamDetail();

		~WebcamDetail();

		bool open(uint32 cameraIndex);

		void close();

		Optional<Webcam::Permission> getPermission() const;

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

		WebCameraCapture m_capture;

		uint32 m_cameraIndex = 0;

		PseudoThread m_thread;

		GLuint m_copyFrameBuffer = 0;

		struct MatFrame 
		{
			FrameBufferUnpacker frameBufferUnpacker;

			bool inUse = false;
		};

		Array<MatFrame> m_frames;		

		std::atomic<bool> m_abort = { false };

		//////
		//
		bool m_captureStarted = false;

		GLuint m_capturedFrameBuffer = 0;

		int32 m_newFrameCount = 0;

		int32 m_totalFrameCount = 0;
		//
		//////

		static bool Run(WebcamDetail& webcam);
	};
}
