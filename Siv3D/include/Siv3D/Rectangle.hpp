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
		constexpr Rectangle(value_type _x, value_type _y, value_type _w, value_type _h) noexcept;

		/// @brief 長方形を作成します。
		/// @param _x 長方形の左上の点の X 座標
		/// @param _y 長方形の左上の点の Y 座標
		/// @param _size 長方形の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(value_type _x, value_type _y, size_type _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _pos 長方形の左上の点の座標
		/// @param _size 長方形の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(position_type _pos, value_type _size) noexcept;

		/// @brief 長方形を作成します。
		/// @param _pos 長方形の左上の点の座標
		/// @param _w 長方形の幅
		/// @param _h 長方形の高さ
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(position_type _pos, value_type _w, value_type _h) noexcept;

		/// @brief 長方形を作成します。
		/// @param _pos 長方形の左上の点の座標
		/// @param _size 	長方形の大きさ
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(position_type _pos, size_type _size) noexcept;

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
		constexpr Rectangle(Arg::center_<position_type> _center, value_type _size) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _w 
		/// @param _h 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::center_<position_type> _center, value_type _w, value_type _h) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _size 
		SIV3D_NODISCARD_CXX20
		constexpr Rectangle(Arg::center_<position_type> _center, size_type _size) noexcept;

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








		[[nodiscard]]
		bool intersects(const Point point) const
		{
			return (x <= point.x) && (point.x < (x + w))
				&& (y <= point.y) && (point.y < (y + h));
		}

		[[nodiscard]]
		size_t hash() const noexcept;

		const Rectangle& draw(const ColorF& color = Palette::White) const;





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
