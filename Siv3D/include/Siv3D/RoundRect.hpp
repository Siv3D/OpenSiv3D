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
# include "NamedParameter.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	class Texture;
	struct TextureRegion;
	struct TexturedRoundRect;

	/// @brief 角丸長方形
	struct RoundRect
	{
		using position_type	= RectF::position_type;

		using size_type		= RectF::size_type;

		using value_type	= position_type::value_type;

	SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			RectF rect;

			struct
			{
				value_type x, y, w, h;
			};
		};

		value_type r;

	SIV3D_DISABLE_MSVC_WARNINGS_POP()

		SIV3D_NODISCARD_CXX20
		RoundRect() = default;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param _w 
		/// @param _h 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(value_type _x, value_type _y, value_type _w, value_type _h, value_type _r) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic R>
	# else
		template <class X, class Y, class W, class H, class R, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<R>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(X _x, Y _y, W _w, H _h, R _r) noexcept;

		/// @brief 
		/// @param pos 
		/// @param _w 
		/// @param _h 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(position_type pos, value_type _w, value_type _h, value_type _r) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic R>
	# else
		template <class W, class H, class R, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<R>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(position_type pos, W _w, H _h, R _r) noexcept;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param size 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(value_type _x, value_type _y, size_type size, value_type _r) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic R>
	# else
		template <class X, class Y, class R, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<R>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(X _x, Y _y, size_type size, R _r) noexcept;

		/// @brief 
		/// @param pos 
		/// @param size 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(position_type pos, value_type size, value_type _r) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic S, Concept::Arithmetic R>
	# else
		template <class S, class R, std::enable_if_t<std::conjunction_v<std::is_arithmetic<S>, std::is_arithmetic<R>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(position_type pos, S size, R _r) noexcept;

		/// @brief 
		/// @param pos 
		/// @param size 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(position_type pos, size_type size, value_type _r) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _w 
		/// @param _h 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(Arg::center_<position_type> _center, value_type _w, value_type _h, value_type _r) noexcept;

		/// @brief 
		/// @param _center 
		/// @param size 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(Arg::center_<position_type> _center, size_type size, value_type _r) noexcept;

		/// @brief 
		/// @param _rect 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(const RectF& _rect, value_type _r) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const RoundRect& lhs, const RoundRect& rhs) noexcept
		{
			return (lhs.rect == rhs.rect)
				&& (lhs.r == rhs.r);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const RoundRect& lhs, const RoundRect& rhs) noexcept
		{
			return (lhs.rect != rhs.rect)
				|| (lhs.r != rhs.r);
		}

		constexpr RoundRect& set(value_type _x, value_type _y, value_type _w, value_type _h, value_type _r) noexcept;

		constexpr RoundRect& set(const position_type& pos, value_type _w, value_type _h, value_type _r) noexcept;

		constexpr RoundRect& set(value_type _x, value_type _y, const size_type& size, value_type _r) noexcept;

		constexpr RoundRect& set(const position_type& pos, const size_type& size, value_type _r) noexcept;

		constexpr RoundRect& set(const RectF& _rect, value_type _r) noexcept;

		constexpr RoundRect& set(const RoundRect& roundRect) noexcept;

		constexpr RoundRect& setPos(value_type _x, value_type _y) noexcept;

		constexpr RoundRect& setPos(position_type _pos) noexcept;

		constexpr RoundRect& setCenter(value_type _x, value_type _y) noexcept;

		constexpr RoundRect& setCenter(position_type _center) noexcept;

		constexpr RoundRect& setSize(value_type _w, value_type _h) noexcept;

		constexpr RoundRect& setSize(size_type _size) noexcept;

		[[nodiscard]]
		constexpr RoundRect movedBy(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		constexpr RoundRect movedBy(position_type v) const noexcept;

		constexpr RoundRect& moveBy(value_type _x, value_type _y) noexcept;

		constexpr RoundRect& moveBy(position_type v) noexcept;

		[[nodiscard]]
		constexpr RoundRect stretched(value_type size) const noexcept;

		[[nodiscard]]
		constexpr RoundRect stretched(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		constexpr RoundRect stretched(size_type xy) const noexcept;

		[[nodiscard]]
		constexpr RoundRect stretched(value_type top, value_type right, value_type bottom, value_type left) const noexcept;

		[[nodiscard]]
		constexpr position_type topCenter() const noexcept;

		[[nodiscard]]
		constexpr position_type bottomCenter() const noexcept;

		[[nodiscard]]
		constexpr position_type leftCenter() const noexcept;

		[[nodiscard]]
		constexpr position_type rightCenter() const noexcept;

		[[nodiscard]]
		constexpr position_type center() const noexcept;

		[[nodiscard]]
		constexpr value_type area() const noexcept;

		[[nodiscard]]
		constexpr value_type perimeter() const noexcept;

		[[nodiscard]]
		constexpr value_type horizontalAspectRatio() const noexcept;

		[[nodiscard]]
		Array<Vec2> outerVertices(uint32 quality = 24) const;

		[[nodiscard]]
		Polygon asPolygon(uint32 quality = 24) const;

		[[nodiscard]]
		constexpr RoundRect lerp(const RoundRect& other, double f) const noexcept;

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

		/// @brief 角丸長方形が現在のフレームで左クリックされ始めたかを返します。
		/// @return 角丸長方形が現在のフレームで左クリックされ始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftClicked() const noexcept;

		/// @brief 角丸長方形が左クリックされているかを返します。
		/// @return 角丸長方形が左クリックされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftPressed() const noexcept;

		/// @brief 現在のフレームで角丸長方形への左クリックが離されたかを返します。
		/// @return 現在のフレームで角丸長方形への左クリックが離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftReleased() const noexcept;

		/// @brief 角丸長方形が現在のフレームで右クリックされ始めたかを返します。
		/// @return 角丸長方形が現在のフレームで右クリックされ始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightClicked() const noexcept;

		/// @brief 角丸長方形が右クリックされているかを返します。
		/// @return 角丸長方形が右クリックされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightPressed() const noexcept;

		/// @brief 現在のフレームで角丸長方形への右クリックが離されたかを返します。
		/// @return 現在のフレームで角丸長方形への右クリックが離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightReleased() const noexcept;

		/// @brief 角丸長方形上にマウスカーソルがあるかを返します。
		/// @return 角丸長方形上にマウスカーソルがある場合 true, それ以外の場合は false
		[[nodiscard]]
		bool mouseOver() const noexcept;

		const RoundRect& paint(Image& dst, const Color& color) const;

		const RoundRect& overwrite(Image& dst, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const RoundRect& paintFrame(Image& dst, int32 innerThickness, int32 outerThickness, const Color& color) const;

		const RoundRect& overwriteFrame(Image& dst, int32 innerThickness, int32 outerThickness, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const RoundRect& draw(const ColorF& color = Palette::White) const;

		const RoundRect& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		const RoundRect& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		const RoundRect& drawShadow(const Vec2& offset, double blurRadius, double spread = 0.0, const ColorF& color = ColorF{ 0.0, 0.5 }) const;

		[[nodiscard]]
		TexturedRoundRect operator ()(const Texture& texture) const;

		[[nodiscard]]
		TexturedRoundRect operator ()(const TextureRegion& textureRegion) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const RoundRect& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(',') << CharType(' ')
				<< value.w << CharType(',') << CharType(' ')
				<< value.h << CharType(',') << CharType(' ')
				<< value.r << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, RoundRect& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused
				>> value.w >> unused
				>> value.h >> unused
				>> value.r >> unused;
		}

		friend void Formatter(FormatData& formatData, const RoundRect& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::RoundRect, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::RoundRect& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {}, {})", value.x, value.y, value.w, value.h, value.r);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.x, value.y, value.w, value.h, value.r);
		}
	}
};

template <>
struct std::hash<s3d::RoundRect>
{
	[[nodiscard]]
	size_t operator ()(const s3d::RoundRect& value) const noexcept
	{
		return value.hash();
	}
};
