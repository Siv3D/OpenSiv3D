//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "Circle.hpp"
# include "Rectangle.hpp"

namespace s3d
{
	/// @brief 楕円
	struct Ellipse
	{
		using position_type	= Vec2;

		using size_type		= position_type::value_type;

		using value_type	= position_type::value_type;

		SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			/// @brief 楕円の中心座標
			position_type center;

			struct
			{
				/// @brief 楕円の中心の X 座標
				value_type x;

				/// @brief 楕円の中心の Y 座標
				value_type y;
			};
		};

		/// @brief 楕円の X 軸上の半径
		value_type a;

		/// @brief 楕円の Y 軸上の半径
		value_type b;

		SIV3D_DISABLE_MSVC_WARNINGS_POP()

		SIV3D_NODISCARD_CXX20
		Ellipse() = default;

		explicit constexpr Ellipse(double _r) noexcept;

		constexpr Ellipse(double _a, double _b) noexcept;

		constexpr Ellipse(double _x, double _y, double _r) noexcept;

		constexpr Ellipse(double _x, double _y, double _a, double _b) noexcept;

		explicit constexpr Ellipse(Vec2 _center) noexcept;

		constexpr Ellipse(const Vec2& _center, double _r) noexcept;

		constexpr Ellipse(const Vec2& _center, double _a, double _b) noexcept;

		constexpr Ellipse(double _x, double _y, const Vec2& _axis) noexcept;

		constexpr Ellipse(const Vec2& _center, const Vec2& _axis) noexcept;

		explicit constexpr Ellipse(const Circle& circle) noexcept;

		explicit constexpr Ellipse(const RectF& rect) noexcept;
	};
}
