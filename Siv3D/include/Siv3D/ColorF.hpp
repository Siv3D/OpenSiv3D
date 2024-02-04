//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "FormatData.hpp"
# include "Color.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// @brief 色を RGBA 各要素について浮動小数点数で表現するクラスです。
	/// @remark 各要素は通常 0.0 以上 1.0 以下の値を持ちます。
	struct ColorF
	{
		/// @brief 赤 | Red
		double r;

		/// @brief 緑 | Green
		double g;

		/// @brief 青 | Blue
		double b;

		/// @brief アルファ | Alpha
		double a;

		SIV3D_NODISCARD_CXX20
		ColorF() = default;

		SIV3D_NODISCARD_CXX20
		ColorF(const ColorF&) = default;

		/// @brief 色を作成します。
		/// @param _r 赤成分
		/// @param _g 緑成分
		/// @param _b 青成分
		/// @param _a アルファ成分
		SIV3D_NODISCARD_CXX20
		constexpr ColorF(double _r, double _g, double _b, double _a = 1.0) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr ColorF(double rgb, double _a = 1.0) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr ColorF(const ColorF& rgb, double _a) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr ColorF(const Vec3& rgb, double _a = 1.0) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr ColorF(const Vec4& rgba) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr ColorF(Color color) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr ColorF(Color rgb, double _a) noexcept;

		SIV3D_NODISCARD_CXX20
		ColorF(const HSV& hsva) noexcept;

		SIV3D_NODISCARD_CXX20
		ColorF(const HSV& hsv, double _a) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr ColorF(StringView code) noexcept;

		[[nodiscard]]
		constexpr double elem(size_t index) const noexcept;

		[[nodiscard]]
		double* getPointer() noexcept;

		[[nodiscard]]
		const double* getPointer() const noexcept;

		constexpr ColorF& operator =(const ColorF&) noexcept = default;

		constexpr ColorF& operator =(Color color) noexcept;

		ColorF& operator =(const HSV& hsva) noexcept;

		[[nodiscard]]
		constexpr ColorF operator +(const ColorF& rgb) const noexcept;

		constexpr ColorF& operator +=(const ColorF& rgb) noexcept;

		[[nodiscard]]
		constexpr ColorF operator -(const ColorF& rgb) const noexcept;

		constexpr ColorF& operator -=(const ColorF& rgb) noexcept;

		[[nodiscard]]
		constexpr ColorF operator *(const double s) const noexcept;

		constexpr ColorF& operator *=(const double s) noexcept;

		[[nodiscard]]
		constexpr ColorF operator *(const ColorF& rgba) const noexcept;

		constexpr ColorF& operator *=(const ColorF& rgba) noexcept;

		[[nodiscard]]
		friend inline constexpr ColorF operator *(const double s, const ColorF& color) noexcept
		{
			return{ s * color.r, s * color.g, s * color.b, color.a };
		}

		[[nodiscard]]
		friend constexpr bool operator ==(const ColorF& lhs, const ColorF& rhs) noexcept
		{
			return (lhs.r == rhs.r)
				&& (lhs.g == rhs.g)
				&& (lhs.b == rhs.b)
				&& (lhs.a == rhs.a);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const ColorF& lhs, const ColorF& rhs) noexcept
		{
			return (lhs.r != rhs.r)
				|| (lhs.g != rhs.g)
				|| (lhs.b != rhs.b)
				|| (lhs.a != rhs.a);
		}

		/// @brief r 成分のみを変更した自身のコピーを返します。
		/// @param _r r 成分
		/// @return r 成分を変更したコピー
		[[nodiscard]]
		constexpr ColorF withR(double _r) const noexcept;

		/// @brief g 成分のみを変更した自身のコピーを返します。
		/// @param _g g 成分
		/// @return g 成分を変更したコピー
		[[nodiscard]]
		constexpr ColorF withG(double _g) const noexcept;

		/// @brief b 成分のみを変更した自身のコピーを返します。
		/// @param _b b 成分
		/// @return b 成分を変更したコピー
		[[nodiscard]]
		constexpr ColorF withB(double _b) const noexcept;

		/// @brief a 成分のみを変更した自身のコピーを返します。
		/// @param _a a 成分
		/// @return a 成分を変更したコピー
		[[nodiscard]]
		constexpr ColorF withA(double _a) const noexcept;

		constexpr ColorF& setR(double _r) noexcept;

		constexpr ColorF& setG(double _g) noexcept;

		constexpr ColorF& setB(double _b) noexcept;

		constexpr ColorF& setA(double _a) noexcept;

		constexpr ColorF& setRGB(double rgb) noexcept;

		constexpr ColorF& setRGB(double _r, double _g, double _b) noexcept;

		constexpr ColorF& set(double rgb, double _a = 1.0) noexcept;

		constexpr ColorF& set(double _r, double _g, double _b, double _a = 1.0) noexcept;

		constexpr ColorF& set(const ColorF& ColorF) noexcept;

		constexpr ColorF withAlpha(double _a) const noexcept;

		/// @brief グレースケール値を返します。
		/// @remark グレースケール値は、`(0.299 * r) + (0.587 * g) + (0.114 * b)` で計算されます。
		/// @return グレースケール値
		[[nodiscard]]
		constexpr double grayscale() const noexcept;

		/// @brief RGB 各成分の最小値を返します。
		/// @return RGB 各成分の最小値
		[[nodiscard]]
		constexpr double minRGBComponent() const noexcept;

		/// @brief RGB 各成分の最大値を返します。
		/// @return RGB 各成分の最大値
		[[nodiscard]]
		constexpr double maxRGBComponent() const noexcept;

		/// @brief RGBA 各成分の最小値を返します。
		/// @return RGBA 各成分の最小値
		[[nodiscard]]
		constexpr double minComponent() const noexcept;

		/// @brief RGBA 各成分の最大値を返します。
		/// @return RGBA 各成分の最大値
		[[nodiscard]]
		constexpr double maxComponent() const noexcept;

		[[nodiscard]]
		constexpr ColorF lerp(const ColorF& other, double f) const noexcept;

		[[nodiscard]]
		ColorF gamma(double gamma) const noexcept;

		[[nodiscard]]
		ColorF removeSRGBCurve() const noexcept;

		[[nodiscard]]
		ColorF applySRGBCurve() const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		/// @brief 色を Color で返します。
		/// @remark 各成分は 0.0～1.0 の範囲にクランプされます。
		/// @return 変換された Color
		[[nodiscard]]
		constexpr Color toColor() const noexcept;

		/// @brief Float4{ r, g, b, a } を返します。
		/// @return Float4{ r, g, b, a }
		[[nodiscard]]
		constexpr Float4 toFloat4() const noexcept;

		/// @brief Vec4{ r, g, b, a } を返します。
		/// @return Vec4{ r, g, b, a }
		[[nodiscard]]
		constexpr Vec4 toVec4() const noexcept;

		/// @brief Vec2{ r, g } を返します。
		/// @return Vec2{ r, g }
		[[nodiscard]]
		constexpr Vec2 rg() const noexcept;

		/// @brief Vec2{ g, b } を返します。
		/// @return Vec2{ g, b }
		[[nodiscard]]
		constexpr Vec2 gb() const noexcept;

		/// @brief Vec2{ b, a } を返します。
		/// @return Vec2{ b, a }
		[[nodiscard]]
		constexpr Vec2 ba() const noexcept;

		/// @brief Vec3{ r, g, b } を返します。
		/// @return Vec3{ r, g, b }
		[[nodiscard]]
		constexpr Vec3 rgb() const noexcept;

		/// @brief Vec3{ g, b, a } を返します。
		/// @return Vec3{ g, b, a }
		[[nodiscard]]
		constexpr Vec3 gba() const noexcept;

		/// @brief Vec3{ b, g, r } を返します。
		/// @return Vec3{ b, g, r }
		[[nodiscard]]
		constexpr Vec3 bgr() const noexcept;

		/// @brief Vec4{ r, g, b, a } を返します。
		/// @remark `toVec4()` と同じです。
		/// @return Vec4{ r, g, b, a }
		[[nodiscard]]
		constexpr Vec4 rgba() const noexcept;

		/// @brief Vec4{ r, g, b, 0 } を返します。
		/// @return Vec4{ r, g, b, 0 }
		[[nodiscard]]
		constexpr Vec4 rgb0() const noexcept;

		/// @brief Vec4{ r, g, b, 1 } を返します。
		/// @return Vec4{ r, g, b, 1 }
		[[nodiscard]]
		constexpr Vec4 rgb1() const noexcept;

		/// @brief Vec4{ a, r, g, b } を返します。
		/// @return Vec4{ a, r, g, b }
		[[nodiscard]]
		constexpr Vec4 argb() const noexcept;

		/// @brief Vec4{ a, b, g, r } を返します。
		/// @return Vec4{ a, b, g, r }
		[[nodiscard]]
		constexpr Vec4 abgr() const noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const ColorF& value)
		{
			return output << CharType('(')
				<< value.r << CharType(',') << CharType(' ')
				<< value.g << CharType(',') << CharType(' ')
				<< value.b << CharType(',') << CharType(' ')
				<< value.a << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, ColorF& value)
		{
			CharType unused;
			input >> unused;

			if (unused == CharType('#'))
			{
				String code;
				input >> code;
				value = ColorF(U'#' + code);
			}
			else
			{
				input >> value.r >> unused
					>> value.g >> unused
					>> value.b >> unused;

				if (unused == CharType(','))
				{
					input >> value.a >> unused;
				}
				else
				{
					value.a = 1.0;
				}
			}

			return input;
		}

		[[nodiscard]]
		static constexpr ColorF Zero() noexcept;

		[[nodiscard]]
		static constexpr ColorF One() noexcept;

		friend void Formatter(FormatData& formatData, const ColorF& value);
	};

	[[nodiscard]]
	inline constexpr ColorF AlphaF(double alpha) noexcept;

	[[nodiscard]]
	inline constexpr ColorF Transparency(double transparency) noexcept;
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::ColorF, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::ColorF& value, FormatContext& ctx)
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
struct std::hash<s3d::ColorF>
{
	[[nodiscard]]
	size_t operator ()(const s3d::ColorF& value) const noexcept
	{
		return value.hash();
	}
};
