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
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Renderer/Metal/CRenderer_Metal.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "MetalBackBuffer.hpp"

namespace s3d
{
	namespace detail
	{
		id<MTLTexture> CreateSceneTexture(id<MTLDevice> device, const Size size, const uint32 sampleCount)
		{
			id<MTLTexture> texture = nil;
			
			@autoreleasepool {
				MTLTextureDescriptor* texDesc = [MTLTextureDescriptor new];
				{
					texDesc.width = size.x;
					texDesc.height = size.y;
					texDesc.depth = 1;
					texDesc.sampleCount = sampleCount;
					texDesc.textureType = (1 < sampleCount) ? MTLTextureType2DMultisample : MTLTextureType2D;
					texDesc.usage = (MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead);
					texDesc.storageMode = MTLStorageModePrivate;
					texDesc.pixelFormat = MTLPixelFormatRGBA8Unorm;
				}
				texture = [device newTextureWithDescriptor:texDesc];
			}
			
			return texture;
		}
	
		id<MTLTexture> CreateResolvedTexture(id<MTLDevice> device, const Size size)
		{
			id<MTLTexture> texture = nil;
			
			@autoreleasepool {
				MTLTextureDescriptor* texDesc = [MTLTextureDescriptor new];
				{
					texDesc.width = size.x;
					texDesc.height = size.y;
					texDesc.depth = 1;
					texDesc.textureType = MTLTextureType2D;
					texDesc.usage = (MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead);
					texDesc.storageMode = MTLStorageModePrivate;
					texDesc.pixelFormat = MTLPixelFormatRGBA8Unorm;
				}
				texture = [device newTextureWithDescriptor:texDesc];
			}
			
			return texture;
		}
	}

	MetalBackBuffer::MetalBackBuffer()
	{
		LOG_SCOPED_TRACE(U"MetalBackBuffer::MetalBackBuffer()");
		
		pRenderer = static_cast<CRenderer_Metal*>(SIV3D_ENGINE(Renderer));
		m_device = pRenderer->getDevice();
		
		m_sceneSize = Window::GetState().virtualSize;

		m_sceneBuffers.scene = detail::CreateSceneTexture(m_device, m_sceneSize, m_sampleCount);
		if (1 < m_sampleCount)
		{
			m_sceneBuffers.resolved = detail::CreateResolvedTexture(m_device, m_sceneSize);
		}

		//clear(GL4ClearTarget::All);
	}

	MetalBackBuffer::~MetalBackBuffer()
	{

	}
/*
	void GL4BackBuffer::clear(const GL4ClearTarget clearTargets)
	{
		if (clearTargets & GL4ClearTarget::BackBuffer)
		{
			::glBindFramebuffer(GL_FRAMEBUFFER, 0);
			::glClearColor(
				static_cast<float>(m_letterboxColor.r),
				static_cast<float>(m_letterboxColor.g),
				static_cast<float>(m_letterboxColor.b),
				1.0f);
			::glClear(GL_COLOR_BUFFER_BIT);
		}

		if (clearTargets & GL4ClearTarget::Scene)
		{
			m_sceneBuffers.scene->clear(m_backgroundColor);
		}
	}

	void GL4BackBuffer::updateFromSceneBuffer()
	{
		if (m_sampleCount == 1)
		{
			::glActiveTexture(GL_TEXTURE0);
			::glBindTexture(GL_TEXTURE_2D, m_sceneBuffers.scene->getTexture());

			SIV3D_ENGINE(Renderer2D)->drawFullScreenTriangle(m_sceneTextureFilter);
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

			SIV3D_ENGINE(Renderer2D)->drawFullScreenTriangle(m_sceneTextureFilter);
		}

		::glBindTexture(GL_TEXTURE_2D, 0);
	}
*/

	uint32 MetalBackBuffer::getSampleCount() const
	{
		return m_sampleCount;
	}

	id<MTLTexture> MetalBackBuffer::getSceneTexture() const
	{
		return m_sceneBuffers.scene;
	}

	id<MTLTexture> MetalBackBuffer::getResolvedTexture() const
	{
		return m_sceneBuffers.resolved;
	}

	//////////////////////////////////////////////////
	//
	//	LetterboxColor
	//
	//////////////////////////////////////////////////

	void MetalBackBuffer::setLetterboxColor(const ColorF& color) noexcept
	{
		m_letterboxColor = color;
	}

	const ColorF& MetalBackBuffer::getLetterBoxColor() const noexcept
	{
		return m_letterboxColor;
	}

	//////////////////////////////////////////////////
	//
	//	BackgroundColor
	//
	//////////////////////////////////////////////////

	void MetalBackBuffer::setBackgroundColor(const ColorF& color) noexcept
	{
		m_backgroundColor = color;
	}

	const ColorF& MetalBackBuffer::getBackgroundColor() const noexcept
	{
		return m_backgroundColor;
	}

	//////////////////////////////////////////////////
	//
	//	SceneTextureFilter
	//
	//////////////////////////////////////////////////

	void MetalBackBuffer::setSceneTextureFilter(const TextureFilter textureFilter) noexcept
	{
		m_sceneTextureFilter = textureFilter;
	}

	TextureFilter MetalBackBuffer::getSceneTextureFilter() const noexcept
	{
		return m_sceneTextureFilter;
	}

	//////////////////////////////////////////////////
	//
	//	SceneResizeMode
	//
	//////////////////////////////////////////////////

	void MetalBackBuffer::setSceneResizeMode(const ResizeMode resizeMode)
	{
		m_sceneResizeMode = resizeMode;

		updateSceneSize();
	}

	ResizeMode MetalBackBuffer::getSceneResizeMode() const noexcept
	{
		return m_sceneResizeMode;
	}

	//////////////////////////////////////////////////
	//
	//	BackBuffer
	//
	//////////////////////////////////////////////////

	void MetalBackBuffer::setBackBufferSize(const Size backBufferSize)
	{
		assert((0 < backBufferSize.x) && (0 < backBufferSize.y));

		LOG_TRACE(U"MetalBackBuffer::setBackBufferSize({})"_fmt(backBufferSize));

		m_backBufferSize = backBufferSize;
		
		static_cast<CRenderer_Metal*>(SIV3D_ENGINE(Renderer))->changeFrameBufferSize(m_backBufferSize);

		updateSceneSize();
	}

	const Size& MetalBackBuffer::getBackBufferSize() const noexcept
	{
		return m_backBufferSize;
	}

	std::pair<float, RectF> MetalBackBuffer::getLetterboxComposition() const noexcept
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

	void MetalBackBuffer::setSceneBufferSize(const Size size)
	{
		assert((0 < size.x) && (0 < size.y));

		if (size == m_sceneSize)
		{
			return;
		}

		LOG_TRACE(U"MetalBackBuffer::setSceneSize({})"_fmt(size));

		//unbindAllRenderTargets();

		m_sceneSize = size;

		{
			m_sceneBuffers = {};
			m_sceneBuffers.scene = detail::CreateSceneTexture(m_device, m_sceneSize, m_sampleCount);
			if (1 < m_sampleCount)
			{
				m_sceneBuffers.resolved = detail::CreateResolvedTexture(m_device, m_sceneSize);
			}
		}

		//clear(GL4ClearTarget::All);
	}

	const Size& MetalBackBuffer::getSceneBufferSize() const noexcept
	{
		return m_sceneSize;
	}

	//////////////////////////////////////////////////
	//
	//	
	//
	//////////////////////////////////////////////////

	void MetalBackBuffer::updateSceneSize()
	{
		LOG_TRACE(U"MetalBackBuffer::updateSceneSize()");

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
