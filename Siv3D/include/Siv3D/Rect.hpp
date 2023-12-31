﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
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
# include "PredefinedYesNo.hpp"

namespace s3d
{
	class Texture;
	struct TextureRegion;
	struct TexturedQuad;

	/// @brief 長方形 (成分が int32 型)
	/// @remark
	///
	///  pos, tl()    top()     tr()
	///        +-----------------+
	///        |                 |
	/// left() |                 | right()
	///		   |                 |
	///        +-----------------+
	///       bl()   bottom()   br() 
	/// 
	struct Rect
	{
		using position_type = Point;

		using size_type		= Point;

		using value_type	= size_type::value_type;

	SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			/// @brief 長方形の左上の点の位置
			position_type pos;

			struct
			{
				/// @brief 長方形の左上の点の X 座標
				value_type x;

				/// @brief 長方形の左上の点の Y 座標
				value_type y;
			};
		};

		union
		{
			/// @brief 長方形のサイズ
			size_type size;

			struct
			{
				/// @brief 長方形の幅
				/// @remark この値が負の時の挙動は未規定です。
				value_type w;

				/// @brief 長方形の高さ
				/// @remark この値が負の時の挙動は未規定です。
				value_type h;
			};
		};

	SIV3D_DISABLE_MSVC_WARNINGS_POP()

		SIV3D_NODISCARD_CXX20
		Rect() = default;

		/// @brief 長方形を作成します。
		/// @param _size 長方形の幅と高さ
		SIV3D_NODISCARD_CXX20
		explicit constexpr Rect(value_type _size) noexcept;

		SIV3D_CONCEPT_INTEGRAL
		SIV3D_NODISCARD_CXX20
		explicit constexpr Rect(Int _r) noexcept;

		/// @brief 長方形を作成します。
		/// @param _w 長方形の幅
		/// @param _h 長方形の高さ
		SIV3D_NODISCARD_CXX20
		constexpr Rect(value_type _w, value_type _h) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Integral W, Concept::Integral H>
	# else
		template <class W, class H, std::enable_if_t<std::conjunction_v<std::is_integral<W>, std::is_integral<H>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		explicit constexpr Rect(W _w, H _h) noexcept;

