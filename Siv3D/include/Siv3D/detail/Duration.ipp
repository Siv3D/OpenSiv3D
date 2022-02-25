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
	template <class DurationTo, class DurationFrom>
	inline constexpr DurationTo DurationCast(const DurationFrom& duration) noexcept
	{
		return std::chrono::duration_cast<DurationTo>(duration);
	}

	inline namespace Literals
	{
		inline namespace DurationLiterals
		{
			inline constexpr Days operator ""_d(const unsigned long long days)
			{
				return Days(days);
			}

			inline constexpr DaysF operator ""_d(const long double days)
			{
				return DaysF(days);
			}
		}
	}
}
