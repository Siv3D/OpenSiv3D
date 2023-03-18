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
	inline constexpr FormatData::DecimalPlaces DecimalPlaces(const int32 width) noexcept
	{
		return FormatData::DecimalPlaces(width);
	}

	inline namespace Literals
	{
		inline namespace DecimalPlaceLiterals
		{
			[[nodiscard]]
			constexpr FormatData::DecimalPlaces operator ""_dp(const unsigned long long width) noexcept
			{
				return DecimalPlaces(static_cast<int32>(width));
			}
		}
	}
}
