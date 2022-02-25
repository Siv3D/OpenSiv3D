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

namespace s3d
{
	/// @brief HSV 表色系の色
	struct HSV
	{
		/// @brief 色相 |Hue [0.0, 360.0)
		double h;

		/// @brief 彩度 | Saturation [0.0, 1.0]
		double s;

		/// @brief 明度 | Value [0.0, 1.0]
		double v;

		/// @brief アルファ | Alpha [0.0, 1.0]
		double a = 1.0;

		SIV3D_NODISCARD_CXX20
		HSV() = default;

		SIV3D_NODISCARD_CXX20
		HSV(const HSV&) = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr HSV(double _h, double _a = 1.0) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		explicit constexpr HSV(Arithmetic _h, double _a = 1.0) noexcept;

		/// @brief HSV 表色系の色を作成します。
		/// @param _h 色相
		/// @param _s 彩度
		/// @param _v 明度
		/// @param _a アルファ
		SIV3D_NODISCARD_CXX20
		constexpr HSV(double _h, double _s, double _v, double _a = 1.0) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr HSV(Arithmetic _h, double _s, double _v, double _a = 1.0) noexcept;

		/// @brief HSV 表色系の色を作成します。
		/// @param hsv 色
		/// @param _a アルファ
		SIV3D_NODISCARD_CXX20
		constexpr HSV(const HSV& hsv, double _a) noexcept;

		/// @brief HSV 表色系の色を作成します。
		/// @param color 色
		SIV3D_NODISCARD_CXX20
		HSV(Color color) noexcept;

		/// @brief HSV 表色系の色を作成します。
		/// @param color 色
		SIV3D_NODISCARD_CXX20
		HSV(const ColorF& color) noexcept;

		[[nodiscard]]
		constexpr double elem(size_t index) const noexcept;

		[[nodiscard]]
		double* getPointer() noexcept;

		[[nodiscard]]
		const double* getPointer() const noexcept;

		constexpr HSV& operator =(const HSV&) = default;

		[[nodiscard]]
		constexpr HSV operator +(const HSV& hsv) const noexcept;

		[[nodiscard]]
		constexpr HSV operator -(const HSV& hsv) const noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const HSV& lhs, const HSV& rhs) noexcept
		{
			return (lhs.h == rhs.h)
				&& (lhs.s == rhs.s)
				&& (lhs.v == rhs.v)
				&& (lhs.a == rhs.a);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const HSV& lhs, const HSV& rhs) noexcept
		{
			return (lhs.h != rhs.h)
				|| (lhs.s != rhs.s)
				|| (lhs.v != rhs.v)
				|| (lhs.a != rhs.a);
		}

		constexpr HSV& setH(double _h) noexcept;

		constexpr HSV& setS(double _s) noexcept;

		constexpr HSV& setV(double _v) noexcept;

		constexpr HSV& setA(double _a) noexcept;

		constexpr HSV& setHSV(double _h, double _s, double _v) noexcept;

		constexpr HSV& set(double _h, double _s, double _v, double _a = 1.0) noexcept;

		constexpr HSV& set(const HSV& hsva) noexcept;

		constexpr HSV withAlpha(double _a) const noexcept;

		[[nodiscard]]
		constexpr HSV lerp(const HSV& other, double f) const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		[[nodiscard]]
		ColorF removeSRGBCurve() const noexcept;

		[[nodiscard]]
		ColorF applySRGBCurve() const noexcept;

		[[nodiscard]]
		Color toColor() const noexcept;

		[[nodiscard]]
		Color toColor(uint32 alpha) const noexcept;

		[[nodiscard]]
		ColorF toColorF() const noexcept;

		[[nodiscard]]
		ColorF toColorF(double alpha) const noexcept;

		[[nodiscard]]
		constexpr Vec3 hsv() const noexcept;

		[[nodiscard]]
		constexpr Vec4 hsva() const noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const HSV& value)
		{
			return output << CharType('(')
				<< value.h << CharType(',') << CharType(' ')
				<< value.s << CharType(',') << CharType(' ')
				<< value.v << CharType(',') << CharType(' ')
				<< value.a << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, HSV& value)
		{
			CharType unused;
			return input >> unused
				>> value.h >> unused
				>> value.s >> unused
				>> value.v >> unused
				>> value.a >> unused;
		}

		[[nodiscard]]
		static constexpr HSV Zero() noexcept;

		friend void Formatter(FormatData& formatData, const HSV& value)
		{
			Formatter(formatData, value.hsva());
		}
	};

	[[nodiscard]]
	inline Color HueToColor(double hue) noexcept;

	[[nodiscard]]
	inline ColorF HueToColorF(double hue) noexcept;
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::HSV, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::HSV& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {})", value.h, value.s, value.v, value.a);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.h, value.s, value.v, value.a);
		}
	}
};

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::HSV>
{
	[[nodiscard]]
	size_t operator ()(const s3d::HSV& value) const noexcept
	{
		return value.hash();
	}
};
