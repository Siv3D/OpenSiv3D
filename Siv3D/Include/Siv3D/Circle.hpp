//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "Line.hpp"
# include "Array.hpp"
# include "Geometry2D.hpp"
# include "MathConstants.hpp"
# include "NamedParameter.hpp"

namespace s3d
{
	struct Circle
	{
		using position_type = Vec2;

		using size_type = position_type::value_type;

		using value_type = position_type::value_type;

		S3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			/// <summary>
			/// 円の中心座標
			/// </summary>
			position_type center;

			struct
			{
				/// <summary>
				/// 円の中心の X 座標
				/// </summary>
				value_type x;

				/// <summary>
				/// 円の中心の Y 座標
				/// </summary>
				value_type y;
			};
		};

		/// <summary>
		/// 円の半径
		/// </summary>
		size_type r;

		S3D_DISABLE_MSVC_WARNINGS_POP()

		Circle() = default;

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="_r">
		/// 円の半径
		/// </param>
		explicit constexpr Circle(size_type _r) noexcept
			: center(0.0, 0.0)
			, r(_r) {}

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="_x">
		/// 円の中心の X 座標
		/// </param>
		/// <param name="_y">
		/// 円の中心の Y 座標
		/// </param>
		/// <param name="_r">
		/// 円の半径
		/// </param>
		constexpr Circle(value_type _x, value_type _y, size_type _r) noexcept
			: center(_x, _y)
			, r(_r) {}

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="_center">
		/// 円の中心の座標
		/// </param>
		/// <param name="_r">
		/// 円の半径
		/// </param>
		constexpr Circle(const position_type& _center, size_type _r) noexcept
			: center(_center)
			, r(_r) {}

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="_center">
		/// 円の中心の座標
		/// </param>
		/// <param name="_r">
		/// 円の半径
		/// </param>
		constexpr Circle(Arg::center_<position_type> _center, size_type _r) noexcept
			: center(_center.value())
			, r(_r) {}

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="topLeft">
		/// 円に外接する正方形の左上の座標
		/// </param>
		/// <param name="_r">
		/// 円の半径
		/// </param>
		constexpr Circle(Arg::topLeft_<position_type> topLeft, size_type _r) noexcept
			: center(topLeft->x + _r, topLeft->y + _r)
			, r(_r) {}

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="topRight">
		/// 円に外接する正方形の右上の座標
		/// </param>
		/// <param name="_r">
		/// 円の半径
		/// </param>
		constexpr Circle(Arg::topRight_<position_type> topRight, size_type _r) noexcept
			: center(topRight->x + _r, topRight->y + _r)
			, r(_r) {}

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="bottomLeft">
		/// 円に外接する正方形の左下の座標
		/// </param>
		/// <param name="_r">
		/// 円の半径
		/// </param>
		constexpr Circle(Arg::bottomLeft_<position_type> bottomLeft, size_type _r) noexcept
			: center(bottomLeft->x + _r, bottomLeft->y - _r)
			, r(_r) {}

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="bottomRight">
		/// 円に外接する正方形の右下の座標
		/// </param>
		/// <param name="_r">
		/// 円の半径
		/// </param>
		constexpr Circle(Arg::bottomRight_<position_type> bottomRight, size_type _r) noexcept
			: center(bottomRight->x - _r, bottomRight->y - _r)
			, r(_r) {}

		constexpr Circle(Arg::topCenter_<position_type> topCenter, size_type _r) noexcept
			: center(topCenter->x, topCenter->y + _r)
			, r(_r) {}

		constexpr Circle(Arg::bottomCenter_<position_type> bottomCenter, size_type _r) noexcept
			: center(bottomCenter->x, bottomCenter->y - _r)
			, r(_r) {}

		constexpr Circle(Arg::leftCenter_<position_type> leftCenter, size_type _r) noexcept
			: center(leftCenter->x + _r, leftCenter->y)
			, r(_r) {}

		constexpr Circle(Arg::rightCenter_<position_type> rightCenter, size_type _r) noexcept
			: center(rightCenter->x - _r, rightCenter->y)
			, r(_r) {}

		Circle(const position_type& p0, const position_type& p1) noexcept
			: center((p0 + p1) / 2.0)
			, r(p0.distanceFrom(p1) / 2.0) {}

		Circle(const position_type& p0, const position_type& p1, const position_type& p2) noexcept;

		explicit Circle(const Line& diameter) noexcept
			: Circle(diameter.begin, diameter.end) {}

		Circle(Arg::center_<position_type> _center, const position_type& p) noexcept
			: center(_center.value())
			, r(p.distanceFrom(_center.value())) {}

		constexpr bool operator ==(const Circle& circle) const noexcept
		{
			return center == circle.center
				&& r == circle.r;
		}

		constexpr bool operator !=(const Circle& circle) const noexcept
		{
			return !(*this == circle);
		}

