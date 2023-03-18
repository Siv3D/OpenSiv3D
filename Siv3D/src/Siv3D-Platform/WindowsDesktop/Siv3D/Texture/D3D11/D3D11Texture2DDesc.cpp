//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "D3D11Texture2DDesc.hpp"

namespace s3d
{
	D3D11Texture2DDesc::D3D11Texture2DDesc(const Size& _size, const TextureFormat& _format, const TextureDesc _desc,
		const uint32 _mipLevels, const uint32 _multisampleCount, const uint32 _multismapleQuality,
		const D3D11_USAGE _usage, const uint32 _bindFlags,
		const uint32 _CPUAccessFlags, const uint32 _miscFlags) noexcept
		: size{ _size }
		, format{ _format }
		, desc{ _desc }
		, mipLevels{ _mipLevels }
		, multisampleCount{ _multisampleCount }
		, multismapleQuality{ _multismapleQuality }
		, usage{ _usage }
		, bindFlags{ _bindFlags }
		, CPUAccessFlags{ _CPUAccessFlags }
		, miscFlags{ _miscFlags } {}

	uint32 D3D11Texture2DDesc::stride() const noexcept
	{
		return (format.pixelSize() * size.x);
	}

	bool D3D11Texture2DDesc::isSRGB() const noexcept
	{
		return format.isSRGB();
	}

	D3D11_TEXTURE2D_DESC D3D11Texture2DDesc::makeTEXTURE2D_DESC() const noexcept
	{
		return CD3D11_TEXTURE2D_DESC(DXGI_FORMAT(format.DXGIFormat()), size.x, size.y, 1, mipLevels, bindFlags, usage,
			CPUAccessFlags, multisampleCount, multismapleQuality, miscFlags);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC D3D11Texture2DDesc::makeSHADER_RESOURCE_VIEW_DESC() const noexcept
	{
		return D3D11_SHADER_RESOURCE_VIEW_DESC{
			.Format			= DXGI_FORMAT(format.DXGIFormat()),
			.ViewDimension	= ((multisampleCount == 1) ? D3D11_SRV_DIMENSION_TEXTURE2D : D3D11_SRV_DIMENSION_TEXTURE2DMS),
			.Texture2D		= { 0, mipLevels }
		};
	}

	D3D11_RENDER_TARGET_VIEW_DESC D3D11Texture2DDesc::makeD3D11_RENDER_TARGET_VIEW_DESC() const noexcept
	{
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc{
			.Format			= DXGI_FORMAT(format.DXGIFormat()),
			.ViewDimension = ((multisampleCount == 1) ? D3D11_RTV_DIMENSION_TEXTURE2D : D3D11_RTV_DIMENSION_TEXTURE2DMS)
		};

		if (rtvDesc.ViewDimension == D3D11_RTV_DIMENSION_TEXTURE2D)
		{
			rtvDesc.Texture2D = { 0 };
		}

		return rtvDesc;
	}
}
