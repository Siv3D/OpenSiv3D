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
# include "PredefinedYesNo.hpp"

namespace s3d
{
	class Texture;
	struct TextureRegion;
	struct TexturedQuad;

	/// @brief 長方形 (成分が double 型)
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
	struct RectF
	{
		using position_type = Vec2;

		using size_type		= Vec2;

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
		RectF() = default;

		/// @brief 長方形を作成します。
		/// @param _size 長方形の幅と高さ
		SIV3D_NODISCARD_CXX20
		explicit constexpr RectF(value_type _size) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		explicit constexpr RectF(Arithmetic _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _w 長方形の幅
		/// @param _h 長方形の高さ
		SIV3D_NODISCARD_CXX20
		constexpr RectF(value_type _w, value_type _h) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H>
	# else
		template <class W, class H, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		explicit constexpr RectF(W _w, H _h) noexcept;

		/// @brief 長方形を作成します。
		/// @param _size 長方形の大きさ
		SIV3D_NODISCARD_CXX20
		explicit constexpr RectF(size_type _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _x 長方形の左上の点の X 座標
		/// @param _y 長方形の左上の点の Y 座標
		/// @param _size 長方形の縦横の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr RectF(value_type _x, value_type _y, value_type _size) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic S>
	# else
		template <class X, class Y, class S, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<S>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr RectF(X _x, Y _y, S _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _x 長方形の左上の点の X 座標
		/// @param _y 長方形の左上の点の Y 座標
		/// @param _w 長方形の幅
		/// @param _h 	長方形の高さ
		SIV3D_NODISCARD_CXX20
		constexpr RectF(value_type _x, value_type _y, value_type _w, value_type _h) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic W, Concept::Arithmetic H>
	# else
		template <class X, class Y, class W, class H, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<W>, std::is_arithmetic<H>>>* = nullptr>
	# endif
		constexpr RectF(X _x, Y _y, W _w, H _h) noexcept;

		/// @brief 長方形を作成します。
		/// @param _x 長方形の左上の点の X 座標
		/// @param _y 長方形の左上の点の Y 座標
		/// @param _size 長方形の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr RectF(value_type _x, value_type _y, size_type _size) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y>
	# else
		template <class X, class Y, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr RectF(X _x, Y _y, size_type _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _pos 長方形の左上の点の座標
		/// @param _size 長方形の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr RectF(position_type _pos, value_type _size) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr RectF(position_type _pos, Arithmetic _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _pos 長方形の左上の点の座標
		/// @param _w 長方形の幅
		/// @param _h 長方形の高さ
		SIV3D_NODISCARD_CXX20
		constexpr RectF(position_type _pos, value_type _w, value_type _h) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H>
	# else
		template <class W, class H, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr RectF(position_type _pos, W _w, H _h) noexcept;

		/// @brief 長方形を作成します。
		/// @param _pos 長方形の左上の点の座標
		/// @param _size 	長方形の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr RectF(position_type _pos, size_type _size) noexcept;

		/// @brief 長方形を作成します。
		/// @tparam Type 長方形のサイズの型
		/// @param r 長方形
		SIV3D_NODISCARD_CXX20
		constexpr RectF(const Rect& r) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::center_<position_type> _center, value_type _size) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::center_<position_type> _center, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::center_<position_type> _center, size_type _size) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::topLeft_<position_type> topLeft, value_type _size) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::topLeft_<position_type> topLeft, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::topLeft_<position_type> topLeft, size_type _size) noexcept;

		/// @brief 
		/// @param topCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::topCenter_<position_type> topCenter, value_type _size) noexcept;

		/// @brief 
		/// @param topCenter 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::topCenter_<position_type> topCenter, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param topCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::topCenter_<position_type> topCenter, size_type _size) noexcept;

		/// @brief 
		/// @param topRight 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::topRight_<position_type> topRight, value_type _size) noexcept;

		/// @brief 
		/// @param topRight 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::topRight_<position_type> topRight, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param topRight 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::topRight_<position_type> topRight, size_type _size) noexcept;

		/// @brief 
		/// @param rightCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::rightCenter_<position_type> rightCenter, value_type _size) noexcept;

		/// @brief 
		/// @param rightCenter 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::rightCenter_<position_type> rightCenter, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param rightCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::rightCenter_<position_type> rightCenter, size_type _size) noexcept;

