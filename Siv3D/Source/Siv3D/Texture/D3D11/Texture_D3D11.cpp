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
# include "Texture_D3D11.hpp"
# include <Siv3D/Image.hpp>
# include <Siv3D/ImageProcessing.hpp>

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

	Texture_D3D11::Texture_D3D11(Render, ID3D11Device* device, const Size& size, const uint32 multisampleCount)
	{
		m_desc.Width			= size.x;
		m_desc.Height			= size.y;
		m_desc.MipLevels		= 1;
		m_desc.ArraySize		= 1;
		m_desc.Format			= DXGI_FORMAT_R8G8B8A8_UNORM;
		m_desc.SampleDesc		= DXGI_SAMPLE_DESC{ multisampleCount, 0 };
		m_desc.Usage			= D3D11_USAGE_DEFAULT;
		m_desc.BindFlags		= D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		m_desc.CPUAccessFlags	= 0;
		m_desc.MiscFlags		= 0;

		if (FAILED(device->CreateTexture2D(&m_desc, nullptr, &m_texture)))
		{
			return;
		}

		m_rtDesc.Format			= m_desc.Format;
		m_rtDesc.ViewDimension	= (m_desc.SampleDesc.Count == 1) ? D3D11_RTV_DIMENSION_TEXTURE2D : D3D11_RTV_DIMENSION_TEXTURE2DMS;
	
		if (FAILED(device->CreateRenderTargetView(m_texture.Get(), &m_rtDesc, &m_renderTargetView)))
		{
			return;
		}

		m_srvDesc.Format		= m_desc.Format;
		m_srvDesc.ViewDimension	= (m_desc.SampleDesc.Count == 1) ? D3D11_SRV_DIMENSION_TEXTURE2D : D3D11_SRV_DIMENSION_TEXTURE2DMS;
		m_srvDesc.Texture2D		= { 0, m_desc.MipLevels };

		if (FAILED(device->CreateShaderResourceView(m_texture.Get(), &m_srvDesc, &m_shaderResourceView)))
		{
			return;
		}

		m_initialized = true;
	}

	Texture_D3D11::Texture_D3D11(ID3D11Device* device, const Image& image, const TextureDesc)
	{
		m_desc.Width				= image.width();
		m_desc.Height				= image.height();
		m_desc.MipLevels			= 1;
		m_desc.ArraySize			= 1;
		m_desc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM; //static_cast<DXGI_FORMAT>(desc == TextureDesc::UnmippedSRGB || desc == TextureDesc::MippedSRGB ? TextureFormat::R8G8B8A8_Unorm_SRGB : TextureFormat::R8G8B8A8_Unorm);
		m_desc.SampleDesc			= DXGI_SAMPLE_DESC{ 1, 0 };
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

	Texture_D3D11::Texture_D3D11(ID3D11Device* device, const Image& image, const Array<Image>& mipmaps, const TextureDesc)
	{
		m_desc.Width				= image.width();
		m_desc.Height				= image.height();
		m_desc.MipLevels			= static_cast<uint32>(mipmaps.size() + 1);
		m_desc.ArraySize			= 1;
		m_desc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM; //static_cast<DXGI_FORMAT>(desc == TextureDesc::UnmippedSRGB || desc == TextureDesc::MippedSRGB ? TextureFormat::R8G8B8A8_Unorm_SRGB : TextureFormat::R8G8B8A8_Unorm);
		m_desc.SampleDesc			= DXGI_SAMPLE_DESC{ 1, 0 };
		m_desc.Usage				= D3D11_USAGE_IMMUTABLE;
		m_desc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
		m_desc.CPUAccessFlags		= 0;
		m_desc.MiscFlags			= 0;

		Array<D3D11_SUBRESOURCE_DATA> initData(m_desc.MipLevels);

		initData[0] = { image.data(), image.stride(), 0 };

		for (uint32 i = 0; i < mipmaps.size(); ++i)
		{
			initData[i + 1] = { mipmaps[i].data(), mipmaps[i].stride(), 0 };
		}

		if (FAILED(device->CreateTexture2D(&m_desc, initData.data(), &m_texture)))
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

	void Texture_D3D11::clearRT(ID3D11DeviceContext* context, const ColorF& color)
	{
		const ColorF clearColor = isSRGB() ? color.gamma(1.0 / 2.2) : color;

		const float colors[4]
		{
			static_cast<float>(clearColor.r),
			static_cast<float>(clearColor.g),
			static_cast<float>(clearColor.b),
			static_cast<float>(clearColor.a),
		};

		context->ClearRenderTargetView(m_renderTargetView.Get(), colors);
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

	bool Texture_D3D11::endResize(Render, ID3D11Device* device, const Size& size, const uint32 multisampleCount)
	{
		*this = Texture_D3D11(Render{}, device, size, multisampleCount);

		return isInitialized();
	}
}

# endif
