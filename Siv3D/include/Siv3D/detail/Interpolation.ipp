//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	namespace Math
	{
		template <class T, class U, class V>
		inline constexpr auto Lerp(const T& v1, const U& v2, V f) noexcept
		{
			if constexpr (detail::HasLerp_v<T>)
			{
				return v1.lerp(v2, f);
			}
			else
			{
				return (v1 + (v2 - v1) * f);
			}
		}

		inline constexpr double InvLerp(double a, double b, double value) noexcept
		{
			return (value - a) / (b - a);
		}
	}
}
