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

# include <Siv3D/Windows.hpp>
# include <wrl.h>
# include <d3d11.h>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/TextureFormat.hpp>

using namespace Microsoft::WRL;

namespace s3d
{
	namespace detail
	{
		[[nodiscard]] inline constexpr DXGI_FORMAT ToDXGIFormat(const TextureFormat format) noexcept
		{
			if (format == TextureFormat::R8G8B8A8_Unorm)
			{
				return DXGI_FORMAT_R8G8B8A8_UNORM;
			}
			else if (format == TextureFormat::R8G8B8A8_Unorm_SRGB)
			{
				return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
			}

			return DXGI_FORMAT_UNKNOWN;
		}

		[[nodiscard]] inline constexpr TextureFormat FromDXGIFormat(const DXGI_FORMAT format) noexcept
		{
			if (format == DXGI_FORMAT_R8G8B8A8_UNORM)
			{
				return TextureFormat::R8G8B8A8_Unorm;
			}
			else if (format == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB)
			{
				return TextureFormat::R8G8B8A8_Unorm_SRGB;
			}

			return TextureFormat::Unknown;
		}
	}

	struct D3D11Texture2DDesc
	{
		Size size = { 0, 0 };

		TextureFormat format = TextureFormat::Unknown;

		DXGI_FORMAT DXGIFormat = DXGI_FORMAT_UNKNOWN;

		TextureDesc desc = TextureDesc::Unmipped;

		// デフォルトは 1
		uint32 mipLevels = 1;

		// デフォルトは 1
		uint32 multisampleCount = 1;

		uint32 multismapleQuality = 0;

		D3D11_USAGE usage = D3D11_USAGE_DEFAULT;

		uint32 bindFlags = 0;

		uint32 CPUAccessFlags = 0;

		uint32 miscFlags = 0;

		bool isSRGB = false;

		constexpr D3D11Texture2DDesc() = default;

		constexpr D3D11Texture2DDesc(const Size& _size, TextureFormat _format, TextureDesc _desc,
			uint32 _mipLevels, uint32 _multisampleCount, uint32 _multismapleQuality,
			D3D11_USAGE _usage, uint32 _bindFlags,
			uint32 _CPUAccessFlags, uint32 _miscFlags) noexcept
			: size(_size)
			, format(_format)
			, DXGIFormat(detail::ToDXGIFormat(_format))
			, desc(_desc)
			, mipLevels(_mipLevels)
			, multisampleCount(_multisampleCount)
			, multismapleQuality(_multismapleQuality)
			, usage(_usage)
			, bindFlags(_bindFlags)
			, CPUAccessFlags(_CPUAccessFlags)
			, miscFlags(_miscFlags)
			, isSRGB(detail::IsSRGB(_format)) {}

		D3D11_TEXTURE2D_DESC makeD3D11Desc() const noexcept
		{
			return CD3D11_TEXTURE2D_DESC(DXGIFormat, size.x, size.y, 1, mipLevels, bindFlags, usage,
				CPUAccessFlags, multisampleCount, multismapleQuality, miscFlags);
		}

		D3D11_RENDER_TARGET_VIEW_DESC makeD3D11RTVDesc() const noexcept
		{
			D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
			rtvDesc.Format = DXGIFormat;
			rtvDesc.ViewDimension = (multisampleCount == 1) ? D3D11_RTV_DIMENSION_TEXTURE2D : D3D11_RTV_DIMENSION_TEXTURE2DMS;
			return rtvDesc;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC makeD3D11SRVDesc() const noexcept
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format = DXGIFormat;
			srvDesc.ViewDimension = (multisampleCount == 1) ? D3D11_SRV_DIMENSION_TEXTURE2D : D3D11_SRV_DIMENSION_TEXTURE2DMS;
			srvDesc.Texture2D = { 0, mipLevels };
			return srvDesc;
		}

		constexpr uint32 stride() const noexcept
		{
			return detail::GetPixelSize(format) * size.x;
		}
	};

	class Texture_D3D11
	{
	private:

		ComPtr<ID3D11Texture2D> m_texture;

		ComPtr<ID3D11Texture2D> m_textureStaging;

		ComPtr<ID3D11RenderTargetView> m_renderTargetView;

		ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;

		D3D11Texture2DDesc m_desc;

		bool m_initialized = false;

		bool createShaderResourceView(ID3D11Device* device);

	public:

		struct Null {};
		struct BackBuffer {};
		struct Dynamic {};
		struct Render {};

		Texture_D3D11() = default;

		Texture_D3D11(Null, ID3D11Device* device);

		Texture_D3D11(BackBuffer, ID3D11Device* device, IDXGISwapChain* swapChain);

		Texture_D3D11(Dynamic, ID3D11Device* device, const Size& size, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc);

		Texture_D3D11(Render, ID3D11Device* device, const Size& size, uint32 multisampleCount);

		Texture_D3D11(ID3D11Device* device, const Image& image, TextureDesc desc);

		Texture_D3D11(ID3D11Device* device, const Image& image, const Array<Image>& mipmaps, TextureDesc);

		bool isInitialized() const noexcept
		{
			return m_initialized;
		}

		const D3D11Texture2DDesc& getDesc() const noexcept
		{
			return m_desc;
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
