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
# include <Siv3D/Webcam.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/PseudoThread/PseudoThread.hpp>
# include "FrameBufferUnpacker.hpp"

namespace s3d
{
	namespace detail
	{
		using siv3dOpenCameraCallback = void(*)(GLuint elementID, void* userData);
		using siv3dPlayVideoCallback = void(*)(void* userData);

		__attribute__((import_name("siv3dOpenCamera")))
		extern void siv3dOpenCamera(int width, int height, siv3dOpenCameraCallback callback, void* callbackArg);

		__attribute__((import_name("siv3dQueryVideoPlaybackedTime")))
		extern double siv3dQueryVideoPlaybackedTime(GLuint elementID);

		__attribute__((import_name("siv3dCaptureVideoFrame")))
		extern void siv3dCaptureVideoFrame(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLuint elementID);

		__attribute__((import_name("siv3dPlayVideo")))
		extern void siv3dPlayVideo(GLuint elementID);

		__attribute__((import_name("siv3dStopVideo")))
		extern void siv3dStopVideo(GLuint elementID);

		__attribute__((import_name("siv3dDestroyVideo")))
		extern void siv3dDestroyVideo(GLuint elementID);

		class WebCameraCapture
		{
		public:

			WebCameraCapture()
			{
				::glGenTextures(1, &m_videoBufferTexture);
				::glBindTexture(GL_TEXTURE_2D, m_videoBufferTexture);
				{
					::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				}
				::glBindTexture(GL_TEXTURE_2D, 0);

				::glGenFramebuffers(1, &m_videoBufferFrameBuffer);
			}

			~WebCameraCapture()
			{
				release();

				::glDeleteTextures(1, &m_videoBufferTexture);
				::glDeleteFramebuffers(1, &m_videoBufferFrameBuffer);
			}

			bool open()
			{
				detail::siv3dOpenCamera(m_captureResolution.x, m_captureResolution.y, &OnOpened, this);
				return true;
			}

			void stop()
			{
				detail::siv3dStopVideo(m_videoElementID);
			}

			void release()
			{
				detail::siv3dDestroyVideo(m_videoElementID);
				m_videoElementID = 0;
			}

			void setResolution(const Size& resolution)
			{
				m_captureResolution = resolution;
			}

			bool grab()
			{
				auto currentPlaybackedTime = detail::siv3dQueryVideoPlaybackedTime(m_videoElementID);
				return (currentPlaybackedTime - m_lastFrameCapturedTime) > 0.001;
			}
		
			GLuint capture()
			{
				m_lastFrameCapturedTime = detail::siv3dQueryVideoPlaybackedTime(m_videoElementID);

				::glBindTexture(GL_TEXTURE_2D, m_videoBufferTexture);
				{
					detail::siv3dCaptureVideoFrame(
						GL_TEXTURE_2D, 0, GL_RGBA8, 
						m_captureResolution.x, m_captureResolution.y, 
						0, GL_RGBA, GL_UNSIGNED_BYTE, m_videoElementID);
				}
				::glBindTexture(GL_TEXTURE_2D, 0);

				return m_videoBufferFrameBuffer;
			}

			bool isOpened() const
			{
				return m_videoElementID != 0;
			}

		private:

			static void OnOpened(GLuint elementID, void* userData)
			{
				auto& webcam = *static_cast<WebCameraCapture*>(userData);

				webcam.m_videoElementID = elementID;
				webcam.prepareBuffers();

				detail::siv3dPlayVideo(elementID);
			} 

			void prepareBuffers()
			{
				::glBindTexture(GL_TEXTURE_2D, m_videoBufferTexture);
				{
					::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_captureResolution.x, m_captureResolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
				}
				::glBindTexture(GL_TEXTURE_2D, 0);

				::glBindFramebuffer(GL_FRAMEBUFFER, m_videoBufferFrameBuffer);
				{
					::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_videoBufferTexture, 0);

					if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
					{
						LOG_ERROR(U"Incomplete Framebuffer");
						return;
					}
				}
				::glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			Size m_captureResolution = { 0, 0 };

			GLuint m_videoElementID = 0;

			GLuint m_videoBufferTexture = 0;

			GLuint m_videoBufferFrameBuffer = 0;

			double m_lastFrameCapturedTime = 0.0;
		};
	}

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

		detail::WebCameraCapture m_capture;

		uint32 m_cameraIndex = 0;

		PseudoThread m_thread;

		Size m_captureResolution = Size { 640, 480 };

		GLuint m_copyFrameBuffer = 0;

		Array<FrameBufferUnpacker> m_frameBufferUnpackers;		

		std::atomic<bool> m_abort = { false };

		//////
		//
		GLuint m_capturedFrameBuffer = 0;

		int32 m_newFrameCount = 0;

		int32 m_totalFrameCount = 0;
		//
		//////

		static bool Run(WebcamDetail& webcam);
	};
}
