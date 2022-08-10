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

namespace s3d
{
	/// @brief アフィン変換用の 3x2 行列クラス
	struct Mat3x2
	{
		using value_type = float;

		value_type _11, _12;
		value_type _21, _22;
		value_type _31, _32;

		SIV3D_NODISCARD_CXX20
		Mat3x2() = default;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		explicit constexpr Mat3x2(Arithmetic s) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Mat3x2(float _11, float _12, float _21, float _22, float _31, float _32) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const Mat3x2& lhs, const Mat3x2& rhs) noexcept
		{
			return (lhs._11 == rhs._11) && (lhs._12 == rhs._12)
				&& (lhs._21 == rhs._21) && (lhs._22 == rhs._22)
				&& (lhs._31 == rhs._31) && (lhs._32 == rhs._32);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Mat3x2& lhs, const Mat3x2& rhs) noexcept
		{
			return (lhs._11 != rhs._11) || (lhs._12 != rhs._12)
				|| (lhs._21 != rhs._21) || (lhs._22 != rhs._22)
				|| (lhs._31 != rhs._31) || (lhs._32 != rhs._32);
		}

		[[nodiscard]]
		Mat3x2 constexpr translated(Float2 v) const noexcept;

		template <class X, class Y>
		[[nodiscard]]
		Mat3x2 constexpr translated(X x, Y y) const noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		Mat3x2 constexpr scaled(Arithmetic s, Float2 center = Float2{ 0, 0 }) const noexcept;

		[[nodiscard]]
		Mat3x2 constexpr scaled(Float2 scale, Float2 center = Float2{ 0, 0 }) const noexcept;

		template <class X, class Y, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>>>* = nullptr>
		[[nodiscard]]
		Mat3x2 constexpr scaled(X sx, Y sy, Float2 center = Float2{ 0, 0 }) const noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		Mat3x2 rotated(Arithmetic angle, Float2 center = Float2{ 0, 0 }) const noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		constexpr Mat3x2 shearedX(Arithmetic sx) const noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		constexpr Mat3x2 shearedY(Arithmetic sy) const noexcept;

		[[nodiscard]]
		constexpr float determinant() const noexcept;

		[[nodiscard]]
		Mat3x2 inverse() const noexcept;

		constexpr void setProduct(const Mat3x2& a, const Mat3x2& b) noexcept;

		[[nodiscard]]
		constexpr Mat3x2 operator *(const Mat3x2& other) const noexcept;

		/// @brief 点の座標を変換します
		/// @param pos 点の座標
		/// @return 変換後の座標
		[[nodiscard]]
		constexpr Float2 transformPoint(Point pos) const noexcept;

		/// @brief 点の座標を変換します
		/// @param pos 点の座標
		/// @return 変換後の座標
		[[nodiscard]]
		constexpr Float2 transformPoint(Float2 pos) const noexcept;

		/// @brief 点の座標を変換します
		/// @param pos 点の座標
		/// @return 変換後の座標
		[[nodiscard]]
		constexpr Vec2 transformPoint(Vec2 pos) const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		/// @brief 何も変換をしない行列を返します。
		/// @return 何も変換をしない行列
		[[nodiscard]]
		static constexpr Mat3x2 Identity() noexcept;

		[[nodiscard]]
		static constexpr Mat3x2 Translate(Float2 v) noexcept;

		template <class X, class Y>
		[[nodiscard]]
		static constexpr Mat3x2 Translate(X x, Y y) noexcept;

		[[nodiscard]]
		static constexpr Mat3x2 Scale(Float2 scale, Float2 center = Float2{ 0, 0 }) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static constexpr Mat3x2 Scale(Arithmetic s, Float2 center = Float2{ 0, 0 }) noexcept;

		template <class X, class Y, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>>>* = nullptr>
		[[nodiscard]]
		static constexpr Mat3x2 Scale(X sx, Y sy, Float2 center = Float2{ 0, 0 }) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Mat3x2 Rotate(Arithmetic angle, Float2 center = Float2{ 0, 0 }) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static constexpr Mat3x2 ShearX(Arithmetic sx) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static constexpr Mat3x2 ShearY(Arithmetic sy) noexcept;

		template <class X, class Y>
		[[nodiscard]]
		static constexpr Mat3x2 Screen(X width, Y height) noexcept;

		[[nodiscard]]
		static constexpr Mat3x2 Screen(Float2 size) noexcept;

		template <class CharType>
		friend inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Mat3x2& value)
		{
			return output << CharType('(')
				<< Float2{ value._11, value._12 } << CharType(',')
				<< Float2{ value._21, value._22 } << CharType(',')
				<< Float2{ value._31, value._32 } << CharType(')');
		}

		template <class CharType>
		friend inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Mat3x2& value)
		{
			CharType unused;
			Float2 r1, r2, r3;

			input >> unused
				>> r1 >> unused
				>> r2 >> unused
				>> r3 >> unused;

			value._11 = r1.x;
			value._12 = r1.y;
			value._21 = r2.x;
			value._22 = r2.y;
			value._31 = r3.x;
			value._32 = r3.y;

			return input;
		}

		friend void Formatter(FormatData& formatData, const Mat3x2& value);
	};
}

# include "detail/Mat3x2.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Mat3x2, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Mat3x2& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"(({}, {}), ({}, {}), ({}, {}))",
				value._11, value._12, value._21, value._22, value._31, value._32);
		}
		else
		{
			const std::u32string format
				= (U"(({:" + tag + U"}, {:" + tag + U"}), ({:" + tag + U"}, {:" + tag + U"}), ({:" + tag + U"}, {:" + tag + U"}))");
			return format_to(ctx.out(), format, value._11, value._12, value._21, value._22, value._31, value._32);
		}
	}
};

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::Mat3x2>
{
	[[nodiscard]]
	size_t operator ()(const s3d::Mat3x2& value) const noexcept
	{
		return value.hash();
	}
};
