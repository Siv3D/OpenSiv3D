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
# include <d3d11.h>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/TextureFormat.hpp>

using namespace Microsoft::WRL;

namespace s3d
{
	class Texture_D3D11
	{
	private:

		ComPtr<ID3D11Texture2D> m_texture;

		ComPtr<ID3D11Texture2D> m_textureStaging;

		ComPtr<ID3D11RenderTargetView> m_renderTargetView;

		ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;

		D3D11_TEXTURE2D_DESC m_desc{};

		D3D11_RENDER_TARGET_VIEW_DESC m_rtDesc{};

		D3D11_SHADER_RESOURCE_VIEW_DESC m_srvDesc{};

		TextureFormat m_format = TextureFormat::Unknown;

		bool m_initialized = false;

		bool isSRGB() const
		{
			// [Siv3D ToDo]
			return false;
		}

	public:

		struct Null {};
		struct BackBuffer {};
		struct Dynamic {};
		struct Render {};

		Texture_D3D11() = default;

		Texture_D3D11(Null, ID3D11Device* device);

		Texture_D3D11(BackBuffer, ID3D11Device* device, IDXGISwapChain* swapChain);

		Texture_D3D11(Dynamic, ID3D11Device* device, const Size& size, const void* pData, uint32 stride, TextureFormat format);

		Texture_D3D11(Render, ID3D11Device* device, const Size& size, uint32 multisampleCount);

		Texture_D3D11(ID3D11Device* device, const Image& image, TextureDesc desc);

		Texture_D3D11(ID3D11Device* device, const Image& image, const Array<Image>& mipmaps, TextureDesc);

		bool isInitialized() const noexcept
		{
			return m_initialized;
		}

		Size getSize() const
		{
			return{ m_desc.Width, m_desc.Height };
		}

		ID3D11Texture2D* getTexture()
		{
			return m_texture.Get();
		}

		ID3D11RenderTargetView* getRTV()
		{
			return m_renderTargetView.Get();
		}

		ID3D11ShaderResourceView** getSRVPtr()
		{
			return m_shaderResourceView.GetAddressOf();
		}

		void clearRT(ID3D11DeviceContext* context, const ColorF& color);

		void beginResize();

		bool endResize(BackBuffer, ID3D11Device* device, IDXGISwapChain* swapChain);

		bool endResize(Render, ID3D11Device* device, const Size& size, uint32 multisampleCount);


		bool fill(ID3D11DeviceContext* context, const ColorF& color, bool wait);

		bool fill(ID3D11DeviceContext* context, const void* src, uint32 stride, bool wait);
	};
}

# endif
