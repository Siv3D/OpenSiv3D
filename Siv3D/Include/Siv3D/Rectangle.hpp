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
# include "NamedParameter.hpp"
# include "PointVector.hpp"
# include "Line.hpp"
# include "Intersection.hpp"
# include "Geometry2D.hpp"
# include "Quad.hpp"
# include "Color.hpp"

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

		using value_type = typename size_type::value_type;
		
		S3D_DISABLE_MSVC_WARNINGS_PUSH(4201)
		
        union
		{
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
			: pos(0, 0)
			, size(_size, _size) {}

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
			: pos(0, 0)
			, size(_w, _h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		explicit constexpr Rectangle(size_type _size) noexcept
			: pos(0, 0)
			, size(_size) {}

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
			: pos(_x, _y)
			, size(_w, _h) {}

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
			: pos(_x, _y)
			, size(_size, _size) {}

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
			: pos(_x, _y)
			, size(_size) {}

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
			: pos(_pos)
			, size(_size, _size) {}

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
			: pos(_pos)
			, size(_w, _h) {}

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
			: pos(_pos)
			, size(_size) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="r">
		/// 長方形
		/// </param>
		template <class Type>
		constexpr Rectangle(const Rectangle<Type>& r) noexcept
			: pos(static_cast<value_type>(r.x), static_cast<value_type>(r.y))
			, size(static_cast<value_type>(r.w), static_cast<value_type>(r.h)) {}

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
			: pos(_center->x - _size / 2, _center->y - _size / 2)
			, size(_size, _size) {}

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
			: pos(_center->x - _w / 2, _center->y - _h / 2)
			, size(_w, _h) {}

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
			: pos(_center->x - _size.x / 2, _center->y - _size.y / 2)
			, size(_size.x, _size.y) {}

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
			: pos(topLeft->x, topLeft->y)
			, size(_size, _size) {}

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
			: pos(topLeft->x, topLeft->y)
			, size(_w, _h) {}

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
			: pos(topLeft->x, topLeft->y)
			, size(_size.x, _size.y) {}

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
			: pos(topRight->x - _size, topRight->y)
			, size(_size, _size) {}

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
			: pos(topRight->x - _w, topRight->y)
			, size(_w, _h) {}

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
			: pos(topRight->x - _size.x, topRight->y)
			, size(_size.x, _size.y) {}

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
			: pos(bottomLeft->x, bottomLeft->y - _size)
			, size(_size, _size) {}

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
			: pos(bottomLeft->x, bottomLeft->y - _h)
			, size(_w, _h) {}

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
			: pos(bottomLeft->x, bottomLeft->y - _size.y)
			, size(_size.x, _size.y) {}

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
			: pos(bottomRight->x - _size, bottomRight->y - _size)
			, size(_size, _size) {}

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
			: pos(bottomRight->x - _w, bottomRight->y - _h)
			, size(_w, _h) {}

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
			: pos(bottomRight->x - _size.x, bottomRight->y - _size.y)
			, size(_size.x, _size.y) {}

		constexpr Rectangle(Arg::topCenter_<position_type> topCenter, value_type _size) noexcept
			: pos(topCenter->x - _size / 2, topCenter->y)
			, size(_size, _size) {}

		constexpr Rectangle(Arg::topCenter_<position_type> topCenter, value_type _w, value_type _h) noexcept
			: pos(topCenter->x - _w / 2, topCenter->y)
			, size(_w, _h) {}

		constexpr Rectangle(Arg::topCenter_<position_type> topCenter, size_type _size) noexcept
			: pos(topCenter->x - _size.x / 2, topCenter->y)
			, size(_size.x, _size.y) {}

		constexpr Rectangle(Arg::bottomCenter_<position_type> bottomCenter, value_type _size) noexcept
			: pos(bottomCenter->x - _size / 2, bottomCenter->y - _size)
			, size(_size, _size) {}

		constexpr Rectangle(Arg::bottomCenter_<position_type> bottomCenter, value_type _w, value_type _h) noexcept
			: pos(bottomCenter->x - _w / 2, bottomCenter->y - _h)
			, size(_w, _h) {}

		constexpr Rectangle(Arg::bottomCenter_<position_type> bottomCenter, size_type _size) noexcept
			: pos(bottomCenter->x - _size.x / 2, bottomCenter->y - _size.y)
			, size(_size.x, _size.y) {}

		constexpr Rectangle(Arg::leftCenter_<position_type> leftCenter, value_type _size) noexcept
			: pos(leftCenter->x, leftCenter->y - _size / 2)
			, size(_size, _size) {}

		constexpr Rectangle(Arg::leftCenter_<position_type> leftCenter, value_type _w, value_type _h) noexcept
			: pos(leftCenter->x, leftCenter->y - _h / 2)
			, size(_w, _h) {}

		constexpr Rectangle(Arg::leftCenter_<position_type> leftCenter, size_type _size) noexcept
			: pos(leftCenter->x, leftCenter->y - _size.y / 2)
			, size(_size.x, _size.y) {}

		constexpr Rectangle(Arg::rightCenter_<position_type> rightCenter, value_type _size) noexcept
			: pos(rightCenter->x - _size, rightCenter->y - _size / 2)
			, size(_size, _size) {}

		constexpr Rectangle(Arg::rightCenter_<position_type> rightCenter, value_type _w, value_type _h) noexcept
			: pos(rightCenter->x - _w, rightCenter->y - _h / 2)
			, size(_w, _h) {}

		constexpr Rectangle(Arg::rightCenter_<position_type> rightCenter, size_type _size) noexcept
			: pos(rightCenter->x - _size.x, rightCenter->y - _size.y / 2)
			, size(_size.x, _size.y) {}

		constexpr bool operator ==(const Rectangle& rect) const noexcept
		{
			return pos == rect.pos
				&& size == rect.size;
		}

		constexpr bool operator !=(const Rectangle& rect) const noexcept
		{
			return !(*this == rect);
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
		constexpr Rectangle& setPos(value_type _x, value_type _y) noexcept
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
		constexpr Rectangle& setPos(const position_type& _pos) noexcept
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
		constexpr Rectangle& setPos(Arg::center_<position_type> _center) noexcept
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
		constexpr Rectangle& setPos(Arg::topLeft_<position_type> topLeft) noexcept
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
		constexpr Rectangle& setPos(Arg::topRight_<position_type> topRight) noexcept
		{
			pos.set(topRight->x - w, topRight->y);
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
		constexpr Rectangle& setPos(Arg::bottomLeft_<position_type> bottomLeft) noexcept
		{
			pos.set(bottomLeft->x, bottomLeft->y - h);
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
		constexpr Rectangle& setPos(Arg::bottomRight_<position_type> bottomRight) noexcept
		{
			pos.set(bottomRight->x - w, bottomRight->y - h);
			return *this;
		}

		constexpr Rectangle& setPos(Arg::topCenter_<position_type> topCenter) noexcept
		{
			pos.set(topCenter->x - w / 2, topCenter->y);
			return *this;
		}

		constexpr Rectangle& setPos(Arg::bottomCenter_<position_type> bottomCenter) noexcept
		{
			pos.set(bottomCenter->x - w / 2, bottomCenter->y - h);
			return *this;
		}

		constexpr Rectangle& setPos(Arg::leftCenter_<position_type> leftCenter) noexcept
		{
			pos.set(leftCenter->x, leftCenter->y - h / 2);
			return *this;
		}

		constexpr Rectangle& setPos(Arg::rightCenter_<position_type> rightCenter) noexcept
		{
			pos.set(rightCenter->x - w, rightCenter->y - h / 2);
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
		constexpr Rectangle& setCenter(value_type _x, value_type _y) noexcept
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
		constexpr Rectangle& setCenter(const position_type& _pos) noexcept
		{
			return setCenter(_pos.x, _pos.y);
		}

		/// <summary>
		/// 長方形の大きさを変更します。
		/// </summary>
		/// <param name="_size">
		/// 新しい幅と高さ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& setSize(value_type _size) noexcept
		{
			size.set(_size, _size);
			return *this;
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
		constexpr Rectangle& setSize(value_type _w, value_type _h) noexcept
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
		constexpr Rectangle& setSize(const size_type& _size) noexcept
		{
			return setSize(_size.x, _size.y);
		}

		/// <summary>
		/// 長方形を設定します。
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
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(value_type _x, value_type _y, value_type _w, value_type _h) noexcept
		{
			pos.set(_x, _y);
			size.set(_w, _h);
			return *this;
		}

		/// <summary>
		/// 長方形を設定します。
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
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(value_type _x, value_type _y, value_type _size) noexcept
		{
			return set(_x, _y, _size, _size);
		}

		/// <summary>
		/// 長方形を設定します。
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
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(value_type _x, value_type _y, size_type _size) noexcept
		{
			return set(_x, _y, _size.x, _size.y);
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="_pos">
		/// 長方形の左上の点の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(position_type _pos, value_type _size) noexcept
		{
			return set(_pos.x, _pos.y, _size, _size);
		}

		/// <summary>
		/// 長方形を設定します。
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
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(position_type _pos, value_type _w, value_type _h) noexcept
		{
			return set(_pos.x, _pos.y, _w, _h);
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="_pos">
		/// 長方形の左上の点の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(position_type _pos, size_type _size) noexcept
		{
			return set(_pos.x, _pos.y, _size.x, _size.y);
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="r">
		/// 長方形
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Type>
		constexpr Rectangle& set(const Rectangle<Type>& r) noexcept
		{
			return set(static_cast<value_type>(r.x), static_cast<value_type>(r.y),
				static_cast<value_type>(r.w), static_cast<value_type>(r.h));
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="_center">
		/// 長方形の中心の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::center_<position_type> _center, value_type _size) noexcept
		{
			return set(_center->x - _size / 2, _center->y - _size / 2, _size, _size);
		}

		/// <summary>
		/// 長方形を設定します。
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
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::center_<position_type> _center, value_type _w, value_type _h) noexcept
		{
			return set(_center->x - _w / 2, _center->y - _h / 2, _w, _h);
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="_center">
		/// 長方形の中心の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::center_<position_type> _center, size_type _size) noexcept
		{
			return set(_center->x - _size.x / 2, _center->y - _size.y / 2, _size.x, _size.y);
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="topLeft">
		/// 長方形の左上の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::topLeft_<position_type> topLeft, value_type _size) noexcept
		{
			return set(topLeft->x, topLeft->y, _size, _size);
		}

		/// <summary>
		/// 長方形を設定します。
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
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::topLeft_<position_type> topLeft, value_type _w, value_type _h) noexcept
		{
			return set(topLeft->x, topLeft->y, _w, _h);
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="topLeft">
		/// 長方形の左上の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::topLeft_<position_type> topLeft, size_type _size) noexcept
		{
			return set(topLeft->x, topLeft->y, _size.x, _size.y);
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="topLeft">
		/// 長方形の右上の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::topRight_<position_type> topRight, value_type _size) noexcept
		{
			return set(topRight->x - _size, topRight->y, _size, _size);
		}

		/// <summary>
		/// 長方形を設定します。
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
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::topRight_<position_type> topRight, value_type _w, value_type _h) noexcept
		{
			return set(topRight->x - _w, topRight->y, _w, _h);
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="topLeft">
		/// 長方形の右上の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::topRight_<position_type> topRight, size_type _size) noexcept
		{
			return set(topRight->x - _size.x, topRight->y, _size.x, _size.y);
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="bottomLeft">
		/// 長方形の左下の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::bottomLeft_<position_type> bottomLeft, value_type _size) noexcept
		{
			return set(bottomLeft->x, bottomLeft->y - _size, _size, _size);
		}

		/// <summary>
		/// 長方形を設定します。
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
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::bottomLeft_<position_type> bottomLeft, value_type _w, value_type _h) noexcept
		{
			return set(bottomLeft->x, bottomLeft->y - _h, _w, _h);
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="bottomLeft">
		/// 長方形の左下の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::bottomLeft_<position_type> bottomLeft, size_type _size) noexcept
		{
			return set(bottomLeft->x, bottomLeft->y - _size.y, _size.x, _size.y);
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="bottomRight">
		/// 長方形の右下の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::bottomRight_<position_type> bottomRight, value_type _size) noexcept
		{
			return set(bottomRight->x - _size, bottomRight->y - _size, _size, _size);
		}

		/// <summary>
		/// 長方形を設定します。
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
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::bottomRight_<position_type> bottomRight, value_type _w, value_type _h) noexcept
		{
			return set(bottomRight->x - _w, bottomRight->y - _h, _w, _h);
		}

		/// <summary>
		/// 長方形を設定します。
		/// </summary>
		/// <param name="bottomRight">
		/// 長方形の右下の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& set(Arg::bottomRight_<position_type> bottomRight, size_type _size) noexcept
		{
			return set(bottomRight->x - _size.x, bottomRight->y - _size.y, _size.x, _size.y);
		}

		constexpr Rectangle& set(Arg::topCenter_<position_type> topCenter, value_type _size) noexcept
		{
			return set(topCenter->x - _size / 2, topCenter->y, _size, _size);
		}

		constexpr Rectangle& set(Arg::topCenter_<position_type> topCenter, value_type _w, value_type _h) noexcept
		{
			return set(topCenter->x - _w / 2, topCenter->y, _w, _h);
		}

		constexpr Rectangle& set(Arg::topCenter_<position_type> topCenter, size_type _size) noexcept
		{
			return set(topCenter->x - _size.x / 2, topCenter->y, _size.x, _size.y);
		}

		constexpr Rectangle& set(Arg::bottomCenter_<position_type> bottomCenter, value_type _size) noexcept
		{
			return set(bottomCenter->x - _size / 2, bottomCenter->y - _size, _size, _size);
		}

		constexpr Rectangle& set(Arg::bottomCenter_<position_type> bottomCenter, value_type _w, value_type _h) noexcept
		{
			return set(bottomCenter->x - _w / 2, bottomCenter->y - _h, _w, _h);
		}

		constexpr Rectangle& set(Arg::bottomCenter_<position_type> bottomCenter, size_type _size) noexcept
		{
			return set(bottomCenter->x - _size.x / 2, bottomCenter->y - _size.y, _size.x, _size.y);
		}

		constexpr Rectangle& set(Arg::leftCenter_<position_type> leftCenter, value_type _size) noexcept
		{
			return set(leftCenter->x, leftCenter->y - _size / 2, _size, _size);
		}

		constexpr Rectangle& set(Arg::leftCenter_<position_type> leftCenter, value_type _w, value_type _h) noexcept
		{
			return set(leftCenter->x, leftCenter->y - _h / 2, _w, _h);
		}

		constexpr Rectangle& set(Arg::leftCenter_<position_type> leftCenter, size_type _size) noexcept
		{
			return set(leftCenter->x, leftCenter->y - _size.y / 2, _size.x, _size.y);
		}

		constexpr Rectangle& set(Arg::rightCenter_<position_type> rightCenter, value_type _size) noexcept
		{
			return set(rightCenter->x - _size, rightCenter->y - _size / 2, _size, _size);
		}

		constexpr Rectangle& set(Arg::rightCenter_<position_type> rightCenter, value_type _w, value_type _h) noexcept
		{
			return set(rightCenter->x - _w, rightCenter->y - _h / 2, _w, _h);
		}

		constexpr Rectangle& set(Arg::rightCenter_<position_type> rightCenter, size_type _size) noexcept
		{
			return set(rightCenter->x - _size.x, rightCenter->y - _size.y / 2, _size.x, _size.y);
		}

		/// <summary>
		/// 移動した長方形を返します。
		/// </summary>
		/// <param name="_x">
		/// X 方向の移動量
		/// </param>
		/// <param name="_y">
		/// Y 方向の移動量
		/// </param>
		/// <returns>
		/// 移動した長方形
		/// </returns>
		constexpr Rectangle movedBy(value_type _x, value_type _y) const noexcept
		{
			return{ pos.movedBy(_x, _y), size };
		}

		/// <summary>
		/// 移動した長方形を返します。
		/// </summary>
		/// <param name="v">
		/// 移動量
		/// </param>
		/// <returns>
		/// 移動した長方形
		/// </returns>
		constexpr Rectangle movedBy(const size_type& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}

		/// <summary>
		/// 長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// X 方向の移動量
		/// </param>
		/// <param name="_y">
		/// Y 方向の移動量
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& moveBy(value_type _x, value_type _y) noexcept
		{
			pos.moveBy(_x, _y);
			return *this;
		}

		/// <summary>
		/// 長方形を移動させます。
		/// </summary>
		/// <param name="v">
		/// 移動量
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Rectangle& moveBy(const size_type& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		/// <summary>
		/// 伸縮した長方形を返します。
		/// </summary>
		/// <param name="xy">
		/// 上下左右方向の伸縮
		/// </param>
		/// <returns>
		/// 伸縮した長方形
		/// </returns>
		constexpr Rectangle stretched(value_type xy) const noexcept
		{
			return stretched({ xy, xy });
		}

		/// <summary>
		/// 伸縮した長方形を返します。
		/// </summary>
		/// <param name="_x">
		/// 左右方向の伸縮
		/// </param>
		/// <param name="_y">
		/// 上下方向の伸縮
		/// </param>
		/// <returns>
		/// 伸縮した長方形
		/// </returns>
		constexpr Rectangle stretched(value_type _x, value_type _y) const noexcept
		{
			return stretched({ _x, _y });
		}

		/// <summary>
		/// 伸縮した長方形を返します。
		/// </summary>
		/// <param name="xy">
		/// 左右方向と上下方向の伸縮
		/// </param>
		/// <returns>
		/// 伸縮した長方形
		/// </returns>
		constexpr Rectangle stretched(const size_type& xy) const noexcept
		{
			return{ pos - xy, size + xy * 2 };
		}

		/// <summary>
		/// 伸縮した長方形を返します。
		/// </summary>
		/// <param name="top">
		/// 上方向の伸縮
		/// </param>
		/// <param name="right">
		/// 右方向の伸縮
		/// </param>
		/// <param name="bottom">
		/// 下方向の伸縮
		/// </param>
		/// <param name="left">
		/// 左方向の伸縮
		/// </param>
		/// <returns>
		/// 伸縮した長方形
		/// </returns>
		constexpr Rectangle stretched(value_type top, value_type right, value_type bottom, value_type left) const noexcept
		{
			return{ pos.x - left, pos.y - top, size.x + left + right, size.y + top + bottom };
		}

		constexpr Rectangle<Vec2> scaled(double s) const noexcept
		{
			return scaled(s, s);
		}

		constexpr Rectangle<Vec2> scaled(double sx, double sy) const noexcept
		{
			return Rectangle<Vec2>(Arg::center(x + w * 0.5, y + h * 0.5), w * sx, h * sy);
		}

		constexpr Rectangle<Vec2> scaled(const Vec2& s) const noexcept
		{
			return scaled(s.x, s.y);
		}

		constexpr Rectangle<Vec2> scaledAt(double _x, double _y, double s) const noexcept
		{
			return scaledAt(_x, _y, s, s);
		}

		constexpr Rectangle<Vec2> scaledAt(double _x, double _y, double sx, double sy) const noexcept
		{
			return Rectangle<Vec2>(_x + (x - _x) * sx, _y + (y - _y) * sy, w * sx, h * sy);
		}

		constexpr Rectangle<Vec2> scaledAt(double _x, double _y, const Vec2& s) const noexcept
		{
			return scaledAt(_x, _y, s.x, s.y);
		}

		constexpr Rectangle<Vec2> scaledAt(const Vec2& _pos, double s) const noexcept
		{
			return scaledAt(_pos.x, _pos.y, s, s);
		}

		constexpr Rectangle<Vec2> scaledAt(const Vec2& _pos, double sx, double sy) const noexcept
		{
			return scaledAt(_pos.x, _pos.y, sx, sy);
		}

		constexpr Rectangle<Vec2> scaledAt(const Vec2& _pos, const Vec2& s) const noexcept
		{
			return scaledAt(_pos.x, _pos.y, s.x, s.y);
		}

		constexpr size_type tl() const noexcept
		{
			return pos;
		}

		constexpr size_type tr() const noexcept
		{
			return{ x + w, y };
		}

		constexpr size_type bl() const noexcept
		{
			return{ x, y + h };
		}

		constexpr size_type br() const noexcept
		{
			return{ x + w, y + h };
		}

		constexpr Vec2 center() const noexcept
		{
			return{ x + w * 0.5, y + h * 0.5 };
		}

		constexpr Line top() const noexcept
		{
			return{ tl(), tr() };
		}

		constexpr Line right() const noexcept
		{
			return{ tr(), br() };
		}

		constexpr Line bottom() const noexcept
		{
			return{ bl(), br() };
		}

		constexpr Line left() const noexcept
		{
			return{ tl(), bl() };
		}

		/// <summary>
		/// 長方形の面積を返します。
		/// </summary>
		/// <returns>
		/// 長方形の面積
		/// </returns>
		constexpr value_type area() const noexcept
		{
			return w * h;
		}

		/// <summary>
		/// 長方形の周の長さを返します。
		/// </summary>
		/// <returns>
		/// 長方形の周の長さ
		/// </returns>
		constexpr value_type perimeter() const noexcept
		{
			return (w + h) * 2;
		}

		/// <summary>
		/// 長方形を回転させた図形を返します。
		/// </summary>
		/// <param name="angle">
		/// 回転角度（ラジアン）
		/// </param>
		/// <returns>
		/// 回転した四角形
		/// </returns>
		Quad rotated(double angle) const noexcept
		{
			const Vec2 cent(x + w * 0.5, y + h * 0.5);
			const double cx = cent.x;
			const double cy = cent.y;
			const double x0 = -size.x * 0.5;
			const double x1 = size.x * 0.5;
			const double y0 = -size.y * 0.5;
			const double y1 = size.y * 0.5;
			const double s = std::sin(angle);
			const double c = std::cos(angle);
			const double x0c = x0*c;
			const double x0s = x0*s;
			const double x1c = x1*c;
			const double x1s = x1*s;
			const double y0c = y0*c;
			const double y0s = y0*s;
			const double y1c = y1*c;
			const double y1s = y1*s;
			return{ { x0c - y0s + cx, x0s + y0c + cy },{ x1c - y0s + cx, x1s + y0c + cy },{ x1c - y1s + cx, x1s + y1c + cy },{ x0c - y1s + cx, x0s + y1c + cy } };
		}

		/// <summary>
		/// 長方形を回転させた図形を返します。
		/// </summary>
		/// <param name="x">
		/// 回転軸の X 座標
		/// </param>
		/// <param name="y">
		/// 回転軸の Y 座標
		/// </param>
		/// <param name="angle">
		/// 回転角度（ラジアン）
		/// </param>
		/// <returns>
		/// 回転した四角形
		/// </returns>
		Quad rotatedAt(double _x, double _y, double angle) const noexcept
		{
			return rotatedAt({ _x, _y }, angle);
		}
		
		/// <summary>
		/// 長方形を回転させた図形を返します。
		/// </summary>
		/// <param name="pos">
		/// 回転軸の位置
		/// </param>
		/// <param name="angle">
		/// 回転角度（ラジアン）
		/// </param>
		/// <returns>
		/// 回転した四角形
		/// </returns>
		Quad rotatedAt(const Vec2& _pos, double angle) const noexcept
		{
			Vec2 pts[4] = { { x, y },{ x + w, y },{ x + w, y + h },{ x, y + h } };

			for (int i = 0; i < 4; ++i)
			{
				pts[i] -= _pos;
			}

			const double s = std::sin(angle);
			const double c = std::cos(angle);

			Quad quad;

			for (int32 i = 0; i < 4; ++i)
			{
				quad.p(i).x = pts[i].x * c - pts[i].y * s + _pos.x;
				quad.p(i).y = pts[i].x * s + pts[i].y * c + _pos.y;
			}

			return quad;
		}

		constexpr Quad shearedX(double vx) const noexcept
		{
			return{
				Vec2(x + vx, y),
				Vec2(x + w + vx, y),
				Vec2(x + w - vx, y + h),
				Vec2(x - vx, y + h) };
		}

		constexpr Quad shearedY(double vy) const noexcept
		{
			return{
				Vec2(x, y - vy),
				Vec2(x + w, y + vy),
				Vec2(x + w, y + h + vy),
				Vec2(x, y + h - vy) };
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

		// paint

		// overpaint

		// paintFrame

		// overpaintFrame

		/// <summary>
		/// 長方形を描きます。
		/// </summary>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Rectangle& draw(const ColorF& color = Palette::White) const;

		/// <summary>
		/// 長方形を描きます。
		/// </summary>
		/// <param name="colors">
		/// 各頂点の色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Rectangle& draw(const ColorF(&colors)[4]) const;

		/// <summary>
		/// 長方形を描きます。
		/// </summary>
		/// <param name="topColor">
		/// 上側の色
		/// </param>
		/// <param name="bottomColor">
		/// 下側の色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Rectangle& draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const
		{
			return draw({ *topColor, *topColor, *bottomColor, *bottomColor });
		}

		/// <summary>
		/// 長方形を描きます。
		/// </summary>
		/// <param name="leftColor">
		/// 左側の色
		/// </param>
		/// <param name="rightColor">
		/// 右側の色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Rectangle& draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const
		{
			return draw({ *leftColor, *rightColor, *rightColor, *leftColor });
		}

		/// <summary>
		/// 長方形の枠を描きます。
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
		const Rectangle& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const
		{
			return drawFrame(thickness * 0.5, thickness * 0.5, color);
		}

		/// <summary>
		/// 長方形の枠を描きます。
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
		const Rectangle& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		/// <summary>
		/// 長方形の影を描きます。
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
		const Rectangle& drawShadow(const Vec2& offset, double blurRadius, double spread = 0.0, const ColorF& color = ColorF(0.0, 0.5)) const;

		 TexturedQuad operator ()(const Texture& texture) const;

		 TexturedQuad operator ()(const TextureRegion& textureRegion) const;

		// Polygon asPolygon() const;
	};

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
namespace s3d
{
	void Formatter(FormatData& formatData, const Rect& value);

	void Formatter(FormatData& formatData, const RectF& value);

	/// <summary>
	/// 出力ストリームに長方形を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="rect">
	/// 長方形
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType, class SizeType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Rectangle<SizeType>& rect)
	{
		return	os << CharType('(')
			<< rect.x << CharType(',')
			<< rect.y << CharType(',')
			<< rect.w << CharType(',')
			<< rect.h << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに長方形を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="rect">
	/// 長方形
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType, class SizeType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, Rectangle<SizeType>& rect)
	{
		CharType unused;
		return	is >> unused
			>> rect.x >> unused
			>> rect.y >> unused
			>> rect.w >> unused
			>> rect.h >> unused;
	}
}

namespace fmt
{
	template <class ArgFormatter, class SizeType>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::Rectangle<SizeType>& rect)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = S3DSTR("({") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("})");

		f.writer().write(fmt, rect.x, rect.y, rect.w, rect.h);
	}
}
//
//////////////////////////////////////////////////////////////////////////////
