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

# include <Siv3DEngine.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/TextureFormat.hpp>
# include <Siv3D/EngineLog.hpp>
# include "Texture_D3D11.hpp"

namespace s3d
{
	namespace detail
	{
		static void FillByColor(void* const buffer, const Size& size, const uint32 dstStride, const ColorF& color, const TextureFormat format)
		{
			const auto prop = GetTextureFormatProperty(format);
			const uint32 pixelSize = prop.pixelSize;
			const uint32 num_channels = prop.num_channels;

			if (pixelSize == 4 && num_channels == 4)
			{
				const uint32 fillValue = Color(color).asUint32();

				uint8* pDst = static_cast<uint8*>(buffer);

				for (int32 y = 0; y < size.y; ++y)
				{
					uint32* pDstLine = static_cast<uint32*>(static_cast<void*>(pDst));

					for (int32 x = 0; x < size.x; ++x)
					{
						*pDstLine++ = fillValue;
					}

					pDst += dstStride;
				}
			}
		}

		static void FillRegionByColor(void* const buffer, const Size& size, const uint32 dstStride, const Rect& rect, const ColorF& color, const TextureFormat format)
		{
			const auto prop = GetTextureFormatProperty(format);
			const uint32 pixelSize = prop.pixelSize;
			const uint32 num_channels = prop.num_channels;

			const int32 leftX = std::clamp(rect.x, 0, size.x);
			const int32 rightX = std::clamp(rect.x + rect.w, 0, size.x);
			const int32 topY = std::clamp(rect.y, 0, size.y);
			const int32 bottomY = std::clamp(rect.y + rect.h, 0, size.y);
			const int32 width = (rightX - leftX);
			const int32 height = (bottomY - topY);

			if (width == 0 || height == 0)
			{
				return;
			}

			if (pixelSize == 4 && num_channels == 4)
			{
				const uint32 fillValue = Color(color).asUint32();

				uint8* pDst = static_cast<uint8*>(buffer);

				pDst += (dstStride * topY);
				pDst += (pixelSize * leftX);

				for (int32 y = 0; y < height; ++y)
				{
					uint32* pDstLine = static_cast<uint32*>(static_cast<void*>(pDst));

					for (int32 x = 0; x < width; ++x)
					{
						*pDstLine++ = fillValue;
					}

					pDst += dstStride;
				}
			}
		}

		static void FillByImage(void* const buffer, const Size& size, const uint32 dstStride, const void* pData, const uint32 srcStride, const TextureFormat format)
		{
			const auto prop = GetTextureFormatProperty(format);
			const uint32 pixelSize = prop.pixelSize;
			const uint32 num_channels = prop.num_channels;

			if (pixelSize == 4 && num_channels == 4)
			{
				uint8* pDst = static_cast<uint8*>(buffer);
				const uint8* pSrc = static_cast<const uint8*>(pData);

				if (dstStride == srcStride)
				{
					std::memcpy(pDst, pSrc, dstStride * size.y);
				}
				else
				{
					const uint32 minStride = std::min(dstStride, srcStride);

					for (int32 y = 0; y < size.y; ++y)
					{
						std::memcpy(pDst, pSrc, minStride);
						pDst += dstStride;
						pSrc += srcStride;
					}
				}
			}
		}

