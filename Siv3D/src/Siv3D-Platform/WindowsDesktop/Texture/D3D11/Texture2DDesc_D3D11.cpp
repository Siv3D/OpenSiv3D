//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "Texture2DDesc_D3D11.hpp"

namespace s3d
{
	Texture2DDesc_D3D11::Texture2DDesc_D3D11(const Size& _size, const TextureFormat _format, const TextureDesc _desc,
		const uint32 _mipLevels, const uint32 _multisampleCount, const uint32 _multismapleQuality,
		const D3D11_USAGE _usage, const uint32 _bindFlags,
		const uint32 _CPUAccessFlags, const uint32 _miscFlags) noexcept
		: size(_size)
		, format(_format)
		, desc(_desc)
		, mipLevels(_mipLevels)
		, multisampleCount(_multisampleCount)
		, multismapleQuality(_multismapleQuality)
		, usage(_usage)
		, bindFlags(_bindFlags)
		, CPUAccessFlags(_CPUAccessFlags)
		, miscFlags(_miscFlags) {}

	uint32 Texture2DDesc_D3D11::stride() const noexcept
	{
		return GetTextureFormatProperty(format).pixelSize * size.x;
	}

	bool Texture2DDesc_D3D11::isSRGB() const noexcept
	{
		return GetTextureFormatProperty(format).isSRGB;
	}

	D3D11_TEXTURE2D_DESC Texture2DDesc_D3D11::makeTEXTURE2D_DESC() const noexcept
	{
		return CD3D11_TEXTURE2D_DESC(DXGI_FORMAT(GetTextureFormatProperty(format).DXGIFormat), size.x, size.y, 1, mipLevels, bindFlags, usage,
			CPUAccessFlags, multisampleCount, multismapleQuality, miscFlags);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC Texture2DDesc_D3D11::makeSHADER_RESOURCE_VIEW_DESC() const noexcept
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT(GetTextureFormatProperty(format).DXGIFormat);
		srvDesc.ViewDimension = (multisampleCount == 1) ? D3D11_SRV_DIMENSION_TEXTURE2D : D3D11_SRV_DIMENSION_TEXTURE2DMS;
		srvDesc.Texture2D = { 0, mipLevels };
		return srvDesc;
	}

	D3D11_RENDER_TARGET_VIEW_DESC Texture2DDesc_D3D11::makeD3D11_RENDER_TARGET_VIEW_DESC() const noexcept
	{
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		rtvDesc.Format = DXGI_FORMAT(GetTextureFormatProperty(format).DXGIFormat);
		rtvDesc.ViewDimension = (multisampleCount == 1) ? D3D11_RTV_DIMENSION_TEXTURE2D : D3D11_RTV_DIMENSION_TEXTURE2DMS;
		rtvDesc.Texture2D = { 0 };
		return rtvDesc;
	}
}
