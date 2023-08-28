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

# include <ThirdParty/libmorton/morton.h>
# include <Siv3D/Morton.hpp>

namespace s3d
{
	namespace Morton
	{
		Morton32 Encode2D32(const uint16 x, const uint16 y) noexcept
		{
			return libmorton::morton2D_32_encode(x, y);
		}

		Morton64 Encode2D64(const uint32 x, const uint32 y) noexcept
		{
			return libmorton::morton2D_64_encode(x, y);
		}

		Morton32 Encode2D32(const Point pos) noexcept
		{
			return libmorton::morton2D_32_encode(static_cast<std::uint_fast16_t>(pos.x), static_cast<std::uint_fast16_t>(pos.y));
		}

		Morton64 Encode2D64(const Point pos) noexcept
		{
			return libmorton::morton2D_64_encode(static_cast<std::uint_fast32_t>(pos.x), static_cast<std::uint_fast32_t>(pos.y));
		}

		Point Decode2D32(const Morton32 morton) noexcept
		{
			std::uint_fast16_t x, y;
			libmorton::morton2D_32_decode(morton, x, y);
			return{ x, y };
		}

		Point Decode2D64(const Morton64 morton) noexcept
		{
			std::uint_fast32_t x, y;
			libmorton::morton2D_64_decode(morton, x, y);
			return{ x, y };
		}
	}
}
