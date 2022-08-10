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
# include "ColorHSV.hpp"
# include "Optional.hpp"
# include "PredefinedNamedParameter.hpp"
# include "PredefinedYesNo.hpp"
# include "LineStyle.hpp"

namespace s3d
{
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

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X0, Concept::Arithmetic Y0, Concept::Arithmetic X1, Concept::Arithmetic Y1>
	# else
		template <class X0, class Y0, class X1, class Y1, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X0>, std::is_arithmetic<Y0>, std::is_arithmetic<X1>, std::is_arithmetic<Y1>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Line(X0 x0, Y0 y0, X1 x1, Y1 y1) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line(position_type p0, value_type x1, value_type y1) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X1, Concept::Arithmetic Y1>
	# else
		template <class X1, class Y1, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X1>, std::is_arithmetic<Y1>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Line(position_type p0, X1 x1, Y1 y1) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line(value_type x0, value_type y0, position_type p1) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X0, Concept::Arithmetic Y0>
	# else
		template <class X0, class Y0, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X0>, std::is_arithmetic<Y0>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Line(X0 x0, Y0 y0, position_type p1) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line(position_type p0, position_type p1) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line(value_type x0, value_type y0, Arg::direction_<position_type> direction) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X0, Concept::Arithmetic Y0>
	# else
		template <class X0, class Y0, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X0>, std::is_arithmetic<Y0>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Line(X0 x0, Y0 y0, Arg::direction_<position_type> direction) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line(position_type origin, Arg::direction_<position_type> direction) noexcept;

		SIV3D_NODISCARD_CXX20
		Line(value_type x0, value_type y0, Arg::angle_<value_type> angle, value_type length) noexcept;

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
		position_type normal() const noexcept;

		[[nodiscard]]
		constexpr Line reversed() const noexcept;

		constexpr Line& reverse() noexcept;

		/// @brief 線分が長さを持つかを返します。
		/// @return 線分が長さを持つ場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool hasLength() const noexcept;

		/// @brief 線分の長さを返します。
		/// @return 線分の長さ
		[[nodiscard]]
		value_type length() const noexcept;

		/// @brief 線分の長さの二乗を返します。
		/// @return 線分の長さの二乗
		[[nodiscard]]
		constexpr value_type lengthSq() const noexcept;

		[[nodiscard]]
		position_type& p(size_t index) noexcept;

		[[nodiscard]]
		const position_type& p(size_t index) const noexcept;

		[[nodiscard]]
		constexpr position_type point(size_t index) const;

		[[nodiscard]]
		constexpr position_type position(double t) const noexcept;

		/// @brief 線分の中心の座標を返します。
		/// @return 線分の中心の座標
		[[nodiscard]]
		constexpr position_type center() const noexcept;

		[[nodiscard]]
		position_type closest(position_type pos) const noexcept;

		[[nodiscard]]
		RectF boundingRect() const noexcept;

		[[nodiscard]]
		Line extractLine(double distanceFromOrigin, double length) const noexcept;

		[[nodiscard]]
		constexpr Line lerp(const Line& other, double f) const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		template <class Shape2DType>
		[[nodiscard]]
		constexpr bool intersects(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& other) const;

		/// @brief 別の線分 other との交点を返します。
		/// @param other 別の線分
		/// @return 交差しない場合は none, 交差する場合はその座標、2 つの線分が重なっている場合 (QNaN, QNaN)
		[[nodiscard]]
		Optional<position_type> intersectsAt(const Line& other) const;

		/// @brief 別の線分 other との交点を返します。`intersectsAt()` と異なり、両者の順序が異なっても一致する結果を返します。
		/// @param other 別の線分
		/// @return 交差しない場合は none, 交差する場合はその座標、2 つの線分が重なっている場合 (QNaN, QNaN)
		[[nodiscard]]
		Optional<position_type> intersectsAtPrecise(const Line& other) const;


		const Line& paint(Image& dst, const Color& color) const;

		const Line& paint(Image& dst, int32 thickness, const Color& color) const;

		const Line& overwrite(Image& dst, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Line& overwrite(Image& dst, int32 thickness, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Line& paintArrow(Image& dst, double width, const Vec2& headSize, const Color& color) const;

		const Line& overwriteArrow(Image& dst, double width, const Vec2& headSize, const Color& color) const;

		const Line& paintDoubleHeadedArrow(Image& dst, double width, const Vec2& headSize, const Color& color) const;

		const Line& overwriteDoubleHeadedArrow(Image& dst, double width, const Vec2& headSize, const Color& color) const;

		
		/// @brief 線分を描きます。
		/// @param color 色
		/// @return *this
		const Line& draw(const ColorF& color = Palette::White) const;

		/// @brief 線分を描きます。
		/// @param colorBegin 始点側の色
		/// @param colorEnd 終点側の色
		/// @return *this
		const Line& draw(const ColorF& colorBegin, const ColorF& colorEnd) const;

		/// @brief 線分を描きます。
		/// @param thickness 線分の太さ
		/// @param color 色
		/// @return *this
		const Line& draw(double thickness, const ColorF& color = Palette::White) const;

		/// @brief 線分を描きます。
		/// @param thickness 線分の太さ
		/// @param colorBegin 始点側の色
		/// @param colorEnd 終点側の色
		/// @return *this
		const Line& draw(double thickness, const ColorF& colorBegin, const ColorF& colorEnd) const;

		/// @brief 線分を描きます。
		/// @param style 線のスタイル
		/// @param thickness 線分の太さ
		/// @param color 色
		/// @return *this
		const Line& draw(const LineStyle& style, double thickness, const ColorF& color = Palette::White) const;

		/// @brief 線分を描きます。
		/// @param style 線のスタイル
		/// @param thickness 線分の太さ
		/// @param colorBegin 始点側の色
		/// @param colorEnd 終点側の色
		/// @return *this
		const Line& draw(const LineStyle& style, double thickness, const ColorF& colorBegin, const ColorF& colorEnd) const;

		/// @brief 線分をもとに矢印を描きます。
		/// @param width 矢印の線の幅
		/// @param headSize 矢印の三角形のサイズ
		/// @param color 色
		/// @return *this
		const Line& drawArrow(double width = 1.0, const SizeF& headSize = SizeF{ 5.0, 5.0 }, const ColorF& color = Palette::White) const;

		/// @brief 線分をもとに両方向矢印を描きます。
		/// @param width 矢印の線の幅
		/// @param headSize 矢印の三角形のサイズ
		/// @param color 色
		/// @return *this
		const Line& drawDoubleHeadedArrow(double width = 1.0, const SizeF& headSize = SizeF{ 5.0, 5.0 }, const ColorF& color = Palette::White) const;


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

		friend void Formatter(FormatData& formatData, const Line& value);
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
	size_t operator ()(const s3d::Line& value) const noexcept
	{
		return value.hash();
	}
};
