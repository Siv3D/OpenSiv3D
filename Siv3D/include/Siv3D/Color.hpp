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
		/// @brief 赤 | Red
		uint8 r;

		/// @brief 緑 | Green
		uint8 g;

		/// @brief 青 | Blue
		uint8 b;

		/// @brief アルファ | Alpha
		uint8 a;

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Color() = default;

		/// @brief コピーコンストラクタ
		SIV3D_NODISCARD_CXX20
		Color(const Color&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr Color(uint8 _r, uint8 _g, uint8 _b, uint8 _a = 255) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Color(uint8 rgb, uint8 _a = 255) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Color(Color rgb, uint8 _a) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Color(const ColorF& color) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Color(const ColorF& color, uint8 _a) noexcept;

		SIV3D_NODISCARD_CXX20
		Color(const HSV& hsva) noexcept;

		SIV3D_NODISCARD_CXX20
		Color(const HSV& hsv, uint8 _a) noexcept;

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
		# if __cpp_lib_is_constant_evaluated
			if (std::is_constant_evaluated()) // MSVC workaround
			{
				return (lhs.r == rhs.r)
					&& (lhs.g == rhs.g)
					&& (lhs.b == rhs.b)
					&& (lhs.a == rhs.a);
			}
			else
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
		# else
			# if __cpp_lib_bit_cast
				return (std::bit_cast<uint32>(lhs) == std::bit_cast<uint32>(rhs));
			# else
				return (lhs.r == rhs.r)
					&& (lhs.g == rhs.g)
					&& (lhs.b == rhs.b)
					&& (lhs.a == rhs.a);
			# endif
		# endif
		}

		[[nodiscard]]
		friend constexpr bool operator !=(Color lhs, Color rhs) noexcept
		{
		# if __cpp_lib_is_constant_evaluated
			if (std::is_constant_evaluated()) // MSVC workaround
			{
				return (lhs.r != rhs.r)
					|| (lhs.g != rhs.g)
					|| (lhs.b != rhs.b)
					|| (lhs.a != rhs.a);
			}
			else
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
		# else
			# if __cpp_lib_bit_cast
				return (std::bit_cast<uint32>(lhs) != std::bit_cast<uint32>(rhs));
			# else
				return (lhs.r != rhs.r)
					|| (lhs.g != rhs.g)
					|| (lhs.b != rhs.b)
					|| (lhs.a != rhs.a);
			# endif
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

				value.r = cols[0];
				value.g = cols[1];
				value.b = cols[2];
				value.a = cols[3];
			}

			return input;
		}

		friend void Formatter(FormatData& formatData, const Color& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Color& value);
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
	size_t operator()(const s3d::Color& value) const noexcept
	{
		return value.hash();
	}
};
