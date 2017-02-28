//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "NamedParameter.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// 長方形
	/// </summary>
	template <class SizeType>
	struct Rectangle
	{
		using position_type = SizeType;

		using size_type = SizeType;

		using value_type = typename SizeType::value_type;
		
		S3D_DISABLE_MSVC_WARNINGS_PUSH(4201)
		
        union
		{
			struct
			{
				/// <summary>
				/// 長方形の左上の点の X 座標
				/// </summary>
				value_type x;

				/// <summary>
				/// 長方形の左上の点の Y 座標
				/// </summary>
				value_type y;

				/// <summary>
				/// 長方形の幅
				/// </summary>
				value_type w;

				/// <summary>
				/// 長方形の高さ
				/// </summary>
				value_type h;
			};

			struct
			{
				/// <summary>
				/// 長方形の左上の点の位置
				/// </summary>
				position_type pos;

				/// <summary>
				/// 長方形のサイズ
				/// </summary>
				size_type size;
			};
		};

		S3D_DISABLE_MSVC_WARNINGS_POP()

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Rectangle() = default;

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_size">
		/// 長方形の幅と高さ
		/// </param>
		explicit constexpr Rectangle(value_type _size) noexcept
			: x(0)
			, y(0)
			, w(_size)
			, h(_size) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_w">
		/// 長方形の幅
		/// </param>
		/// <param name="_h">
		/// 長方形の高さ
		/// </param>
		constexpr Rectangle(value_type _w, value_type _h) noexcept
			: x(0)
			, y(0)
			, w(_w)
			, h(_h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		explicit constexpr Rectangle(size_type _size) noexcept
			: x(0)
			, y(0)
			, w(_size.x)
			, h(_size.y) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_w">
		/// 長方形の左上の点の X 座標
		/// </param>
		/// <param name="_h">
		/// 長方形の左上の点の Y 座標
		/// </param>
		/// <param name="_w">
		/// 長方形の幅
		/// </param>
		/// <param name="_h">
		/// 長方形の高さ
		/// </param>
		constexpr Rectangle(value_type _x, value_type _y, value_type _w, value_type _h) noexcept
			: x(_x)
			, y(_y)
			, w(_w)
			, h(_h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_w">
		/// 長方形の左上の点の X 座標
		/// </param>
		/// <param name="_h">
		/// 長方形の左上の点の Y 座標
		/// </param>
		/// <param name="_size">
		/// 長方形の縦横の大きさ
		/// </param>
		constexpr Rectangle(value_type _x, value_type _y, value_type _size) noexcept
			: x(_x)
			, y(_y)
			, w(_size)
			, h(_size) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_w">
		/// 長方形の左上の点の X 座標
		/// </param>
		/// <param name="_h">
		/// 長方形の左上の点の Y 座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(value_type _x, value_type _y, size_type _size) noexcept
			: x(_x)
			, y(_y)
			, w(_size.x)
			, h(_size.y) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_pos">
		/// 長方形の左上の点の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(position_type _pos, value_type _size) noexcept
			: x(_pos.x)
			, y(_pos.y)
			, w(_size)
			, h(_size) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_pos">
		/// 長方形の左上の点の座標
		/// </param>
		/// <param name="_w">
		/// 長方形の幅
		/// </param>
		/// <param name="_h">
		/// 長方形の高さ
		/// </param>
		constexpr Rectangle(position_type _pos, value_type _w, value_type _h) noexcept
			: x(_pos.x)
			, y(_pos.y)
			, w(_w)
			, h(_h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_pos">
		/// 長方形の左上の点の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(position_type _pos, size_type _size) noexcept
			: x(_pos.x)
			, y(_pos.y)
			, w(_size.x)
			, h(_size.y) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="r">
		/// 長方形
		/// </param>
		template <class Type>
		constexpr Rectangle(const Rectangle<Type>& r) noexcept
			: x(static_cast<value_type>(r.x))
			, y(static_cast<value_type>(r.y))
			, w(static_cast<value_type>(r.w))
			, h(static_cast<value_type>(r.h)) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_center">
		/// 長方形の中心の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(Arg::center_<position_type> _center, value_type _size) noexcept
			: x(_center->x - _size / 2)
			, y(_center->y - _size / 2)
			, w(_size)
			, h(_size) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_center">
		/// 長方形の中心の座標
		/// </param>
		/// <param name="_w">
		/// 長方形の幅
		/// </param>
		/// <param name="_h">
		/// 長方形の高さ
		/// </param>
		constexpr Rectangle(Arg::center_<position_type> _center, value_type _w, value_type _h) noexcept
			: x(_center->x - _w / 2)
			, y(_center->y - _h / 2)
			, w(_w)
			, h(_h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_center">
		/// 長方形の中心の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(Arg::center_<position_type> _center, size_type _size) noexcept
			: x(_center->x - _size.x / 2)
			, y(_center->y - _size.y / 2)
			, w(_size.x)
			, h(_size.y) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="topLeft">
		/// 長方形の左上の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(Arg::topLeft_<position_type> topLeft, value_type _size) noexcept
			: x(topLeft->x)
			, y(topLeft->y)
			, w(_size)
			, h(_size) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="topLeft">
		/// 長方形の左上の座標
		/// </param>
		/// <param name="_w">
		/// 長方形の幅
		/// </param>
		/// <param name="_h">
		/// 長方形の高さ
		/// </param>
		constexpr Rectangle(Arg::topLeft_<position_type> topLeft, value_type _w, value_type _h) noexcept
			: x(topLeft->x)
			, y(topLeft->y)
			, w(_w)
			, h(_h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="topLeft">
		/// 長方形の左上の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(Arg::topLeft_<position_type> topLeft, size_type _size) noexcept
			: x(topLeft->x)
			, y(topLeft->y)
			, w(_size.x)
			, h(_size.y) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="topLeft">
		/// 長方形の右上の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(Arg::topRight_<position_type> topRight, value_type _size) noexcept
			: x(topRight->x - _size)
			, y(topRight->y)
			, w(_size)
			, h(_size) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="topLeft">
		/// 長方形の右上の座標
		/// </param>
		/// <param name="_w">
		/// 長方形の幅
		/// </param>
		/// <param name="_h">
		/// 長方形の高さ
		/// </param>
		constexpr Rectangle(Arg::topRight_<position_type> topRight, value_type _w, value_type _h) noexcept
			: x(topRight->x - _w)
			, y(topRight->y)
			, w(_w)
			, h(_h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="topLeft">
		/// 長方形の右上の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(Arg::topRight_<position_type> topRight, size_type _size) noexcept
			: x(topRight->x - _size.x)
			, y(topRight->y)
			, w(_size.x)
			, h(_size.y) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="bottomLeft">
		/// 長方形の左下の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(Arg::bottomLeft_<position_type> bottomLeft, value_type _size) noexcept
			: x(bottomLeft->x)
			, y(bottomLeft->y - _size)
			, w(_size)
			, h(_size) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="bottomLeft">
		/// 長方形の左下の座標
		/// </param>
		/// <param name="_w">
		/// 長方形の幅
		/// </param>
		/// <param name="_h">
		/// 長方形の高さ
		/// </param>
		constexpr Rectangle(Arg::bottomLeft_<position_type> bottomLeft, value_type _w, value_type _h) noexcept
			: x(bottomLeft->x)
			, y(bottomLeft->y - _h)
			, w(_w)
			, h(_h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="bottomLeft">
		/// 長方形の左下の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(Arg::bottomLeft_<position_type> bottomLeft, size_type _size) noexcept
			: x(bottomLeft->x)
			, y(bottomLeft->y - _size.y)
			, w(_size.x)
			, h(_size.y) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="bottomRight">
		/// 長方形の右下の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(Arg::bottomRight_<position_type> bottomRight, value_type _size) noexcept
			: x(bottomRight->x - _size)
			, y(bottomRight->y - _size)
			, w(_size)
			, h(_size) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="bottomRight">
		/// 長方形の右下の座標
		/// </param>
		/// <param name="_w">
		/// 長方形の幅
		/// </param>
		/// <param name="_h">
		/// 長方形の高さ
		/// </param>
		constexpr Rectangle(Arg::bottomRight_<position_type> bottomRight, value_type _w, value_type _h) noexcept
			: x(bottomRight->x - _w)
			, y(bottomRight->y - _h)
			, w(_w)
			, h(_h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="bottomRight">
		/// 長方形の右下の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(Arg::bottomRight_<position_type> bottomRight, size_type _size) noexcept
			: x(bottomRight->x - _size.x)
			, y(bottomRight->y - _size.y)
			, w(_size.x)
			, h(_size.y) {}

		constexpr bool operator ==(const Rectangle& r) const noexcept
		{
			return pos == r.pos
				&& size == r.size;
		}

		constexpr bool operator !=(const Rectangle& r) const noexcept
		{
			return !(*this == r);
		}

		/// <summary>
		/// 長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 左上の点の新しい X 座標
		/// </param>
		/// <param name="_y">
		/// 左上の点の新しい Y 座標
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Rectangle& setPos(value_type _x, value_type _y)
		{
			pos.set(_x, _y);
			return *this;
		}

		/// <summary>
		/// 長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 左上の点の新しい位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Rectangle& setPos(const position_type& _pos)
		{
			return setPos(_pos.x, _pos.y);
		}

		/// <summary>
		/// 長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 中心の点の新しい位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Rectangle& setPos(Arg::center_<position_type> _center)
		{
			return setCenter(_center.value());
		}

		/// <summary>
		/// 長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 左上の点の新しい位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Rectangle& setPos(Arg::topLeft_<position_type> topLeft)
		{
			return setPos(topLeft.value());
		}

		/// <summary>
		/// 長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 右上の点の新しい位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Rectangle& setPos(Arg::topRight_<position_type> topRight)
		{
			x = topRight->x - w;
			y = topRight->y;
			return *this;
		}

		/// <summary>
		/// 長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 左下の点の新しい位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Rectangle& setPos(Arg::bottomLeft_<position_type> bottomLeft)
		{
			x = bottomLeft->x;
			y = bottomLeft->y - h;
			return *this;
		}

		/// <summary>
		/// 長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 右下の点の新しい位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Rectangle& setPos(Arg::bottomRight_<position_type> bottomRight)
		{
			x = bottomRight->x - w;
			y = bottomRight->y - h;
			return *this;
		}
	
		/// <summary>
		/// 中心位置を指定して長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 長方形の中心の新しい X 座標
		/// </param>
		/// <param name="_y">
		/// 長方形の中心の新しい Y 座標
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Rectangle& setCenter(value_type _x, value_type _y)
		{
			pos.set(_x - w / 2, _y - h / 2);
			return *this;
		}

		/// <summary>
		/// 中心位置を指定して長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 長方形の中心の新しい位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Rectangle& setCenter(const position_type& _pos)
		{
			return setCenter(_pos.x, _pos.y);
		}

		/// <summary>
		/// 長方形の大きさを変更します。
		/// </summary>
		/// <param name="_w">
		/// 新しい幅
		/// </param>
		/// <param name="_h">
		/// 新しい高さ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Rectangle& setSize(value_type _w, value_type _h)
		{
			size.set(_w, _h);
			return *this;
		}

		/// <summary>
		/// 長方形の大きさを変更します。
		/// </summary>
		/// <param name="_size">
		/// 新しい大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Rectangle& setSize(const size_type& _size)
		{
			return setSize(_size.x, _size.y);
		}


		// set

		// movedBy

		// moveBy

		// stretched

		// scaled

		// +

		// -

		// tl() tr() bl() br() center()

		// top() right() bottom() left()

		/// <summary>
		/// 長方形の面積を返します。
		/// </summary>
		/// <returns>
		/// 長方形の面積
		/// </returns>
		constexpr value_type area() const
		{
			return w * h;
		}

		/// <summary>
		/// 長方形の周の長さを返します。
		/// </summary>
		/// <returns>
		/// 長方形の周の長さ
		/// </returns>
		constexpr value_type perimeter() const
		{
			return (w + h) * 2;
		}

		// intersects

		// contains

		// leftClicked() leftPressed() leftReleased()

		// rightClicked() rightPressed() rightReleased()

		// mouseOver()

		// paint

		// overpaint

		// paintFrame

		// overpaintFrame

		// draw

		// drawFrame

		// drawShadow

		// rotated

		// rotatedAt

		// shearedX

		// shearedY

		// TexturedQuad operator()(const Texture& texture) const;

		// TexturedQuad operator()(const TextureRegion& textureRegion) const;

		// Polygon asPolygon() const;
	};

	//template <class CharType, class SizeType>
	//inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Rectangle<SizeType>& r)
	//{
	//	return	os << CharType('(')
	//		<< r.x << CharType(',')
	//		<< r.y << CharType(',')
	//		<< r.w << CharType(',')
	//		<< r.h << CharType(')');
	//}

	//template <class CharType, class SizeType>
	//inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, Rectangle<SizeType>& r)
	//{
	//	CharType unused;
	//	return	is >> unused
	//		>> r.x >> unused
	//		>> r.y >> unused
	//		>> r.w >> unused
	//		>> r.h >> unused;
	//}

	/// <summary>
	/// 長方形（要素が int 型）
	/// </summary>
	using Rect = Rectangle<Point>;

	/// <summary>
	/// 長方形（要素が double 型）
	/// </summary>
	using RectF = Rectangle<Vec2>;
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Rectangle
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[x] istream
//	[x] wistream
//	[x] fmtlib BasicFormatter<wchar>
//
/*
namespace s3d
{
	void Formatter(FormatData& formatData, const HSV& value);

	/// <summary>
	/// 出力ストリームに色を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="hsv">
	/// 色
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const HSV& hsv)
	{
		return os << CharType('(')
			<< hsv.h << CharType(',')
			<< hsv.s << CharType(',')
			<< hsv.v << CharType(')')
			<< hsv.a << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに色を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="hsv">
	/// 色
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, HSV& hsv)
	{
		CharType unused;

		is >> unused
			>> hsv.h >> unused
			>> hsv.s >> unused
			>> hsv.v >> unused;

		if (unused == CharType(','))
		{
			is >> hsv.a >> unused;
		}
		else
		{
			hsv.a = 1.0;
		}

		return is;
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::HSV& hsv)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = L"({" + tag + L"},{" + tag + L"},{" + tag + L"},{" + tag + L"})";

		f.writer().write(fmt, hsv.h, hsv.s, hsv.v, hsv.a);
	}
}
*/
//
//////////////////////////////////////////////////////////////////////////////