		static void FillRegionByImage(void* const buffer, const Size& size, const uint32 dstStride, const void* pData, const uint32 srcStride, const Rect& rect, const TextureFormat format)
		{
			const auto prop = GetTextureFormatProperty(format);
			const uint32 pixelSize = prop.pixelSize;
			const uint32 num_channels = prop.num_channels;

			const int32 leftX = std::clamp(rect.x, 0, size.x);
			const int32 topY = std::clamp(rect.y, 0, size.y);
			const int32 rightX = std::clamp(rect.x + rect.w, 0, size.x);
			const int32 bottomY = std::clamp(rect.y + rect.h, 0, size.y);
			const int32 width = (rightX - leftX);
			const int32 height = (bottomY - topY);

			if (width == 0 || height == 0)
			{
				return;
			}

			if (pixelSize == 4 && num_channels == 4)
			{
				uint8* pDst = static_cast<uint8*>(buffer);
				const uint8* pSrc = static_cast<const uint8*>(pData);
				
				pDst += (dstStride * topY);
				pDst += (pixelSize * leftX);

				pSrc += (srcStride * topY);
				pSrc += (pixelSize * leftX);

				const uint32 copyStride = pixelSize * width;

				for (int32 y = 0; y < height; ++y)
				{
					std::memcpy(pDst, pSrc, copyStride);
					
					if (y + 1 < height)
					{
						pDst += dstStride;
						pSrc += srcStride;
					}
				}
			}
		}
	}
	/*
	Texture_D3D11::Texture_D3D11(Null, ID3D11Device* const device)
	{
		m_desc = D3D11Texture2DDesc(Size(16, 16),
			TextureFormat::R8G8B8A8_Unorm, TextureDesc::Unmipped,
			1, 1, 0,
			D3D11_USAGE_IMMUTABLE,
			D3D11_BIND_SHADER_RESOURCE,
			0, 0);

		const D3D11_TEXTURE2D_DESC d3d11Desc = m_desc.makeD3D11Desc();
		const Image image(m_desc.size, Palette::Yellow);
		const D3D11_SUBRESOURCE_DATA initData{ image.data(), image.stride(), 0 };

		if (FAILED(device->CreateTexture2D(&d3d11Desc, &initData, &m_texture)))
		{
			return;
		}

		if (!createShaderResourceView(device))
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

		D3D11_TEXTURE2D_DESC d3d11Desc;
		m_texture->GetDesc(&d3d11Desc);

		m_desc = D3D11Texture2DDesc(Size(d3d11Desc.Width, d3d11Desc.Height),
			detail::FromDXGIFormat(d3d11Desc.Format), TextureDesc::Unmipped,
			d3d11Desc.MipLevels, d3d11Desc.SampleDesc.Count, d3d11Desc.SampleDesc.Quality,
			d3d11Desc.Usage,
			d3d11Desc.BindFlags,
			d3d11Desc.CPUAccessFlags, d3d11Desc.MiscFlags);

		if (FAILED(device->CreateRenderTargetView(m_texture.Get(), nullptr, &m_renderTargetView)))
		{
			return;
		}

		if (FAILED(device->CreateShaderResourceView(m_texture.Get(), nullptr, &m_shaderResourceView)))
		{
			return;
		}

		m_initialized = true;
	}
	*/
	Texture_D3D11::Texture_D3D11(Dynamic, ID3D11Device* const device, const Size& size, const void* pData, const uint32 stride, const TextureFormat format, const TextureDesc _desc)
		: m_desc(size,
			format,
			_desc,
			1,
			1, 0,
			D3D11_USAGE_DEFAULT,
			D3D11_BIND_SHADER_RESOURCE,
			0, 0)
	{
		if (!InRange(size.x, 1, Image::MaxWidth) || !InRange(size.y, 1, Image::MaxHeight))
		{
			return;
		}

		const D3D11_SUBRESOURCE_DATA initData{ pData, stride, 0 };
		{
			D3D11_TEXTURE2D_DESC d3d11Desc = m_desc.makeTEXTURE2D_DESC();
			if (HRESULT hr = device->CreateTexture2D(&d3d11Desc, &initData, &m_texture);
				FAILED(hr))
			{
				LOG_FAIL(U"❌ Texture_D3D11::Texture_D3D11() : Failed to create Texture2D (D3D11_USAGE_DEFAULT). Error code: {0}"_fmt(ToHex(hr)));
				return;
			}

			d3d11Desc.Usage				= D3D11_USAGE_STAGING;
			d3d11Desc.BindFlags			= 0;
			d3d11Desc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;

			if (HRESULT hr = device->CreateTexture2D(&d3d11Desc, pData ? &initData : nullptr, &m_textureStaging);
				FAILED(hr))
			{
				LOG_FAIL(U"❌ Texture_D3D11::Texture_D3D11() : Failed to create Texture2D (D3D11_USAGE_STAGING). Error code: {0}"_fmt(ToHex(hr)));
				return;
			}
		}

		{
			const D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = m_desc.makeSHADER_RESOURCE_VIEW_DESC();
			if (HRESULT hr = device->CreateShaderResourceView(m_texture.Get(), &srvDesc, &m_shaderResourceView);
				FAILED(hr))
			{
				LOG_FAIL(U"❌ Texture_D3D11::Texture_D3D11() : Failed to create ShaderResourceView. Error code: {0}"_fmt(ToHex(hr)));
				return;
			}
		}

		m_initialized = true;
	}
	/*
	Texture_D3D11::Texture_D3D11(Render, ID3D11Device* const device, const Size& size, const uint32 multisampleCount)
	{
		m_desc = D3D11Texture2DDesc(size,
			TextureFormat::R8G8B8A8_Unorm, TextureDesc::Unmipped,
			1, multisampleCount, 0,
			D3D11_USAGE_DEFAULT,
			D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE,
			0, 0);

		const D3D11_TEXTURE2D_DESC d3d11Desc = m_desc.makeD3D11Desc();

		if (FAILED(device->CreateTexture2D(&d3d11Desc, nullptr, &m_texture)))
		{
			return;
		}

		const D3D11_RENDER_TARGET_VIEW_DESC rtDesc = m_desc.makeD3D11RTVDesc();

		if (FAILED(device->CreateRenderTargetView(m_texture.Get(), &rtDesc, &m_renderTargetView)))
		{
			return;
		}

		if (!createShaderResourceView(device))
		{
			return;
		}

		m_initialized = true;
	}
	*/
	Texture_D3D11::Texture_D3D11(ID3D11Device* device, const Image& image, const TextureDesc desc)
		: m_desc(image.size(),
			detail::IsSRGB(desc) ? TextureFormat::R8G8B8A8_Unorm_SRGB : TextureFormat::R8G8B8A8_Unorm,
			desc,
			1,
			1, 0,
			D3D11_USAGE_IMMUTABLE,
			D3D11_BIND_SHADER_RESOURCE,
			0, 0)
	{
		const D3D11_SUBRESOURCE_DATA initData{ image.data(), image.stride(), 0 };
		{
			const D3D11_TEXTURE2D_DESC d3d11Desc = m_desc.makeTEXTURE2D_DESC();
			if (HRESULT hr = device->CreateTexture2D(&d3d11Desc, &initData, &m_texture);
				FAILED(hr))
			{
				LOG_FAIL(U"❌ Texture_D3D11::Texture_D3D11() : Failed to create Texture2D. Error code: {0}"_fmt(ToHex(hr)));
				return;
			}
		}

		{
			const D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = m_desc.makeSHADER_RESOURCE_VIEW_DESC();
			if (HRESULT hr = device->CreateShaderResourceView(m_texture.Get(), &srvDesc, &m_shaderResourceView);
				FAILED(hr))
			{
				LOG_FAIL(U"❌ Texture_D3D11::Texture_D3D11() : Failed to create ShaderResourceView. Error code: {0}"_fmt(ToHex(hr)));
				return;
			}
		}

		m_initialized = true;
	}

