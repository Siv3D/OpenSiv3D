//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "D3D11Texture.hpp"
# include <Siv3D/Image.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	D3D11Texture::D3D11Texture(ID3D11Device* device, const Image& image, const TextureDesc desc)
		: m_desc{ image.size(),
			(detail::IsSRGB(desc) ? TextureFormat::R8G8B8A8_Unorm_SRGB : TextureFormat::R8G8B8A8_Unorm),
			desc,
			1,
			1, 0,
			D3D11_USAGE_IMMUTABLE,
			D3D11_BIND_SHADER_RESOURCE,
			0, 0 }
	{
		// [メインテクスチャ] を作成
		const D3D11_SUBRESOURCE_DATA initData{ image.data(), image.stride(), 0 };
		{
			const D3D11_TEXTURE2D_DESC d3d11Desc = m_desc.makeTEXTURE2D_DESC();
			if (HRESULT hr = device->CreateTexture2D(&d3d11Desc, &initData, &m_texture);
				FAILED(hr))
			{
				LOG_FAIL(U"❌ Texture_D3D11::Texture_D3D11() : Failed to create Texture2D. Error code: {:#X}"_fmt(hr));
				return;
			}
		}

		// [シェーダ・リソース・ビュー] を作成
		{
			const D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = m_desc.makeSHADER_RESOURCE_VIEW_DESC();
			if (HRESULT hr = device->CreateShaderResourceView(m_texture.Get(), &srvDesc, &m_shaderResourceView);
				FAILED(hr))
			{
				LOG_FAIL(U"❌ Texture_D3D11::Texture_D3D11() : Failed to create ShaderResourceView. Error code: {:#X}"_fmt(hr));
				return;
			}
		}

		m_type = TextureType::Default;
		m_initialized = true;
	}

	D3D11Texture::D3D11Texture(ID3D11Device* const device, const Image& image, const Array<Image>& mips, const TextureDesc desc)
		: m_desc{ image.size(),
			(detail::IsSRGB(desc) ? TextureFormat::R8G8B8A8_Unorm_SRGB : TextureFormat::R8G8B8A8_Unorm),
			desc,
			static_cast<uint32>(mips.size() + 1),
			1, 0,
			D3D11_USAGE_IMMUTABLE,
			D3D11_BIND_SHADER_RESOURCE,
			0, 0 }
	{
		Array<D3D11_SUBRESOURCE_DATA> initData(m_desc.mipLevels);
		{
			initData[0] = { image.data(), image.stride(), 0 };
			for (uint32 i = 0; i < mips.size(); ++i)
			{
				initData[i + 1] = { mips[i].data(), mips[i].stride(), 0 };
			}
		}

		// [メインテクスチャ] を作成
		{
			const D3D11_TEXTURE2D_DESC d3d11Desc = m_desc.makeTEXTURE2D_DESC();
			if (HRESULT hr = device->CreateTexture2D(&d3d11Desc, initData.data(), &m_texture);
				FAILED(hr))
			{
				LOG_FAIL(U"❌ Texture_D3D11::Texture_D3D11() : Failed to create Texture2D. Error code: {:#X}"_fmt(hr));
				return;
			}
		}

		// [シェーダ・リソース・ビュー] を作成
		{
			const D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = m_desc.makeSHADER_RESOURCE_VIEW_DESC();
			if (HRESULT hr = device->CreateShaderResourceView(m_texture.Get(), &srvDesc, &m_shaderResourceView);
				FAILED(hr))
			{
				LOG_FAIL(U"❌ Texture_D3D11::Texture_D3D11() : Failed to create ShaderResourceView. Error code: {:#X}"_fmt(hr));
				return;
			}
		}

		m_type = TextureType::Default;
		m_initialized = true;
	}

	bool D3D11Texture::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const D3D11Texture2DDesc& D3D11Texture::getDesc() const noexcept
	{
		return m_desc;
	}

	ID3D11ShaderResourceView** D3D11Texture::getSRVPtr()
	{
		return m_shaderResourceView.GetAddressOf();
	}

	ID3D11RenderTargetView* D3D11Texture::getRTV()
	{
		return m_renderTargetView.Get();
	}
}