		/// @brief 
		/// @param bottomRight 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::bottomRight_<position_type> bottomRight, value_type _size) noexcept;

		/// @brief 
		/// @param bottomRight 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::bottomRight_<position_type> bottomRight, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param bottomRight 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::bottomRight_<position_type> bottomRight, size_type _size) noexcept;

		/// @brief 
		/// @param bottomCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::bottomCenter_<position_type> bottomCenter, value_type _size) noexcept;

		/// @brief 
		/// @param bottomCenter 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::bottomCenter_<position_type> bottomCenter, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param bottomCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::bottomCenter_<position_type> bottomCenter, size_type _size) noexcept;

		/// @brief 
		/// @param bottomLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::bottomLeft_<position_type> bottomLeft, value_type _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param bottomLeft 長方形の左下の座標
		/// @param _w 長方形の幅
		/// @param _h 長方形の高さ
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::bottomLeft_<position_type> bottomLeft, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param bottomLeft 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::bottomLeft_<position_type> bottomLeft, size_type _size) noexcept;

		/// @brief 
		/// @param leftCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::leftCenter_<position_type> leftCenter, value_type _size) noexcept;

		/// @brief 
		/// @param leftCenter 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::leftCenter_<position_type> leftCenter, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param leftCenter 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr RectF(Arg::leftCenter_<position_type> leftCenter, size_type _size) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const RectF& lhs, const RectF& rhs) noexcept
		{
			return (lhs.pos == rhs.pos)
				&& (lhs.size == rhs.size);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const RectF& lhs, const RectF& rhs) noexcept
		{
			return (lhs.pos != rhs.pos)
				|| (lhs.size != rhs.size);
		}


		constexpr RectF& setPos(value_type _x, value_type _y) noexcept;

		constexpr RectF& setPos(position_type _pos) noexcept;

		constexpr RectF& setPos(Arg::center_<position_type> _center) noexcept;

		constexpr RectF& setPos(Arg::topLeft_<position_type> topLeft) noexcept;

		constexpr RectF& setPos(Arg::topCenter_<position_type> topCenter) noexcept;

		constexpr RectF& setPos(Arg::topRight_<position_type> topRight) noexcept;

		constexpr RectF& setPos(Arg::rightCenter_<position_type> rightCenter) noexcept;

		constexpr RectF& setPos(Arg::bottomRight_<position_type> bottomRight) noexcept;

		constexpr RectF& setPos(Arg::bottomCenter_<position_type> bottomCenter) noexcept;

		constexpr RectF& setPos(Arg::bottomLeft_<position_type> bottomLeft) noexcept;

		constexpr RectF& setPos(Arg::leftCenter_<position_type> leftCenter) noexcept;

		constexpr RectF& setCenter(value_type _x, value_type _y) noexcept;

		constexpr RectF& setCenter(position_type _pos) noexcept;

		constexpr RectF& setSize(value_type _size) noexcept;

		constexpr RectF& setSize(value_type _w, value_type _h) noexcept;

		constexpr RectF& setSize(size_type _size) noexcept;

		constexpr RectF& set(value_type _x, value_type _y, value_type _w, value_type _h) noexcept;

		constexpr RectF& set(value_type _x, value_type _y, value_type _size) noexcept;

		constexpr RectF& set(value_type _x, value_type _y, size_type _size) noexcept;

		constexpr RectF& set(position_type _pos, value_type _size) noexcept;

		constexpr RectF& set(position_type _pos, value_type _w, value_type _h) noexcept;

		constexpr RectF& set(position_type _pos, size_type _size) noexcept;

		constexpr RectF& set(const Rect& r) noexcept;

		constexpr RectF& set(const RectF& r) noexcept;

		constexpr RectF& set(Arg::center_<position_type> _center, value_type _size) noexcept;

		constexpr RectF& set(Arg::center_<position_type> _center, value_type _w, value_type _h) noexcept;

		constexpr RectF& set(Arg::center_<position_type> _center, size_type _size) noexcept;

		constexpr RectF& set(Arg::topLeft_<position_type> topLeft, value_type _size) noexcept;

		constexpr RectF& set(Arg::topLeft_<position_type> topLeft, value_type _w, value_type _h) noexcept;

		constexpr RectF& set(Arg::topLeft_<position_type> topLeft, size_type _size) noexcept;

