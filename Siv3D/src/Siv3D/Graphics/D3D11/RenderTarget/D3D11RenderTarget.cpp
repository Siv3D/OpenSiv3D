//------m_context------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "D3D11RenderTarget.hpp"
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	D3D11RenderTarget::D3D11RenderTarget(ID3D11Device* device, ID3D11DeviceContext* context,
		IDXGISwapChain* swapChain, CTexture_D3D11* texture, const DXGI_SAMPLE_DESC& sample2D)
		: m_device(device)
		, m_context(context)
		, m_swapChain(swapChain)
		, m_texture(texture)
		, m_sample2D(sample2D)
	{

	}

	D3D11RenderTarget::~D3D11RenderTarget()
	{

	}

	bool D3D11RenderTarget::init()
	{
		m_rt2D = RenderTexture(Window::DefaultClientSize, m_sample2D.Count);

		if (!m_rt2D)
		{
			return false;
		}

		return true;
	}

	void D3D11RenderTarget::setClearColor(const ColorF& color)
	{
		m_clearColor = color;
	}

	void D3D11RenderTarget::clear()
	{
		m_rt2D.clear(m_clearColor);
	}

	void D3D11RenderTarget::resolve()
	{
		ID3D11RenderTargetView* pRTV[3]
		{
			nullptr,
			nullptr,
			nullptr,
		};

		m_context->OMSetRenderTargets(3, pRTV, nullptr);

		m_context->ResolveSubresource(m_texture->getTexture(m_backBuffer.id()), 0,
			m_texture->getTexture(m_rt2D.id()), 0,
			DXGI_FORMAT_R8G8B8A8_UNORM);

		pRTV[0] = m_texture->getRTV(m_rt2D.id());

		m_context->OMSetRenderTargets(3, pRTV, nullptr);
	}

	void D3D11RenderTarget::beginResize()
	{
		ID3D11RenderTargetView* pRTV[3]
		{
			nullptr,
			nullptr,
			nullptr,
		};

		m_context->OMSetRenderTargets(3, pRTV, nullptr);

		m_rt2D.beginResize();
		m_backBuffer.beginResize();
	}

	bool D3D11RenderTarget::endResize(const Size& size)
	{
		if (!m_backBuffer.endResize())
		{
			return false;
		}

		if (!m_rt2D.endResize(size, m_sample2D.Count))
		{
			return false;
		}

		m_currentBackBufferResolution = size;

		return true;
	}

	const Size& D3D11RenderTarget::getCurrentRenderTargetSize() const
	{
		return m_currentBackBufferResolution;
	}

	void D3D11RenderTarget::setRenderTargetView(ID3D11RenderTargetView* rtv)
	{
		ID3D11RenderTargetView* pRTV[3]
		{
			rtv,
			nullptr,
			nullptr,
		};

		m_context->OMSetRenderTargets(3, pRTV, nullptr);
	}

	const BackBufferTexture& D3D11RenderTarget::getBackBufferTexture() const
	{
		return m_backBuffer;
	}

	const RenderTexture& D3D11RenderTarget::getBackBuffer2D() const
	{
		return m_rt2D;
	}
}

# endif
