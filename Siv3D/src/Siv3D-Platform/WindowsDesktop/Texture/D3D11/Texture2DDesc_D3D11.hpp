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

# pragma once
# include <Siv3D/Windows.hpp>
# include <d3d11.h>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/TextureFormat.hpp>
# include <Siv3D/TextureDesc.hpp>

namespace s3d
{
	struct Texture2DDesc_D3D11
	{
		Size size = { 0, 0 };

		TextureFormat format = TextureFormat::Unknown;

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

		Texture2DDesc_D3D11() = default;

		Texture2DDesc_D3D11(const Size& _size, const TextureFormat& _format, TextureDesc _desc,
			uint32 _mipLevels, uint32 _multisampleCount, uint32 _multismapleQuality,
			D3D11_USAGE _usage, uint32 _bindFlags,
			uint32 _CPUAccessFlags, uint32 _miscFlags) noexcept;

		uint32 stride() const noexcept;

		bool isSRGB() const noexcept;

		D3D11_TEXTURE2D_DESC makeTEXTURE2D_DESC() const noexcept;

		D3D11_SHADER_RESOURCE_VIEW_DESC makeSHADER_RESOURCE_VIEW_DESC() const noexcept;

		D3D11_RENDER_TARGET_VIEW_DESC makeD3D11_RENDER_TARGET_VIEW_DESC() const noexcept;
	};
}
