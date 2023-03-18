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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include <Siv3D/TextureFormat.hpp>
# include <Siv3D/TextureDesc.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	struct D3D11Texture2DDesc
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

		SIV3D_NODISCARD_CXX20
		D3D11Texture2DDesc() = default;

		SIV3D_NODISCARD_CXX20
		D3D11Texture2DDesc(const Size& _size, const TextureFormat& _format, TextureDesc _desc,
			uint32 _mipLevels, uint32 _multisampleCount, uint32 _multismapleQuality,
			D3D11_USAGE _usage, uint32 _bindFlags,
			uint32 _CPUAccessFlags, uint32 _miscFlags) noexcept;

		[[nodiscard]]
		uint32 stride() const noexcept;

		[[nodiscard]]
		bool isSRGB() const noexcept;

		[[nodiscard]]
		D3D11_TEXTURE2D_DESC makeTEXTURE2D_DESC() const noexcept;

		[[nodiscard]]
		D3D11_SHADER_RESOURCE_VIEW_DESC makeSHADER_RESOURCE_VIEW_DESC() const noexcept;

		[[nodiscard]]
		D3D11_RENDER_TARGET_VIEW_DESC makeD3D11_RENDER_TARGET_VIEW_DESC() const noexcept;
	};
}
