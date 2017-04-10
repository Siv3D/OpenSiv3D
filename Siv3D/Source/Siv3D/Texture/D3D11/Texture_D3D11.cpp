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

# include "../../Siv3DEngine.hpp"
# include "Texture_D3D11.hpp"

namespace s3d
{
	Texture_D3D11 Texture_D3D11::CreateBackBuffer(ID3D11Device* const device, IDXGISwapChain* const swapChain)
	{
		Texture_D3D11 texture;

		if (FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &texture.m_texture)))
		{
			return Texture_D3D11();
		}

		texture.m_texture->GetDesc(&texture.m_desc);

		if (FAILED(device->CreateRenderTargetView(texture.m_texture.Get(), nullptr, &texture.m_renderTargetView)))
		{
			return Texture_D3D11();
		}

		texture.m_initialized = true;

		return texture;
	}
}
