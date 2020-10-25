﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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
# include <Siv3D/Renderer2D/GL4/CRenderer2D_GL4.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	CRenderer_GL4::CRenderer_GL4() = default;

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

		pRenderer2D = dynamic_cast<CRenderer2D_GL4*>(SIV3D_ENGINE(Renderer2D));
		m_hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());

		m_wglContext.init(m_hWnd);

		m_backBuffer = std::make_unique<GL4BackBuffer>();

		SIV3D_ENGINE(Texture)->init();
		SIV3D_ENGINE(Shader)->init();
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
	}

	void CRenderer_GL4::flush()
	{
		// Scene に 2D 描画
		{
			m_backBuffer->bindSceneBuffer();
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
		//wglSwapIntervalEXT(0);

		m_wglContext.swapBuffers();

		return true;
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
}
