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
# include "Rectangle.hpp"
# include "Math.hpp"

namespace s3d
{
	struct RoundRect
	{
		using position_type = RectF::position_type;

		using size_type = RectF::size_type;

		using value_type = position_type::value_type;

		S3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			struct
			{
				RectF rect;
			};
			
			struct
			{
				value_type x, y, w, h;
			};
		};

		value_type r;

		S3D_DISABLE_MSVC_WARNINGS_POP()

		RoundRect() = default;

		constexpr RoundRect(value_type _x, value_type _y, value_type _w, value_type _h, value_type _r) noexcept
			: rect(_x, _y, _w, _h)
			, r(_r) {}

		constexpr RoundRect(const position_type& pos, value_type _w, value_type _h, value_type _r) noexcept
			: rect(pos, _w, _h)
			, r(_r) {}

		constexpr RoundRect(value_type _x, value_type _y, const size_type& size, value_type _r) noexcept
			: rect(_x, _y, size)
			, r(_r) {}

		constexpr RoundRect(const position_type& pos, const size_type& size, value_type _r) noexcept
			: rect(pos, size)
			, r(_r) {}

		constexpr RoundRect(const RectF& _rect, value_type _r) noexcept
			: rect(_rect)
			, r(_r) {}

		constexpr RoundRect& set(value_type _x, value_type _y, value_type _w, value_type _h, value_type _r) noexcept
		{
			rect.set(_x, _y, _w, _h);
			r = _r;
			return *this;
		}

		constexpr RoundRect& set(const position_type& pos, value_type _w, value_type _h, value_type _r) noexcept
		{
			return set(pos.x, pos.y, _w, _h, _r);
		}

		constexpr RoundRect& set(value_type _x, value_type _y, const size_type& size, value_type _r) noexcept
		{
			return set(_x, _y, size.x, size.y, _r);
		}

		constexpr RoundRect& set(const position_type& pos, const size_type& size, value_type _r) noexcept
		{
			return set(pos.x, pos.y, size.x, size.y, _r);
		}

		constexpr RoundRect& set(const RectF& _rect, value_type _r) noexcept
		{
			return set(_rect.x, _rect.y, _rect.w, _rect.h, _r);
		}

		constexpr RoundRect& set(const RoundRect& roundRect) noexcept
		{
			return *this = roundRect;
		}

		constexpr RoundRect& setCenter(value_type _x, value_type _y) noexcept
		{
			rect.setCenter(_x, _y);
			return *this;
		}

		constexpr RoundRect& setCenter(const position_type& _center) noexcept
		{
			return setCenter(_center.x, _center.y);
		}

		constexpr RoundRect& setPos(value_type _x, value_type _y) noexcept
		{
			rect.setPos(_x, _y);
			return *this;
		}

		constexpr RoundRect& setPos(const position_type& _center) noexcept
		{
			return setCenter(_center.x, _center.y);
		}

		constexpr RoundRect movedBy(value_type _x, value_type _y) const noexcept
		{
			return{ rect.movedBy(_x, _y), r };
		}

		constexpr RoundRect movedBy(const position_type& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}

		constexpr RoundRect& moveBy(value_type _x, value_type _y) noexcept
		{
			rect.moveBy(_x, _y);
			return *this;
		}

		constexpr RoundRect& moveBy(const position_type& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		constexpr RoundRect stretched(value_type size) const noexcept
		{
			return RoundRect(rect.stretched(size), r);
		}

		constexpr RoundRect stretched(value_type _x, value_type _y) const noexcept
		{
			return RoundRect(rect.stretched(_x, _y), r);
		}

		constexpr RoundRect stretched(const size_type& xy) const noexcept
		{
			return RoundRect(rect.stretched(xy.x, xy.y), r);
		}

		constexpr RoundRect stretched(value_type top, value_type right, value_type bottom, value_type left) const noexcept
		{
			return RoundRect(rect.stretched(top, right, bottom, left), r);
		}

		constexpr double area() const noexcept
		{
			return rect.area() - (4 - Math::Pi) * r * r;
		}

		constexpr double perimeter() const noexcept
		{
			return rect.perimeter() + r * (2 * Math::Pi - 8);
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

		/*
		bool leftClicked() const;

		bool leftPressed() const;

		bool leftReleased() const;

		bool rightClicked() const;

		bool rightPressed() const;

		bool rightReleased() const;

		bool mouseOver() const;
		*/

		// paint / overpaint

		// draw / drawFrmae/ drawShadow
	};
}