		constexpr Circle& set(value_type _x, value_type _y, size_type _r) noexcept
		{
			center.set(_x, _y);
			r = _r;
			return *this;
		}

		constexpr Circle& set(const position_type& _center, size_type _r) noexcept
		{
			return set(_center.x, _center.y, _r);
		}

		constexpr Circle& set(Arg::center_<position_type> _center, size_type _r) noexcept
		{
			return set(_center->x, _center->y, _r);
		}

		constexpr Circle& set(Arg::topLeft_<position_type> topLeft, size_type _r) noexcept
		{
			return set(topLeft->x + _r, topLeft->y + _r, _r);
		}

		constexpr Circle& set(Arg::topRight_<position_type> topRight, size_type _r) noexcept
		{
			return set(topRight->x + _r, topRight->y + _r, _r);
		}

		constexpr Circle& set(Arg::bottomLeft_<position_type> bottomLeft, size_type _r) noexcept
		{
			return set(bottomLeft->x + _r, bottomLeft->y - _r, _r);
		}

		constexpr Circle& set(Arg::bottomRight_<position_type> bottomRight, size_type _r) noexcept
		{
			return set(bottomRight->x - _r, bottomRight->y - _r, _r);
		}

		constexpr Circle& set(Arg::topCenter_<position_type> topCenter, size_type _r) noexcept
		{
			return set(topCenter->x, topCenter->y + _r, _r);
		}

		constexpr Circle& set(Arg::bottomCenter_<position_type> bottomCenter, size_type _r) noexcept
		{
			return set(bottomCenter->x, bottomCenter->y - _r, _r);
		}

		constexpr Circle& set(Arg::leftCenter_<position_type> leftCenter, size_type _r) noexcept
		{
			return set(leftCenter->x + _r, leftCenter->y, _r);
		}

		constexpr Circle& set(Arg::rightCenter_<position_type> rightCenter, size_type _r) noexcept
		{
			return set(rightCenter->x - _r, rightCenter->y, _r);
		}

		constexpr Circle& set(const Circle& circle) noexcept
		{
			return *this = circle;
		}

		constexpr Circle& setCenter(value_type _x, value_type _y) noexcept
		{
			center.set(_x, _y);
			return *this;
		}

		constexpr Circle& setCenter(const position_type& _center) noexcept
		{
			return setCenter(_center.x, _center.y);
		}

		constexpr Circle& setPos(value_type _x, value_type _y) noexcept
		{
			return setCenter(_x, _y);
		}

		constexpr Circle& setPos(const position_type& _center) noexcept
		{
			return setCenter(_center.x, _center.y);
		}

		constexpr Circle& setPos(Arg::center_<position_type> _center) noexcept
		{
			return setCenter(_center->x, _center->y);
		}

		constexpr Circle& setPos(Arg::topLeft_<position_type> topLeft) noexcept
		{
			return setCenter(topLeft->x + r, topLeft->y + r);
		}

		constexpr Circle& setPos(Arg::topRight_<position_type> topRight) noexcept
		{
			return setCenter(topRight->x + r, topRight->y + r);
		}

		constexpr Circle& setPos(Arg::bottomLeft_<position_type> bottomLeft) noexcept
		{
			return setCenter(bottomLeft->x + r, bottomLeft->y - r);
		}

		constexpr Circle& setPos(Arg::bottomRight_<position_type> bottomRight) noexcept
		{
			return setCenter(bottomRight->x - r, bottomRight->y - r);
		}

		constexpr Circle& setPos(Arg::topCenter_<position_type> topCenter) noexcept
		{
			return setCenter(topCenter->x, topCenter->y + r);
		}

		constexpr Circle& setPos(Arg::bottomCenter_<position_type> bottomCenter) noexcept
		{
			return setCenter(bottomCenter->x, bottomCenter->y - r);
		}

		constexpr Circle& setPos(Arg::leftCenter_<position_type> leftCenter) noexcept
		{
			return setCenter(leftCenter->x + r, leftCenter->y);
		}

		constexpr Circle& setPos(Arg::rightCenter_<position_type> rightCenter) noexcept
		{
			return setCenter(rightCenter->x - r, rightCenter->y);
		}

		constexpr Circle& setR(double _r) noexcept
		{
			r = _r;
			return *this;
		}

		constexpr Circle movedBy(value_type _x, value_type _y) const noexcept
		{
			return{ center.movedBy(_x, _y), r };
		}

		constexpr Circle movedBy(const position_type& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}

		constexpr Circle& moveBy(value_type _x, value_type _y) noexcept
		{
			center.moveBy(_x, _y);
			return *this;
		}

