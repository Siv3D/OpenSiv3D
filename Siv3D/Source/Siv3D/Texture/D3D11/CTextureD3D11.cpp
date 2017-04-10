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

# include "CTextureD3D11.hpp"

namespace s3d
{
	CTextureD3D11::~CTextureD3D11()
	{
		m_textures.destroy();
	}

	bool CTextureD3D11::init(ID3D11Device* const device, IDXGISwapChain* const swapChain)
	{
		m_device = device;
		m_swapChain = swapChain;

		const auto nullTexture = std::make_shared<Texture_D3D11>(Texture_D3D11::Null{}, device);

		if (!nullTexture->isInitialized())
		{
			return false;
		}

		m_textures.setNullData(nullTexture);

		return true;
	}

	Texture::IDType CTextureD3D11::createFromBackBuffer()
	{
		const auto texture = std::make_shared<Texture_D3D11>(Texture_D3D11::BackBuffer{}, m_device, m_swapChain);

		if (!texture->isInitialized())
		{
			return 0;
		}

		return m_textures.add(texture);
	}

	void CTextureD3D11::release(const Texture::IDType handleID)
	{
		m_textures.erase(handleID);
	}

	Size CTextureD3D11::getSize(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getSize();
	}

	ID3D11RenderTargetView* CTextureD3D11::getRTV(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getRTV();
	}
}

# endif
