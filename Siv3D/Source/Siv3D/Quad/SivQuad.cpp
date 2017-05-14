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
# include <Siv3D/Line.hpp>
# include <Siv3D/FloatQuad.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedQuad.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	namespace detail
	{
		//
		// http://imagingsolution.blog107.fc2.com/blog-entry-137.html
		//
		static constexpr Vec2 GetP(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3) noexcept
		{
			const double a = (p3.x - p2.x) * (p0.y - p2.y) - (p3.y - p2.y) * (p0.x - p2.x);
			const double b = (p3.x - p2.x) * (p2.y - p1.y) - (p3.y - p2.y) * (p2.x - p1.x);
			const double c = a / (a + b);
			return Vec2(p0.x + (p1.x - p0.x) * c, p0.y + (p1.y - p0.y) * c);
		}
	}

	Quad Quad::stretched(const value_type size) const noexcept
	{
		Line lines[4] =
		{
			{ p0, p1 },{ p1, p2 },{ p2, p3 },{ p3, p0 }
		};

		for (auto& line : lines)
		{
			const Vec2 v = (line.end - line.begin).setLength(size);
			line.moveBy(v.y, -v.x);
		}

		const Vec2 t0 = detail::GetP(lines[3].begin, lines[3].end, lines[0].begin, lines[0].end);
		const Vec2 t1 = detail::GetP(lines[0].begin, lines[0].end, lines[1].begin, lines[1].end);
		const Vec2 t2 = detail::GetP(lines[1].begin, lines[1].end, lines[2].begin, lines[2].end);
		const Vec2 t3 = detail::GetP(lines[2].begin, lines[2].end, lines[3].begin, lines[3].end);
		return Quad(t0, t1, t2, t3);
	}

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

	bool Quad::leftClicked() const
	{
		return MouseL.down() && mouseOver();
	}

	bool Quad::leftPressed() const
	{
		return MouseL.pressed() && mouseOver();
	}

	bool Quad::leftReleased() const
	{
		return MouseL.up() && mouseOver();
	}

	bool Quad::rightClicked() const
	{
		return MouseR.down() && mouseOver();
	}

	bool Quad::rightPressed() const
	{
		return MouseR.pressed() && mouseOver();
	}

	bool Quad::rightReleased() const
	{
		return MouseR.up() && mouseOver();
	}

	bool Quad::mouseOver() const
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const Quad& Quad::draw(const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addQuad(FloatQuad(p0, p1, p2, p3), color.toFloat4());

		return *this;
	}

	const Quad& Quad::draw(const ColorF(&colors)[4]) const
	{
		Siv3DEngine::GetRenderer2D()->addQuad(FloatQuad(p0, p1, p2, p3),
			{ colors[0].toFloat4(), colors[1].toFloat4(), colors[2].toFloat4(), colors[3].toFloat4() });

		return *this;
	}

	const Quad& Quad::drawFrame(double thickness, const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addLineString(LineStyle::SquareCap, &p0, 4, s3d::none,
			static_cast<float>(thickness), false, color.toFloat4(), true);

		return *this;
	}

	const Quad& Quad::drawFrame(double innerThickness, double outerThickness, const ColorF& color) const
	{
		const double offset = (outerThickness - innerThickness) * 0.5;

		const Quad t = stretched(offset);

		Siv3DEngine::GetRenderer2D()->addLineString(LineStyle::SquareCap, &t.p0, 4, none,
			static_cast<float>(innerThickness + outerThickness),
			outerThickness == 0.0, color.toFloat4(), true);

		return *this;
	}

	TexturedQuad Quad::operator ()(const Texture& texture) const
	{
		const Vec2 center = (p0 + p1 + p2 + p3) * 0.25;

		return TexturedQuad(texture,
			0.0f, 0.0f, 1.0f, 1.0f,
			*this,
			center);
	}

	TexturedQuad Quad::operator ()(const TextureRegion& textureRegion) const
	{
		const Vec2 center = (p0 + p1 + p2 + p3) * 0.25;

		return TexturedQuad(textureRegion.texture,
			textureRegion.uvRect,
			*this,
			center);
	}

	void Formatter(FormatData& formatData, const Quad& value)
	{
		formatData.string.push_back(S3DCHAR('('));
		Formatter(formatData, value.p0);
		formatData.string.push_back(S3DCHAR(','));
		Formatter(formatData, value.p1);
		formatData.string.push_back(S3DCHAR(','));
		Formatter(formatData, value.p2);
		formatData.string.push_back(S3DCHAR(','));
		Formatter(formatData, value.p3);
		formatData.string.push_back(S3DCHAR(')'));
	}
}
