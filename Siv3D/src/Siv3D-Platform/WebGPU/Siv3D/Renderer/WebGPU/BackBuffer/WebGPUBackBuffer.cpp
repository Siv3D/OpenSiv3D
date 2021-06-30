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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Renderer2D/WebGPU/CRenderer2D_WebGPU.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "WebGPUBackBuffer.hpp"

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	WebGPUBackBuffer::WebGPUBackBuffer(const wgpu::Device& device)
		: m_device(device)
	{
		LOG_SCOPED_TRACE(U"WebGPUBackBuffer::WebGPUBackBuffer()");

		pRenderer2D = dynamic_cast<CRenderer2D_WebGPU*>(SIV3D_ENGINE(Renderer2D));

		m_sceneSize = Window::GetState().virtualSize;

		m_sceneBuffers.scene = WebGPUInternalTexture2D::CreateRenderTargetTexture2D(m_device, m_sceneSize, m_sampleCount);

		if (m_sampleCount > 1)
		{
			m_sceneBuffers.resolved = WebGPUInternalTexture2D::CreateRenderTargetTexture2D(m_device, m_sceneSize);
		}

		clear(WebGPUClearTarget::All);

		wgpu::SamplerDescriptor desc
		{
			.magFilter = wgpu::FilterMode::Linear,
			.minFilter = wgpu::FilterMode::Linear
		};

		m_sampler = m_device.CreateSampler(&desc);

		wgpu::BindGroupEntry uniformEntries[] =
		{
			{
				.binding = 0,
				.sampler = m_sampler,
			},
			{
				.binding = 1,
				.textureView = m_sceneBuffers.scene->getTextureView()
			}
		};

		// wgpu::BindGroupDescriptor uniformDesc
		// {
		// 	.entries = uniformEntries,
		// 	.entryCount = 2
		// };

		// m_uniform = m_device.CreateBindGroup(&uniformDesc);
	}

	WebGPUBackBuffer::~WebGPUBackBuffer()
	{
		// do nothing
	}

	void WebGPUBackBuffer::clear(const WebGPUClearTarget clearTargets)
	{
		if (clearTargets & WebGPUClearTarget::BackBuffer)
		{
			//
		}

		if (clearTargets & WebGPUClearTarget::Scene)
		{
			// m_sceneBuffers.scene->clear(m_backgroundColor);
		}
	}

	void WebGPUBackBuffer::updateFromSceneBuffer(const wgpu::RenderPassEncoder& pass)
	{
		

		// pRenderer2D->drawFullScreenTriangle(m_sceneTextureFilter);

	
	}

	void WebGPUBackBuffer::capture()
	{
		if (m_screenCaptureImage.size() != m_sceneSize)
		{
			m_screenCaptureImage.resize(m_sceneSize);
		}

		if (m_sampleCount == 1)
		{
			// ::glBindFramebuffer(GL_FRAMEBUFFER, m_sceneBuffers.scene->getTexture());
			// {
			// 	::glReadPixels(0, 0, m_sceneSize.x, m_sceneSize.y, GL_RGBA, GL_UNSIGNED_BYTE, m_screenCaptureImage.data());
			// }
			// ::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else
		{
			// ::glBindFramebuffer(GL_FRAMEBUFFER, m_sceneBuffers.resolved->getTexture());
			// {
			// 	::glReadPixels(0, 0, m_sceneSize.x, m_sceneSize.y, GL_RGBA, GL_UNSIGNED_BYTE, m_screenCaptureImage.data());
			// }
			// ::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	const Image& WebGPUBackBuffer::getScreenCapture() const
	{
		return m_screenCaptureImage;
	}

	//////////////////////////////////////////////////
	//
	//	LetterboxColor
	//
	//////////////////////////////////////////////////

	void WebGPUBackBuffer::setLetterboxColor(const ColorF& color) noexcept
	{
		m_letterboxColor = color;
	}

	const ColorF& WebGPUBackBuffer::getLetterBoxColor() const noexcept
	{
		return m_letterboxColor;
	}

	//////////////////////////////////////////////////
	//
	//	BackgroundColor
	//
	//////////////////////////////////////////////////

	void WebGPUBackBuffer::setBackgroundColor(const ColorF& color) noexcept
	{
		m_backgroundColor = color;
	}

	const ColorF& WebGPUBackBuffer::getBackgroundColor() const noexcept
	{
		return m_backgroundColor;
	}

	//////////////////////////////////////////////////
	//
	//	SceneTextureFilter
	//
	//////////////////////////////////////////////////

	void WebGPUBackBuffer::setSceneTextureFilter(const TextureFilter textureFilter) noexcept
	{
		m_sceneTextureFilter = textureFilter;
	}

	TextureFilter WebGPUBackBuffer::getSceneTextureFilter() const noexcept
	{
		return m_sceneTextureFilter;
	}

	//////////////////////////////////////////////////
	//
	//	SceneResizeMode
	//
	//////////////////////////////////////////////////

	void WebGPUBackBuffer::setSceneResizeMode(const ResizeMode resizeMode)
	{
		m_sceneResizeMode = resizeMode;

		updateSceneSize();
	}

	ResizeMode WebGPUBackBuffer::getSceneResizeMode() const noexcept
	{
		return m_sceneResizeMode;
	}

	//////////////////////////////////////////////////
	//
	//	BackBuffer
	//
	//////////////////////////////////////////////////

	void WebGPUBackBuffer::setBackBufferSize(const Size backBufferSize)
	{
		assert((0 < backBufferSize.x) && (0 < backBufferSize.y));

		LOG_TRACE(U"WebGPUBackBuffer::setBackBufferSize({})"_fmt(backBufferSize));

		m_backBufferSize = backBufferSize;

		updateSceneSize();
	}

	const Size& WebGPUBackBuffer::getBackBufferSize() const noexcept
	{
		return m_backBufferSize;
	}

	std::pair<float, RectF> WebGPUBackBuffer::getLetterboxComposition() const noexcept
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

	void WebGPUBackBuffer::setSceneBufferSize(const Size size)
	{
		assert((0 < size.x) && (0 < size.y));

		if (size == m_sceneSize)
		{
			return;
		}

		LOG_TRACE(U"WebGPUBackBuffer::setSceneSize({})"_fmt(size));

		//unbindAllRenderTargets();

		m_sceneSize = size;

		{
			m_sceneBuffers = {};

			m_sceneBuffers.scene = WebGPUInternalTexture2D::CreateRenderTargetTexture2D(m_device, m_sceneSize, m_sampleCount);

			if (m_sampleCount > 1)
			{
				m_sceneBuffers.resolved = WebGPUInternalTexture2D::CreateRenderTargetTexture2D(m_device, m_sceneSize);
			}
		}

		wgpu::BindGroupEntry uniformEntries[] =
		{
			{
				.binding = 0,
				.sampler = m_sampler,
			},
			{
				.binding = 1,
				.textureView = m_sceneBuffers.scene->getTextureView()
			}
		};

		wgpu::BindGroupDescriptor uniformDesc
		{
			.entries = uniformEntries,
			.entryCount = 2
		};

		m_uniform = m_device.CreateBindGroup(&uniformDesc);

		clear(WebGPUClearTarget::All);
	}

	const Size& WebGPUBackBuffer::getSceneBufferSize() const noexcept
	{
		return m_sceneSize;
	}

	//////////////////////////////////////////////////
	//
	//	
	//
	//////////////////////////////////////////////////

	void WebGPUBackBuffer::updateSceneSize()
	{
		LOG_TRACE(U"WebGPUBackBuffer::updateSceneSize()");

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