	Texture_D3D11::Texture_D3D11(ID3D11Device* const device, const Image& image, const Array<Image>& mips, const TextureDesc desc)
		: m_desc(image.size(), 
			detail::IsSRGB(desc) ? TextureFormat::R8G8B8A8_Unorm_SRGB : TextureFormat::R8G8B8A8_Unorm,
			desc,
			static_cast<uint32>(mips.size() + 1),
			1, 0,
			D3D11_USAGE_IMMUTABLE,
			D3D11_BIND_SHADER_RESOURCE,
			0, 0)
	{
		Array<D3D11_SUBRESOURCE_DATA> initData(m_desc.mipLevels);
		initData[0] = { image.data(), image.stride(), 0 };
		for (uint32 i = 0; i < mips.size(); ++i)
		{
			initData[i + 1] = { mips[i].data(), mips[i].stride(), 0 };
		}
		{
			const D3D11_TEXTURE2D_DESC d3d11Desc = m_desc.makeTEXTURE2D_DESC();
			if (HRESULT hr = device->CreateTexture2D(&d3d11Desc, initData.data(), &m_texture);
				FAILED(hr))
			{
				LOG_FAIL(U"❌ Texture_D3D11::Texture_D3D11() : Failed to create Texture2D. Error code: {0}"_fmt(ToHex(hr)));
				return;
			}
		}

		{
			const D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = m_desc.makeSHADER_RESOURCE_VIEW_DESC();
			if (HRESULT hr = device->CreateShaderResourceView(m_texture.Get(), &srvDesc, &m_shaderResourceView);
				FAILED(hr))
			{
				LOG_FAIL(U"❌ Texture_D3D11::Texture_D3D11() : Failed to create ShaderResourceView. Error code: {0}"_fmt(ToHex(hr)));
				return;
			}
		}
			
		m_initialized = true;
	}

	bool Texture_D3D11::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const Texture2DDesc_D3D11& Texture_D3D11::getDesc() const noexcept
	{
		return m_desc;
	}

	ID3D11ShaderResourceView** Texture_D3D11::getSRVPtr()
	{
		return m_shaderResourceView.GetAddressOf();
	}

	ID3D11Texture2D* Texture_D3D11::getTexture()
	{
		return m_texture.Get();
	}