		/// @brief 長方形を作成します。
		/// @param _size 長方形の大きさ
		SIV3D_NODISCARD_CXX20
		explicit constexpr Rect(size_type _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _x 長方形の左上の点の X 座標
		/// @param _y 長方形の左上の点の Y 座標
		/// @param _size 長方形の縦横の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr Rect(value_type _x, value_type _y, value_type _size) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Integral X, Concept::Integral Y, Concept::Integral S>
	# else
		template <class X, class Y, class S, std::enable_if_t<std::conjunction_v<std::is_integral<X>, std::is_integral<Y>, std::is_integral<S>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Rect(X _x, Y _y, S _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _x 長方形の左上の点の X 座標
		/// @param _y 長方形の左上の点の Y 座標
		/// @param _w 長方形の幅
		/// @param _h 	長方形の高さ
		SIV3D_NODISCARD_CXX20
		constexpr Rect(value_type _x, value_type _y, value_type _w, value_type _h) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Integral X, Concept::Integral Y, Concept::Integral W, Concept::Integral H>
	# else
		template <class X, class Y, class W, class H, std::enable_if_t<std::conjunction_v<std::is_integral<X>, std::is_integral<Y>, std::is_integral<W>, std::is_integral<H>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Rect(X _x, Y _y, W _w, H _h) noexcept;

		/// @brief 長方形を作成します。
		/// @param _x 長方形の左上の点の X 座標
		/// @param _y 長方形の左上の点の Y 座標
		/// @param _size 長方形の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr Rect(value_type _x, value_type _y, size_type _size) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Integral X, Concept::Integral Y>
	# else
		template <class X, class Y, std::enable_if_t<std::conjunction_v<std::is_integral<X>, std::is_integral<Y>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Rect(X _x, Y _y, size_type _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _pos 長方形の左上の点の座標
		/// @param _size 長方形の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr Rect(position_type _pos, value_type _size) noexcept;

		SIV3D_CONCEPT_INTEGRAL
		SIV3D_NODISCARD_CXX20
		constexpr Rect(position_type _pos, Int _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _pos 長方形の左上の点の座標
		/// @param _w 長方形の幅
		/// @param _h 長方形の高さ
		SIV3D_NODISCARD_CXX20
		constexpr Rect(position_type _pos, value_type _w, value_type _h) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Integral W, Concept::Integral H>
	# else
		template <class W, class H, std::enable_if_t<std::conjunction_v<std::is_integral<W>, std::is_integral<H>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Rect(position_type _pos, W _w, H _h) noexcept;

		/// @brief 長方形を作成します。
		/// @param _pos 長方形の左上の点の座標
		/// @param _size 	長方形の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr Rect(position_type _pos, size_type _size) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::center_<position_type> _center, value_type _size) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::center_<position_type> _center, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::center_<position_type> _center, size_type _size) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::topLeft_<position_type> topLeft, value_type _size) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::topLeft_<position_type> topLeft, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::topLeft_<position_type> topLeft, size_type _size) noexcept;

		/// @brief 
		/// @param topCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::topCenter_<position_type> topCenter, value_type _size) noexcept;

		/// @brief 
		/// @param topCenter 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::topCenter_<position_type> topCenter, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param topCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::topCenter_<position_type> topCenter, size_type _size) noexcept;

		/// @brief 
		/// @param topRight 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::topRight_<position_type> topRight, value_type _size) noexcept;

		/// @brief 
		/// @param topRight 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::topRight_<position_type> topRight, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param topRight 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::topRight_<position_type> topRight, size_type _size) noexcept;

		/// @brief 
		/// @param rightCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::rightCenter_<position_type> rightCenter, value_type _size) noexcept;

		/// @brief 
		/// @param rightCenter 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::rightCenter_<position_type> rightCenter, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param rightCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::rightCenter_<position_type> rightCenter, size_type _size) noexcept;

		/// @brief 
		/// @param bottomRight 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::bottomRight_<position_type> bottomRight, value_type _size) noexcept;

		/// @brief 
		/// @param bottomRight 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::bottomRight_<position_type> bottomRight, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param bottomRight 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::bottomRight_<position_type> bottomRight, size_type _size) noexcept;

		/// @brief 
		/// @param bottomCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::bottomCenter_<position_type> bottomCenter, value_type _size) noexcept;

		/// @brief 
		/// @param bottomCenter 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::bottomCenter_<position_type> bottomCenter, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param bottomCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::bottomCenter_<position_type> bottomCenter, size_type _size) noexcept;

		/// @brief 
		/// @param bottomLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::bottomLeft_<position_type> bottomLeft, value_type _size) noexcept;

		/// @brief 
		/// @param bottomLeft 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::bottomLeft_<position_type> bottomLeft, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param bottomLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::bottomLeft_<position_type> bottomLeft, size_type _size) noexcept;

		/// @brief 
		/// @param leftCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::leftCenter_<position_type> leftCenter, value_type _size) noexcept;

		/// @brief 
		/// @param leftCenter 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::leftCenter_<position_type> leftCenter, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param leftCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rect(Arg::leftCenter_<position_type> leftCenter, size_type _size) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const Rect& lhs, const Rect& rhs) noexcept
		{
			return (lhs.pos == rhs.pos)
				&& (lhs.size == rhs.size);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Rect& lhs, const Rect& rhs) noexcept
		{
			return (lhs.pos != rhs.pos)
				|| (lhs.size != rhs.size);
		}


		constexpr Rect& setPos(value_type _x, value_type _y) noexcept;

		constexpr Rect& setPos(position_type _pos) noexcept;

		constexpr Rect& setPos(Arg::center_<position_type> _center) noexcept;

		constexpr Rect& setPos(Arg::topLeft_<position_type> topLeft) noexcept;

		constexpr Rect& setPos(Arg::topCenter_<position_type> topCenter) noexcept;

		constexpr Rect& setPos(Arg::topRight_<position_type> topRight) noexcept;

		constexpr Rect& setPos(Arg::rightCenter_<position_type> rightCenter) noexcept;

		constexpr Rect& setPos(Arg::bottomRight_<position_type> bottomRight) noexcept;

		constexpr Rect& setPos(Arg::bottomCenter_<position_type> bottomCenter) noexcept;

		constexpr Rect& setPos(Arg::bottomLeft_<position_type> bottomLeft) noexcept;

		constexpr Rect& setPos(Arg::leftCenter_<position_type> leftCenter) noexcept;

		constexpr Rect& setCenter(value_type _x, value_type _y) noexcept;

		constexpr Rect& setCenter(position_type _pos) noexcept;

		constexpr Rect& setSize(value_type _size) noexcept;

		constexpr Rect& setSize(value_type _w, value_type _h) noexcept;

		constexpr Rect& setSize(size_type _size) noexcept;

		constexpr Rect& set(value_type _x, value_type _y, value_type _w, value_type _h) noexcept;

		constexpr Rect& set(value_type _x, value_type _y, value_type _size) noexcept;

		constexpr Rect& set(value_type _x, value_type _y, size_type _size) noexcept;

		constexpr Rect& set(position_type _pos, value_type _size) noexcept;

		constexpr Rect& set(position_type _pos, value_type _w, value_type _h) noexcept;

		constexpr Rect& set(position_type _pos, size_type _size) noexcept;

		constexpr Rect& set(const Rect& r) noexcept;

		constexpr Rect& set(Arg::center_<position_type> _center, value_type _size) noexcept;

		constexpr Rect& set(Arg::center_<position_type> _center, value_type _w, value_type _h) noexcept;

		constexpr Rect& set(Arg::center_<position_type> _center, size_type _size) noexcept;

		constexpr Rect& set(Arg::topLeft_<position_type> topLeft, value_type _size) noexcept;

		constexpr Rect& set(Arg::topLeft_<position_type> topLeft, value_type _w, value_type _h) noexcept;

		constexpr Rect& set(Arg::topLeft_<position_type> topLeft, size_type _size) noexcept;

		constexpr Rect& set(Arg::topCenter_<position_type> topCenter, value_type _size) noexcept;

		constexpr Rect& set(Arg::topCenter_<position_type> topCenter, value_type _w, value_type _h) noexcept;

		constexpr Rect& set(Arg::topCenter_<position_type> topCenter, size_type _size) noexcept;

		constexpr Rect& set(Arg::topRight_<position_type> topRight, value_type _size) noexcept;

		constexpr Rect& set(Arg::topRight_<position_type> topRight, value_type _w, value_type _h) noexcept;

		constexpr Rect& set(Arg::topRight_<position_type> topRight, size_type _size) noexcept;

		constexpr Rect& set(Arg::rightCenter_<position_type> rightCenter, value_type _size) noexcept;

		constexpr Rect& set(Arg::rightCenter_<position_type> rightCenter, value_type _w, value_type _h) noexcept;

		constexpr Rect& set(Arg::rightCenter_<position_type> rightCenter, size_type _size) noexcept;

		constexpr Rect& set(Arg::bottomRight_<position_type> bottomRight, value_type _size) noexcept;

		constexpr Rect& set(Arg::bottomRight_<position_type> bottomRight, value_type _w, value_type _h) noexcept;

		constexpr Rect& set(Arg::bottomRight_<position_type> bottomRight, size_type _size) noexcept;

		constexpr Rect& set(Arg::bottomCenter_<position_type> bottomCenter, value_type _size) noexcept;

		constexpr Rect& set(Arg::bottomCenter_<position_type> bottomCenter, value_type _w, value_type _h) noexcept;

		constexpr Rect& set(Arg::bottomCenter_<position_type> bottomCenter, size_type _size) noexcept;

		constexpr Rect& set(Arg::bottomLeft_<position_type> bottomLeft, value_type _size) noexcept;

		constexpr Rect& set(Arg::bottomLeft_<position_type> bottomLeft, value_type _w, value_type _h) noexcept;

		constexpr Rect& set(Arg::bottomLeft_<position_type> bottomLeft, size_type _size) noexcept;

		constexpr Rect& set(Arg::leftCenter_<position_type> leftCenter, value_type _size) noexcept;

		constexpr Rect& set(Arg::leftCenter_<position_type> leftCenter, value_type _w, value_type _h) noexcept;

		constexpr Rect& set(Arg::leftCenter_<position_type> leftCenter, size_type _size) noexcept;

		/// @brief 座標を移動した新しい長方形を返します。
		/// @param _x X 軸方向の移動量
		/// @param _y Y 軸方向の移動量
		/// @return 新しい長方形
		[[nodiscard]]
		constexpr Rect movedBy(value_type _x, value_type _y) const noexcept;

		/// @brief 座標を移動した新しい長方形を返します。
		/// @param v 移動量
		/// @return 新しい長方形
		[[nodiscard]]
		constexpr Rect movedBy(size_type v) const noexcept;

		/// @brief 長方形を移動させます。
		/// @param _x X 軸方向の移動量
		/// @param _y Y 軸方向の移動量
		/// @return *this
		constexpr Rect& moveBy(value_type _x, value_type _y) noexcept;

		/// @brief 長方形を移動させます。
		/// @param v 移動量
		/// @return *this
		constexpr Rect& moveBy(size_type v) noexcept;

		/// @brief 左右・上下方向に拡大縮小した長方形を返します。
		/// @param xy 左方向・右方向・上方向・下方向のそれぞれの拡大縮小量
		/// @return 左右・上下方向に拡大縮小した長方形
		[[nodiscard]]
		constexpr Rect stretched(value_type xy) const noexcept;

		/// @brief 左右・上下方向に拡大縮小した長方形を返します。
		/// @param _x 左方向と右方向のそれぞれの拡大縮小量
		/// @param _y 上方向と下方向のそれぞれの拡大縮小量
		/// @return 左右・上下方向に拡大縮小した長方形
		[[nodiscard]]
		constexpr Rect stretched(value_type _x, value_type _y) const noexcept;

		/// @brief 左右・上下方向に拡大縮小した長方形を返します。
		/// @param xy 左方向と右方向・上方向と下方向のそれぞれの拡大縮小量
		/// @return 左右・上下方向に拡大縮小した長方形
		[[nodiscard]]
		constexpr Rect stretched(size_type xy) const noexcept;

		/// @brief 上下左右方向に拡大縮小した長方形を返します。
		/// @param top 上方向の拡大縮小量
		/// @param right 右方向の拡大縮小量
		/// @param bottom 下方向の拡大縮小量
		/// @param left 左方向の拡大縮小量
		/// @return 上下左右方向に拡大縮小した長方形
		[[nodiscard]]
		constexpr Rect stretched(value_type top, value_type right, value_type bottom, value_type left) const noexcept;

		[[nodiscard]]
		constexpr RectF scaled(double s) const noexcept;

		[[nodiscard]]
		constexpr RectF scaled(double sx, double sy) const noexcept;

		[[nodiscard]]
		constexpr RectF scaled(Vec2 s) const noexcept;

		[[nodiscard]]
		constexpr RectF scaledAt(Vec2 _pos, double s) const noexcept;

		[[nodiscard]]
		constexpr RectF scaledAt(Vec2 _pos, double sx, double sy) const noexcept;

		[[nodiscard]]
		constexpr RectF scaledAt(Vec2 _pos, Vec2 s) const noexcept;

		/// @brief 長方形が空でないかを返します。
		/// @remark `hasArea()` と同じです。
		/// @return 長方形が空でない場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr explicit operator bool() const noexcept;

		/// @brief 長方形が空であるかを返します。
		/// @return 空の長方形である場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool isEmpty() const noexcept;

		/// @brief 長方形が大きさを持っているかを返します。
		/// @return 長方形が大きさを持っている場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool hasArea() const noexcept;

		/// @brief 長方形の左辺の X 座標を返します。
		/// @return 長方形の左辺の X 座標
		[[nodiscard]]
		constexpr value_type leftX() const noexcept;

		/// @brief 長方形の右辺の X 座標を返します。
		/// @return 長方形の右辺の X 座標
		[[nodiscard]]
		constexpr value_type rightX() const noexcept;

		/// @brief 長方形の上辺の Y 座標を返します。
		/// @return 長方形の上辺の Y 座標
		[[nodiscard]]
		constexpr value_type topY() const noexcept;

		/// @brief 長方形の下辺の Y 座標を返します。
		/// @return 長方形の下辺の Y 座標
		[[nodiscard]]
		constexpr value_type bottomY() const noexcept;

		/// @brief 長方形の中心の X 座標を返します。
		/// @return 長方形の中心の X 座標
		[[nodiscard]]
		constexpr double centerX() const noexcept;

		/// @brief 長方形の中心の Y 座標を返します。
		/// @return 長方形の中心の Y 座標
		[[nodiscard]]
		constexpr double centerY() const noexcept;

		/// @brief 長方形の左上の座標を返します。
		/// @return 長方形の左上の座標
		[[nodiscard]]
		constexpr size_type tl() const noexcept;

		/// @brief 長方形の右上の座標を返します。
		/// @return 長方形の右上の座標
		[[nodiscard]]
		constexpr size_type tr() const noexcept;

		/// @brief 長方形の右下の座標を返します。
		/// @return 長方形の右下の座標
		[[nodiscard]]
		constexpr size_type br() const noexcept;

		/// @brief 長方形の左下の座標を返します。
		/// @return 長方形の左下の座標
		[[nodiscard]]
		constexpr size_type bl() const noexcept;

		/// @brief 長方形の上辺の中心座標を返します。
		/// @return 長方形の上辺の中心座標
		[[nodiscard]]
		constexpr Vec2 topCenter() const noexcept;

		/// @brief 長方形の右辺の中心座標を返します。
		/// @return 長方形の右辺の中心座標
		[[nodiscard]]
		constexpr Vec2 rightCenter() const noexcept;

		/// @brief 長方形の下辺の中心座標を返します。
		/// @return 長方形の下辺の中心座標
		[[nodiscard]]
		constexpr Vec2 bottomCenter() const noexcept;

		/// @brief 長方形の左辺の中心座標を返します。
		/// @return 長方形の左辺の中心座標
		[[nodiscard]]
		constexpr Vec2 leftCenter() const noexcept;

		/// @brief 長方形の中心座標を返します。
		/// @return 長方形の中心座標
		[[nodiscard]]
		constexpr Vec2 center() const noexcept;

		/// @brief 長方形の左上を (0 ,0), 右下を (1, 1) としたときの (relativeX, relativeY) の座標を返します。
		/// @param relativeX X 座標の相対的な位置
		/// @param relativeY Y 座標の相対的な位置
		/// @return 長方形の左上を (0 ,0), 右下を (1, 1) としたときの (relativeX, relativeY) の座標
		[[nodiscard]]
		constexpr Vec2 getRelativePoint(double relativeX, double relativeY) const noexcept;

		/// @brief 長方形の上辺を Line として返します。
		/// @return 長方形の上辺
		[[nodiscard]]
		constexpr Line top() const noexcept;

		/// @brief 長方形の右辺を Line として返します。
		/// @return 長方形の右辺
		[[nodiscard]]
		constexpr Line right() const noexcept;

		/// @brief 長方形の下辺を Line として返します。
		/// @return 長方形の下辺
		[[nodiscard]]
		constexpr Line bottom() const noexcept;

		/// @brief 長方形の左辺を Line として返します。
		/// @return 長方形の左辺
		[[nodiscard]]
		constexpr Line left() const noexcept;

		[[nodiscard]]
		constexpr position_type point(size_t index) const;

		[[nodiscard]]
		constexpr Line side(size_t index) const;

		[[nodiscard]]
		constexpr Triangle triangle(size_t index) const;

		/// @brief 長方形の面積を返します。
		/// @return 長方形の面積
		[[nodiscard]]
		constexpr value_type area() const noexcept;

		/// @brief 長方形の周の長さを返します。
		/// @return 長方形の周の長さ
		[[nodiscard]]
		constexpr value_type perimeter() const noexcept;

		template <class Type = double>
		[[nodiscard]]
		constexpr Type horizontalAspectRatio() const noexcept;

		[[nodiscard]]
		Quad rotated(double angle) const noexcept;

		[[nodiscard]]
		Quad rotatedAt(double _x, double _y, double angle) const noexcept;

		[[nodiscard]]
		Quad rotatedAt(Vec2 _pos, double angle) const noexcept;

		/// @brief _posを中心とし、時計回りに 90°* n 回転した長方形を返します。
		/// @param _pos 回転の中心座標
		/// @param n 時計回りに 90° 回転させる回数（負の場合は反時計回り）
		/// @return _posを中心とし、時計回りに 90°* n 回転した長方形
		[[nodiscard]]
		constexpr Rect rotated90At(const position_type& _pos, int32 n = 1) const noexcept;

		/// @brief _posを中心とし、自身を時計回りに 90°* n 回転します。
		/// @param _pos 回転の中心座標
		/// @param n 時計回りに 90° 回転させる回数（負の場合は反時計回り）
		/// @return *this
		constexpr Rect& rotate90At(const position_type& _pos, int32 n = 1) noexcept;

		[[nodiscard]]
		constexpr Quad shearedX(double vx) const noexcept;

		[[nodiscard]]
		constexpr Quad shearedY(double vy) const noexcept;

		[[nodiscard]]
		Quad skewedX(double angle) const noexcept;

		[[nodiscard]]
		Quad skewedY(double angle) const noexcept;

		/// @brief 角を丸めた RoundRect を作成して返します。
		/// @param r 角の半径
		/// @return 作成した RoundRect
		[[nodiscard]]
		constexpr RoundRect rounded(double r) const noexcept;

		[[nodiscard]]
		Polygon rounded(double tl, double tr, double br, double bl) const noexcept;

		/// @brief 長方形を Quad として返します。
		/// @return 長方形の Quad
		[[nodiscard]]
		constexpr Quad asQuad() const noexcept;

		/// @brief 長方形の輪郭を LineString として返します。
		/// @param closeRing 頂点配列の終点を始点と重ねるかどうか
		/// @return 長方形の輪郭の LineString
		[[nodiscard]]
		LineString outline(CloseRing closeRing = CloseRing::No) const;

		/// @brief 長方形の輪郭の一部を LineString として返します。
		/// @param distanceFromOrigin 開始地点の距離（長方形の左上の頂点から時計回りでの距離）
		/// @param length 長さ
		/// @return 長方形の輪郭の一部の LineString
		[[nodiscard]]
		LineString outline(double distanceFromOrigin, double length) const;

		/// @brief 長方形を Polygon として返します。
		/// @return 長方形の Polygon
		[[nodiscard]]
		Polygon asPolygon() const;

		[[nodiscard]]
		constexpr RectF lerp(const Rect& other, double f) const noexcept;

		[[nodiscard]]
		constexpr RectF lerp(const RectF& other, double f) const noexcept;

		/// @brief 別の長方形と重なる領域を返します。重ならない場合は空の長方形を返します。
		/// @param other 別の長方形
		/// @return 別の長方形と重なる領域。重ならない場合は空の長方形
		[[nodiscard]]
		constexpr Rect getOverlap(const Rect& other) const noexcept;

		/// @brief 別の長方形と重なる領域を返します。重ならない場合は空の長方形を返します。
		/// @param other 別の長方形
		/// @return 別の長方形と重なる領域。重ならない場合は空の長方形
		[[nodiscard]]
		constexpr RectF getOverlap(const RectF& other) const noexcept;

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

		/// @brief 長方形が現在のフレームで左クリックされ始めたかを返します。
		/// @return 長方形が現在のフレームで左クリックされ始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftClicked() const noexcept;

		/// @brief 長方形が左クリックされているかを返します。
		/// @return 長方形が左クリックされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftPressed() const noexcept;

		/// @brief 現在のフレームで長方形への左クリックが離されたかを返します。
		/// @return 現在のフレームで長方形への左クリックが離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftReleased() const noexcept;

		/// @brief 長方形が現在のフレームで右クリックされ始めたかを返します。
		/// @return 長方形が現在のフレームで右クリックされ始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightClicked() const noexcept;

		/// @brief 長方形が右クリックされているかを返します。
		/// @return 長方形が右クリックされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightPressed() const noexcept;

		/// @brief 現在のフレームで長方形への右クリックが離されたかを返します。
		/// @return 現在のフレームで長方形への右クリックが離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightReleased() const noexcept;

		/// @brief 長方形上にマウスカーソルがあるかを返します。
		/// @return 長方形上にマウスカーソルがある場合 true, それ以外の場合は false
		[[nodiscard]]
		bool mouseOver() const noexcept;

		const Rect& paint(Image& dst, const Color& color) const;

		const Rect& overwrite(Image& dst, const Color& color) const;

		const Rect& paintFrame(Image& dst, int32 innerThickness, int32 outerThickness, const Color& color) const;

		const Rect& overwriteFrame(Image& dst, int32 innerThickness, int32 outerThickness, const Color& color) const;

		/// @brief 長方形を描画します。
		/// @param color 色
		/// @return *this
		const Rect& draw(const ColorF& color = Palette::White) const;

		/// @brief 長方形を描画します。
		/// @param colors 左上、右上、右下、左下の各頂点の色
		/// @remark 描画時には 2 つの三角形に分割されるため、斜め方向のグラデーションは方向によってグラデーションのかかり方が変わります。上下、左右方向のグラデーションには影響しません。
		/// @return *this
		const Rect& draw(const ColorF(&colors)[4]) const;

		/// @brief 長方形を描画します。
		/// @param topColor 長方形の上側の色
		/// @param bottomColor 長方形の下側の色
		/// @remark `rect.draw(Arg::top = ColorF{ 0.0 }, Arg::bottom = ColorF{ 1.0 })` のように呼びます。
		/// @return *this
		const Rect& draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		/// @brief 長方形を描画します。
		/// @param leftColor 長方形の左側の色
		/// @param rightColor 長方形の右側の色
		/// @remark `rect.draw(Arg::left = ColorF{ 0.0 }, Arg::right = ColorF{ 1.0 })` のように呼びます。
		/// @return *this
		const Rect& draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

		/// @brief 長方形を描画します。
		/// @param topLeftColor 長方形の左上の色
		/// @param bottomRightColor 長方形の右下の色
		/// @remark `rect.draw(Arg::topLeft = ColorF{ 0.0 }, Arg::bottomRight = ColorF{ 1.0 })` のように呼びます。
		/// @return *this
		const Rect& draw(Arg::topLeft_<ColorF> topLeftColor, Arg::bottomRight_<ColorF> bottomRightColor) const;

		/// @brief 長方形を描画します。
		/// @param topRightColor 長方形の右上の色
		/// @param bottomLeftColor 長方形の左下の色
		/// @remark `rect.draw(Arg::topRight = ColorF{ 0.0 }, Arg::bottomLeft = ColorF{ 1.0 })` のように呼びます。
		/// @return 
		const Rect& draw(Arg::topRight_<ColorF> topRightColor, Arg::bottomLeft_<ColorF> bottomLeftColor) const;

		/// @brief 長方形の枠を描画します。
		/// @param thickness 枠の太さ
		/// @param color 色
		/// @return *this
		const Rect& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		/// @brief 長方形の枠を描画します。
		/// @param thickness 枠の太さ
		/// @param innerColor 内側寄りの枠の色
		/// @param outerColor 外側寄りの枠の色
		/// @return *this
		const Rect& drawFrame(double thickness, const ColorF& innerColor, const ColorF& outerColor) const;
		
		/// @brief 長方形の枠を描画します。
		/// @param thickness 枠の太さ
		/// @param topColor 上側の色
		/// @param bottomColor 下側の色
		/// @return *this
		const Rect& drawFrame(double thickness, Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		/// @brief 長方形の枠を描画します。
		/// @param innerThickness 内側寄りの枠の太さ
		/// @param outerThickness 外側寄りの枠の太さ
		/// @param color 色
		/// @return *this
		const Rect& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		/// @brief 長方形の枠を描画します。
		/// @param innerThickness 内側寄りの枠の太さ
		/// @param outerThickness 外側寄りの枠の太さ
		/// @param innerColor 内側寄りの枠の色
		/// @param outerColor 外側寄りの枠の色
		/// @return *this
		const Rect& drawFrame(double innerThickness, double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const;

		/// @brief 長方形の枠を描画します。
		/// @param innerThickness 内側寄りの枠の太さ
		/// @param outerThickness 外側寄りの枠の太さ
		/// @param topColor 上側の色
		/// @param bottomColor 下側の色
		/// @return *this
		const Rect& drawFrame(double innerThickness, double outerThickness, Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		/// @brief 長方形の影を描画します。
		/// @param offset 影の位置のオフセット（ピクセル）
		/// @param blur ぼかしの大きさ（ピクセル）
		/// @param spread 影の膨張（ピクセル）
		/// @param color 影の色
		/// @param fill 影の内部を塗りつぶすか
		/// @return *this
		const Rect& drawShadow(const Vec2& offset, double blur, double spread = 0.0, const ColorF& color = ColorF{ 0.0, 0.5 }, bool fill = true) const;

		[[nodiscard]]
		TexturedQuad operator ()(const Texture& texture) const;

		[[nodiscard]]
		TexturedQuad operator ()(const TextureRegion& textureRegion) const;

		/// @brief 空の長方形を返します。
		/// @return 空の長方形 (`Rect{ 0, 0, 0, 0 }`)
		[[nodiscard]]
		static constexpr Rect Empty() noexcept;

		/// @brief 対角線上の 2 点の座標をもとに長方形を作成します。
		/// @param a 対角線をなす座標の 1 つ
		/// @param b 対角線をなす座標の 1 つ
		/// @return 作成した長方形
		[[nodiscard]]
		static constexpr Rect FromPoints(position_type a, position_type b) noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Rect& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(',') << CharType(' ')
				<< value.w << CharType(',') << CharType(' ')
				<< value.h << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Rect& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused
				>> value.w >> unused
				>> value.h >> unused;
		}

		friend void Formatter(FormatData& formatData, const Rect& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Rect, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Rect& value, FormatContext& ctx)
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

template <>
struct std::hash<s3d::Rect>
{
	[[nodiscard]]
	size_t operator ()(const s3d::Rect& value) const noexcept
	{
		return value.hash();
	}
};
