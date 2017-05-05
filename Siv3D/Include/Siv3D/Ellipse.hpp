//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "Circle.hpp"
# include "Rectangle.hpp"

namespace s3d
{
	struct Ellipse
	{
		using position_type = Vec2;

		using size_type = position_type::value_type;

		using value_type = position_type::value_type;

		S3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			/// <summary>
			/// 楕円の中心座標
			/// </summary>
			position_type center;

			position_type axis;

			struct
			{
				value_type x;

				value_type y;

				value_type a;

				value_type b;
			};
		};

		S3D_DISABLE_MSVC_WARNINGS_POP()
	
		Ellipse() = default;

		explicit constexpr Ellipse(double _r) noexcept
			: center(0, 0)
			, axis(_r, _r) {}

		constexpr Ellipse(double _a, double _b) noexcept
			: center(0, 0)
			, axis(_a, _b) {}

		constexpr Ellipse(double _x, double _y, double _r) noexcept
			: center(_x, _y)
			, axis(_r, _r) {}

		constexpr Ellipse(double _x, double _y, double _a, double _b) noexcept
			: center(_x, _y)
			, axis(_a, _b) {}

		explicit constexpr Ellipse(const Vec2& _center) noexcept
			: center(_center)
			, axis(0, 0) {}

		constexpr Ellipse(const Vec2& _center, double _r) noexcept
			: center(_center)
			, axis(_r, _r) {}

		constexpr Ellipse(const Vec2& _center, double _a, double _b) noexcept
			: center(_center)
			, axis(_a, _b) {}

		constexpr Ellipse(double _x, double _y, const Vec2& _axis) noexcept
			: center(_x, _y)
			, axis(_axis) {}

		constexpr Ellipse(const Vec2& _center, const Vec2& _axis) noexcept
			: center(_center)
			, axis(_axis) {}

		explicit constexpr Ellipse(const Circle& circle) noexcept
			: center(circle.center)
			, axis(circle.r, circle.r) {}

		explicit constexpr Ellipse(const RectF& rect) noexcept
			: center(rect.center())
			, axis(rect.w * 0.5, rect.h * 0.5) {}

		constexpr bool operator ==(const Ellipse& ellipse) const noexcept
		{
			return center == ellipse.center
				&& axis == ellipse.axis;
		}

		constexpr bool operator !=(const Ellipse& ellipse) const noexcept
		{
			return !(*this == ellipse);
		}

		constexpr Ellipse& set(value_type _x, value_type _y, size_type _a, size_type _b) noexcept
		{
			center.set(_x, _y);
			axis.set(_a, _b);
			return *this;
		}

		constexpr Ellipse& set(double _x, double _y, double _r) noexcept
		{
			return set(_x, _y, _r, _r);
		}

		constexpr Ellipse& set(const Vec2& _center, double _r) noexcept
		{
			return set(_center.x, _center.y, _r, _r);
		}

		constexpr Ellipse& set(const Vec2& _center, double _a, double _b) noexcept
		{
			return set(_center.x, _center.y, _a, _b);
		}

		constexpr Ellipse& set(double _x, double _y, const Vec2& _axis) noexcept
		{
			return set(_x, _y, _axis.x, _axis.y);
		}

		constexpr Ellipse& set(const Vec2& _center, const Vec2& _axis) noexcept
		{
			return set(_center.x, _center.y, _axis.x, _axis.y);
		}

		constexpr Ellipse& set(const Circle& circle) noexcept
		{
			return set(circle.x, circle.y, circle.r, circle.r);
		}

		constexpr Ellipse& set(const RectF& rect) noexcept
		{
			return set(rect.center(), rect.w * 0.5, rect.h * 0.5);
		}

		constexpr Ellipse& set(const Ellipse& ellipse) noexcept
		{
			return *this = ellipse;
		}

		constexpr Ellipse& setCenter(value_type _x, value_type _y) noexcept
		{
			center.set(_x, _y);
			return *this;
		}

		constexpr Ellipse& setCenter(const position_type& _center) noexcept
		{
			return setCenter(_center.x, _center.y);
		}

		constexpr Ellipse& setPos(value_type _x, value_type _y) noexcept
		{
			return setCenter(_x, _y);
		}

		constexpr Ellipse& setPos(const position_type& _center) noexcept
		{
			return setCenter(_center.x, _center.y);
		}

		constexpr Ellipse movedBy(value_type _x, value_type _y) const noexcept
		{
			return{ center.movedBy(_x, _y), a, b };
		}

		constexpr Ellipse movedBy(const position_type& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}

		constexpr Ellipse& moveBy(value_type _x, value_type _y) noexcept
		{
			center.moveBy(_x, _y);
			return *this;
		}

		constexpr Ellipse& moveBy(const position_type& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		constexpr Ellipse stretched(value_type size) const noexcept
		{
			return Ellipse(center, a + size, b + size);
		}

		constexpr Ellipse stretched(double _x, double _y) const noexcept
		{
			return Ellipse(center, a + _x, b + _y);
		}

		constexpr Ellipse scaled(double s) const noexcept
		{
			return Ellipse(center, a * s, b * s);
		}

		constexpr Ellipse scaled(double sx, double sy) const noexcept
		{
			return Ellipse(center, a * sx, b * sy);
		}

		constexpr value_type area() const noexcept
		{
			return a * b * Math::Pi;
		}

		template <class Shape2DType>
		bool intersects(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::Intersect(*this, shape)))
		{
			return Geometry2D::Intersect(*this, shape);
		}

		template <class Shape2DType>
		bool contains(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::Contains(*this, shape)))
		{
			return Geometry2D::Contains(*this, shape);
		}

		bool leftClicked() const;

		bool leftPressed() const;

		bool leftReleased() const;

		bool rightClicked() const;

		bool rightPressed() const;

		bool rightReleased() const;

		bool mouseOver() const;
	};
}
