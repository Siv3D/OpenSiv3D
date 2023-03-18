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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Renderer2D/GLES3/CRenderer2D_GLES3.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "GLES3BackBuffer.hpp"

namespace s3d
{
	GLES3BackBuffer::GLES3BackBuffer()
	{
		LOG_SCOPED_TRACE(U"GLES3BackBuffer::GLES3BackBuffer()");

		pRenderer2D = static_cast<CRenderer2D_GLES3*>(SIV3D_ENGINE(Renderer2D));

		m_sceneSize = Window::GetState().virtualSize;

		m_sceneBuffers.scene = GLES3InternalTexture2D::CreateRenderTargetTexture2D(m_sceneSize, m_sampleCount);

		if (m_sampleCount > 1)
		{
			m_sceneBuffers.resolved = GLES3InternalTexture2D::CreateRenderTargetTexture2D(m_sceneSize);
		}

		clear(GLES3ClearTarget::All);
	}

	GLES3BackBuffer::~GLES3BackBuffer()
	{
		// do nothing
	}

	void GLES3BackBuffer::clear(const GLES3ClearTarget clearTargets)
	{
		if (clearTargets & GLES3ClearTarget::BackBuffer)
		{
			::glBindFramebuffer(GL_FRAMEBUFFER, 0);
			::glClearColor(
				static_cast<float>(m_letterboxColor.r),
				static_cast<float>(m_letterboxColor.g),
				static_cast<float>(m_letterboxColor.b),
				1.0f);
			::glClear(GL_COLOR_BUFFER_BIT);
		}

		if (clearTargets & GLES3ClearTarget::Scene)
		{
			m_sceneBuffers.scene->clear(m_backgroundColor);
		}
	}

	void GLES3BackBuffer::bindSceneToContext()
	{
		::glBindFramebuffer(GL_FRAMEBUFFER, m_sceneBuffers.scene->getFrameBuffer());
	}

	void GLES3BackBuffer::bindToScene(const GLuint frameBuffer)
	{
		::glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	}