	/*
	void Texture_D3D11::clearRT(ID3D11DeviceContext* const context, const ColorF& color)
	{
		const ColorF clearColor = m_desc.isSRGB ? color.gamma(1.0 / 2.2) : color;

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

	bool Texture_D3D11::endResize(Render, ID3D11Device* const device, const Size& size, const uint32 multisampleCount)
	{
		*this = Texture_D3D11(Render{}, device, size, multisampleCount);

		return isInitialized();
	}
	*/
	bool Texture_D3D11::fill(ID3D11DeviceContext* context, const ColorF& color, const bool wait)
	{
		if (!m_textureStaging)
		{
			return false;
		}

		D3D11_MAPPED_SUBRESOURCE mapped;
		{
			if (FAILED(context->Map(m_textureStaging.Get(), 0, D3D11_MAP_WRITE, wait ? 0 : D3D11_MAP_FLAG_DO_NOT_WAIT, & mapped)))
			{
				return false;
			}

			if (!mapped.pData)
			{
				return false;
			}

			if (m_desc.stride() > mapped.RowPitch)
			{
				context->Unmap(m_textureStaging.Get(), 0);
				return false;
			}

			detail::FillByColor(mapped.pData, m_desc.size, mapped.RowPitch, color, m_desc.format);

			context->Unmap(m_textureStaging.Get(), 0);
		}

		context->CopyResource(m_texture.Get(), m_textureStaging.Get());

		return true;
	}

	bool Texture_D3D11::fillRegion(ID3D11DeviceContext* context, const ColorF& color, const Rect& rect)
	{
		if (!m_textureStaging)
		{
			return false;
		}

		D3D11_MAPPED_SUBRESOURCE mapped;
		{
			if (FAILED(context->Map(m_textureStaging.Get(), 0, D3D11_MAP_WRITE, 0, & mapped)))
			{
				return false;
			}

			if (!mapped.pData)
			{
				return false;
			}

			if (m_desc.stride() > mapped.RowPitch)
			{
				context->Unmap(m_textureStaging.Get(), 0);
				return false;
			}

			detail::FillRegionByColor(mapped.pData, m_desc.size, mapped.RowPitch, rect, color, m_desc.format);

			context->Unmap(m_textureStaging.Get(), 0);
		}

		context->CopyResource(m_texture.Get(), m_textureStaging.Get());

		return true;
	}

	bool Texture_D3D11::fill(ID3D11DeviceContext* context, const void* src, const uint32 stride, const bool wait)
	{
		if (!m_textureStaging)
		{
			return false;
		}

		D3D11_MAPPED_SUBRESOURCE mapped;
		{
			if (FAILED(context->Map(m_textureStaging.Get(), 0, D3D11_MAP_WRITE, wait ? 0 : D3D11_MAP_FLAG_DO_NOT_WAIT, &mapped)))
			{
				return false;
			}

			if (!mapped.pData)
			{
				return false;
			}

			if (m_desc.stride() > mapped.RowPitch)
			{
				context->Unmap(m_textureStaging.Get(), 0);
				return false;
			}

			detail::FillByImage(mapped.pData, m_desc.size, mapped.RowPitch, src, stride, m_desc.format);

			context->Unmap(m_textureStaging.Get(), 0);
		}

		context->CopyResource(m_texture.Get(), m_textureStaging.Get());

		return true;
	}

	bool Texture_D3D11::fillRegion(ID3D11DeviceContext* context, const void* src, uint32 stride, const Rect& rect, const bool wait)
	{
		if (!m_textureStaging)
		{
			return false;
		}

		D3D11_MAPPED_SUBRESOURCE mapped;
		{
			if (FAILED(context->Map(m_textureStaging.Get(), 0, D3D11_MAP_WRITE, wait ? 0 : D3D11_MAP_FLAG_DO_NOT_WAIT, &mapped)))
			{
				return false;
			}

			if (!mapped.pData)
			{
				return false;
			}

			if (m_desc.stride() > mapped.RowPitch)
			{
				context->Unmap(m_textureStaging.Get(), 0);
				return false;
			}

			detail::FillRegionByImage(mapped.pData, m_desc.size, mapped.RowPitch, src, stride, rect, m_desc.format);

			context->Unmap(m_textureStaging.Get(), 0);
		}

		const int32 leftX = std::clamp(rect.x, 0, m_desc.size.x);
		const int32 rightX = std::clamp(rect.x + rect.w, 0, m_desc.size.x);
		const int32 topY = std::clamp(rect.y, 0, m_desc.size.y);
		const int32 bottomY = std::clamp(rect.y + rect.h, 0, m_desc.size.y);
		const int32 width = (rightX - leftX);
		const int32 height = (bottomY - topY);

		if (width == 0 || height == 0)
		{
			return true;
		}

		D3D11_BOX box = CD3D11_BOX(leftX, topY, 0, rightX, bottomY, 1);
		context->CopySubresourceRegion(m_texture.Get(), 0, leftX, topY, 0, m_textureStaging.Get(), 0, &box);

		return true;
	}
}
