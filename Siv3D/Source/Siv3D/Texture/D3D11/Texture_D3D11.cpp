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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "../../Siv3DEngine.hpp"
# include "Texture_D3D11.hpp"
# include <Siv3D/Image.hpp>

namespace s3d
{
	Texture_D3D11::Texture_D3D11(Null, ID3D11Device* const device)
	{
		const Image image(16, 16, Palette::Yellow);
		m_desc.Width				= image.width();
		m_desc.Height				= image.height();
		m_desc.MipLevels			= 1;
		m_desc.ArraySize			= 1;
		m_desc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
		m_desc.SampleDesc.Count		= 1;
		m_desc.SampleDesc.Quality	= 0;
		m_desc.Usage				= D3D11_USAGE_IMMUTABLE;
		m_desc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
		m_desc.CPUAccessFlags		= 0;
		m_desc.MiscFlags			= 0;

		const D3D11_SUBRESOURCE_DATA initData{ image.data(), image.stride(), 0 };

		if (FAILED(device->CreateTexture2D(&m_desc, &initData, &m_texture)))
		{
			return;
		}

		m_srvDesc.Format		= m_desc.Format;
		m_srvDesc.ViewDimension	= D3D11_SRV_DIMENSION_TEXTURE2D;
		m_srvDesc.Texture2D		= { 0, m_desc.MipLevels };

		if (FAILED(device->CreateShaderResourceView(m_texture.Get(), &m_srvDesc, &m_shaderResourceView)))
		{
			return;
		}

		m_initialized = true;
	}

	Texture_D3D11::Texture_D3D11(BackBuffer, ID3D11Device* const device, IDXGISwapChain* const swapChain)
	{
		if (FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &m_texture)))
		{
			return;
		}

		m_texture->GetDesc(&m_desc);

		if (FAILED(device->CreateRenderTargetView(m_texture.Get(), nullptr, &m_renderTargetView)))
		{
			return;
		}

		if (FAILED(device->CreateShaderResourceView(m_texture.Get(), nullptr, &m_shaderResourceView)))
		{
			return;
		}

		m_shaderResourceView->GetDesc(&m_srvDesc);

		m_initialized = true;
	}

	void Texture_D3D11::beginResize()
	{
		*this = Texture_D3D11();
	}

	bool Texture_D3D11::endResize(BackBuffer, ID3D11Device* const device, IDXGISwapChain* const swapChain)
	{
		*this = Texture_D3D11(BackBuffer{}, device, swapChain);

		return isInitialized();
	}
}

# endif
