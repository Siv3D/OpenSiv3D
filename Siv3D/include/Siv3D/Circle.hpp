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
# include "LineStyle.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	class Texture;
	struct TextureRegion;
	struct TexturedCircle;

	/// @brief 円
	struct Circle
	{
		using position_type	= Vec2;

		using size_type		= position_type::value_type;

		using value_type	= position_type::value_type;

	SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			/// @brief 円の中心座標
			position_type center;

			struct
			{
				/// @brief 円の中心の X 座標
				value_type x;

				/// @brief 円の中心の Y 座標
				value_type y;
			};
		};

		/// @brief 円の半径
		/// @remark この値が負の時の挙動は未規定です。
		size_type r;

	SIV3D_DISABLE_MSVC_WARNINGS_POP()

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Circle() = default;

		/// @brief 中心が { 0, 0 } の円を作成します。
		/// @param _r 円の半径
		SIV3D_NODISCARD_CXX20
		explicit constexpr Circle(size_type _r) noexcept;

		/// @brief 中心が { 0, 0 } の円を作成します。
		/// @param _r 円の半径
		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		explicit constexpr Circle(Arithmetic _r) noexcept;

		/// @brief 円を作成します。
		/// @param _x 円の中心の X 座標
		/// @param _y 円の中心の Y 座標
		/// @param _r 円の半径
		SIV3D_NODISCARD_CXX20
		constexpr Circle(value_type _x, value_type _y, size_type _r) noexcept;

		/// @brief 円を作成します。
		/// @tparam X 引数の型
		/// @tparam Y 引数の型
		/// @tparam R 引数の型
		/// @param _x 円の中心の X 座標
		/// @param _y 円の中心の Y 座標
		/// @param _r 円の半径
		template <class X, class Y, class R>
		SIV3D_NODISCARD_CXX20
		constexpr Circle(X _x, Y _y, R _r) noexcept;

		/// @brief 円を作成します。
		/// @param _center 円の中心座標
		/// @param _r 円の半径
		SIV3D_NODISCARD_CXX20
		constexpr Circle(position_type _center, size_type _r) noexcept;

		/// @brief 円を作成します。
		/// @param _center 円の中心座標
		/// @param _r 円の半径
		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Circle(position_type _center, Arithmetic _r) noexcept;

		/// @brief 円を作成します。
		/// @param _center 円の中心座標
		/// @param _r 円の半径
		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::center_<position_type> _center, Arithmetic _r) noexcept;

		/// @brief 円を作成します。
		/// @param topLeft 円に外接する正方形の左上の座標
		/// @param _r 円の半径
		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::topLeft_<position_type> topLeft, Arithmetic _r) noexcept;

		/// @brief 円を作成します。
		/// @param topCenter 円に外接する正方形の上辺中心の座標
		/// @param _r 円の半径
		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::topCenter_<position_type> topCenter, Arithmetic _r) noexcept;

		/// @brief 円を作成します。
		/// @param topRight 円に外接する正方形の右上の座標
		/// @param _r 円の半径
		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::topRight_<position_type> topRight, Arithmetic _r) noexcept;

		/// @brief 
		/// @param rightCenter 
		/// @param _r 
		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::rightCenter_<position_type> rightCenter, Arithmetic _r) noexcept;

		/// @brief 
		/// @param bottomRight 
		/// @param _r 
		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::bottomRight_<position_type> bottomRight, Arithmetic _r) noexcept;

		/// @brief 
		/// @param bottomCenter 
		/// @param _r 
		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::bottomCenter_<position_type> bottomCenter, Arithmetic _r) noexcept;

		/// @brief 
		/// @param bottomLeft 
		/// @param _r 
		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::bottomLeft_<position_type> bottomLeft, Arithmetic _r) noexcept;

		/// @brief 
		/// @param leftCenter 
		/// @param _r 
		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::leftCenter_<position_type> leftCenter, Arithmetic _r) noexcept;

		/// @brief 
		/// @param p0 
		/// @param p1 
		SIV3D_NODISCARD_CXX20
		Circle(position_type p0, position_type p1) noexcept;

		/// @brief 
		/// @param p0 
		/// @param p1 
		/// @param p2 
		SIV3D_NODISCARD_CXX20
		Circle(const position_type& p0, const position_type& p1, const position_type& p2) noexcept;

		/// @brief 
		/// @param diameter 
		SIV3D_NODISCARD_CXX20
		explicit Circle(const Line& diameter) noexcept;

		/// @brief 
		/// @param _center 
		/// @param p 
		SIV3D_NODISCARD_CXX20
		Circle(Arg::center_<position_type> _center, const position_type& p) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const Circle& lhs, const Circle& rhs) noexcept
		{
			return (lhs.center == rhs.center)
				&& (lhs.r == rhs.r);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Circle& lhs, const Circle& rhs) noexcept
		{
			return (lhs.center != rhs.center)
				|| (lhs.r != rhs.r);
		}

		constexpr Circle& set(value_type _x, value_type _y, size_type _r) noexcept;

		constexpr Circle& set(position_type _center, size_type _r) noexcept;

		constexpr Circle& set(Arg::center_<position_type> _center, size_type _r) noexcept;

		constexpr Circle& set(Arg::topLeft_<position_type> topLeft, size_type _r) noexcept;

		constexpr Circle& set(Arg::topCenter_<position_type> topCenter, size_type _r) noexcept;

		constexpr Circle& set(Arg::topRight_<position_type> topRight, size_type _r) noexcept;

		constexpr Circle& set(Arg::rightCenter_<position_type> rightCenter, size_type _r) noexcept;

		constexpr Circle& set(Arg::bottomRight_<position_type> bottomRight, size_type _r) noexcept;

		constexpr Circle& set(Arg::bottomCenter_<position_type> bottomCenter, size_type _r) noexcept;

		constexpr Circle& set(Arg::bottomLeft_<position_type> bottomLeft, size_type _r) noexcept;

		constexpr Circle& set(Arg::leftCenter_<position_type> leftCenter, size_type _r) noexcept;

		constexpr Circle& set(const Circle& circle) noexcept;

		constexpr Circle& setCenter(value_type _x, value_type _y) noexcept;

		constexpr Circle& setCenter(position_type _center) noexcept;

		constexpr Circle& setPos(value_type _x, value_type _y) noexcept;

		constexpr Circle& setPos(position_type _center) noexcept;

		constexpr Circle& setPos(Arg::center_<position_type> _center) noexcept;

		constexpr Circle& setPos(Arg::topLeft_<position_type> topLeft) noexcept;

		constexpr Circle& setPos(Arg::topCenter_<position_type> topCenter) noexcept;

		constexpr Circle& setPos(Arg::topRight_<position_type> topRight) noexcept;

		constexpr Circle& setPos(Arg::rightCenter_<position_type> rightCenter) noexcept;

		constexpr Circle& setPos(Arg::bottomRight_<position_type> bottomRight) noexcept;

		constexpr Circle& setPos(Arg::bottomCenter_<position_type> bottomCenter) noexcept;

		constexpr Circle& setPos(Arg::bottomLeft_<position_type> bottomLeft) noexcept;

		constexpr Circle& setPos(Arg::leftCenter_<position_type> leftCenter) noexcept;

		constexpr Circle& setR(value_type _r) noexcept;

		/// @brief 中心座標を移動した新しい円を返します。
		/// @param _x X 軸方向の移動量
		/// @param _y Y 軸方向の移動量
		/// @return 新しい円
		[[nodiscard]]
		constexpr Circle movedBy(value_type _x, value_type _y) const noexcept;

		/// @brief 中心座標を移動した新しい円を返します。
		/// @param v 移動量
		/// @return 新しい円
		[[nodiscard]]
		constexpr Circle movedBy(position_type v) const noexcept;

		/// @brief 中心座標を移動させます。
		/// @param _x X 軸方向の移動量
		/// @param _y Y 軸方向の移動量
		/// @return *this
		constexpr Circle& moveBy(value_type _x, value_type _y) noexcept;

		/// @brief 中心座標を移動させます。
		/// @param v 移動量
		/// @return *this
		constexpr Circle& moveBy(position_type v) noexcept;

		/// @brief 半径を変化させた新しい円を返します。
		/// @param size 半径の変化量
		/// @return 新しい円
		[[nodiscard]]
		constexpr Circle stretched(value_type size) const noexcept;

		/// @brief X 軸、Y 軸上で径を変化させて楕円を作成します。
		/// @param _x X 軸上の径の変化量
		/// @param _y Y 軸上の径の変化量
		/// @return 楕円
		[[nodiscard]]
		constexpr Ellipse stretched(double _x, double _y) const noexcept;

		/// @brief 半径を拡大した新しい円を返します。
		/// @param s 拡大倍率
		/// @return 新しい円
		[[nodiscard]]
		constexpr Circle scaled(double s) const noexcept;

		/// @brief X 軸、Y 軸上に拡大して楕円を作成します。
		/// @param sx X 軸方向の拡大倍率
		/// @param sy Y 軸方向の拡大倍率
		/// @return 楕円
		[[nodiscard]]
		constexpr Ellipse scaled(double sx, double sy) const noexcept;

		/// @brief 円周上で最も上にある点の座標を返します。
		/// @return 最も上にある点の座標
		[[nodiscard]]
		constexpr position_type top() const noexcept;

		/// @brief 円周上で最も右にある点の座標を返します。
		/// @return 最も右にある点の座標
		[[nodiscard]]
		constexpr position_type right() const noexcept;

		/// @brief 円周上で最も下にある点の座標を返します。
		/// @return 最も下にある点の座標
		[[nodiscard]]
		constexpr position_type bottom() const noexcept;

		/// @brief 円周上で最も左にある点の座標を返します。
		/// @return 最も左にある点の座標
		[[nodiscard]]
		constexpr position_type left() const noexcept;

		[[nodiscard]]
		constexpr Line horizontalDiameter() const noexcept;

		[[nodiscard]]
		constexpr Line verticalDiameter() const noexcept;

		/// @brief 円の面積を返します。
		/// @return 円の面積
		[[nodiscard]]
		constexpr value_type area() const noexcept;

		/// @brief 円の周の長さを返します。
		/// @return 円の周の長さ
		[[nodiscard]]
		constexpr value_type perimeter() const noexcept;

		/// @brief 円に外接する正方形を返します。
		/// @return 円に外接する正方形
		[[nodiscard]]
		constexpr RectF boundingRect() const noexcept;

		/// @brief 円周上の点をラジアン (12 時方向が 0, 3 時方向が π/2, 6 時方向が π) で取得します。
		/// @param angle 方向（ラジアン）
		/// @return 円周上の点
		[[nodiscard]]
		position_type getPointByAngle(double angle) const noexcept;

		/// @brief 円から Polygon を作成します。
		/// @param quality 品質
		/// @return Polygon
		[[nodiscard]]
		Polygon asPolygon(uint32 quality = 24) const;

		[[nodiscard]]
		Polygon pieAsPolygon(double startAngle, double angle, uint32 quality = 24) const;

		[[nodiscard]]
		Polygon arcAsPolygon(double startAngle, double angle, double innerThickness, double outerThickness, uint32 quality = 24) const;

		[[nodiscard]]
		constexpr Circle lerp(const Circle& other, double f) const noexcept;

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

		/// @brief 円が現在のフレームで左クリックされ始めたかを返します。
		/// @return 円が現在のフレームで左クリックされ始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftClicked() const noexcept;

		/// @brief 円が左クリックされているかを返します。
		/// @return 円が左クリックされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftPressed() const noexcept;

		/// @brief 現在のフレームで円への左クリックが離されたかを返します。
		/// @return 現在のフレームで円への左クリックが離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftReleased() const noexcept;

		/// @brief 円が現在のフレームで右クリックされ始めたかを返します。
		/// @return 円が現在のフレームで右クリックされ始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightClicked() const noexcept;

		/// @brief 円が右クリックされているかを返します。
		/// @return 円が右クリックされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightPressed() const noexcept;

		/// @brief 現在のフレームで円への右クリックが離されたかを返します。
		/// @return 現在のフレームで円への右クリックが離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightReleased() const noexcept;

		/// @brief 円上にマウスカーソルがあるかを返します。
		/// @return 円上にマウスカーソルがある場合 true, それ以外の場合は false
		[[nodiscard]]
		bool mouseOver() const noexcept;

		const Circle& paint(Image& dst, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Circle& overwrite(Image& dst, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Circle& paintFrame(Image& dst, double innerThickness, double outerThickness, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Circle& overwriteFrame(Image& dst, double innerThickness, double outerThickness, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		//const Circle& paintPie(Image& dst, double startAngle, double angle, const Color& color) const;

		//const Circle& overwritePie(Image& dst, double startAngle, double angle, const Color& color) const;

		//const Circle& paintArc(Image& dst, double startAngle, double angle, double innerThickness, double outerThickness, const Color& color) const;

		//const Circle& overwriteArc(Image& dst, double startAngle, double angle, double innerThickness, double outerThickness, const Color& color) const;

		/// @brief 円を描きます。
		/// @param color 円の色
		/// @return *this
		const Circle& draw(const ColorF& color = Palette::White) const;

		/// @brief 円を描きます。
		/// @param innerColor 円の内側の色
		/// @param outerColor 円の外側の色
		/// @return *this
		const Circle& draw(const ColorF& innerColor, const ColorF& outerColor) const;

		/// @brief 円の枠を描きます
		/// @param thickness 枠の太さ
		/// @param color 枠の色
		/// @return *this
		const Circle& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		/// @brief 円の枠を描きます
		/// @param thickness 枠の太さ
		/// @param innerColor 内側部分の枠の色
		/// @param outerColor 外側部分の枠の色
		/// @return *this
		const Circle& drawFrame(double thickness, const ColorF& innerColor, const ColorF& outerColor) const;

		/// @brief 円の枠を描きます。
		/// @param innerThickness 基準の円から内側方向への枠の太さ
		/// @param outerThickness 基準の円から外側方向への枠の太さ
		/// @param color 枠の色
		/// @return *this
		const Circle& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		/// @brief 円の枠を描きます。
		/// @param innerThickness 基準の円から内側方向への枠の太さ
		/// @param outerThickness 基準の円から外側方向への枠の太さ
		/// @param innerColor 内側部分の枠の色
		/// @param outerColor 外側部分の枠の色
		/// @return *this
		const Circle& drawFrame(double innerThickness, double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const;
		
		const Circle& drawPie(double startAngle, double angle, const ColorF& color = Palette::White) const;

		const Circle& drawPie(double startAngle, double angle, const ColorF& innerColor, const ColorF& outerColor) const;

		const Circle& drawArc(double startAngle, double angle, double innerThickness = 1.0, double outerThickness = 0.0, const ColorF& color = Palette::White) const;

		const Circle& drawArc(double startAngle, double angle, double innerThickness, double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const;

		const Circle& drawArc(const LineStyle& style, double startAngle, double angle, double innerThickness = 1.0, double outerThickness = 0.0, const ColorF& color = Palette::White) const;

		const Circle& drawArc(const LineStyle& style, double startAngle, double angle, double innerThickness, double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const;

		const Circle& drawShadow(const Vec2& offset, double blurRadius, double spread = 0.0, const ColorF& color = ColorF{ 0.0, 0.5 }) const;

		[[nodiscard]]
		TexturedCircle operator ()(const Texture& texture) const;

		[[nodiscard]]
		TexturedCircle operator ()(const TextureRegion& textureRegion) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Circle& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(',') << CharType(' ')
				<< value.r << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Circle& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused
				>> value.r >> unused;
		}

		friend void Formatter(FormatData& formatData, const Circle& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Circle, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Circle& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {})", value.x, value.y, value.r);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.x, value.y, value.r);
		}
	}
};

template <>
struct std::hash<s3d::Circle>
{
	[[nodiscard]]
	size_t operator ()(const s3d::Circle& value) const noexcept
	{
		return value.hash();
	}
};
