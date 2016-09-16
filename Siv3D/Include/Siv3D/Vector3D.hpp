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
# include <cmath>
# include <utility>
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "Hash.hpp"

namespace s3d
{
	/// <summary>
	/// 3 次元ベクトル
	/// </summary>
	template <class Type>
	struct Vector3D
	{
		using value_type = Type;

		value_type x, y, z;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Vector3D() noexcept = default;

		constexpr Vector3D(const Vector3D&) noexcept = default;

		template <class U, class V, class W>
		constexpr Vector3D(U _x, V _y, W _z) noexcept
			: x(static_cast<value_type>(_x))
			, y(static_cast<value_type>(_y))
			, z(static_cast<value_type>(_z)) {}

		constexpr Vector3D(value_type _x, value_type _y, value_type _z) noexcept
			: x(_x)
			, y(_y)
			, z(_z) {}

		template <class U>
		constexpr Vector3D(const Vector2D<value_type>& xy, U _z) noexcept
			: x(static_cast<value_type>(xy.x))
			, y(static_cast<value_type>(xy.y))
			, z(static_cast<value_type>(_z)) {}

		template <class U>
		constexpr Vector3D(U _x, const Vector2D<value_type>& yz) noexcept
			: x(static_cast<value_type>(_x))
			, y(static_cast<value_type>(yz.x))
			, z(static_cast<value_type>(yz.y)) {}

		template <class U>
		constexpr Vector3D(const Vector3D<U>& v) noexcept
			: x(static_cast<value_type>(v.x))
			, y(static_cast<value_type>(v.y))
			, z(static_cast<value_type>(v.z)) {}
	};
	
	using Float3	= Vector3D<float>;
	using Vec3		= Vector3D<double>;
}
