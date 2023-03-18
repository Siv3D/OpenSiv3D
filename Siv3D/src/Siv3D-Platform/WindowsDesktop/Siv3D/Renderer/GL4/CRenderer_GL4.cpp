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

# include "CRenderer_GL4.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/Mesh/IMesh.hpp>
# include <Siv3D/Renderer2D/GL4/CRenderer2D_GL4.hpp>
# include <Siv3D/Renderer3D/GL4/CRenderer3D_GL4.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	CRenderer_GL4::CRenderer_GL4()
	{

	}

	CRenderer_GL4::~CRenderer_GL4()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::~CRenderer_GL4()");

		m_wglContext.destroy();
	}

	EngineOption::Renderer CRenderer_GL4::getRendererType() const noexcept
	{
		return EngineOption::Renderer::OpenGL;
	}

	void CRenderer_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::init()");

		pRenderer2D = static_cast<CRenderer2D_GL4*>(SIV3D_ENGINE(Renderer2D));
		pRenderer3D = static_cast<CRenderer3D_GL4*>(SIV3D_ENGINE(Renderer3D));
		m_hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());

		m_wglContext.init(m_hWnd);

		m_backBuffer		= std::make_unique<GL4BackBuffer>();
		m_blendState		= std::make_unique<GL4BlendState>();
		m_rasterizerState	= std::make_unique<GL4RasterizerState>();
		m_depthStencilState = std::make_unique<GL4DepthStencilState>();
		m_samplerState		= std::make_unique<GL4SamplerState>();

		pTexture = static_cast<CTexture_GL4*>(SIV3D_ENGINE(Texture));
		pTexture->init();

		SIV3D_ENGINE(Shader)->init();
		SIV3D_ENGINE(Mesh)->init();

		clear();
	}

	StringView CRenderer_GL4::getName() const
	{
		static constexpr StringView name(U"OpenGL");
		return name;
	}

	void CRenderer_GL4::clear()
	{
		m_backBuffer->clear(GL4ClearTarget::BackBuffer | GL4ClearTarget::Scene);

		const auto& windowState = SIV3D_ENGINE(Window)->getState();

		if (const Size frameBufferSize = windowState.frameBufferSize; 
			(frameBufferSize != m_backBuffer->getBackBufferSize()))
		{
			m_backBuffer->setBackBufferSize(frameBufferSize);

			if (windowState.sizeMove)
			{
				::Sleep(100);
			}
		}

		pRenderer2D->update();
	}

	void CRenderer_GL4::flush()
	{
		// Scene に 3D, 2D 描画
		{
			pRenderer3D->flush();
			pRenderer2D->flush();
			m_backBuffer->unbind();
		}

		// ウィンドウに Scene を描画
		{
			m_backBuffer->updateFromSceneBuffer();
		}
	}

	bool CRenderer_GL4::present()
	{
		m_wglContext.swapBuffers();

		return true;
	}

	void CRenderer_GL4::setVSyncEnabled(const bool enabled)
	{
		if (m_vSyncEnabled == enabled)
		{
			return;
		}

		m_vSyncEnabled = enabled;

		wglSwapIntervalEXT(static_cast<int32>(m_vSyncEnabled));
	}

	bool CRenderer_GL4::isVSyncEnabled() const
	{
		return m_vSyncEnabled;
	}

	void CRenderer_GL4::captureScreenshot()
	{
		m_backBuffer->capture();
	}

	const Image& CRenderer_GL4::getScreenCapture() const
	{
		return m_backBuffer->getScreenCapture();
	}

	void CRenderer_GL4::setSceneResizeMode(const ResizeMode resizeMode)
	{
		m_backBuffer->setSceneResizeMode(resizeMode);
	}

	ResizeMode CRenderer_GL4::getSceneResizeMode() const noexcept
	{
		return m_backBuffer->getSceneResizeMode();
	}

	void CRenderer_GL4::setSceneBufferSize(const Size size)
	{
		m_backBuffer->setSceneBufferSize(size);
	}

	Size CRenderer_GL4::getSceneBufferSize() const noexcept
	{
		return m_backBuffer->getSceneBufferSize();
	}

	void CRenderer_GL4::setSceneTextureFilter(const TextureFilter textureFilter)
	{
		m_backBuffer->setSceneTextureFilter(textureFilter);
	}

	TextureFilter CRenderer_GL4::getSceneTextureFilter() const noexcept
	{
		return m_backBuffer->getSceneTextureFilter();
	}

	void CRenderer_GL4::setBackgroundColor(const ColorF& color)
	{
		m_backBuffer->setBackgroundColor(color);
	}

	const ColorF& CRenderer_GL4::getBackgroundColor() const noexcept
	{
		return m_backBuffer->getBackgroundColor();
	}

	void CRenderer_GL4::setLetterboxColor(const ColorF& color)
	{
		m_backBuffer->setLetterboxColor(color);
	}

	const ColorF& CRenderer_GL4::getLetterboxColor() const noexcept
	{
		return m_backBuffer->getLetterBoxColor();
	}

	std::pair<float, RectF> CRenderer_GL4::getLetterboxComposition() const noexcept
	{
		return m_backBuffer->getLetterboxComposition();
	}

	void CRenderer_GL4::updateSceneSize()
	{
		m_backBuffer->updateSceneSize();
	}

	GL4BackBuffer& CRenderer_GL4::getBackBuffer() noexcept
	{
		return *m_backBuffer;
	}

	GL4BlendState& CRenderer_GL4::getBlendState() noexcept
	{
		return *m_blendState;
	}

	GL4RasterizerState& CRenderer_GL4::getRasterizerState() noexcept
	{
		return *m_rasterizerState;
	}

	GL4DepthStencilState& CRenderer_GL4::getDepthStencilState() noexcept
	{
		return *m_depthStencilState;
	}

	GL4SamplerState& CRenderer_GL4::getSamplerState() noexcept
	{
		return *m_samplerState;
	}
}
