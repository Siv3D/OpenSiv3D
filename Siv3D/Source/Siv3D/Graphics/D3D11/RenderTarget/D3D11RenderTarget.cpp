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
	D3D11RenderTarget::D3D11RenderTarget(ID3D11Device* device, ID3D11DeviceContext* context, IDXGISwapChain* swapChain)
		: m_device(device)
		, m_context(context)
		, m_swapChain(swapChain)
	{

	}

	D3D11RenderTarget::~D3D11RenderTarget()
	{

	}

	bool D3D11RenderTarget::init()
	{
		if (FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &m_backBufferTexture)))
		{
			return false;
		}

		if (FAILED(m_device->CreateRenderTargetView(m_backBufferTexture.Get(), nullptr, &m_backBufferRenderTargetView)))
		{
			return false;
		}

		m_context->OMSetRenderTargets(1, m_backBufferRenderTargetView.GetAddressOf(), nullptr);

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
		const float colors[4]
		{
			static_cast<float>(m_clearColor.r),
			static_cast<float>(m_clearColor.g),
			static_cast<float>(m_clearColor.b),
			static_cast<float>(m_clearColor.a),
		};

		m_context->ClearRenderTargetView(m_backBufferRenderTargetView.Get(), colors);
	}

	void D3D11RenderTarget::beginResize()
	{
		m_context->OMSetRenderTargets(1, m_backBufferRenderTargetView.GetAddressOf(), nullptr);

		m_backBufferRenderTargetView.Reset();
		m_backBufferTexture.Reset();
	}

	bool D3D11RenderTarget::endResize(const Size& size)
	{
		if (FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &m_backBufferTexture)))
		{
			return false;
		}

		if (FAILED(m_device->CreateRenderTargetView(m_backBufferTexture.Get(), nullptr, &m_backBufferRenderTargetView)))
		{
			return false;
		}

		m_context->OMSetRenderTargets(1, m_backBufferRenderTargetView.GetAddressOf(), nullptr);

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
