﻿//-----------------------------------------------
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

# include "CTexture_D3D11.hpp"
# include <Siv3D/Image.hpp>
# include <Siv3D/ImageProcessing.hpp>
# include <Siv3D/TextureFormat.hpp>

namespace s3d
{
	namespace detail
	{
		Array<Byte> GenerateInitialColorBuffer(const Size& size, const ColorF& color, const TextureFormat format)
		{
			const size_t num_pixels = size.x * size.y;

			if (format == TextureFormat::R8G8B8A8_Unorm)
			{
				Array<Byte> bytes(num_pixels * sizeof(uint32));

				const uint32 value = Color(color).asUint32();

				uint32* pDst = static_cast<uint32*>(static_cast<void*>(bytes.data()));

				for (size_t i = 0; i < num_pixels; ++i)
				{
					*pDst++ = value;
				}

				return bytes;
			}

			return Array<Byte>();
		}
	}

	CTexture_D3D11::~CTexture_D3D11()
	{
		m_textures.destroy();
	}

	bool CTexture_D3D11::init(ID3D11Device* const device, ID3D11DeviceContext* const context, IDXGISwapChain* const swapChain)
	{
		m_device = device;
		m_context = context;
		m_swapChain = swapChain;

		const auto nullTexture = std::make_shared<Texture_D3D11>(Texture_D3D11::Null{}, device);

		if (!nullTexture->isInitialized())
		{
			return false;
		}

		m_textures.setNullData(nullTexture);

		LOG_INFO(U"ℹ️ Texture initialized");

		return true;
	}

	TextureID CTexture_D3D11::createFromBackBuffer()
	{
		const auto texture = std::make_shared<Texture_D3D11>(Texture_D3D11::BackBuffer{}, m_device, m_swapChain);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		return m_textures.add(texture, U"(Back buffer)");
	}

	TextureID CTexture_D3D11::create(const Image& image, const TextureDesc desc)
	{
		if (!image)
		{
			return TextureID::NullAsset();
		}

		const auto texture = std::make_shared<Texture_D3D11>(m_device, image, desc);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		return m_textures.add(texture, U"(size:{0}x{1})"_fmt(image.width(), image.height()));
	}

	TextureID CTexture_D3D11::create(const Image& image, const Array<Image>& mipmaps, TextureDesc desc)
	{
		if (!image)
		{
			return TextureID::NullAsset();
		}

		const auto texture = std::make_shared<Texture_D3D11>(m_device, image, mipmaps, desc);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		return m_textures.add(texture, U"(size:{0}x{1})"_fmt(image.width(), image.height()));
	}

	TextureID CTexture_D3D11::createDynamic(const Size& size, const void* pData, const uint32 stride, const TextureFormat format, const TextureDesc desc)
	{
		const auto texture = std::make_shared<Texture_D3D11>(Texture_D3D11::Dynamic{}, m_device, size, pData, stride, format, desc);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		return m_textures.add(texture, U"(Dynamic, size:{0}x{1})"_fmt(size.x, size.y));
	}

	TextureID CTexture_D3D11::createDynamic(const Size& size, const ColorF& color, const TextureFormat format, const TextureDesc desc)
	{
		const Array<Byte> initialData = detail::GenerateInitialColorBuffer(size, color, format);

		return createDynamic(size, initialData.data(), static_cast<uint32>(initialData.size() / size.y), format, desc);
	}

	TextureID CTexture_D3D11::createRT(const Size& size, const uint32 multisampleCount)
	{
		const auto texture = std::make_shared<Texture_D3D11>(Texture_D3D11::Render{}, m_device, size, multisampleCount);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		return m_textures.add(texture, U"(Render target, size:{0}x{1})"_fmt(size.x, size.y));
	}

	void CTexture_D3D11::release(const TextureID handleID)
	{
		m_textures.erase(handleID);
	}

	Size CTexture_D3D11::getSize(const TextureID handleID)
	{
		return m_textures[handleID]->getDesc().size;
	}

	TextureDesc CTexture_D3D11::getDesc(const TextureID handleID)
	{
		return m_textures[handleID]->getDesc().desc;
	}

	void CTexture_D3D11::clearRT(const TextureID handleID, const ColorF& color)
	{
		m_textures[handleID]->clearRT(m_context, color);
	}

	void CTexture_D3D11::beginResize(const TextureID handleID)
	{
		m_textures[handleID]->beginResize();
	}

	bool CTexture_D3D11::endResizeBackBuffer(const TextureID handleID)
	{
		return m_textures[handleID]->endResize(Texture_D3D11::BackBuffer{}, m_device, m_swapChain);
	}

	bool CTexture_D3D11::endResizeRT(const TextureID handleID, const Size& size, const uint32 multisampleCount)
	{
		return m_textures[handleID]->endResize(Texture_D3D11::Render{}, m_device, size, multisampleCount);
	}

	ID3D11Texture2D* CTexture_D3D11::getTexture(const TextureID handleID)
	{
		return m_textures[handleID]->getTexture();
	}

	ID3D11RenderTargetView* CTexture_D3D11::getRTV(const TextureID handleID)
	{
		return m_textures[handleID]->getRTV();
	}



	void CTexture_D3D11::setPS(const uint32 slot, const TextureID handleID)
	{
		m_context->PSSetShaderResources(slot, 1, m_textures[handleID]->getSRVPtr());
	}

	bool CTexture_D3D11::fill(const TextureID handleID, const ColorF& color, const bool wait)
	{
		return m_textures[handleID]->fill(m_context, color, wait);
	}

	bool CTexture_D3D11::fill(const TextureID handleID, const void* const src, const uint32 stride, const bool wait)
	{
		return m_textures[handleID]->fill(m_context, src, stride, wait);
	}
}

# endif
