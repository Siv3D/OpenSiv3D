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
# include <Siv3D/Fwd.hpp>
# include <GLES3/gl3.h>

namespace s3d
{
    class WebCameraCapture
    {
    public:

        WebCameraCapture();

        ~WebCameraCapture();

        bool openCamera();

        bool openVideo(FilePathView filepath);

        void play();

        void seek(double time);

        double tell() const;

        void stop();

        void release();
    
        void setResolution(const Size& resolution);

        Size getResolution() const;

        double getFPS() const;

        double getDuration() const;

        bool grab();
    
        void capture();

        GLuint retrieve() const;

        bool isOpened() const;

        bool hasError() const;

        bool isReachedEnd() const;

    private:

        static void OnOpened(GLuint elementID, void* userData);

        static void OnResolutionUpdated(void* userData);

        static void OnUpdated(void* userData);

        void prepareBuffers();

        Size m_captureResolution = { 0, 0 };

        double m_playbackFPS = 0.0;

        double m_videoDuration = 0.0;

        GLuint m_videoElementID = 0;

        GLuint m_videoBufferTexture = 0;

        GLuint m_videoBufferFrameBuffer = 0;

        double m_lastCapturedFrameTime = 0.0;

        bool m_hasNewFrame = false;

        bool m_hasError = false;

        bool m_shouldAutoPlay = false;
    };
}