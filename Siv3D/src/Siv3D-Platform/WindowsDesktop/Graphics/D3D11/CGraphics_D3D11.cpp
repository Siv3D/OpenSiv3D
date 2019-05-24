//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/PointVector.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3DEngine.hpp>
# include <Window/IWindow.hpp>
# include <Shader/IShader.hpp>
# include <Texture/ITexture.hpp>
# include <Renderer2D/IRenderer2D.hpp>
# include <Shader/D3D11/CShader_D3D11.hpp>
# include <Texture/D3D11/CTexture_D3D11.hpp>
# include <Renderer2D/D3D11/CRenderer2D_D3D11.hpp>
# include "CGraphics_D3D11.hpp"

namespace s3d
{
	CGraphics_D3D11::CGraphics_D3D11()
	{

	}

	CGraphics_D3D11::~CGraphics_D3D11()
	{
		LOG_TRACE(U"CGraphics_D3D11::~CGraphics_D3D11()");
	}

	void CGraphics_D3D11::init()
	{
		LOG_TRACE(U"CGraphics_D3D11::init()");

		HWND hWnd		= static_cast<HWND>(Siv3DEngine::Get<ISiv3DWindow>()->getHandle());
		m_device		= std::make_unique<D3D11Device>();
		m_swapChain		= std::make_unique<D3D11SwapChain>(*m_device, hWnd, Siv3DEngine::Get<ISiv3DWindow>()->getClientSize());
		m_renderTarget	= std::make_unique<D3D11RenderTarget>(*m_device, *m_swapChain);

		m_pBlendState			= std::make_unique<D3D11BlendState>(m_device->getDevice(), m_device->getContext());
		m_pRasterizerState		= std::make_unique<D3D11RasterizerState>(m_device->getDevice(), m_device->getContext());
		m_pDepthStencilState	= std::make_unique<D3D11DepthStencilState>(m_device->getDevice(), m_device->getContext());
		m_pSamplerState			= std::make_unique<D3D11SamplerState>(m_device->getDevice(), m_device->getContext());
		m_pScreenCapture		= std::make_unique<D3D11ScreenCapture>(m_device->getDevice(), m_device->getContext());

		if (CShader_D3D11* shader = dynamic_cast<CShader_D3D11*>(Siv3DEngine::Get<ISiv3DShader>()))
		{
			shader->init(m_device->getDevice(), m_device->getContext());
		}
		else
		{
			throw EngineError(U"dynamic_cast<CShader_D3D11*> failed");
		}

		if (CTexture_D3D11* texture = dynamic_cast<CTexture_D3D11*>(Siv3DEngine::Get<ISiv3DTexture>()))
		{
			texture->init(m_device->getDevice(), m_device->getContext());
		}
		else
		{
			throw EngineError(U"dynamic_cast<CTexture_D3D11*> failed");
		}

		if (CRenderer2D_D3D11 * renderer2D = dynamic_cast<CRenderer2D_D3D11*>(Siv3DEngine::Get<ISiv3DRenderer2D>()))
		{
			renderer2D->init(m_device->getDevice(), m_device->getContext());
		}
		else
		{
			throw EngineError(U"dynamic_cast<CRenderer2D_D3D11*> failed");
		}

		m_device->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		LOG_INFO(U"ℹ️ CGraphics_D3D11 initialized");
	}

	bool CGraphics_D3D11::present()
	{
		if (!m_swapChain->present())
		{
			return false;
		}

		if (m_pScreenCapture->isRequested())
		{
			const BackBuffer& backBuffer = m_renderTarget->getBackBuffer();
			m_pScreenCapture->capture(backBuffer.texture.Get(), backBuffer.size);
		}

		return true;
	}

	void CGraphics_D3D11::clear()
	{
		m_renderTarget->clear(false);
	}

	void CGraphics_D3D11::flush()
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->flush();

		m_renderTarget->resolve();
	}

	void CGraphics_D3D11::setSceneTextureFilter(const TextureFilter textureFilter)
	{
		m_renderTarget->setSceneTextureFilter(textureFilter);
	}

	TextureFilter CGraphics_D3D11::getSceneTextureFilter() const
	{
		return m_renderTarget->getSceneTextureFilter();
	}

	void CGraphics_D3D11::setBackgroundColor(const ColorF& color)
	{
		m_renderTarget->setBackgroundColor(color);
	}

	void CGraphics_D3D11::setLetterboxColor(const ColorF& color)
	{
		m_renderTarget->setLetterboxColor(color);
	}

	void CGraphics_D3D11::setTargetFrameRateHz(const Optional<double>& targetFrameRateHz)
	{
		m_swapChain->setTargetFrameRateHz(targetFrameRateHz);
	}

	Optional<double> CGraphics_D3D11::getTargetFrameRateHz() const
	{
		return m_swapChain->getTargetFrameRateHz();
	}

	double CGraphics_D3D11::getDPIScaling() const
	{
		return m_swapChain->getDPIScaling();
	}

	double CGraphics_D3D11::getDisplayRefreshRateHz() const
	{
		return m_swapChain->getDisplayRefreshRateHz();
	}

	void CGraphics_D3D11::skipClearScreen()
	{
		m_renderTarget->skipClearScreen();
	}

	const Size& CGraphics_D3D11::getBackBufferSize() const
	{
		return m_renderTarget->getBackBufferSize();
	}

	const Size& CGraphics_D3D11::getSceneSize() const
	{
		return m_renderTarget->getSceneSize();
	}

	void CGraphics_D3D11::setSceneSize(const Size& sceneSize)
	{
		m_renderTarget->resizeScene(sceneSize);
	}

	void CGraphics_D3D11::resizeBuffers(const Size& backBufferSize, const Size& sceneSize)
	{
		m_renderTarget->resizeBuffers(backBufferSize, sceneSize);
	}

	Optional<Rect> CGraphics_D3D11::getFullscreenRect()
	{
		return m_swapChain->getFullscreenRect();
	}

	void CGraphics_D3D11::requestScreenCapture()
	{
		m_pScreenCapture->request();
	}

	const Image& CGraphics_D3D11::getScreenCapture() const
	{
		return m_pScreenCapture->getImage();
	}
}