		constexpr Circle& moveBy(const position_type& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		constexpr Circle stretched(value_type size) const noexcept
		{
			return Circle(center, r + size);
		}

		Ellipse stretched(double _x, double _y) const noexcept;

		constexpr Circle scaled(double s) const noexcept
		{
			return Circle(center, r * s);
		}

		Ellipse scaled(double sx, double sy) const noexcept;

		constexpr position_type top() const noexcept
		{
			return{ center.x, center.y - r };
		}

		constexpr position_type right() const noexcept
		{
			return{ center.x + r, center.y };
		}

		constexpr position_type bottom() const noexcept
		{
			return{ center.x, center.y + r };
		}

		constexpr position_type left() const noexcept
		{
			return{ center.x - r, center.y };
		}

		constexpr Line lineDiameter() const noexcept
		{
			return{ left(), right() };
		}

		constexpr value_type area() const noexcept
		{
			return r * r * Math::Pi;
		}

		constexpr value_type perimeter() const noexcept
		{
			return 2 * r * Math::Pi;
		}

		template <class Shape2DType>
		bool intersects(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::Intersect(*this, shape)))
		{
			return Geometry2D::Intersect(*this, shape);
		}

		template <class Shape2DType>
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::IntersectAt(*this, shape)))
		{
			return Geometry2D::IntersectAt(*this, shape);
		}

		template <class Shape2DType>
		bool contains(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::Contains(*this, shape)))
		{
			return Geometry2D::Contains(*this, shape);
		}

		bool leftClicked() const;

		bool leftPressed() const;

		bool leftReleased() const;

		bool rightClicked() const;

		bool rightPressed() const;

		bool rightReleased() const;

		bool mouseOver() const;

		// paint~ overpaint~ draw~

		/// <summary>
		/// 円を描きます。
		/// </summary>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Circle& draw(const ColorF& color = Palette::White) const;

		/// <summary>
		/// 円の枠を描きます。
		/// </summary>
		/// <param name="thickness">
		/// 枠の太さ
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Circle& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const
		{
			return drawFrame(thickness * 0.5, thickness * 0.5, color);
		}

		/// <summary>
		/// 円の枠を描きます。
		/// </summary>
		/// <param name="innerThickness">
		/// 内側の太さ
		/// </param>
		/// <param name="outerThickness">
		/// 外側の太さ
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Circle& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		/// <summary>
		/// 円の枠を描きます。
		/// </summary>
		/// <param name="innerThickness">
		/// 内側の太さ
		/// </param>
		/// <param name="outerThickness">
		/// 外側の太さ
		/// </param>
		/// <param name="innerColor">
		/// 色
		/// </param>
		/// <param name="outerColor">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Circle& drawFrame(double innerThickness, double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const;

		/// <summary>
		/// 扇形を描きます。
		/// </summary>
		/// <param name="startAngle">
		/// 開始角度
		/// </param>
		/// <param name="angle">
		/// 角度
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Circle& drawPie(double startAngle, double angle, const ColorF& color = Palette::White) const;

		/// <summary>
		/// 弧を描きます。
		/// </summary>
		/// <param name="startAngle">
		/// 開始角度
		/// </param>
		/// <param name="angle">
		/// 角度
		/// </param>
		/// <param name="innerThickness">
		/// 内側の太さ
		/// </param>
		/// <param name="outerThickness">
		/// 外側の太さ
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Circle& drawArc(double startAngle, double angle, double innerThickness = 1.0, double outerThickness = 0.0, const ColorF& color = Palette::White) const;

		/// <summary>
		/// 円の影を描きます。
		/// </summary>
		/// <param name="offset">
		/// 影の移動量（ピクセル）
		/// </param>
		/// <param name="blurRadius">
		/// 影のぼかしの大きさ（ピクセル）
		/// </param>
		/// <param name="spread">
		/// 長方形の広がり（ピクセル）
		/// </param>
		/// <param name="color">
		/// 影の色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Circle& drawShadow(const Vec2& offset, double blurRadius, double spread = 0.0, const ColorF& color = ColorF(0.0, 0.5)) const;

		TexturedCircle operator ()(const Texture& texture) const;

		TexturedCircle operator ()(const TextureRegion& textureRegion) const;

		// Polygon asPolygon() const;
	};
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Circle
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[x] istream
//	[x] wistream
//	[x] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	inline void Formatter(FormatData& formatData, const Circle& value)
	{
		Formatter(formatData, Vec3(value.x, value.y, value.r));
	}

	/// <summary>
	/// 出力ストリームに円を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="circle">
	/// 円
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Circle& circle)
	{
		return	os << CharType('(')
			<< circle.x << CharType(',')
			<< circle.y << CharType(',')
			<< circle.r << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに円を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="circle">
	/// 円
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, Circle& circle)
	{
		CharType unused;
		return	is >> unused
			>> circle.x >> unused
			>> circle.y >> unused
			>> circle.r >> unused;
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::Circle& circle)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = S3DSTR("({") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("})");

		f.writer().write(fmt, circle.x, circle.y, circle.r);
	}
}
//
//////////////////////////////////////////////////////////////////////////////
