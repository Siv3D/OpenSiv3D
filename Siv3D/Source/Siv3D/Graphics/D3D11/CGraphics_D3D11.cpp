//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "../../Siv3DEngine.hpp"
# include "CGraphics_D3D11.hpp"
# include "../../Shader/IShader.hpp"

namespace s3d
{
	CGraphics_D3D11::CGraphics_D3D11()
	{

	}

	CGraphics_D3D11::~CGraphics_D3D11()
	{

	}

	bool CGraphics_D3D11::init()
	{
		//////////////////////////////////////////////////////
		//
		//	 D3D11Device
		//
		m_device = std::make_unique<D3D11Device>();

		if (!m_device->init())
		{
			return false;
		}

		//////////////////////////////////////////////////////
		//
		//	 D3D11SwapChain
		//
		m_swapChain = std::make_unique<D3D11SwapChain>(m_device->getDevice(), m_device->getContext(), m_device->getAdapter());

		if (!m_swapChain->init())
		{
			return false;
		}

		//////////////////////////////////////////////////////
		//
		//	 CTexture_D3D11
		//
		m_texture = dynamic_cast<CTexture_D3D11*>(Siv3DEngine::GetTexture());

		if (!m_texture)
		{
			return false;
		}

		if (!m_texture->init(m_device->getDevice(), m_device->getContext(), m_swapChain->getSwapChain()))
		{
			return false;
		}

		//////////////////////////////////////////////////////
		//
		//	 CShader_D3D11
		//
		m_shader = dynamic_cast<CShader_D3D11*>(Siv3DEngine::GetShader());

		if (!m_shader)
		{
			return false;
		}

		if (!m_shader->init(m_device->getDevice(), m_device->getContext()))
		{
			return false;
		}

		//////////////////////////////////////////////////////
		//
		//	 D3D11RenderTarget
		//
		const DXGI_SAMPLE_DESC sample2D = m_device->getBestMSAA(DXGI_FORMAT_R8G8B8A8_UNORM, 4);

		m_renderTarget = std::make_unique<D3D11RenderTarget>(m_device->getDevice(),
			m_device->getContext(), m_swapChain->getSwapChain(), m_texture, sample2D);

		if (!m_renderTarget->init())
		{
			return false;
		}

		//////////////////////////////////////////////////////
		//
		//	 D3D11BlendState
		//
		m_pBlendState = std::make_unique<D3D11BlendState>(m_device->getDevice(), m_device->getContext());

		//////////////////////////////////////////////////////
		//
		//	 D3D11RasterizerState
		//
		m_pRasterizerState = std::make_unique<D3D11RasterizerState>(m_device->getDevice(), m_device->getContext());

		//////////////////////////////////////////////////////
		//
		//	 D3D11DepthStencilState
		//
		m_pDepthStencilState = std::make_unique<D3D11DepthStencilState>(m_device->getDevice(), m_device->getContext());

		//////////////////////////////////////////////////////
		//
		//	 D3D11SamplerState
		//
		m_pSamplerState = std::make_unique<D3D11SamplerState>(m_device->getDevice(), m_device->getContext());

		//////////////////////////////////////////////////////
		//
		//	 CRenderer2D_D3D11
		//
		m_renderer2D = dynamic_cast<CRenderer2D_D3D11*>(Siv3DEngine::GetRenderer2D());

		if (!m_renderer2D)
		{
			return false;
		}

		if (!m_renderer2D->init(m_device->getDevice(), m_device->getContext()))
		{
			return false;
		}

		//////////////////////////////////////////////////////
		//
		//
		//
		m_device->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		return true;
	}

	Array<DisplayOutput> CGraphics_D3D11::enumOutputs()
	{
		return m_swapChain->enumOutputs();
	}

	void CGraphics_D3D11::setClearColor(const ColorF& color)
	{
		m_renderTarget->setClearColor(color);
	}

	bool CGraphics_D3D11::setFullScreen(bool fullScreen, const Size& size, size_t displayIndex, double refreshRateHz)
	{
		return m_swapChain->setFullScreen(fullScreen, size, displayIndex, refreshRateHz);
	}

	bool CGraphics_D3D11::present()
	{
		return m_swapChain->present();
	}

	void CGraphics_D3D11::clear()
	{
		m_renderTarget->clear();
	}

	void CGraphics_D3D11::beginResize()
	{
		m_renderTarget->beginResize();
	}

	bool CGraphics_D3D11::endResize(const Size& size)
	{
		return m_renderTarget->endResize(size);
	}

	void CGraphics_D3D11::setVSyncEnabled(const bool enabled)
	{
		m_swapChain->setVSyncEnabled(enabled);
	}

	bool CGraphics_D3D11::isVSyncEnabled() const
	{
		return m_swapChain->isVSyncEnabled();
	}

	void CGraphics_D3D11::setTargetFrameRateHz(const Optional<double>& targetFrameRateHz)
	{
		m_swapChain->setTargetFrameRateHz(targetFrameRateHz);
	}

	Optional<double> CGraphics_D3D11::getTargetFrameRateHz() const
	{
		return m_swapChain->getTargetFrameRateHz();
	}

	double CGraphics_D3D11::getDisplayRefreshRateHz() const
	{
		return m_swapChain->getDisplayRefreshRateHz();
	}

	bool CGraphics_D3D11::flush()
	{
		m_renderer2D->flush();

		m_renderTarget->resolve();

		return true;
	}

	const Size& CGraphics_D3D11::getCurrentRenderTargetSize() const
	{
		return m_renderTarget->getCurrentRenderTargetSize();
	}

	const RenderTexture& CGraphics_D3D11::getBackBuffer2D() const
	{
		return m_renderTarget->getBackBuffer2D();
	}
}

# endif
