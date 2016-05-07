//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	struct Point
	{
		using value_type = int32;

		value_type x, y;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Point() noexcept = default;

		constexpr Point(int32 _x, int32 _y) noexcept
			: x(_x)
			, y(_y) {}

		template <class U, class V>
		constexpr Point(U _x, V _y)
			: x(static_cast<value_type>(_x))
			, y(static_cast<value_type>(_y)) {}
	};

	using Size = Point;
}
