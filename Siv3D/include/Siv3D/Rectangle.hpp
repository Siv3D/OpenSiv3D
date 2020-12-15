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
# include "NamedParameter.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	struct Line;
	struct Quad;
	struct RoundRect;
	class Polygon;

	/// @brief 長方形
	/// @tparam SizeType 位置とサイズを表すベクトルの型
	///
	///  pos, tl()    top()     tr()
	///        +-----------------+
	///        |                 |
	/// left() |                 | right()
	///		   |                 |
	///        +-----------------+
	///       bl()   bottom()   br() 
	/// 
	template <class SizeType>
	struct Rectangle
	{
		using position_type = SizeType;

		using size_type = SizeType;

		using value_type = typename size_type::value_type;

		SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			struct
			{
				/// @brief 長方形の左上の点の位置
				position_type pos;

				/// @brief 長方形のサイズ
				size_type size;
			};

			struct
			{
				/// @brief 長方形の左上の点の X 座標
				value_type x;

				/// @brief 長方形の左上の点の Y 座標
				value_type y;

				/// @brief 長方形の幅
				value_type w;

				/// @brief 長方形の高さ
				value_type h;
			};
		};

		SIV3D_DISABLE_MSVC_WARNINGS_POP()

		SIV3D_NODISCARD_CXX20
		Rectangle() = default;

		/// @brief 長方形を作成します。
		/// @param _size 長方形の幅と高さ
		SIV3D_NODISCARD_CXX20
		explicit constexpr Rectangle(value_type _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _w 長方形の幅
		/// @param _h 長方形の高さ
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(value_type _w, value_type _h) noexcept;

		/// @brief 長方形を作成します。
		/// @param _size 長方形の大きさ
		SIV3D_NODISCARD_CXX20
		explicit constexpr Rectangle(size_type _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _x 長方形の左上の点の X 座標
		/// @param _y 長方形の左上の点の Y 座標
		/// @param _size 長方形の縦横の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(value_type _x, value_type _y, value_type _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _x 長方形の左上の点の X 座標
		/// @param _y 長方形の左上の点の Y 座標
		/// @param _w 長方形の幅
		/// @param _h 	長方形の高さ
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(value_type _x, value_type _y, value_type _w, value_type _h) noexcept
			: pos{ _x, _y }
			, size{ _w, _h } {}

		/// @brief 長方形を作成します。
		/// @param _x 長方形の左上の点の X 座標
		/// @param _y 長方形の左上の点の Y 座標
		/// @param _size 長方形の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(value_type _x, value_type _y, size_type _size) noexcept
			: pos{ _x, _y }
			, size{ _size } {}

		/// @brief 長方形を作成します。
		/// @param _pos 長方形の左上の点の座標
		/// @param _size 長方形の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(position_type _pos, value_type _size) noexcept
			: pos{ _pos }
			, size{ _size, _size } {}

		/// @brief 長方形を作成します。
		/// @param _pos 長方形の左上の点の座標
		/// @param _w 長方形の幅
		/// @param _h 長方形の高さ
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(position_type _pos, value_type _w, value_type _h) noexcept
			: pos{ _pos }
			, size{ _w, _h } {}

		/// @brief 長方形を作成します。
		/// @param _pos 長方形の左上の点の座標
		/// @param _size 	長方形の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(position_type _pos, size_type _size) noexcept
			: pos{ _pos }
			, size{ _size } {}

		/// @brief 長方形を作成します。
		/// @tparam Type 長方形のサイズの型
		/// @param r 長方形
		template <class Type>
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(const Rectangle<Type>& r) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::center_<position_type> _center, value_type _size) noexcept
			: pos{ (_center->x - _size / 2), (_center->y - _size / 2) }
			, size{ _size, _size } {}

		/// @brief 
		/// @param _center 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::center_<position_type> _center, value_type _w, value_type _h) noexcept
			: pos{ (_center->x - _w / 2), (_center->y - _h / 2) }
			, size{ _w, _h } {}

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::center_<position_type> _center, size_type _size) noexcept
			: pos{ (_center->x - _size.x / 2), (_center->y - _size.y / 2) }
			, size{ _size.x, _size.y } {}

		/// @brief 
		/// @param topLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::topLeft_<position_type> topLeft, value_type _size) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::topLeft_<position_type> topLeft, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::topLeft_<position_type> topLeft, size_type _size) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::topCenter_<position_type> _center, value_type _size) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::topCenter_<position_type> _center, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::topCenter_<position_type> _center, size_type _size) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::topRight_<position_type> topLeft, value_type _size) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::topRight_<position_type> topLeft, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::topRight_<position_type> topLeft, size_type _size) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::rightCenter_<position_type> _center, value_type _size) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::rightCenter_<position_type> _center, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::rightCenter_<position_type> _center, size_type _size) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::bottomRight_<position_type> topLeft, value_type _size) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::bottomRight_<position_type> topLeft, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::bottomRight_<position_type> topLeft, size_type _size) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::bottomCenter_<position_type> _center, value_type _size) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::bottomCenter_<position_type> _center, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::bottomCenter_<position_type> _center, size_type _size) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::bottomLeft_<position_type> topLeft, value_type _size) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::bottomLeft_<position_type> topLeft, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::bottomLeft_<position_type> topLeft, size_type _size) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::leftCenter_<position_type> _center, value_type _size) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::leftCenter_<position_type> _center, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::leftCenter_<position_type> _center, size_type _size) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const Rectangle& lhs, const Rectangle& rhs) noexcept
		{
			return (lhs.pos == rhs.pos)
				&& (lhs.size == rhs.size);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Rectangle& lhs, const Rectangle& rhs) noexcept
		{
			return (lhs.pos != rhs.pos)
				|| (lhs.size != rhs.size);
		}


		constexpr Rectangle& setPos(value_type _x, value_type _y) noexcept;

		constexpr Rectangle& setPos(position_type _pos) noexcept;

		constexpr Rectangle& setPos(Arg::center_<position_type> _center) noexcept;

		constexpr Rectangle& setPos(Arg::topLeft_<position_type> topLeft) noexcept;

		constexpr Rectangle& setPos(Arg::topCenter_<position_type> topCenter) noexcept;

		constexpr Rectangle& setPos(Arg::topRight_<position_type> topRight) noexcept;

		constexpr Rectangle& setPos(Arg::rightCenter_<position_type> rightCenter) noexcept;

		constexpr Rectangle& setPos(Arg::bottomRight_<position_type> bottomRight) noexcept;

		constexpr Rectangle& setPos(Arg::bottomCenter_<position_type> bottomCenter) noexcept;

		constexpr Rectangle& setPos(Arg::bottomLeft_<position_type> bottomLeft) noexcept;

		constexpr Rectangle& setPos(Arg::leftCenter_<position_type> leftCenter) noexcept;

		constexpr Rectangle& setCenter(value_type _x, value_type _y) noexcept;

		constexpr Rectangle& setCenter(position_type _pos) noexcept;

		constexpr Rectangle& setSize(value_type _size) noexcept;

		constexpr Rectangle& setSize(value_type _w, value_type _h) noexcept;

		constexpr Rectangle& setSize(size_type _size) noexcept;

		constexpr Rectangle& set(value_type _x, value_type _y, value_type _w, value_type _h) noexcept;

		constexpr Rectangle& set(value_type _x, value_type _y, value_type _size) noexcept;

		constexpr Rectangle& set(value_type _x, value_type _y, size_type _size) noexcept;

		constexpr Rectangle& set(position_type _pos, value_type _size) noexcept;

		constexpr Rectangle& set(position_type _pos, value_type _w, value_type _h) noexcept;

		constexpr Rectangle& set(position_type _pos, size_type _size) noexcept;

		template <class Type>
		constexpr Rectangle& set(const Rectangle<Type>& r) noexcept;

		constexpr Rectangle& set(Arg::center_<position_type> _center, value_type _size) noexcept;

		constexpr Rectangle& set(Arg::center_<position_type> _center, value_type _w, value_type _h) noexcept;

		constexpr Rectangle& set(Arg::center_<position_type> _center, size_type _size) noexcept;

		constexpr Rectangle& set(Arg::topLeft_<position_type> topLeft, value_type _size) noexcept;

		constexpr Rectangle& set(Arg::topLeft_<position_type> topLeft, value_type _w, value_type _h) noexcept;

		constexpr Rectangle& set(Arg::topLeft_<position_type> topLeft, size_type _size) noexcept;

		constexpr Rectangle& set(Arg::topCenter_<position_type> topCenter, value_type _size) noexcept;

		constexpr Rectangle& set(Arg::topCenter_<position_type> topCenter, value_type _w, value_type _h) noexcept;

		constexpr Rectangle& set(Arg::topCenter_<position_type> topCenter, size_type _size) noexcept;

		constexpr Rectangle& set(Arg::topRight_<position_type> topRight, value_type _size) noexcept;

		constexpr Rectangle& set(Arg::topRight_<position_type> topRight, value_type _w, value_type _h) noexcept;

		constexpr Rectangle& set(Arg::topRight_<position_type> topRight, size_type _size) noexcept;

		constexpr Rectangle& set(Arg::rightCenter_<position_type> rightCenter, value_type _size) noexcept;

		constexpr Rectangle& set(Arg::rightCenter_<position_type> rightCenter, value_type _w, value_type _h) noexcept;

		constexpr Rectangle& set(Arg::rightCenter_<position_type> rightCenter, size_type _size) noexcept;

		constexpr Rectangle& set(Arg::bottomRight_<position_type> bottomRight, value_type _size) noexcept;

		constexpr Rectangle& set(Arg::bottomRight_<position_type> bottomRight, value_type _w, value_type _h) noexcept;

		constexpr Rectangle& set(Arg::bottomRight_<position_type> bottomRight, size_type _size) noexcept;

		constexpr Rectangle& set(Arg::bottomCenter_<position_type> bottomCenter, value_type _size) noexcept;

		constexpr Rectangle& set(Arg::bottomCenter_<position_type> bottomCenter, value_type _w, value_type _h) noexcept;

		constexpr Rectangle& set(Arg::bottomCenter_<position_type> bottomCenter, size_type _size) noexcept;

		constexpr Rectangle& set(Arg::bottomLeft_<position_type> bottomLeft, value_type _size) noexcept;

		constexpr Rectangle& set(Arg::bottomLeft_<position_type> bottomLeft, value_type _w, value_type _h) noexcept;

		constexpr Rectangle& set(Arg::bottomLeft_<position_type> bottomLeft, size_type _size) noexcept;

		constexpr Rectangle& set(Arg::leftCenter_<position_type> leftCenter, value_type _size) noexcept;

		constexpr Rectangle& set(Arg::leftCenter_<position_type> leftCenter, value_type _w, value_type _h) noexcept;

		constexpr Rectangle& set(Arg::leftCenter_<position_type> leftCenter, size_type _size) noexcept;

		[[nodiscard]]
		constexpr Rectangle movedBy(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		constexpr Rectangle movedBy(size_type v) const noexcept;

		constexpr Rectangle& moveBy(value_type _x, value_type _y) noexcept;

		constexpr Rectangle& moveBy(size_type v) noexcept;

		[[nodiscard]]
		constexpr Rectangle stretched(value_type xy) const noexcept;

		[[nodiscard]]
		constexpr Rectangle stretched(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		constexpr Rectangle stretched(size_type xy) const noexcept;

		[[nodiscard]]
		constexpr Rectangle stretched(value_type top, value_type right, value_type bottom, value_type left) const noexcept;

		[[nodiscard]]
		constexpr Rectangle<Vec2> scaled(double s) const noexcept;

		[[nodiscard]]
		constexpr Rectangle<Vec2> scaled(double sx, double sy) const noexcept;

		[[nodiscard]]
		constexpr Rectangle<Vec2> scaled(Vec2 s) const noexcept;

		[[nodiscard]]
		constexpr Rectangle<Vec2> scaledAt(double _x, double _y, double s) const noexcept;

		[[nodiscard]]
		constexpr Rectangle<Vec2> scaledAt(double _x, double _y, double sx, double sy) const noexcept;

		[[nodiscard]]
		constexpr Rectangle<Vec2> scaledAt(double _x, double _y, Vec2 s) const noexcept;

		[[nodiscard]]
		constexpr Rectangle<Vec2> scaledAt(Vec2 _pos, double s) const noexcept;

		[[nodiscard]]
		constexpr Rectangle<Vec2> scaledAt(Vec2 _pos, double sx, double sy) const noexcept;

		[[nodiscard]]
		constexpr Rectangle<Vec2> scaledAt(Vec2 _pos, Vec2 s) const noexcept;


		[[nodiscard]]
		constexpr size_type tl() const noexcept;

		[[nodiscard]]
		constexpr size_type tr() const noexcept;

		[[nodiscard]]
		constexpr size_type bl() const noexcept;

		[[nodiscard]]
		constexpr size_type br() const noexcept;

		[[nodiscard]]
		constexpr Vec2 topCenter() const noexcept;

		[[nodiscard]]
		constexpr Vec2 bottomCenter() const noexcept;

		[[nodiscard]]
		constexpr Vec2 leftCenter() const noexcept;

		[[nodiscard]]
		constexpr Vec2 rightCenter() const noexcept;

		[[nodiscard]]
		constexpr Vec2 center() const noexcept;

		[[nodiscard]]
		constexpr Line top() const noexcept;

		[[nodiscard]]
		constexpr Line right() const noexcept;

		[[nodiscard]]
		constexpr Line bottom() const noexcept;

		[[nodiscard]]
		constexpr Line left() const noexcept;

		[[nodiscard]]
		constexpr position_type point(size_t index) noexcept;

		[[nodiscard]]
		constexpr Line side(size_t index) noexcept;


		/// <summary>
		/// 長方形の面積を返します。
		/// </summary>
		/// <returns>
		/// 長方形の面積
		/// </returns>
		[[nodiscard]]
		constexpr value_type area() const noexcept;

		/// <summary>
		/// 長方形の周の長さを返します。
		/// </summary>
		/// <returns>
		/// 長方形の周の長さ
		/// </returns>
		[[nodiscard]]
		constexpr value_type perimeter() const noexcept;

		[[nodiscard]]
		Quad rotated(double angle) const noexcept;

		[[nodiscard]]
		Quad rotatedAt(double _x, double _y, double angle) const noexcept;

		[[nodiscard]]
		Quad rotatedAt(Vec2 _pos, double angle) const noexcept;

		[[nodiscard]]
		constexpr Quad shearedX(double vx) const noexcept;

		[[nodiscard]]
		constexpr Quad shearedY(double vy) const noexcept;

		[[nodiscard]]
		constexpr RoundRect rounded(double r) const noexcept;

		[[nodiscard]]
		Polygon rounded(double tl, double tr, double br, double bl) const noexcept;

		[[nodiscard]]
		constexpr Quad asQuad() const noexcept;

		[[nodiscard]]
		Polygon asPolygon() const;

		[[nodiscard]]
		constexpr Rectangle<Vec2> lerp(const Rectangle& other, double f) const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		template <class Shape2DType>
		[[nodiscard]]
		bool intersects(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		bool contains(const Shape2DType& other) const;

		[[nodiscard]] bool leftClicked() const noexcept;

		[[nodiscard]] bool leftPressed() const noexcept;

		[[nodiscard]] bool leftReleased() const noexcept;

		[[nodiscard]] bool rightClicked() const noexcept;

		[[nodiscard]] bool rightPressed() const noexcept;

		[[nodiscard]] bool rightReleased() const noexcept;

		[[nodiscard]] bool mouseOver() const noexcept;

		//const Rectangle& paint(Image& dst, const Color& color) const;

		//const Rectangle& overwrite(Image& dst, const Color& color) const;

		//const Rectangle& paintFrame(Image& dst, int32 innerThickness, int32 outerThickness, const Color& color) const;

		//const Rectangle& overwriteFrame(Image& dst, int32 innerThickness, int32 outerThickness, const Color& color) const;

		const Rectangle& draw(const ColorF& color = Palette::White) const;

		const Rectangle& draw(const ColorF(&colors)[4]) const;

		const Rectangle& draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		const Rectangle& draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

		const Rectangle& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		const Rectangle& drawFrame(double thickness, const ColorF& innerColor, const ColorF& outerColor) const;

		const Rectangle& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		const Rectangle& drawFrame(double innerThickness, double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const;

		//const Rectangle& drawShadow(const Vec2& offset, double blurRadius, double spread = 0.0, const ColorF& color = ColorF{ 0.0, 0.5 }) const;

		//[[nodiscard]] TexturedQuad operator ()(const Texture& texture) const;

		//[[nodiscard]] TexturedQuad operator ()(const TextureRegion& textureRegion) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Rectangle& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(',') << CharType(' ')
				<< value.w << CharType(',') << CharType(' ')
				<< value.h << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Rectangle& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused
				>> value.w >> unused
				>> value.h >> unused;
		}

		friend void Formatter(FormatData& formatData, const Rectangle& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Rectangle& value);
	};

	/// @brief 長方形（要素が int32 型）
	using Rect = Rectangle<Point>;

	/// @brief 長方形（要素が double 型）
	using RectF = Rectangle<Vec2>;
}

template <class Type>
struct SIV3D_HIDDEN fmt::formatter<s3d::Rectangle<Type>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Rectangle<Type>& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {})", value.x, value.y, value.w, value.h);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.x, value.y, value.w, value.h);
		}
	}
};

template <class Type>
struct std::hash<s3d::Rectangle<Type>>
{
	[[nodiscard]]
	size_t operator()(const s3d::Rectangle<Type>& value) const noexcept
	{
		return value.hash();
	}
};
