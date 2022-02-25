//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
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
		inline constexpr bool IsMipped(const TextureDesc desc) noexcept
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
	}
}
