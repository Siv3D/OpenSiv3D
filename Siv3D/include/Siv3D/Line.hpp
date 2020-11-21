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
# include "Circular.hpp"
# include "ColorHSV.hpp"
# include "Optional.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	template <class SizeType> struct Rectangle;
	using Rect = Rectangle<Point>;
	using RectF = Rectangle<Vec2>;

	/// @brief 線分
	struct Line
	{
		using position_type	= Vec2;

		using value_type	= position_type::value_type;

		/// @brief 線分の開始位置
		position_type begin;

		/// @brief 線分の終点位置
		position_type end;

		SIV3D_NODISCARD_CXX20
		Line() = default;

		SIV3D_NODISCARD_CXX20
		constexpr Line(value_type x0, value_type y0, value_type x1, value_type y1) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line(position_type p0, value_type x1, value_type y1) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line(value_type x0, value_type y0, position_type p1) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line(position_type p0, position_type p1) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line(position_type origin, Arg::direction_<position_type> direction) noexcept;

		SIV3D_NODISCARD_CXX20
		Line(position_type origin, Arg::angle_<value_type> angle, value_type length) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const Line& lhs, const Line& rhs) noexcept
		{
			return (lhs.begin == rhs.begin)
				&& (lhs.end == rhs.end);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Line& lhs, const Line& rhs) noexcept
		{
			return (lhs.begin != rhs.begin)
				|| (lhs.end != rhs.end);
		}

		constexpr Line& set(value_type x0, value_type y0, value_type x1, value_type y1) noexcept;

		constexpr Line& set(position_type p0, value_type x1, value_type y1) noexcept;

		constexpr Line& set(value_type x0, value_type y0, position_type p1) noexcept;

		constexpr Line& set(position_type p0, position_type p1) noexcept;

		constexpr Line& set(const Line& line) noexcept;

		[[nodiscard]]
		constexpr Line movedBy(value_type x, value_type y) const noexcept;

		[[nodiscard]]
		constexpr Line movedBy(position_type v) const noexcept;

		constexpr Line& moveBy(value_type x, value_type y) noexcept;

		constexpr Line& moveBy(position_type v) noexcept;

		[[nodiscard]]
		Line stretched(value_type length) const noexcept;

		[[nodiscard]]
		Line stretched(value_type lengthBegin, value_type lengthEnd) const noexcept;

		[[nodiscard]]
		constexpr position_type vector() const noexcept;

		[[nodiscard]]
		constexpr Line reversed() const noexcept;

		constexpr Line& reverse() noexcept;

		[[nodiscard]]
		value_type length() const noexcept;

		[[nodiscard]]
		constexpr value_type lengthSq() const noexcept;

		[[nodiscard]]
		constexpr position_type center() const noexcept;

		[[nodiscard]]
		position_type closest(position_type pos) const noexcept;

		[[nodiscard]]
		RectF boundingRect() const noexcept;

		[[nodiscard]]
		constexpr Line lerp(const Line& other, double f) const noexcept;

		template <class Shape2DType>
		[[nodiscard]]
		bool intersects(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& other) const;

		[[nodiscard]]
		Optional<position_type> intersectsAt(const Line& other) const;

		[[nodiscard]]
		Optional<position_type> intersectsAtPrecise(const Line& other) const;

		[[nodiscard]]
		size_t hash() const noexcept;




		const Line& draw(const ColorF& color = Palette::White) const;

		const Line& draw(const ColorF& colorBegin, const ColorF& colorEnd) const;

		const Line& draw(double thickness, const ColorF& color = Palette::White) const;

		const Line& draw(double thickness, const ColorF& colorBegin, const ColorF& colorEnd) const;





		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Line& value)
		{
			return output << CharType('(')
				<< value.begin << CharType(',') << CharType(' ')
				<< value.end << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Line& value)
		{
			CharType unused;
			return input >> unused
				>> value.begin >> unused
				>> value.end >> unused;
		}

		friend void Formatter(FormatData& formatData, const Line& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Line& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Line, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Line& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {})", value.begin, value.end);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.begin, value.end);
		}
	}
};

template <>
struct std::hash<s3d::Line>
{
	[[nodiscard]]
	size_t operator()(const s3d::Line& value) const noexcept
	{
		return value.hash();
	}
};
