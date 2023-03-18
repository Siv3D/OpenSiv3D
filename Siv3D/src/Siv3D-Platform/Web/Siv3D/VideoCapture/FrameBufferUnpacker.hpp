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
# include <Siv3D/PointVector.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Image.hpp>
# include <GLES3/gl3.h>
# include <webgl/webgl2.h>

namespace s3d
{
    struct FrameBufferUnpacker
    {
        FrameBufferUnpacker()
        {
            ::glGenBuffers(1, &m_pixelBuffer);
        }

        ~FrameBufferUnpacker()
        {
            if (m_pixelReadSync)
            {
                ::glDeleteSync(m_pixelReadSync);
            }

            ::glDeleteBuffers(1, &m_pixelBuffer);
        }

        void resize(Size bufferSize)
        {
            m_BufferSize = bufferSize;

            ::glBindBuffer(GL_PIXEL_PACK_BUFFER, m_pixelBuffer);
            ::glBufferData(GL_PIXEL_PACK_BUFFER, bufferSize.x * bufferSize.y * 4, nullptr, GL_STREAM_READ);
        }

        bool hasFinishedUnpack() const
        {
            if (not m_pixelReadSync)
            {
                return false;	
            }

            auto waitResult = ::glClientWaitSync(m_pixelReadSync, 0, 0);
            auto unpackFinished = waitResult == GL_CONDITION_SATISFIED || waitResult == GL_ALREADY_SIGNALED;

            return unpackFinished;
        }

        void startUnpack(GLuint frameBuffer)
        {
            ::glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
            ::glBindBuffer(GL_PIXEL_PACK_BUFFER, m_pixelBuffer);
            {
                ::glPixelStorei(0x9240 /*GL_UNPACK_FLIP_Y_WEBGL*/, GL_TRUE);
                ::glReadPixels(0, 0, m_BufferSize.x, m_BufferSize.y, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
                ::glPixelStorei(0x9240 /*GL_UNPACK_FLIP_Y_WEBGL*/, GL_FALSE);
            }
            ::glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
            ::glBindFramebuffer(GL_FRAMEBUFFER, 0);

            if (m_pixelReadSync)
            {
                ::glDeleteSync(m_pixelReadSync);
            }

            m_pixelReadSync = ::glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
            ::glFlush();
        }

        void readPixels(Image& image) const
        {
            image.resize(m_BufferSize);
          
            ::glBindBuffer(GL_PIXEL_PACK_BUFFER, m_pixelBuffer);
            {	
                ::glGetBufferSubData(GL_PIXEL_PACK_BUFFER, 0, m_BufferSize.x * m_BufferSize.y * 4, image.data());	
            }
            ::glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
        }

    private:

        Size m_BufferSize = Size(0, 0);

        GLuint m_pixelBuffer = 0;

        GLsync m_pixelReadSync = nullptr;
    };
}