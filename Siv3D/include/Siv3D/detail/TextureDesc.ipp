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

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline constexpr bool HasMipMap(const TextureDesc desc) noexcept
		{
			return (desc == TextureDesc::Mipped)
				|| (desc == TextureDesc::MippedSRGB);
		}

		[[nodiscard]]
		inline constexpr bool IsSRGB(const TextureDesc desc) noexcept
		{
			return (desc == TextureDesc::UnmippedSRGB)
				|| (desc == TextureDesc::MippedSRGB);
		}

		[[nodiscard]]
		inline constexpr bool IsSDF(const TextureDesc desc) noexcept
		{
			return (desc == TextureDesc::SDF);
		}

		[[nodiscard]]
		inline constexpr TextureDesc MakeTextureDesc(const bool hasMipMap, const bool isSRGB)
		{
			if (hasMipMap)
			{
				return (isSRGB ? TextureDesc::MippedSRGB : TextureDesc::Mipped);
			}
			else
			{
				return (isSRGB ? TextureDesc::UnmippedSRGB : TextureDesc::Unmipped);
			}
		}
	}
}
