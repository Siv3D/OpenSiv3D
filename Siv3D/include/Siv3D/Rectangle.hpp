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

namespace s3d
{
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

		SIV3D_DISABLE_MSVC_WARNINGS_POP()

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
		SIV3D_NODISCARD_CXX20
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
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(value_type _w, value_type _h) noexcept
			: pos(0, 0)
			, size(_w, _h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		SIV3D_NODISCARD_CXX20
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
		/// <param name="_size">
		/// 長方形の縦横の大きさ
		/// </param>
		SIV3D_NODISCARD_CXX20
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
		/// <param name="_w">
		/// 長方形の幅
		/// </param>
		/// <param name="_h">
		/// 長方形の高さ
		/// </param>
		SIV3D_NODISCARD_CXX20
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
		/// 長方形の大きさ
		/// </param>
		SIV3D_NODISCARD_CXX20
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
		SIV3D_NODISCARD_CXX20
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
		SIV3D_NODISCARD_CXX20
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
		SIV3D_NODISCARD_CXX20
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
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(const Rectangle<Type>& r) noexcept
			: pos(static_cast<value_type>(r.x), static_cast<value_type>(r.y))
			, size(static_cast<value_type>(r.w), static_cast<value_type>(r.h)) {}


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




		const Rectangle& draw(const ColorF& color = Palette::White) const;
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
