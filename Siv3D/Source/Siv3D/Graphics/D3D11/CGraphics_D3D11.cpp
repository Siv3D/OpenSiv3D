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
		//	 CTextureD3D11
		//
		m_texture = dynamic_cast<CTextureD3D11*>(Siv3DEngine::GetTexture());

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
		//	 D3D11RenderTarget
		//
		m_renderTarget = std::make_unique<D3D11RenderTarget>(m_device->getDevice(),
			m_device->getContext(), m_swapChain->getSwapChain(), m_texture);

		if (!m_renderTarget->init())
		{
			return false;
		}

		//////////////////////////////////////////////////////
		//
		//	 D3D11BlendState
		//
		m_pBlendState = std::make_unique<D3D11BlendState>(m_device->getDevice(), m_device->getContext());

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
}

# endif
