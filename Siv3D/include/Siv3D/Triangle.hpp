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
# include "PredefinedYesNo.hpp"

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

		constexpr Triangle& set(value_type x0, value_type y0, value_type x1, value_type y1, value_type x2, value_type y2) noexcept;

		constexpr Triangle& set(const position_type& _p0, const position_type& _p1, const position_type& _p2) noexcept;

		constexpr Triangle& set(const Triangle& triangle) noexcept;

		[[nodiscard]]
		constexpr Triangle movedBy(value_type x, value_type y) const noexcept;

		[[nodiscard]]
		constexpr Triangle movedBy(position_type v) const noexcept;

		constexpr Triangle& moveBy(value_type x, value_type y) noexcept;

		constexpr Triangle& moveBy(position_type v) noexcept;

		constexpr Triangle& setCentroid(value_type x, value_type y) noexcept;

		constexpr Triangle& setCentroid(position_type pos) noexcept;

		[[nodiscard]]
		constexpr position_type centroid() const noexcept;

		[[nodiscard]]
		Triangle stretched(value_type size) const noexcept;

		[[nodiscard]]
		Triangle rotated(value_type angle) const noexcept;

		[[nodiscard]]
		Triangle rotatedAt(value_type x, value_type y, value_type angle) const noexcept;

		[[nodiscard]]
		Triangle rotatedAt(position_type pos, value_type angle) const noexcept;

		[[nodiscard]]
		constexpr Triangle scaled(double s) const noexcept;
		
		[[nodiscard]]
		constexpr Triangle scaled(double sx, double sy) const noexcept;
		
		[[nodiscard]]
		constexpr Triangle scaled(Vec2 s) const noexcept;

		constexpr Triangle& scale(double s) noexcept;

		constexpr Triangle& scale(double sx, double sy) noexcept;

		constexpr Triangle& scale(Vec2 s) noexcept;

		[[nodiscard]]
		constexpr Triangle scaledAt(Vec2 pos, double s) const noexcept;

		[[nodiscard]]
		constexpr Triangle scaledAt(Vec2 pos, double sx, double sy) const noexcept;

		[[nodiscard]]
		constexpr Triangle scaledAt(Vec2 pos, Vec2 s) const noexcept;

		constexpr Triangle& scaleAt(Vec2 pos, double s) noexcept;

		constexpr Triangle& scaleAt(Vec2 pos, double sx, double sy) noexcept;

		constexpr Triangle& scaleAt(Vec2 pos, Vec2 s) noexcept;

		[[nodiscard]]
		constexpr position_type& p(size_t index) noexcept;

		[[nodiscard]]
		constexpr const position_type& p(size_t index) const noexcept;

		[[nodiscard]]
		constexpr position_type point(size_t index) const;

		[[nodiscard]]
		constexpr Line side(size_t index) const;

		[[nodiscard]] value_type area() const noexcept;

		[[nodiscard]] value_type perimeter() const noexcept;
	
		[[nodiscard]]
		constexpr RectF boundingRect() const noexcept;

		[[nodiscard]]
		Circle getCircumscribedCircle() const noexcept;

		[[nodiscard]]
		Circle getInscribedCircle() const noexcept;

		[[nodiscard]]
		Polygon calculateBuffer(double distance) const;

		[[nodiscard]]
		Polygon calculateRoundBuffer(double distance) const;

		[[nodiscard]]
		LineString outline(CloseRing closeRing = CloseRing::No) const;

		[[nodiscard]]
		LineString outline(double distanceFromOrigin, double length) const;

		[[nodiscard]]
		Polygon asPolygon() const;

		[[nodiscard]]
		constexpr Triangle lerp(const Triangle& other, double f) const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		template <class Shape2DType>
		[[nodiscard]]
		constexpr bool intersects(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		bool contains(const Shape2DType& other) const;

		/// @brief 三角形が現在のフレームで左クリックされ始めたかを返します。
		/// @return 三角形が現在のフレームで左クリックされ始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftClicked() const noexcept;

		/// @brief 三角形が左クリックされているかを返します。
		/// @return 三角形が左クリックされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftPressed() const noexcept;

		/// @brief 現在のフレームで三角形への左クリックが離されたかを返します。
		/// @return 現在のフレームで三角形への左クリックが離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftReleased() const noexcept;

		/// @brief 三角形が現在のフレームで右クリックされ始めたかを返します。
		/// @return 三角形が現在のフレームで右クリックされ始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightClicked() const noexcept;

		/// @brief 三角形が右クリックされているかを返します。
		/// @return 三角形が右クリックされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightPressed() const noexcept;

		/// @brief 現在のフレームで三角形への右クリックが離されたかを返します。
		/// @return 現在のフレームで三角形への右クリックが離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightReleased() const noexcept;

		/// @brief 三角形上にマウスカーソルがあるかを返します。
		/// @return 三角形上にマウスカーソルがある場合 true, それ以外の場合は false
		[[nodiscard]]
		bool mouseOver() const noexcept;

		const Triangle& paint(Image& dst, const Color& color) const;

		const Triangle& overwrite(Image& dst, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Triangle& paintFrame(Image& dst, int32 thickness, const Color& color) const;

		const Triangle& overwriteFrame(Image& dst, int32 thickness, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Triangle& draw(const ColorF& color = Palette::White) const;

		const Triangle& draw(const ColorF& color0, const ColorF& color1, const ColorF& color2) const;

		const Triangle& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		const Triangle& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		[[nodiscard]]
		static Triangle FromPoints(const position_type& baseCenter, const position_type& top, double baseLength) noexcept;

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

		friend void Formatter(FormatData& formatData, const Triangle& value);
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
	size_t operator ()(const s3d::Triangle& value) const noexcept
	{
		return value.hash();
	}
};
