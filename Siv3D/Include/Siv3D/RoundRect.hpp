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
# include "Rectangle.hpp"
# include "NamedParameter.hpp"
# include "Math.hpp"

namespace s3d
{
	struct RoundRect
	{
		using position_type = RectF::position_type;

		using size_type = RectF::size_type;

		using value_type = position_type::value_type;

		S3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			RectF rect;

			struct
			{
				value_type x, y, w, h;
			};
		};

		value_type r;

		S3D_DISABLE_MSVC_WARNINGS_POP()

		RoundRect() = default;

		constexpr RoundRect(value_type _x, value_type _y, value_type _w, value_type _h, value_type _r) noexcept
			: rect(_x, _y, _w, _h)
			, r(_r) {}

		constexpr RoundRect(const position_type& pos, value_type _w, value_type _h, value_type _r) noexcept
			: rect(pos, _w, _h)
			, r(_r) {}

		constexpr RoundRect(value_type _x, value_type _y, const size_type& size, value_type _r) noexcept
			: rect(_x, _y, size)
			, r(_r) {}

		constexpr RoundRect(const position_type& pos, const size_type& size, value_type _r) noexcept
			: rect(pos, size)
			, r(_r) {}

		constexpr RoundRect(Arg::center_<position_type> _center, value_type _w, value_type _h, value_type _r) noexcept
			: rect(_center, _w, _h)
			, r(_r) {}

		constexpr RoundRect(Arg::center_<position_type> _center, value_type _size, value_type _r) noexcept
			: rect(_center, _size)
			, r(_r) {}

		constexpr RoundRect(const RectF& _rect, value_type _r) noexcept
			: rect(_rect)
			, r(_r) {}

		constexpr RoundRect& set(value_type _x, value_type _y, value_type _w, value_type _h, value_type _r) noexcept
		{
			rect.set(_x, _y, _w, _h);
			r = _r;
			return *this;
		}

		constexpr RoundRect& set(const position_type& pos, value_type _w, value_type _h, value_type _r) noexcept
		{
			return set(pos.x, pos.y, _w, _h, _r);
		}

		constexpr RoundRect& set(value_type _x, value_type _y, const size_type& size, value_type _r) noexcept
		{
			return set(_x, _y, size.x, size.y, _r);
		}

		constexpr RoundRect& set(const position_type& pos, const size_type& size, value_type _r) noexcept
		{
			return set(pos.x, pos.y, size.x, size.y, _r);
		}

		constexpr RoundRect& set(const RectF& _rect, value_type _r) noexcept
		{
			return set(_rect.x, _rect.y, _rect.w, _rect.h, _r);
		}

		constexpr RoundRect& set(const RoundRect& roundRect) noexcept
		{
			return *this = roundRect;
		}

		constexpr RoundRect& setCenter(value_type _x, value_type _y) noexcept
		{
			rect.setCenter(_x, _y);
			return *this;
		}

		constexpr RoundRect& setCenter(const position_type& _center) noexcept
		{
			return setCenter(_center.x, _center.y);
		}

		constexpr RoundRect& setPos(value_type _x, value_type _y) noexcept
		{
			rect.setPos(_x, _y);
			return *this;
		}

		constexpr RoundRect& setPos(const position_type& _center) noexcept
		{
			return setPos(_center.x, _center.y);
		}

		constexpr RoundRect& setSize(value_type _w, value_type _h) noexcept
		{
			rect.setSize(_w, _h);
			return *this;
		}

		constexpr RoundRect& setSize(const size_type& _size) noexcept
		{
			return setSize(_size.x, _size.y);
		}

		constexpr RoundRect movedBy(value_type _x, value_type _y) const noexcept
		{
			return{ rect.movedBy(_x, _y), r };
		}

		constexpr RoundRect movedBy(const position_type& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}

		constexpr RoundRect& moveBy(value_type _x, value_type _y) noexcept
		{
			rect.moveBy(_x, _y);
			return *this;
		}

		constexpr RoundRect& moveBy(const position_type& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		constexpr RoundRect stretched(value_type size) const noexcept
		{
			return RoundRect(rect.stretched(size), r);
		}

		constexpr RoundRect stretched(value_type _x, value_type _y) const noexcept
		{
			return RoundRect(rect.stretched(_x, _y), r);
		}

		constexpr RoundRect stretched(const size_type& xy) const noexcept
		{
			return RoundRect(rect.stretched(xy.x, xy.y), r);
		}

		constexpr RoundRect stretched(value_type top, value_type right, value_type bottom, value_type left) const noexcept
		{
			return RoundRect(rect.stretched(top, right, bottom, left), r);
		}

		constexpr position_type center() const noexcept
		{
			return rect.center();
		}

		constexpr double area() const noexcept
		{
			return rect.area() - (4 - Math::Pi) * r * r;
		}

		constexpr double perimeter() const noexcept
		{
			return rect.perimeter() + r * (2 * Math::Pi - 8);
		}

		template <class Shape2DType>
		bool intersects(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::Intersect(*this, shape)))
		{
			return Geometry2D::Intersect(*this, shape);
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

		// paint / overpaint

		const RoundRect& draw(const ColorF& color = Palette::White) const;

		const RoundRect& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const
		{
			return drawFrame(thickness * 0.5, thickness * 0.5, color);
		}

		const RoundRect& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		/// <summary>
		/// 角丸長方形の影を描きます。
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
		const RoundRect& drawShadow(const Vec2& offset, double blurRadius, double spread = 0.0, const ColorF& color = ColorF(0.0, 0.5)) const;

		TexturedRoundRect operator ()(const Texture& texture) const;

		TexturedRoundRect operator ()(const TextureRegion& textureRegion) const;
	};
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting RoundRect
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
	void Formatter(FormatData& formatData, const RoundRect& value);

	/// <summary>
	/// 出力ストリームに角丸長方形を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="roundRect">
	/// 角丸長方形
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const RoundRect& roundRect)
	{
		return	os << CharType('(')
			<< roundRect.x << CharType(',')
			<< roundRect.y << CharType(',')
			<< roundRect.w << CharType(',')
			<< roundRect.h << CharType(',')
			<< roundRect.r << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに角丸長方形を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="roundRect">
	/// 角丸長方形
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, RoundRect& roundRect)
	{
		CharType unused;
		return	is >> unused
			>> roundRect.x >> unused
			>> roundRect.y >> unused
			>> roundRect.w >> unused
			>> roundRect.h >> unused
			>> roundRect.r >> unused;
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::RoundRect& roundRect)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = S3DSTR("({") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("})");

		f.writer().write(fmt, roundRect.x, roundRect.y, roundRect.w, roundRect.h, roundRect.r);
	}
}
//
//////////////////////////////////////////////////////////////////////////////

