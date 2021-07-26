//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
		Vec3 begin;

		Vec3 end;

		SIV3D_NODISCARD_CXX20
		Line3D() = default;

		SIV3D_NODISCARD_CXX20
		Line3D(const Line3D&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(double bx, double by, double bz, double ex, double ey, double ez) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(const Vec3& _begin, double ex, double ey, double ez) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(double bx, double by, double bz, const Vec3& _end) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(const Vec3& _begin, const Vec3& _end) noexcept;

		[[nodiscard]]
		Line3D toScreen(const Mat4x4& vp) const noexcept;

		[[nodiscard]]
		Line toScreenLine(const Mat4x4& vp) const noexcept;

		[[nodiscard]]
		constexpr Line asLine() const noexcept;

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

		friend void Formatter(FormatData& formatData, const Line3D& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Line3D& value);
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
