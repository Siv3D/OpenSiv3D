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

namespace s3d
{
	struct Quad
	{
		using position_type = Vec2;

		using value_type = position_type::value_type;

		position_type p0, p1, p2, p3;
		
		position_type& p(size_t index) noexcept
		{
			return (&p0)[index];
		}
		
		const position_type& p(size_t index) const noexcept
		{
			return (&p0)[index];
		}

		Quad() = default;

		constexpr Quad(value_type x0, value_type y0, value_type x1, value_type y1, value_type x2, value_type y2, value_type x3, value_type y3) noexcept
			: p0(x0, y0)
			, p1(x1, y1)
			, p2(x2, y2)
			, p3(x3, y3) {}

		constexpr Quad(const position_type& _p0, const position_type& _p1, const position_type& _p2, const position_type& _p3) noexcept
			: p0(_p0)
			, p1(_p1)
			, p2(_p2)
			, p3(_p3) {}

		constexpr Quad& set(value_type x0, value_type y0, value_type x1, value_type y1, value_type x2, value_type y2, value_type x3, value_type y3) noexcept
		{
			p0.set(x0, y0);
			p1.set(x1, y1);
			p2.set(x2, y2);
			p3.set(x3, y3);
			return *this;
		}

		constexpr Quad& set(const position_type& _p0, const position_type& _p1, const position_type& _p2, const position_type& _p3) noexcept
		{
			p0.set(_p0);
			p1.set(_p1);
			p2.set(_p2);
			p3.set(_p3);
			return *this;
		}

		constexpr Quad& set(const Quad& quad) noexcept
		{
			return *this = quad;
		}

		constexpr Quad movedBy(value_type x, value_type y) const noexcept
		{
			return{ p0.movedBy(x, y), p1.movedBy(x, y), p2.movedBy(x, y), p3.movedBy(x, y) };
		}

		constexpr Quad movedBy(const position_type& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}

		constexpr Quad& moveBy(value_type x, value_type y) noexcept
		{
			p0.moveBy(x, y);
			p1.moveBy(x, y);
			p2.moveBy(x, y);
			p3.moveBy(x, y);
			return *this;
		}

		constexpr Quad& moveBy(const position_type& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		Quad stretched(value_type size) const noexcept;

		Quad rotatedAt(value_type x, value_type y, value_type angle) const noexcept
		{
			return rotatedAt(position_type(x, y), angle);
		}

		Quad rotatedAt(const position_type& pos, value_type angle) const noexcept;

		value_type area() const noexcept;

		value_type perimeter() const noexcept;

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

		// paint~ overpaint~ draw~

		const Quad& draw(const ColorF& color = Palette::White) const;

		const Quad& draw(const ColorF(&colors)[4]) const;

		const Quad& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		const Quad& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		TexturedQuad operator ()(const Texture& texture) const;

		TexturedQuad operator ()(const TextureRegion& textureRegion) const;

		// Polygon asPolygon() const;
	};
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Quad
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
	void Formatter(FormatData& formatData, const Quad& value);

	/// <summary>
	/// 出力ストリームに四角形を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="quad">
	/// 四角形
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Quad& quad)
	{
		return	os << CharType('(')
			<< quad.p0 << CharType(',')
			<< quad.p1 << CharType(',')
			<< quad.p2 << CharType(',')
			<< quad.p3 << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに四角形を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="quad">
	/// 四角形
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, Quad& quad)
	{
		CharType unused;
		return	is >> unused
			>> quad.p0 >> unused
			>> quad.p1 >> unused
			>> quad.p2 >> unused
			>> quad.p3 >> unused;
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::Quad& quad)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = S3DSTR("({") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("})");

		f.writer().write(fmt, quad.p0, quad.p1, quad.p2, quad.p3);
	}
}
//
//////////////////////////////////////////////////////////////////////////////