		constexpr RectF& set(Arg::topCenter_<position_type> topCenter, value_type _size) noexcept;

		constexpr RectF& set(Arg::topCenter_<position_type> topCenter, value_type _w, value_type _h) noexcept;

		constexpr RectF& set(Arg::topCenter_<position_type> topCenter, size_type _size) noexcept;

		constexpr RectF& set(Arg::topRight_<position_type> topRight, value_type _size) noexcept;

		constexpr RectF& set(Arg::topRight_<position_type> topRight, value_type _w, value_type _h) noexcept;

		constexpr RectF& set(Arg::topRight_<position_type> topRight, size_type _size) noexcept;

		constexpr RectF& set(Arg::rightCenter_<position_type> rightCenter, value_type _size) noexcept;

		constexpr RectF& set(Arg::rightCenter_<position_type> rightCenter, value_type _w, value_type _h) noexcept;

		constexpr RectF& set(Arg::rightCenter_<position_type> rightCenter, size_type _size) noexcept;

		constexpr RectF& set(Arg::bottomRight_<position_type> bottomRight, value_type _size) noexcept;

		constexpr RectF& set(Arg::bottomRight_<position_type> bottomRight, value_type _w, value_type _h) noexcept;

		constexpr RectF& set(Arg::bottomRight_<position_type> bottomRight, size_type _size) noexcept;

		constexpr RectF& set(Arg::bottomCenter_<position_type> bottomCenter, value_type _size) noexcept;

		constexpr RectF& set(Arg::bottomCenter_<position_type> bottomCenter, value_type _w, value_type _h) noexcept;

		constexpr RectF& set(Arg::bottomCenter_<position_type> bottomCenter, size_type _size) noexcept;

		constexpr RectF& set(Arg::bottomLeft_<position_type> bottomLeft, value_type _size) noexcept;

		constexpr RectF& set(Arg::bottomLeft_<position_type> bottomLeft, value_type _w, value_type _h) noexcept;

		constexpr RectF& set(Arg::bottomLeft_<position_type> bottomLeft, size_type _size) noexcept;

		constexpr RectF& set(Arg::leftCenter_<position_type> leftCenter, value_type _size) noexcept;

		constexpr RectF& set(Arg::leftCenter_<position_type> leftCenter, value_type _w, value_type _h) noexcept;

		constexpr RectF& set(Arg::leftCenter_<position_type> leftCenter, size_type _size) noexcept;

		/// @brief 座標を移動した新しい長方形を返します。
		/// @param _x X 軸方向の移動量
		/// @param _y Y 軸方向の移動量
		/// @return 新しい長方形
		[[nodiscard]]
		constexpr RectF movedBy(value_type _x, value_type _y) const noexcept;

		/// @brief 座標を移動した新しい長方形を返します。
		/// @param v 移動量
		/// @return 新しい長方形
		[[nodiscard]]
		constexpr RectF movedBy(size_type v) const noexcept;

		/// @brief 長方形を移動させます。
		/// @param _x X 軸方向の移動量
		/// @param _y Y 軸方向の移動量
		/// @return *this
		constexpr RectF& moveBy(value_type _x, value_type _y) noexcept;

		/// @brief 長方形を移動させます。
		/// @param v 移動量
		/// @return *this
		constexpr RectF& moveBy(size_type v) noexcept;

		[[nodiscard]]
		constexpr RectF stretched(value_type xy) const noexcept;

