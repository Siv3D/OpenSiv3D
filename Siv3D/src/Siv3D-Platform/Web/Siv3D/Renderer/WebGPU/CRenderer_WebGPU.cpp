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

# include "CRenderer_WebGPU.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/Renderer2D/GLES3/CRenderer2D_GLES3.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

# include <emscripten/html5_webgpu.h>

namespace s3d
{
	namespace detail
	{
		/*
		static void GLDebugMessageARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const GLvoid* userParam)
		{
			// [Siv3D ToDo] Linux でのデバッグ用
		}
		
		static void GLDebugMessageAMD(GLuint id, GLuint category, GLenum severity, GLsizei length, const GLchar *message, GLvoid* userParam)
		{
			// [Siv3D ToDo] Linux でのデバッグ用
		}
		*/
	}

	CRenderer_WebGPU::CRenderer_WebGPU()
	{
	
	}

	CRenderer_WebGPU::~CRenderer_WebGPU()
	{
		LOG_SCOPED_TRACE(U"CRenderer_WebGPU::~CRenderer_WebGPU()");
	}

	EngineOption::Renderer CRenderer_WebGPU::getRendererType() const noexcept
	{
		return EngineOption::Renderer::OpenGL;
	}	

	void CRenderer_WebGPU::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_WebGPU::init()");
		
		pRenderer2D = dynamic_cast<CRenderer2D_GLES3*>(SIV3D_ENGINE(Renderer2D));
		m_window = static_cast<GLFWwindow*>(SIV3D_ENGINE(Window)->getHandle());
		
		m_device = wgpu::Device { ::emscripten_webgpu_get_device() };
        m_instance = wgpu::CreateInstance();
		
        wgpu::SurfaceDescriptorFromCanvasHTMLSelector canvasDescripter;
        canvasDescripter.selector = "canvas";

        wgpu::SurfaceDescriptor surfaceDescripter
        {
            .nextInChain = &canvasDescripter
        };

        wgpu::Surface surface = m_instance.CreateSurface(&surfaceDescripter);

        const Vec2 frameBufferSize = SIV3D_ENGINE(Window)->getState().frameBufferSize;

        wgpu::SwapChainDescriptor swapChainDescripter
        {
            .usage = wgpu::TextureUsage::OutputAttachment,
            .presentMode = wgpu::PresentMode::Fifo,
            .width = static_cast<uint32_t>(frameBufferSize.x),
            .height = static_cast<uint32_t>(frameBufferSize.y),
            .format = wgpu::TextureFormat::BGRA8Unorm
        };
      
        m_swapChain = m_device.CreateSwapChain(surface, &swapChainDescripter);

		m_queue = m_device.GetQueue();

		// m_backBuffer		= std::make_unique<GLES3BackBuffer>();
		// m_blendState		= std::make_unique<GLES3BlendState>();
		// m_rasterizerState	= std::make_unique<GLES3RasterizerState>();
		// m_samplerState		= std::make_unique<GLES3SamplerState>();
		
		// pTexture = dynamic_cast<CTexture_GLES3*>(SIV3D_ENGINE(Texture));
		// pTexture->init();

		// SIV3D_ENGINE(Shader)->init();

