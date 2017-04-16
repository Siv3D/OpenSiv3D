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
# include "../../../Texture/D3D11/CTexture_D3D11.hpp"

# include "../../../Siv3DEngine.hpp"


namespace s3d
{
	class RenderTexture : public Texture
	{
	public:

		RenderTexture()
			: Texture() {}

		RenderTexture(const Size& size, uint32 multisampleCount = 1)
			: Texture(Texture::Render{}, size, multisampleCount) {}

		void clear(CTexture_D3D11* texture, const ColorF& color)
		{
			texture->clearRT(m_handle->getID(), color);
		}

		void beginResize(CTexture_D3D11* texture)
		{
			texture->beginResize(m_handle->getID());
		}

		bool endResize(CTexture_D3D11* texture, const Size& size, const uint32 multisampleCount)
		{
			return texture->endResizeRenderTexture(m_handle->getID(), size, multisampleCount);
		}
	};

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

		Size m_currentRenderTargetResolution = { 640, 480 };
		
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
	};
}

# endif
