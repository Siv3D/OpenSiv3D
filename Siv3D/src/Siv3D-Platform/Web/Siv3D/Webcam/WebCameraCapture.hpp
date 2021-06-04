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
# include <Siv3D/Fwd.hpp>
# include <GLES3/gl3.h>

namespace s3d
{
    class WebCameraCapture
    {
    public:

        WebCameraCapture();

        ~WebCameraCapture();

        bool open();

        void stop();

        void release();
    
        void setResolution(const Size& resolution);

        bool grab();
    
        GLuint capture();

        bool isOpened() const;

    private:

        static void OnOpened(GLuint elementID, void* userData);

        void prepareBuffers();

        Size m_captureResolution = { 0, 0 };

        GLuint m_videoElementID = 0;

        GLuint m_videoBufferTexture = 0;

        GLuint m_videoBufferFrameBuffer = 0;

        double m_lastFrameCapturedTime = 0.0;
    };
}