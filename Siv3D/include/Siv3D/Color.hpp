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
# if  __has_include(<bit>)
#	include <bit>
# endif
# include "Common.hpp"
# include "FormatData.hpp"
# include "FormatLiteral.hpp"

namespace s3d
{
	struct ColorF;
	struct HSV;

	struct Color
	{
		using value_type = uint8;

		/// @brief 赤 | Red
		value_type r;

		/// @brief 緑 | Green
		value_type g;

		/// @brief 青 | Blue
		value_type b;

		/// @brief アルファ | Alpha
		value_type a;

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Color() = default;

		/// @brief コピーコンストラクタ
		SIV3D_NODISCARD_CXX20
		Color(const Color&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr Color(value_type _r, value_type _g, value_type _b, value_type _a = 255) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Color(value_type rgb, value_type _a = 255) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Color(Color rgb, value_type _a) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Color(const ColorF& color) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Color(const ColorF& color, value_type _a) noexcept;

		SIV3D_NODISCARD_CXX20
		Color(const HSV& hsva) noexcept;

		SIV3D_NODISCARD_CXX20
		Color(const HSV& hsv, value_type _a) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Color(StringView code) noexcept;

		constexpr Color& operator =(const Color&) noexcept = default;

		constexpr Color& operator =(const ColorF& color) noexcept;

		Color& operator =(const HSV& hsva) noexcept;

		[[nodiscard]]
		constexpr Color operator ~() const noexcept;

		/// @brief 2 つの色が等しいかを返します。
		/// @param lhs 比較する色
		/// @param rhs 比較する色
		/// @return 2 つの色が等しい場合 true, それ以外の場合は false
		[[nodiscard]]
		friend constexpr bool operator ==(Color lhs, Color rhs) noexcept
		{
		# if __cpp_lib_bit_cast
			return (std::bit_cast<uint32>(lhs) == std::bit_cast<uint32>(rhs));
		# else
			return (lhs.r == rhs.r)
				&& (lhs.g == rhs.g)
				&& (lhs.b == rhs.b)
				&& (lhs.a == rhs.a);
		# endif
		}

		[[nodiscard]]
		friend constexpr bool operator !=(Color lhs, Color rhs) noexcept
		{
		# if __cpp_lib_bit_cast
			return (std::bit_cast<uint32>(lhs) != std::bit_cast<uint32>(rhs));
		# else
			return (lhs.r != rhs.r)
				|| (lhs.g != rhs.g)
				|| (lhs.b != rhs.b)
				|| (lhs.a != rhs.a);
		# endif
		}

		constexpr Color& setR(uint32 _r) noexcept;

		constexpr Color& setG(uint32 _g) noexcept;

		constexpr Color& setB(uint32 _b) noexcept;

		constexpr Color& setA(uint32 _a) noexcept;

		constexpr Color& setRGB(uint32 rgb) noexcept;

		constexpr Color& setRGB(uint32 _r, uint32 _g, uint32 _b) noexcept;

		constexpr Color& set(uint32 rgb, uint32 _a = 255) noexcept;

		constexpr Color& set(uint32 _r, uint32 _g, uint32 _b, uint32 _a = 255) noexcept;

		constexpr Color& set(Color color) noexcept;

		constexpr Color withAlpha(uint32 _a) const noexcept;

		[[nodiscard]]
		constexpr uint8 grayscale0_255() const noexcept;

		[[nodiscard]]
		constexpr double grayscale() const noexcept;

		[[nodiscard]]
		constexpr uint8 minRGBComponent() const noexcept;

		[[nodiscard]]
		constexpr uint8 maxRGBComponent() const noexcept;

		[[nodiscard]]
		constexpr uint8 minComponent() const noexcept;

		[[nodiscard]]
		constexpr uint8 maxComponent() const noexcept;

		[[nodiscard]]
		constexpr uint32 asUint32() const noexcept;

		[[nodiscard]]
		constexpr Color lerp(Color other, double f) const noexcept;

		[[nodiscard]]
		Color gamma(double gamma) const noexcept;

		[[nodiscard]]
		ColorF removeSRGBCurve() const noexcept;

		[[nodiscard]]
		ColorF applySRGBCurve() const noexcept;

		[[nodiscard]]
		String toHex() const;

		[[nodiscard]]
		size_t hash() const noexcept;

		[[nodiscard]]
		static constexpr Color Zero() noexcept;

		[[nodiscard]]
		static constexpr uint8 ToUint8(float x) noexcept;

		[[nodiscard]]
		static constexpr uint8 ToUint8(double x) noexcept;

		[[nodiscard]]
		static constexpr Color FromRGBA(uint32 rgba) noexcept;

		[[nodiscard]]
		static constexpr Color FromABGR(uint32 abgr) noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Color& value)
		{
			return output << CharType('(')
				<< value.r << CharType(',') << CharType(' ')
				<< value.g << CharType(',') << CharType(' ')
				<< value.b << CharType(',') << CharType(' ')
				<< value.a << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Color& value)
		{
			CharType unused;
			input >> unused;

			if (unused == CharType('#'))
			{
				String code;
				input >> code;
				value = Color(U'#' + code);
			}
			else
			{
				uint32 cols[4];
				input
					>> cols[0] >> unused
					>> cols[1] >> unused
					>> cols[2] >> unused;

				if (unused == CharType(','))
				{
					input >> cols[3] >> unused;
				}
				else
				{
					cols[3] = 255;
				}

				value.r = static_cast<uint8>(cols[0]);
				value.g = static_cast<uint8>(cols[1]);
				value.b = static_cast<uint8>(cols[2]);
				value.a = static_cast<uint8>(cols[3]);
			}

			return input;
		}

		friend void Formatter(FormatData& formatData, const Color& value);
	};

	[[nodiscard]]
	inline constexpr Color Alpha(uint32 alpha) noexcept;

	[[nodiscard]]
	inline constexpr Color ToColor(float rgb) noexcept;

	[[nodiscard]]
	inline constexpr Color ToColor(double rgb) noexcept;
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Color, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Color& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {})", value.r, value.g, value.b, value.a);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.r, value.g, value.b, value.a);
		}
	}
};

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::Color>
{
	[[nodiscard]]
	size_t operator ()(const s3d::Color& value) const noexcept
	{
		return value.hash();
	}
};
