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
# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <wrl.h>
# include <d3d11.h>

using namespace Microsoft::WRL;

namespace s3d
{
	class Texture_D3D11
	{
	private:

		ComPtr<ID3D11Texture2D> m_texture;

		ComPtr<ID3D11RenderTargetView> m_renderTargetView;

		D3D11_TEXTURE2D_DESC m_desc{};

		bool m_initialized = false;

	public:

		Texture_D3D11() = default;

		static Texture_D3D11 CreateBackBuffer(ID3D11Device* device, IDXGISwapChain* swapChain);
	};
}
