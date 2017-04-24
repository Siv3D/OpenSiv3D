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

# include <Siv3D/Triangle.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	Triangle::Triangle(const value_type sides, const value_type angle) noexcept
		: p0(Circular(1.0 / detail::Sqrt3 * sides, angle))
		, p1(Circular(1.0 / detail::Sqrt3 * sides, 2.0 * Math::OneThirdPi + angle))
		, p2(Circular(1.0 / detail::Sqrt3 * sides, 4.0 * Math::OneThirdPi + angle))
	{

	}

	Triangle Triangle::rotatedAt(const position_type& pos, value_type angle) const noexcept
	{
		const position_type a0 = p0 - pos;
		const position_type a1 = p1 - pos;
		const position_type a2 = p2 - pos;
		const value_type s = std::sin(angle);
		const value_type c = std::cos(angle);
		const position_type x0(a0.x*c - a0.y*s, a0.x*s + a0.y*c);
		const position_type x1(a1.x*c - a1.y*s, a1.x*s + a1.y*c);
		const position_type x2(a2.x*c - a2.y*s, a2.x*s + a2.y*c);
		return{ x0 + pos, x1 + pos, x2 + pos };
	}

	Triangle::value_type Triangle::area() const noexcept
	{
		return std::abs((p0.x - p2.x) * (p1.y - p0.y) - (p0.x - p1.x) * (p2.y - p0.y)) * 0.5;
	}

	Triangle::value_type Triangle::perimeter() const noexcept
	{
		return p0.distanceFrom(p1) + p1.distanceFrom(p2) + p2.distanceFrom(p0);
	}

	bool Triangle::leftClicked() const
	{
		return MouseL.down() && mouseOver();
	}

	bool Triangle::leftPressed() const
	{
		return MouseL.pressed() && mouseOver();
	}

	bool Triangle::leftReleased() const
	{
		return MouseL.up() && mouseOver();
	}

	bool Triangle::rightClicked() const
	{
		return MouseR.down() && mouseOver();
	}

	bool Triangle::rightPressed() const
	{
		return MouseR.pressed() && mouseOver();
	}

	bool Triangle::rightReleased() const
	{
		return MouseR.up() && mouseOver();
	}

	bool Triangle::mouseOver() const
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const Triangle& Triangle::draw(const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addTriangle({ p0, p1, p2 }, Float4(color.r, color.g, color.b, color.a));

		return *this;
	}

	const Triangle& Triangle::draw(const ColorF(&colors)[3]) const
	{
		Siv3DEngine::GetRenderer2D()->addTriangle(	
		{ p0, p1, p2 },
		{
			Float4(colors[0].r, colors[0].g, colors[0].b, colors[0].a),
			Float4(colors[1].r, colors[1].g, colors[1].b, colors[1].a),
			Float4(colors[2].r, colors[2].g, colors[2].b, colors[2].a)
		});

		return *this;
	}

	void Formatter(FormatData& formatData, const Triangle& value)
	{
		formatData.string.push_back(L'(');
		Formatter(formatData, value.p0);
		formatData.string.push_back(L',');
		Formatter(formatData, value.p1);
		formatData.string.push_back(L',');
		Formatter(formatData, value.p2);
		formatData.string.push_back(L')');
	}
}