		clear();
	}

	StringView CRenderer_WebGPU::getName() const
	{
		static constexpr StringView name(U"WebGPU");
		return name;
	}	

	void CRenderer_WebGPU::clear()
	{
		// m_backBuffer->clear(GLES3ClearTarget::BackBuffer | GLES3ClearTarget::Scene);
		
		// const auto& windowState = SIV3D_ENGINE(Window)->getState();

		// if (const Size frameBufferSize = windowState.frameBufferSize; 
		// 	(frameBufferSize != m_backBuffer->getBackBufferSize()))
		// {
		// 	m_backBuffer->setBackBufferSize(frameBufferSize);

		// 	if (windowState.sizeMove)
		// 	{
		// 		// sleep
		// 	}
		// }

		// pRenderer2D->update();
	}

	void CRenderer_WebGPU::flush()
	{
		// // Scene に 2D 描画
		// {
		// 	m_backBuffer->bindSceneBuffer();
		// 	pRenderer2D->flush();
		// 	m_backBuffer->unbind();
		// }

		// ウィンドウに Scene を描画
		{
			auto backBufferView = m_swapChain.GetCurrentTextureView();

			wgpu::RenderPassColorAttachment colorAttachment
			{
				.view = backBufferView,
				.loadOp = wgpu::LoadOp::Clear,
				.storeOp = wgpu::StoreOp::Store,
				.clearColor = 
				{
					.r = 0.5,
					.g = 0.5,
					.b = 0.8,
					.a = 1.0
				}
			};

			wgpu::RenderPassDescriptor descripter
			{
				.colorAttachmentCount = 1,
				.colorAttachments = &colorAttachment
			};

			auto commamdEncoder = m_device.CreateCommandEncoder();

			{
				auto pass = commamdEncoder.BeginRenderPass(&descripter);

				// m_backBuffer->updateFromSceneBuffer();
				pass.EndPass();
			}
			
			auto commands = commamdEncoder.Finish();
			commamdEncoder.Release();
			
			m_queue.Submit(1, &commands);
		}
	}

	bool CRenderer_WebGPU::present()
	{
        // m_swapChain.Present();
		
		if constexpr (SIV3D_BUILD(DEBUG))
		{
			//CheckGLError();
		}

		return true;
	}

	void CRenderer_WebGPU::setVSyncEnabled(const bool enabled)
	{
		if (m_vSyncEnabled == enabled)
		{
			return;
		}

		m_vSyncEnabled = enabled;

		// ::glfwSwapInterval(static_cast<int32>(m_vSyncEnabled));
	}

	bool CRenderer_WebGPU::isVSyncEnabled() const
	{
		return m_vSyncEnabled;
	}

	void CRenderer_WebGPU::captureScreenshot()
	{
		m_backBuffer->capture();
	}

	const Image& CRenderer_WebGPU::getScreenCapture() const
	{
		return m_backBuffer->getScreenCapture();
	}

	void CRenderer_WebGPU::setSceneResizeMode(const ResizeMode resizeMode)
	{
		m_backBuffer->setSceneResizeMode(resizeMode);
	}

	ResizeMode CRenderer_WebGPU::getSceneResizeMode() const noexcept
	{
		return m_backBuffer->getSceneResizeMode();
	}

	void CRenderer_WebGPU::setSceneBufferSize(const Size size)
	{
		m_backBuffer->setSceneBufferSize(size);
	}

	Size CRenderer_WebGPU::getSceneBufferSize() const noexcept
	{
		return m_backBuffer->getSceneBufferSize();
	}

	void CRenderer_WebGPU::setSceneTextureFilter(const TextureFilter textureFilter)
	{
		m_backBuffer->setSceneTextureFilter(textureFilter);
	}

	TextureFilter CRenderer_WebGPU::getSceneTextureFilter() const noexcept
	{
		return m_backBuffer->getSceneTextureFilter();
	}

	void CRenderer_WebGPU::setBackgroundColor(const ColorF& color)
	{
		m_backBuffer->setBackgroundColor(color);
	}

	const ColorF& CRenderer_WebGPU::getBackgroundColor() const noexcept
	{
		return m_backBuffer->getBackgroundColor();
	}

	void CRenderer_WebGPU::setLetterboxColor(const ColorF& color)
	{
		m_backBuffer->setLetterboxColor(color);
	}

	const ColorF& CRenderer_WebGPU::getLetterboxColor() const noexcept
	{
		return m_backBuffer->getLetterBoxColor();
	}

	std::pair<float, RectF> CRenderer_WebGPU::getLetterboxComposition() const noexcept
	{
		return m_backBuffer->getLetterboxComposition();
	}

	void CRenderer_WebGPU::updateSceneSize()
	{
		m_backBuffer->updateSceneSize();
	}

	GLES3BackBuffer& CRenderer_WebGPU::getBackBuffer() noexcept
	{
		return *m_backBuffer;
	}

	GLES3BlendState& CRenderer_WebGPU::getBlendState() noexcept
	{
		return *m_blendState;
	}

	GLES3RasterizerState& CRenderer_WebGPU::getRasterizerState() noexcept
	{
		return *m_rasterizerState;
	}

	GLES3SamplerState& CRenderer_WebGPU::getSamplerState() noexcept
	{
		return *m_samplerState;
	}
}
