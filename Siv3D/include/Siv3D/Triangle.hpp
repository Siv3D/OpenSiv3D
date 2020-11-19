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
	
	


		[[nodiscard]]
		size_t hash() const noexcept;



		const Triangle& draw(const ColorF& color = Palette::White) const;

		const Triangle& draw(const ColorF& color0, const ColorF& color1, const ColorF& color2) const;






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
