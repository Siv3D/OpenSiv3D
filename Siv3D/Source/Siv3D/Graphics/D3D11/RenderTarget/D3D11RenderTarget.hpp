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

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <wrl.h>
using namespace Microsoft::WRL;
# include <d3d11.h>
# include <Siv3D/Color.hpp>
# include "../../../Texture/D3D11/BackBufferTexture.hpp"
# include "../../../Texture/D3D11/CTextureD3D11.hpp"

namespace s3d
{
	class D3D11RenderTarget
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		IDXGISwapChain* m_swapChain = nullptr;

		CTextureD3D11* m_texture;

		ColorF m_clearColor = Color(11, 22, 33);

		BackBufferTexture m_backBuffer;
		
	public:

		D3D11RenderTarget(ID3D11Device* device, ID3D11DeviceContext* context, IDXGISwapChain* swapChain, CTextureD3D11* texture);

		~D3D11RenderTarget();

		bool init();

		void setClearColor(const ColorF& color);

		void clear();

		void beginResize();

		bool endResize(const Size& size);
	};
}

# endif
