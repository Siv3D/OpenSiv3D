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

# include "CTexture_D3D11.hpp"
# include <Siv3D/Image.hpp>
# include <Siv3D/ImageProcessing.hpp>

namespace s3d
{
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

		return true;
	}

	Texture::IDType CTexture_D3D11::createFromBackBuffer()
	{
		const auto texture = std::make_shared<Texture_D3D11>(Texture_D3D11::BackBuffer{}, m_device, m_swapChain);

		if (!texture->isInitialized())
		{
			return Texture::NullHandleID;
		}

		return m_textures.add(texture);
	}

	Texture::IDType CTexture_D3D11::create(const Image& image, const TextureDesc desc)
	{
		if (!image)
		{
			return Texture::NullHandleID;
		}

		const auto texture = std::make_shared<Texture_D3D11>(m_device, image, desc);

		if (!texture->isInitialized())
		{
			return Texture::NullHandleID;
		}

		return m_textures.add(texture);
	}

	Texture::IDType CTexture_D3D11::create(const Image& image, const Array<Image>& mipmaps, TextureDesc desc)
	{
		if (!image)
		{
			return Texture::NullHandleID;
		}

		const auto texture = std::make_shared<Texture_D3D11>(m_device, image, mipmaps, desc);

		if (!texture->isInitialized())
		{
			return Texture::NullHandleID;
		}

		return m_textures.add(texture);
	}

	Texture::IDType CTexture_D3D11::createRT(const Size& size, const uint32 multisampleCount)
	{
		const auto texture = std::make_shared<Texture_D3D11>(Texture_D3D11::Render{}, m_device, size, multisampleCount);

		if (!texture->isInitialized())
		{
			return Texture::NullHandleID;
		}

		return m_textures.add(texture);
	}

	void CTexture_D3D11::release(const Texture::IDType handleID)
	{
		m_textures.erase(handleID);
	}

	Size CTexture_D3D11::getSize(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getSize();
	}

	void CTexture_D3D11::clearRT(Texture::IDType handleID, const ColorF& color)
	{
		m_textures[handleID]->clearRT(m_context, color);
	}

	void CTexture_D3D11::beginResize(const Texture::IDType handleID)
	{
		m_textures[handleID]->beginResize();
	}

	bool CTexture_D3D11::endResizeBackBuffer(const Texture::IDType handleID)
	{
		return m_textures[handleID]->endResize(Texture_D3D11::BackBuffer{}, m_device, m_swapChain);
	}

	bool CTexture_D3D11::endResizeRT(const Texture::IDType handleID, const Size& size, const uint32 multisampleCount)
	{
		return m_textures[handleID]->endResize(Texture_D3D11::Render{}, m_device, size, multisampleCount);
	}

	ID3D11Texture2D* CTexture_D3D11::getTexture(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getTexture();
	}

	ID3D11RenderTargetView* CTexture_D3D11::getRTV(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getRTV();
	}



	void CTexture_D3D11::setPS(const uint32 slot, const Texture::IDType handleID)
	{
		m_context->PSSetShaderResources(slot, 1, m_textures[handleID]->getSRVPtr());
	}
}

# endif