		[[nodiscard]]
		constexpr RectF stretched(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		constexpr RectF stretched(size_type xy) const noexcept;

		[[nodiscard]]
		constexpr RectF stretched(value_type top, value_type right, value_type bottom, value_type left) const noexcept;

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
		constexpr value_type centerX() const noexcept;

		/// @brief 長方形の中心の Y 座標を返します。
		/// @return 長方形の中心の Y 座標
		[[nodiscard]]
		constexpr value_type centerY() const noexcept;

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
		constexpr position_type getRelativePoint(double relativeX, double relativeY) const noexcept;

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

		[[nodiscard]]
		constexpr value_type horizontalAspectRatio() const noexcept;

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
		
		/// @brief 長方形を Rect として返します。
		/// @return 長方形の Rect
		[[nodiscard]]
		constexpr Rect asRect() const noexcept;

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
		constexpr RectF lerp(const RectF& other, double f) const noexcept;

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

		const RectF& paint(Image& dst, const Color& color) const;

		const RectF& overwrite(Image& dst, const Color& color) const;

		const RectF& paintFrame(Image& dst, int32 innerThickness, int32 outerThickness, const Color& color) const;

		const RectF& overwriteFrame(Image& dst, int32 innerThickness, int32 outerThickness, const Color& color) const;

		/// @brief 長方形を描画します。
		/// @param color 色
		/// @return *this
		const RectF& draw(const ColorF& color = Palette::White) const;

		/// @brief 長方形を描画します。
		/// @param colors 左上、右上、右下、左下の各頂点の色
		/// @remark 描画時には 2 つの三角形に分割されるため、斜め方向のグラデーションは方向によってグラデーションのかかり方が変わります。上下、左右方向のグラデーションには影響しません。
		/// @return *this
		const RectF& draw(const ColorF(&colors)[4]) const;

		/// @brief 長方形を描画します。
		/// @param topColor 長方形の上側の色
		/// @param bottomColor 長方形の下側の色
		/// @remark `rect.draw(Arg::top = ColorF{ 0.0 }, Arg::bottom = ColorF{ 1.0 })` のように呼びます。
		/// @return *this
		const RectF& draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		/// @brief 長方形を描画します。
		/// @param leftColor 長方形の左側の色
		/// @param rightColor 長方形の右側の色
		/// @remark `rect.draw(Arg::left = ColorF{ 0.0 }, Arg::right = ColorF{ 1.0 })` のように呼びます。
		/// @return *this
		const RectF& draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

		/// @brief 長方形の枠を描画します。
		/// @param thickness 枠の太さ
		/// @param color 色
		/// @return *this
		const RectF& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		/// @brief 長方形の枠を描画します。
		/// @param thickness 枠の太さ
		/// @param innerColor 内側寄りの枠の色
		/// @param outerColor 外側寄りの枠の色
		/// @return *this
		const RectF& drawFrame(double thickness, const ColorF& innerColor, const ColorF& outerColor) const;

		/// @brief 長方形の枠を描画します。
		/// @param innerThickness 内側寄りの枠の太さ
		/// @param outerThickness 外側寄りの枠の太さ
		/// @param color 色
		/// @return *this
		const RectF& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		/// @brief 長方形の枠を描画します。
		/// @param innerThickness 内側寄りの枠の太さ
		/// @param outerThickness 外側寄りの枠の太さ
		/// @param innerColor 内側寄りの枠の色
		/// @param outerColor 外側寄りの枠の色
		/// @return *this
		const RectF& drawFrame(double innerThickness, double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const;

		/// @brief 長方形の影を描画します。
		/// @param offset 影の位置のオフセット（ピクセル）
		/// @param blurRadius 影のぼかし半径（ピクセル）
		/// @param spread 影の膨張（ピクセル）
		/// @param color 影の色
		/// @return *this
		const RectF& drawShadow(const Vec2& offset, double blurRadius, double spread = 0.0, const ColorF& color = ColorF{ 0.0, 0.5 }) const;

		[[nodiscard]]
		TexturedQuad operator ()(const Texture& texture) const;

		[[nodiscard]]
		TexturedQuad operator ()(const TextureRegion& textureRegion) const;

		/// @brief 空の長方形を返します。
		/// @return 空の長方形 (`RectF{ 0, 0, 0, 0 }`)
		[[nodiscard]]
		static constexpr RectF Empty() noexcept;

		/// @brief 対角線上の 2 点の座標をもとに長方形を作成します。
		/// @param a 対角線をなす座標の 1 つ
		/// @param b 対角線をなす座標の 1 つ
		/// @return 作成した長方形
		[[nodiscard]]
		static constexpr RectF FromPoints(position_type a, position_type b) noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const RectF& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(',') << CharType(' ')
				<< value.w << CharType(',') << CharType(' ')
				<< value.h << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, RectF& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused
				>> value.w >> unused
				>> value.h >> unused;
		}

		friend void Formatter(FormatData& formatData, const RectF& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::RectF, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::RectF& value, FormatContext& ctx)
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
struct std::hash<s3d::RectF>
{
	[[nodiscard]]
	size_t operator ()(const s3d::RectF& value) const noexcept
	{
		return value.hash();
	}
};
