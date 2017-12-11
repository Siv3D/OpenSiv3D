﻿//-----------------------------------------------
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

namespace s3d
{
	namespace detail
	{
		constexpr double Sqrt3 = 1.73205080756887729353; // std::sqrt(3.0)
	}

	struct Triangle
	{
		using position_type = Vec2;

		using value_type = position_type::value_type;

		position_type p0, p1, p2;
		
		position_type& p(size_t index)
		{
			return (&p0)[index];
		}
		
		const position_type& p(size_t index) const
		{
			return (&p0)[index];
		}

		Triangle() = default;

		explicit constexpr Triangle(value_type sides) noexcept
			: p0(0.0, -1.0 / detail::Sqrt3 * sides)
			, p1(sides * 0.5, sides / (2.0 * detail::Sqrt3))
			, p2(-p1.x, p1.y) {}

		Triangle(value_type sides, value_type angle) noexcept;

		constexpr Triangle(value_type x, value_type y, value_type sides) noexcept
			: Triangle(Triangle(sides).moveBy(x, y)) {}

		constexpr Triangle(const position_type& pos, value_type sides) noexcept
			: Triangle(pos.x, pos.y, sides) {}

		Triangle(value_type x, value_type y, value_type sides, value_type angle) noexcept
			: Triangle(Triangle(sides, angle).moveBy(x, y)) {}
			
		Triangle(const position_type& pos, value_type sides, value_type angle) noexcept
			: Triangle(pos.x, pos.y, sides, angle) {}

		constexpr Triangle(value_type x0, value_type y0, value_type x1, value_type y1, value_type x2, value_type y2) noexcept
			: p0(x0, y0)
			, p1(x1, y1)
			, p2(x2, y2) {}

		constexpr Triangle(const position_type& _p0, const position_type& _p1, const position_type& _p2) noexcept
			: p0(_p0)
			, p1(_p1)
			, p2(_p2) {}

		constexpr Triangle& set(value_type x0, value_type y0, value_type x1, value_type y1, value_type x2, value_type y2) noexcept
		{
			p0.set(x0, y0);
			p1.set(x1, y1);
			p2.set(x2, y2);
			return *this;
		}

		constexpr Triangle& set(const position_type& _p0, const position_type& _p1, const position_type& _p2) noexcept
		{
			p0.set(_p0);
			p1.set(_p1);
			p2.set(_p2);
			return *this;
		}

		constexpr Triangle& set(const Triangle& triangle) noexcept
		{
			return *this = triangle;
		}

		constexpr Triangle movedBy(value_type x, value_type y) const noexcept
		{
			return{ p0.movedBy(x, y), p1.movedBy(x, y), p2.movedBy(x, y) };
		}

		constexpr Triangle movedBy(const position_type& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}

		constexpr Triangle& moveBy(value_type x, value_type y) noexcept
		{
			p0.moveBy(x, y);
			p1.moveBy(x, y);
			p2.moveBy(x, y);
			return *this;
		}

		constexpr Triangle& moveBy(const position_type& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		constexpr Triangle& setCentroid(value_type x, value_type y) noexcept
		{
			return moveBy(position_type(x, y) - centroid());
		}

		constexpr Triangle& setCentroid(const position_type& pos) noexcept
		{
			return setCentroid(pos.x, pos.y);
		}

		constexpr position_type centroid() const noexcept
		{
			return (p0 + p1 + p2) / 3.0;
		}

		Triangle stretched(value_type size) const noexcept;

		Triangle rotated(value_type angle) const noexcept
		{
			return rotatedAt(centroid(), angle);
		}

		Triangle rotatedAt(value_type x, value_type y, value_type angle) const noexcept
		{
			return rotatedAt(position_type(x, y), angle);
		}

		Triangle rotatedAt(const position_type& pos, value_type angle) const noexcept;

		value_type area() const noexcept;

		value_type perimeter() const noexcept;

		template <class Shape2DType>
		bool intersects(const Shape2DType& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		template <class Shape2DType>
		bool contains(const Shape2DType& shape) const
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

		// paint~ overpaint~ draw~

		const Triangle& draw(const ColorF& color = Palette::White) const;

		const Triangle& draw(const ColorF(&colors)[3]) const;

		const Triangle& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		const Triangle& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		// Polygon asPolygon() const;
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Triangle& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Triangle& value)
	{
		return output << CharType('(')
			<< value.p0 << CharType(',')
			<< value.p1 << CharType(',')
			<< value.p2 << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Triangle& value)
	{
		CharType unused;
		return input >> unused
			>> value.p0 >> unused
			>> value.p1 >> unused
			>> value.p2 >> unused;
	}
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <>
	struct hash<s3d::Triangle>
	{
		[[nodiscard]] size_t operator ()(const s3d::Triangle& value) const noexcept
		{
			return s3d::Hash::FNV1a(value);
		}
	};
}

//////////////////////////////////////////////////
//
//	fmt
//
//////////////////////////////////////////////////

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::char32, ArgFormatter>& f, const s3d::char32*& format_str, const s3d::Triangle& value)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = U"({" + tag + U"},{" + tag + U"},{" + tag + U"})";

		f.writer().write(fmt, value.p0, value.p1, value.p2);
	}
}