	void GLES3BackBuffer::unbind()
	{
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GLES3BackBuffer::updateFromSceneBuffer()
	{
		if (m_sampleCount == 1)
		{
			::glActiveTexture(GL_TEXTURE0);
			::glBindTexture(GL_TEXTURE_2D, m_sceneBuffers.scene->getTexture());
		}
		else
		{
			::glBindFramebuffer(GL_READ_FRAMEBUFFER, m_sceneBuffers.scene->getFrameBuffer());
			::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_sceneBuffers.resolved->getFrameBuffer());
			::glBlitFramebuffer(0, 0, m_sceneSize.x, m_sceneSize.y, 0, 0, m_sceneSize.x, m_sceneSize.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
			::glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
			::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

			::glActiveTexture(GL_TEXTURE0);
			::glBindTexture(GL_TEXTURE_2D, m_sceneBuffers.resolved->getTexture());
		}

		pRenderer2D->drawFullScreenTriangle(m_sceneTextureFilter);

		::glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLES3BackBuffer::capture()
	{
		if (m_screenCaptureImage.size() != m_sceneSize)
		{
			m_screenCaptureImage.resize(m_sceneSize);
		}

		if (m_sampleCount == 1)
		{
			::glBindFramebuffer(GL_FRAMEBUFFER, m_sceneBuffers.scene->getTexture());
			{
				::glReadPixels(0, 0, m_sceneSize.x, m_sceneSize.y, GL_RGBA, GL_UNSIGNED_BYTE, m_screenCaptureImage.data());
			}
			::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else
		{
			::glBindFramebuffer(GL_FRAMEBUFFER, m_sceneBuffers.resolved->getTexture());
			{
				::glReadPixels(0, 0, m_sceneSize.x, m_sceneSize.y, GL_RGBA, GL_UNSIGNED_BYTE, m_screenCaptureImage.data());
			}
			::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	const Image& GLES3BackBuffer::getScreenCapture() const
	{
		return m_screenCaptureImage;
	}

	//////////////////////////////////////////////////
	//
	//	LetterboxColor
	//
	//////////////////////////////////////////////////

	void GLES3BackBuffer::setLetterboxColor(const ColorF& color) noexcept
	{
		m_letterboxColor = color;
	}

	const ColorF& GLES3BackBuffer::getLetterBoxColor() const noexcept
	{
		return m_letterboxColor;
	}

	//////////////////////////////////////////////////
	//
	//	BackgroundColor
	//
	//////////////////////////////////////////////////

	void GLES3BackBuffer::setBackgroundColor(const ColorF& color) noexcept
	{
		m_backgroundColor = color;
	}

	const ColorF& GLES3BackBuffer::getBackgroundColor() const noexcept
	{
		return m_backgroundColor;
	}

	//////////////////////////////////////////////////
	//
	//	SceneTextureFilter
	//
	//////////////////////////////////////////////////

	void GLES3BackBuffer::setSceneTextureFilter(const TextureFilter textureFilter) noexcept
	{
		m_sceneTextureFilter = textureFilter;
	}

	TextureFilter GLES3BackBuffer::getSceneTextureFilter() const noexcept
	{
		return m_sceneTextureFilter;
	}

	//////////////////////////////////////////////////
	//
	//	SceneResizeMode
	//
	//////////////////////////////////////////////////

	void GLES3BackBuffer::setSceneResizeMode(const ResizeMode resizeMode)
	{
		m_sceneResizeMode = resizeMode;

		updateSceneSize();
	}

	ResizeMode GLES3BackBuffer::getSceneResizeMode() const noexcept
	{
		return m_sceneResizeMode;
	}

	//////////////////////////////////////////////////
	//
	//	BackBuffer
	//
	//////////////////////////////////////////////////

	void GLES3BackBuffer::setBackBufferSize(const Size backBufferSize)
	{
		assert((0 < backBufferSize.x) && (0 < backBufferSize.y));

		LOG_TRACE(U"GLES3BackBuffer::setBackBufferSize({})"_fmt(backBufferSize));

		m_backBufferSize = backBufferSize;

		updateSceneSize();
	}

	const Size& GLES3BackBuffer::getBackBufferSize() const noexcept
	{
		return m_backBufferSize;
	}

	std::pair<float, RectF> GLES3BackBuffer::getLetterboxComposition() const noexcept
	{
		const Float2 sceneSize		= m_sceneSize;
		const Float2 backBufferSize	= m_backBufferSize;

		const float sx = (backBufferSize.x / sceneSize.x);
		const float sy = (backBufferSize.y / sceneSize.y);
		const float s = Min(sx, sy);

		if (sx <= sy)
		{
			const float offsetY = ((backBufferSize.y - sceneSize.y * s) * 0.5f);
			const float width = backBufferSize.x;
			const float height = (backBufferSize.y - offsetY * 2.0f);

			return{ s, RectF(0.0f, offsetY, width, height) };
		}
		else
		{
			const float offsetX = ((backBufferSize.x - sceneSize.x * s) * 0.5f);
			const float width = (backBufferSize.x - offsetX * 2.0f);
			const float height = backBufferSize.y;

			return{ s, RectF(offsetX, 0.0f, width, height) };
		}
	}

	//////////////////////////////////////////////////
	//
	//	SceneBuffer
	//
	//////////////////////////////////////////////////

	void GLES3BackBuffer::setSceneBufferSize(const Size size)
	{
		assert((0 < size.x) && (0 < size.y));

		if (size == m_sceneSize)
		{
			return;
		}

		LOG_TRACE(U"GLES3BackBuffer::setSceneSize({})"_fmt(size));

		//unbindAllRenderTargets();

		m_sceneSize = size;

		{
			m_sceneBuffers = {};

			m_sceneBuffers.scene = GLES3InternalTexture2D::CreateRenderTargetTexture2D(m_sceneSize, m_sampleCount);

			if (m_sampleCount > 1)
			{
				m_sceneBuffers.resolved = GLES3InternalTexture2D::CreateRenderTargetTexture2D(m_sceneSize);
			}
		}

		clear(GLES3ClearTarget::All);
	}

	const Size& GLES3BackBuffer::getSceneBufferSize() const noexcept
	{
		return m_sceneSize;
	}

	//////////////////////////////////////////////////
	//
	//	
	//
	//////////////////////////////////////////////////

	void GLES3BackBuffer::updateSceneSize()
	{
		LOG_TRACE(U"GLES3BackBuffer::updateSceneSize()");

		if (m_sceneResizeMode == ResizeMode::Actual)
		{
			setSceneBufferSize(Window::GetState().frameBufferSize);
		}
		else if (m_sceneResizeMode == ResizeMode::Virtual)
		{
			setSceneBufferSize(Window::GetState().virtualSize);
		}
	}
}
