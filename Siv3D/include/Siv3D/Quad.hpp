//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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
		
		[[nodiscard]] position_type& p(size_t index) noexcept
		{
			return (&p0)[index];
		}
		
		[[nodiscard]] const position_type& p(size_t index) const noexcept
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

		[[nodiscard]] constexpr Quad movedBy(value_type x, value_type y) const noexcept
		{
			return{ p0.movedBy(x, y), p1.movedBy(x, y), p2.movedBy(x, y), p3.movedBy(x, y) };
		}

		[[nodiscard]] constexpr Quad movedBy(const position_type& v) const noexcept
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

		[[nodiscard]] Quad stretched(value_type size) const noexcept;

		[[nodiscard]] Quad rotatedAt(value_type x, value_type y, value_type angle) const noexcept
		{
			return rotatedAt(position_type(x, y), angle);
		}

		[[nodiscard]] Quad rotatedAt(const position_type& pos, value_type angle) const noexcept;

		[[nodiscard]] value_type area() const noexcept;

		[[nodiscard]] value_type perimeter() const noexcept;

		template <class Shape2DType>
		[[nodiscard]] bool intersects(const Shape2DType& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		template <class Shape2DType>
		[[nodiscard]] bool contains(const Shape2DType& shape) const
		{
			return Geometry2D::Contains(*this, shape);
		}

		[[nodiscard]] bool leftClicked() const;

		[[nodiscard]] bool leftPressed() const;

		[[nodiscard]] bool leftReleased() const;

		[[nodiscard]] bool rightClicked() const;

		[[nodiscard]] bool rightPressed() const;

		[[nodiscard]] bool rightReleased() const;

		[[nodiscard]] bool mouseOver() const;

		const Quad& paint(Image& dst, const Color& color) const;

		const Quad& overwrite(Image& dst, const Color& color, bool antialiased = true) const;

		const Quad& draw(const ColorF& color = Palette::White) const;

		const Quad& draw(const ColorF(&colors)[4]) const;

		const Quad& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		const Quad& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		[[nodiscard]] TexturedQuad operator ()(const Texture& texture) const;

		[[nodiscard]] TexturedQuad operator ()(const TextureRegion& textureRegion) const;

		[[nodiscard]] Polygon asPolygon() const;
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Quad& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Quad& value)
	{
		return	output << CharType('(')
			<< value.p0 << CharType(',')
			<< value.p1 << CharType(',')
			<< value.p2 << CharType(',')
			<< value.p3 << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Quad& value)
	{
		CharType unused;
		return	input >> unused
			>> value.p0 >> unused
			>> value.p1 >> unused
			>> value.p2 >> unused
			>> value.p3 >> unused;
	}
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <>
	struct hash<s3d::Quad>
	{
		[[nodiscard]] size_t operator ()(const s3d::Quad& value) const noexcept
		{
			return s3d::Hash::FNV1a(value);
		}
	};
}

//////////////////////////////////////////////////
//
//	fmt
//
//////////////////////////////////////////////////

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::char32, ArgFormatter>& f, const s3d::char32*& format_str, const s3d::Quad& value)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = U"({" + tag + U"},{" + tag + U"},{" + tag + U"},{" + tag + U"})";

		f.writer().write(fmt, value.p0, value.p1, value.p2, value.p3);
	}
}
