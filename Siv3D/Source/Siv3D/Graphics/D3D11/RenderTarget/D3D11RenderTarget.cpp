//------m_context------------------------------------------
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

# include "D3D11RenderTarget.hpp"
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	D3D11RenderTarget::D3D11RenderTarget(ID3D11Device* device, ID3D11DeviceContext* context, IDXGISwapChain* swapChain, CTextureD3D11* texture)
		: m_device(device)
		, m_context(context)
		, m_swapChain(swapChain)
		, m_texture(texture)
	{

	}

	D3D11RenderTarget::~D3D11RenderTarget()
	{

	}

	bool D3D11RenderTarget::init()
	{
		ID3D11RenderTargetView* pRTV[3]
		{
			m_texture->getRTV(m_backBuffer.id()),
			nullptr,
			nullptr,
		};

		m_context->OMSetRenderTargets(3, pRTV, nullptr);

		D3D11_VIEWPORT m_viewport;
		m_viewport.TopLeftX = 0;
		m_viewport.TopLeftY = 0;
		m_viewport.Width = 640;
		m_viewport.Height = 480;
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;
		m_context->RSSetViewports(1, &m_viewport);

		return true;
	}

	void D3D11RenderTarget::setClearColor(const ColorF& color)
	{
		m_clearColor = color;
	}

	void D3D11RenderTarget::clear()
	{
		m_backBuffer.clear(m_texture, m_clearColor);
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

		m_backBuffer.beginResize(m_texture);
	}

	bool D3D11RenderTarget::endResize(const Size& size)
	{
		m_backBuffer.endResize(m_texture);

		ID3D11RenderTargetView* pRTV[3]
		{
			m_texture->getRTV(m_backBuffer.id()),
			nullptr,
			nullptr,
		};

		m_context->OMSetRenderTargets(3, pRTV, nullptr);

		D3D11_VIEWPORT m_viewport;
		m_viewport.TopLeftX = 0;
		m_viewport.TopLeftY = 0;
		m_viewport.Width = static_cast<float>(size.x);
		m_viewport.Height = static_cast<float>(size.y);
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;
		m_context->RSSetViewports(1, &m_viewport);

		return true;
	}
}

# endif
