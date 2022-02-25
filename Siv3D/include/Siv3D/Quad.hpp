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
	class Texture;
	struct TextureRegion;
	struct TexturedQuad;

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

		SIV3D_NODISCARD_CXX20
		explicit constexpr Quad(const Rect& rect) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Quad(const RectF& rect) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const Quad& lhs, const Quad& rhs) noexcept
		{
			return (lhs.p0 == rhs.p0)
				&& (lhs.p1 == rhs.p1)
				&& (lhs.p2 == rhs.p2)
				&& (lhs.p3 == rhs.p3);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Quad& lhs, const Quad& rhs) noexcept
		{
			return (lhs.p0 != rhs.p0)
				|| (lhs.p1 != rhs.p1)
				|| (lhs.p2 != rhs.p2)
				|| (lhs.p3 != rhs.p3);
		}

		constexpr Quad& set(value_type x0, value_type y0, value_type x1, value_type y1, value_type x2, value_type y2, value_type x3, value_type y3) noexcept;

		constexpr Quad& set(const position_type& _p0, const position_type& _p1, const position_type& _p2, const position_type& _p3) noexcept;

		constexpr Quad& set(const Quad& quad) noexcept;

		[[nodiscard]]
		constexpr Quad movedBy(value_type x, value_type y) const noexcept;

		[[nodiscard]]
		constexpr Quad movedBy(position_type v) const noexcept;

		constexpr Quad& moveBy(value_type x, value_type y) noexcept;

		constexpr Quad& moveBy(position_type v) noexcept;

		[[nodiscard]]
		Quad stretched(value_type size) const noexcept;

		[[nodiscard]]
		Quad rotatedAt(value_type x, value_type y, value_type angle) const noexcept;

		[[nodiscard]]
		Quad rotatedAt(position_type pos, value_type angle) const noexcept;

		[[nodiscard]]
		constexpr Quad scaled(double s) const noexcept;

		[[nodiscard]]
		constexpr Quad scaled(double sx, double sy) const noexcept;

		[[nodiscard]]
		constexpr Quad scaled(Vec2 s) const noexcept;

		constexpr Quad& scale(double s) noexcept;

		constexpr Quad& scale(double sx, double sy) noexcept;

		constexpr Quad& scale(Vec2 s) noexcept;

		[[nodiscard]]
		constexpr Quad scaledAt(Vec2 pos, double s) const noexcept;

		[[nodiscard]]
		constexpr Quad scaledAt(Vec2 pos, double sx, double sy) const noexcept;

		[[nodiscard]]
		constexpr Quad scaledAt(Vec2 pos, Vec2 s) const noexcept;

		constexpr Quad& scaleAt(Vec2 pos, double s) noexcept;

		constexpr Quad& scaleAt(Vec2 pos, double sx, double sy) noexcept;

		constexpr Quad& scaleAt(Vec2 pos, Vec2 s) noexcept;

		[[nodiscard]]
		position_type& p(size_t index) noexcept;

		[[nodiscard]]
		const position_type& p(size_t index) const noexcept;

		[[nodiscard]]
		constexpr position_type point(size_t index) const;

		[[nodiscard]]
		constexpr Line side(size_t index) const;

		[[nodiscard]]
		constexpr Triangle triangle(size_t index) const;

		[[nodiscard]]
		constexpr value_type area() const noexcept;

		[[nodiscard]]
		value_type perimeter() const noexcept;

		[[nodiscard]]
		constexpr RectF boundingRect() const noexcept;

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
		constexpr Quad lerp(const Quad& other, double f) const noexcept;

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

		/// @brief 四角形が現在のフレームで左クリックされ始めたかを返します。
		/// @return 四角形が現在のフレームで左クリックされ始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftClicked() const noexcept;

		/// @brief 四角形が左クリックされているかを返します。
		/// @return 四角形が左クリックされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftPressed() const noexcept;

		/// @brief 現在のフレームで四角形への左クリックが離されたかを返します。
		/// @return 現在のフレームで四角形への左クリックが離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftReleased() const noexcept;

		/// @brief 四角形が現在のフレームで右クリックされ始めたかを返します。
		/// @return 四角形が現在のフレームで右クリックされ始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightClicked() const noexcept;

		/// @brief 四角形が右クリックされているかを返します。
		/// @return 四角形が右クリックされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightPressed() const noexcept;

		/// @brief 現在のフレームで四角形への右クリックが離されたかを返します。
		/// @return 現在のフレームで四角形への右クリックが離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightReleased() const noexcept;

		/// @brief 四角形上にマウスカーソルがあるかを返します。
		/// @return 四角形上にマウスカーソルがある場合 true, それ以外の場合は false
		[[nodiscard]]
		bool mouseOver() const noexcept;

		const Quad& paint(Image& dst, const Color& color) const;

		const Quad& overwrite(Image& dst, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Quad& paintFrame(Image& dst, int32 thickness, const Color& color) const;

		const Quad& overwriteFrame(Image& dst, int32 thickness, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Quad& draw(const ColorF& color = Palette::White) const;

		const Quad& draw(const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		const Quad& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		const Quad& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		[[nodiscard]]
		TexturedQuad operator ()(const Texture& texture) const;

		[[nodiscard]]
		TexturedQuad operator ()(const TextureRegion& textureRegion) const;

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

		friend void Formatter(FormatData& formatData, const Quad& value);
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
	size_t operator ()(const s3d::Quad& value) const noexcept
	{
		return value.hash();
	}
};
