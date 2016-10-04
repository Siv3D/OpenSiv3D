//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
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
		using value_type = typename SizeType::value_type;

#pragma warning(disable:4201)
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
				SizeType pos;

				/// <summary>
				/// 長方形のサイズ
				/// </summary>
				SizeType size;
			};
		};

#pragma warning(default:4201)

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
		explicit constexpr Rectangle(SizeType _size) noexcept
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
		constexpr Rectangle(value_type _x, value_type _y, SizeType _size) noexcept
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
		constexpr Rectangle(SizeType _pos, value_type _size) noexcept
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
		constexpr Rectangle(SizeType _pos, value_type _w, value_type _h) noexcept
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
		constexpr Rectangle(SizeType _pos, SizeType _size) noexcept
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
		/// <param name="_pos">
		/// 長方形の左上の点の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(Arg::center_<SizeType> _center, value_type _size) noexcept
			: x(_center->x - _size / 2)
			, y(_center->y - _size / 2)
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
		constexpr Rectangle(Arg::center_<SizeType> _center, value_type _w, value_type _h) noexcept
			: x(_center->x - _w / 2)
			, y(_center->y - _h / 2)
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
		constexpr Rectangle(Arg::center_<SizeType> _center, SizeType _size) noexcept
			: x(_center->x - _size.x / 2)
			, y(_center->y - _size.y / 2)
			, w(_size.x)
			, h(_size.y) {}




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
		Rectangle& setCenter(value_type _x, value_type _y) { pos.set(_x - w / 2, _y - h / 2); return *this; }

		/// <summary>
		/// 中心位置を指定して長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 長方形の中心の新しい位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Rectangle& setCenter(const SizeType& _pos) { pos.set(_pos - size / 2); return *this; }



		constexpr bool operator == (const Rectangle& r) const
		{
			return pos == r.pos
				&& size == r.size;
		}

		constexpr bool operator != (const Rectangle& r) const
		{
			return !(*this == r);
		}
	};

	template <class CharType, class SizeType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Rectangle<SizeType>& r)
	{
		return	os << CharType('(')
			<< r.x << CharType(',')
			<< r.y << CharType(',')
			<< r.w << CharType(',')
			<< r.h << CharType(')');
	}

	template <class CharType, class SizeType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, Rectangle<SizeType>& r)
	{
		CharType unused;
		return	is >> unused
			>> r.x >> unused
			>> r.y >> unused
			>> r.w >> unused
			>> r.h >> unused;
	}

	/// <summary>
	/// 長方形（要素が int 型）
	/// </summary>
	using Rect = Rectangle<Point>;

	/// <summary>
	/// 長方形（要素が double 型）
	/// </summary>
	using RectF = Rectangle<Vec2>;
}
