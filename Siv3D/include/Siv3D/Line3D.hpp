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
# include "Common.hpp"
# include "PointVector.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	struct Mat4x4;

	struct Line3D
	{
		using position_type = Vec3;

		using value_type = position_type::value_type;


		position_type begin;

		position_type end;


		SIV3D_NODISCARD_CXX20
		Line3D() = default;

		SIV3D_NODISCARD_CXX20
		Line3D(const Line3D&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(value_type bx, value_type by, value_type bz, value_type ex, value_type ey, value_type ez) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(const position_type& _begin, value_type ex, value_type ey, value_type ez) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(value_type bx, value_type by, value_type bz, const position_type& _end) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(const position_type& _begin, const position_type& _end) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(const position_type& origin, Arg::direction_<position_type> direction) noexcept;

		Line3D& operator =(const Line3D&) = default;


		[[nodiscard]]
		friend constexpr bool operator ==(const Line3D& lhs, const Line3D& rhs) noexcept
		{
			return (lhs.begin == rhs.begin)
				&& (lhs.end == rhs.end);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Line3D& lhs, const Line3D& rhs) noexcept
		{
			return (lhs.begin != rhs.begin)
				|| (lhs.end != rhs.end);
		}


		constexpr Line3D& set(value_type x0, value_type y0, value_type z0, value_type x1, value_type y1, value_type z1) noexcept;

		constexpr Line3D& set(position_type p0, value_type x1, value_type y1, value_type z1) noexcept;

		constexpr Line3D& set(value_type x0, value_type y0, value_type z0, position_type p1) noexcept;

		constexpr Line3D& set(position_type p0, position_type p1) noexcept;

		constexpr Line3D& set(const Line3D& line) noexcept;


		[[nodiscard]]
		constexpr Line3D movedBy(value_type x, value_type y, value_type z) const noexcept;

		[[nodiscard]]
		constexpr Line3D movedBy(position_type v) const noexcept;

		constexpr Line3D& moveBy(value_type x, value_type y, value_type z) noexcept;

		constexpr Line3D& moveBy(position_type v) noexcept;


		[[nodiscard]]
		Line3D stretched(value_type length) const noexcept;

		[[nodiscard]]
		Line3D stretched(value_type lengthBegin, value_type lengthEnd) const noexcept;


		[[nodiscard]]
		constexpr position_type vector() const noexcept;

		[[nodiscard]]
		constexpr Line3D reversed() const noexcept;

		constexpr Line3D& reverse() noexcept;


		[[nodiscard]]
		constexpr bool hasLength() const noexcept;

		[[nodiscard]]
		value_type length() const noexcept;

		[[nodiscard]]
		constexpr value_type lengthSq() const noexcept;

		[[nodiscard]]
		position_type& p(size_t index) noexcept;

		[[nodiscard]]
		const position_type& p(size_t index) const noexcept;

		[[nodiscard]]
		constexpr position_type point(size_t index);

		[[nodiscard]]
		constexpr position_type position(double t) const noexcept;

		[[nodiscard]]
		constexpr position_type center() const noexcept;

		[[nodiscard]]
		constexpr Line3D lerp(const Line3D& other, double f) const noexcept;


		[[nodiscard]]
		Line3D toScreen(const Mat4x4& vp) const noexcept;

		[[nodiscard]]
		Line toScreenLine(const Mat4x4& vp) const noexcept;


		const Line3D& draw(const ColorF& color = Palette::White) const;

		const Line3D& draw(const ColorF& colorBegin, const ColorF& colorEnd) const;


		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Line3D& value)
		{
			return output << CharType('(')
				<< value.begin << CharType(',') << CharType(' ')
				<< value.end << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Line3D& value)
		{
			CharType unused;
			return input >> unused
				>> value.begin >> unused
				>> value.end >> unused;
		}

		friend void Formatter(FormatData& formatData, const Line3D& value);
	};
}

# include "detail/Line3D.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Line3D, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Line3D& value, FormatContext& ctx)
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
