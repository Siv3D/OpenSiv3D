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

# include <Siv3D/Quad.hpp>
# include <Siv3D/FloatQuad.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	Quad Quad::rotatedAt(const position_type& pos, value_type angle) const noexcept
	{
		const position_type a0 = p0 - pos;
		const position_type a1 = p1 - pos;
		const position_type a2 = p2 - pos;
		const position_type a3 = p3 - pos;
		const value_type s = std::sin(angle);
		const value_type c = std::cos(angle);
		const position_type x0{ a0.x*c - a0.y*s, a0.x*s + a0.y*c };
		const position_type x1{ a1.x*c - a1.y*s, a1.x*s + a1.y*c };
		const position_type x2{ a2.x*c - a2.y*s, a2.x*s + a2.y*c };
		const position_type x3{ a3.x*c - a3.y*s, a3.x*s + a3.y*c };

		return{ x0 + pos, x1 + pos, x2 + pos, x3 + pos };
	}

	Quad::value_type Quad::area() const noexcept
	{
		const value_type s0 = std::abs((p0.x - p2.x)*(p1.y - p0.y) - (p0.x - p1.x)*(p2.y - p0.y));
		const value_type s1 = std::abs((p2.x - p0.x)*(p3.y - p2.y) - (p2.x - p3.x)*(p0.y - p2.y));
		return (s0 + s1) * 0.5;
	}

	Quad::value_type Quad::perimeter() const noexcept
	{
		return p0.distanceFrom(p1) + p1.distanceFrom(p2) + p2.distanceFrom(p3) + p3.distanceFrom(p0);
	}

	const Quad& Quad::draw(const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addQuad(FloatQuad(p0, p1, p2, p3), Float4(color.r, color.g, color.b, color.a));

		return *this;
	}

	const Quad& Quad::draw(const ColorF(&colors)[4]) const
	{
		Siv3DEngine::GetRenderer2D()->addQuad(FloatQuad(p0, p1, p2, p3),
		{
			Float4(colors[0].r, colors[0].g, colors[0].b, colors[0].a),
				Float4(colors[1].r, colors[1].g, colors[1].b, colors[1].a),
				Float4(colors[2].r, colors[2].g, colors[2].b, colors[2].a),
				Float4(colors[3].r, colors[3].g, colors[3].b, colors[3].a)
		});

		return *this;
	}

	void Formatter(FormatData& formatData, const Quad& value)
	{
		formatData.string.push_back(L'(');
		Formatter(formatData, value.p0);
		formatData.string.push_back(L',');
		Formatter(formatData, value.p1);
		formatData.string.push_back(L',');
		Formatter(formatData, value.p2);
		formatData.string.push_back(L',');
		Formatter(formatData, value.p3);
		formatData.string.push_back(L')');
	}
}
