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
# include "Fwd.hpp"

namespace s3d
{
	enum class TextureFormat
	{
		Unknown,

		R8G8B8A8_Unorm,

		R8G8B8A8_Unorm_SRGB,
	};

	namespace detail
	{
		[[nodiscard]] constexpr bool IsSRGB(const TextureFormat format) noexcept
		{
			return (format == TextureFormat::R8G8B8A8_Unorm_SRGB);
		}

		[[nodiscard]] inline constexpr uint32 GetPixelSize(const TextureFormat format) noexcept
		{
			if (format == TextureFormat::R8G8B8A8_Unorm)
			{
				return 4;
			}
			else if (format == TextureFormat::R8G8B8A8_Unorm_SRGB)
			{
				return 4;
			}

			return 0;
		}
	}
}
