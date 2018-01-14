//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Windows.hpp>
# include <d3d11.h>
# include <Siv3D/Color.hpp>
# include <Siv3D/RenderTexture.hpp>
# include "../../../Texture/D3D11/BackBufferTexture.hpp"
# include "../../../Texture/D3D11/CTexture_D3D11.hpp"
# include "../../../Siv3DEngine.hpp"

namespace s3d
{
	class D3D11RenderTarget
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		IDXGISwapChain* m_swapChain = nullptr;

		CTexture_D3D11* m_texture = nullptr;

		DXGI_SAMPLE_DESC m_sample2D = { 1, 0 };

		ColorF m_clearColor = Color(11, 22, 33);

		BackBufferTexture m_backBuffer;

		RenderTexture m_rt2D;

		Size m_currentBackBufferResolution = { 640, 480 };
		
	public:

		D3D11RenderTarget(ID3D11Device* device, ID3D11DeviceContext* context, IDXGISwapChain* swapChain, CTexture_D3D11* texture, const DXGI_SAMPLE_DESC& sample2D);

		~D3D11RenderTarget();

		bool init();

		void setClearColor(const ColorF& color);

		void clear();

		void resolve();

		void beginResize();

		bool endResize(const Size& size);

		const Size& getCurrentRenderTargetSize() const;

		void setRenderTargetView(ID3D11RenderTargetView* rtv);

		const BackBufferTexture& getBackBufferTexture() const;

		const RenderTexture& getBackBuffer2D() const;
	};
}

# endif
