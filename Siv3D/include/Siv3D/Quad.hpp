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

namespace s3d
{
	/// @brief 凸四角形
	struct Quad
	{
		using position_type	= Vec2;

		using value_type	= position_type::value_type;

		position_type p0;

		position_type p1;

		position_type p2;

		position_type p3;

		SIV3D_NODISCARD_CXX20
		Quad() = default;

		/// @brief 
		/// @param x0 
		/// @param y0 
		/// @param x1 
		/// @param y1 
		/// @param x2 
		/// @param y2 
		/// @param x3 
		/// @param y3 
		SIV3D_NODISCARD_CXX20
		constexpr Quad(value_type x0, value_type y0, value_type x1, value_type y1, value_type x2, value_type y2, value_type x3, value_type y3) noexcept;

		/// @brief 
		/// @param _p0 
		/// @param _p1 
		/// @param _p2 
		/// @param _p3 
		SIV3D_NODISCARD_CXX20
		constexpr Quad(const position_type& _p0, const position_type& _p1, const position_type& _p2, const position_type& _p3) noexcept;



		[[nodiscard]]
		size_t hash() const noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Quad& value)
		{
			return output << CharType('(')
				<< value.p0 << CharType(',') << CharType(' ')
				<< value.p1 << CharType(',') << CharType(' ')
				<< value.p2 << CharType(',') << CharType(' ')
				<< value.p3 << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Quad& value)
		{
			CharType unused;
			return input >> unused
				>> value.p0 >> unused
				>> value.p1 >> unused
				>> value.p2 >> unused
				>> value.p3 >> unused;
		}

		friend void Formatter(FormatData& formatData, const Quad& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Quad& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Quad, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Quad& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {})", value.p0, value.p1, value.p2, value.p3);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.p0, value.p1, value.p2, value.p3);
		}
	}
};

template <>
struct std::hash<s3d::Quad>
{
	[[nodiscard]]
	size_t operator()(const s3d::Quad& value) const noexcept
	{
		return value.hash();
	}
};
