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

# include <Siv3D/System.hpp>
# include <Siv3D/EngineLog.hpp>
# include "WebCameraCapture.hpp"

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

    }

    WebCameraCapture::WebCameraCapture()
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

    WebCameraCapture::~WebCameraCapture()
    {
        release();

        ::glDeleteTextures(1, &m_videoBufferTexture);
        ::glDeleteFramebuffers(1, &m_videoBufferFrameBuffer);
    }

    bool WebCameraCapture::open()
    {
        detail::siv3dOpenCamera(m_captureResolution.x, m_captureResolution.y, &OnOpened, this);
        return true;
    }

    void WebCameraCapture::stop()
    {
        detail::siv3dStopVideo(m_videoElementID);
    }

    void WebCameraCapture::release()
    {
        detail::siv3dDestroyVideo(m_videoElementID);
        m_videoElementID = 0;
    }

    void WebCameraCapture::setResolution(const Size& resolution)
    {
        m_captureResolution = resolution;
    }

    bool WebCameraCapture::grab()
    {
        auto currentPlaybackedTime = detail::siv3dQueryVideoPlaybackedTime(m_videoElementID);
        return (currentPlaybackedTime - m_lastFrameCapturedTime) > 0.001;
    }

    GLuint WebCameraCapture::capture()
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

    bool WebCameraCapture::isOpened() const
    {
        return m_videoElementID != 0;
    }

    void WebCameraCapture::OnOpened(GLuint elementID, void* userData)
    {
        auto& webcam = *static_cast<WebCameraCapture*>(userData);

        webcam.m_videoElementID = elementID;
        webcam.prepareBuffers();

        detail::siv3dPlayVideo(elementID);
    } 

    void WebCameraCapture::prepareBuffers()
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

}
