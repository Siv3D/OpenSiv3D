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

# include "GLES3InternalTexture2D.hpp"

namespace s3d
{
	GLES3InternalTexture2D::~GLES3InternalTexture2D()
	{
		if (m_texture)
		{
			::glDeleteTextures(1, &m_texture);
			m_texture = 0;
		}

		if (m_frameBuffer)
		{
			::glDeleteFramebuffers(1, &m_frameBuffer);
			m_frameBuffer = 0;
		}
	}

	bool GLES3InternalTexture2D::isEmpty() const noexcept
	{
		return m_size.isZero();
	}

	GLES3InternalTexture2D::operator bool() const noexcept
	{
		return (not isEmpty());
	}

	const Size& GLES3InternalTexture2D::size() const noexcept
	{
		return m_size;
	}

	void GLES3InternalTexture2D::clear(const ColorF color)
	{
		if (isEmpty())
		{
			return;
		}

		::glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
		::glClearColor(
			static_cast<float>(color.r),
			static_cast<float>(color.g),
			static_cast<float>(color.b),
			1.0f);
		::glClear(GL_COLOR_BUFFER_BIT);
	}

	GLuint GLES3InternalTexture2D::getFrameBuffer() const noexcept
	{
		return m_frameBuffer;
	}

	GLuint GLES3InternalTexture2D::getTexture() const noexcept
	{
		return m_texture;
	}

	std::unique_ptr<GLES3InternalTexture2D> GLES3InternalTexture2D::CreateRenderTargetTexture2D(const Size size, const uint32 sampleCount)
	{
		assert(sampleCount != 0);

		auto p = std::make_unique<GLES3InternalTexture2D>();

		GLuint frameBuffer = 0;
		GLuint texture = 0;

		if (sampleCount == 1)
		{
			::glGenFramebuffers(1, &frameBuffer);
			::glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

			::glGenTextures(1, &texture);
			::glBindTexture(GL_TEXTURE_2D, texture);
			::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,  GL_TEXTURE_2D, texture, 0);
			if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				return nullptr;
			}
			::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else
		{
			return nullptr;
			// ::glGenFramebuffers(1, &frameBuffer);

			// ::glGenTextures(1, &texture);
			// ::glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture);
			// ::glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sampleCount, GL_RGBA8, size.x, size.y, GL_FALSE);

			// ::glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
			// ::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texture, 0);
			// if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			// {
			// 	return nullptr;
			// }
			// ::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		p->m_frameBuffer	= frameBuffer;
		p->m_texture		= texture;
		p->m_size			= size;

		return p;
	}
}
