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
# include "ColorHSV.hpp"

namespace s3d
{
	/// @brief 三角形
	struct Triangle
	{
		using position_type	= Vec2;

		using value_type	= position_type::value_type;

		position_type p0;

		position_type p1;

		position_type p2;

		/// @brief 
		SIV3D_NODISCARD_CXX20
		Triangle() = default;

		/// @brief 
		/// @param sides 
		SIV3D_NODISCARD_CXX20
		explicit constexpr Triangle(value_type sides) noexcept;

		/// @brief 
		/// @param sides 
		/// @param angle 
		SIV3D_NODISCARD_CXX20
		Triangle(value_type sides, value_type angle) noexcept;

		/// @brief 
		/// @param x 
		/// @param y 
		/// @param sides 
		SIV3D_NODISCARD_CXX20
		constexpr Triangle(value_type x, value_type y, value_type sides) noexcept;

		/// @brief 
		/// @param pos 
		/// @param sides 
		SIV3D_NODISCARD_CXX20
		constexpr Triangle(const position_type& pos, value_type sides) noexcept;

		/// @brief 
		/// @param x 
		/// @param y 
		/// @param sides 
		/// @param angle 
		SIV3D_NODISCARD_CXX20
		Triangle(value_type x, value_type y, value_type sides, value_type angle) noexcept;

		/// @brief 
		/// @param pos 
		/// @param sides 
		/// @param angle 
		SIV3D_NODISCARD_CXX20
		Triangle(const position_type& pos, value_type sides, value_type angle) noexcept;

		/// @brief 
		/// @param x0 
		/// @param y0 
		/// @param x1 
		/// @param y1 
		/// @param x2 
		/// @param y2 
		SIV3D_NODISCARD_CXX20
		constexpr Triangle(value_type x0, value_type y0, value_type x1, value_type y1, value_type x2, value_type y2) noexcept;

		/// @brief 
		/// @param _p0 
		/// @param _p1 
		/// @param _p2 
		SIV3D_NODISCARD_CXX20
		constexpr Triangle(const position_type& _p0, const position_type& _p1, const position_type& _p2) noexcept;
	
		[[nodiscard]]
		friend constexpr bool operator ==(const Triangle& lhs, const Triangle& rhs) noexcept
		{
			return (lhs.p0 == rhs.p0)
				&& (lhs.p1 == rhs.p1)
				&& (lhs.p2 == rhs.p2);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Triangle& lhs, const Triangle& rhs) noexcept
		{
			return (lhs.p0 != rhs.p0)
				|| (lhs.p1 != rhs.p1)
				|| (lhs.p2 != rhs.p2);
		}
	
		[[nodiscard]] constexpr position_type& p(size_t index)
		{
			return (&p0)[index];
		}

		[[nodiscard]] constexpr const position_type& p(size_t index) const
		{
			return (&p0)[index];
		}

		[[nodiscard]] constexpr Line side(size_t index) const
		{
			if (index == 0)
			{
				return Line(p0, p1);
			}
			else if (index == 1)
			{
				return Line(p1, p2);
			}
			else if (index == 2)
			{
				return Line(p2, p0);
			}
			else
			{
				throw std::out_of_range("Triangle::side() index out of range");
			}
		}

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

		[[nodiscard]] constexpr Triangle movedBy(value_type x, value_type y) const noexcept
		{
			return{ p0.movedBy(x, y), p1.movedBy(x, y), p2.movedBy(x, y) };
		}

		[[nodiscard]] constexpr Triangle movedBy(const position_type& v) const noexcept
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

		[[nodiscard]] constexpr position_type centroid() const noexcept
		{
			return position_type((p0.x + p1.x + p2.x) / 3.0, (p0.y + p1.y + p2.y) / 3.0);
		}

		[[nodiscard]] Triangle stretched(value_type size) const noexcept;

		[[nodiscard]] Triangle rotated(value_type angle) const noexcept
		{
			return rotatedAt(centroid(), angle);
		}

		[[nodiscard]] Triangle rotatedAt(value_type x, value_type y, value_type angle) const noexcept
		{
			return rotatedAt(position_type(x, y), angle);
		}

		[[nodiscard]] Triangle rotatedAt(const position_type& pos, value_type angle) const noexcept;

		[[nodiscard]] value_type area() const noexcept;

		[[nodiscard]] value_type perimeter() const noexcept;
	
		[[nodiscard]]
		constexpr RectF boundingRect() const noexcept;

		[[nodiscard]]
		Polygon asPolygon() const;

		[[nodiscard]]
		constexpr Triangle lerp(const Triangle& other, double f) const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		template <class Shape2DType>
		[[nodiscard]]
		bool intersects(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		bool contains(const Shape2DType& other) const;

		[[nodiscard]]
		bool leftClicked() const noexcept;

		[[nodiscard]]
		bool leftPressed() const noexcept;

		[[nodiscard]]
		bool leftReleased() const noexcept;

		[[nodiscard]]
		bool rightClicked() const noexcept;

		[[nodiscard]]
		bool rightPressed() const noexcept;

		[[nodiscard]]
		bool rightReleased() const noexcept;

		[[nodiscard]]
		bool mouseOver() const noexcept;

		//const Triangle& paint(Image& dst, const Color& color) const;

		//const Triangle& overwrite(Image& dst, const Color& color, bool antialiased = true) const;

		//const Triangle& paintFrame(Image& dst, int32 thickness, const Color& color) const;

		//const Triangle& overwriteFrame(Image& dst, int32 thickness, const Color& color, bool antialiased = true) const;

		const Triangle& draw(const ColorF& color = Palette::White) const;

		const Triangle& draw(const ColorF& color0, const ColorF& color1, const ColorF& color2) const;

		const Triangle& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		const Triangle& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Triangle& value)
		{
			return output << CharType('(')
				<< value.p0 << CharType(',') << CharType(' ')
				<< value.p1 << CharType(',') << CharType(' ')
				<< value.p2 << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Triangle& value)
		{
			CharType unused;
			return input >> unused
				>> value.p0 >> unused
				>> value.p1 >> unused
				>> value.p2 >> unused;
		}

		friend void Formatter(FormatData& formatData, const Triangle& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Triangle& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Triangle, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Triangle& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {})", value.p0, value.p1, value.p2);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.p0, value.p1, value.p2);
		}
	}
};

template <>
struct std::hash<s3d::Triangle>
{
	[[nodiscard]]
	size_t operator()(const s3d::Triangle& value) const noexcept
	{
		return value.hash();
	}
};
