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
	template <class Type>
	inline bool IsNaN([[maybe_unused]] const Type value) noexcept
	{
		if constexpr (std::is_floating_point_v<Type>)
		{
			return std::isnan(value);
		}
		else
		{
			return false;
		}
	}

	template <class Type>
	inline bool IsFinite([[maybe_unused]] const Type value) noexcept
	{
		if constexpr (std::is_floating_point_v<Type>)
		{
			return std::isfinite(value);
		}
		else
		{
			return true;
		}
	}

	template <class Type>
	inline bool IsInfinity([[maybe_unused]] const Type value) noexcept
	{
		if constexpr (std::is_floating_point_v<Type>)
		{
			return std::isinf(value);
		}
		else
		{
			return false;
		}
	}
}
