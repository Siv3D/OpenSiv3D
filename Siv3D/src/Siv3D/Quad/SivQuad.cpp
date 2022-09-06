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

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Geometry2D.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedQuad.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		//
		// http://imagingsolution.blog107.fc2.com/blog-entry-137.html
		//
		[[nodiscard]]
		static constexpr Vec2 GetP(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3) noexcept
		{
			const double a = (p3.x - p2.x) * (p0.y - p2.y) - (p3.y - p2.y) * (p0.x - p2.x);
			const double b = (p3.x - p2.x) * (p2.y - p1.y) - (p3.y - p2.y) * (p2.x - p1.x);
			const double c = (a / (a + b));
			return{ (p0.x + (p1.x - p0.x) * c), (p0.y + (p1.y - p0.y) * c) };
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
		return{ t0, t1, t2, t3 };
	}

	Quad Quad::rotatedAt(const position_type pos, const value_type angle) const noexcept
	{
		const position_type a0 = (p0 - pos);
		const position_type a1 = (p1 - pos);
		const position_type a2 = (p2 - pos);
		const position_type a3 = (p3 - pos);
		const value_type s = std::sin(angle);
		const value_type c = std::cos(angle);
		const position_type x0{ (a0.x * c - a0.y * s), (a0.x * s + a0.y * c) };
		const position_type x1{ (a1.x * c - a1.y * s), (a1.x * s + a1.y * c) };
		const position_type x2{ (a2.x * c - a2.y * s), (a2.x * s + a2.y * c) };
		const position_type x3{ (a3.x * c - a3.y * s), (a3.x * s + a3.y * c) };

		return{ (x0 + pos), (x1 + pos), (x2 + pos), (x3 + pos) };
	}

	Quad::value_type Quad::perimeter() const noexcept
	{
		return (p0.distanceFrom(p1) + p1.distanceFrom(p2) + p2.distanceFrom(p3) + p3.distanceFrom(p0));
	}

	LineString Quad::outline(const CloseRing closeRing) const
	{
		if (closeRing)
		{
			return{ p0, p1, p2, p3, p0 };
		}
		else
		{
			return{ p0, p1, p2, p3 };
		}
	}

	LineString Quad::outline(double distanceFromOrigin, double length) const
	{
		if (length <= 0.0)
		{
			distanceFromOrigin += length;
			length = -length;
		}

		constexpr size_t N = 4;
		const double lens[N] = {
			p0.distanceFrom(p1),
			p1.distanceFrom(p2),
			p2.distanceFrom(p3),
			p3.distanceFrom(p0)
		};
		const double perim = (lens[0] + lens[1] + lens[2] + lens[3]);

		distanceFromOrigin = std::fmod(distanceFromOrigin, perim) + (distanceFromOrigin < 0 ? perim : 0);
		length = Min(length, perim);
		const double distanceToTarget = (distanceFromOrigin + length);

		LineString points;
		double currentLength = 0.0;

		for (size_t n = 0; n < (N * 2); ++n)
		{
			const size_t i = (n % N);
			const double len = lens[i];
			const Vec2 pFrom = p(i);
			const Vec2 pTo = p((N <= (i + 1)) ? (i - (N - 1)) : (i + 1));

			if (not points)
			{
				if ((distanceFromOrigin <= (currentLength + len)))
				{
					const Vec2 origin = pFrom + (pTo - pFrom)
						.setLength(distanceFromOrigin - currentLength);
					points << origin;

					if (distanceToTarget <= (currentLength + len))
					{
						const Vec2 target = pFrom + (pTo - pFrom)
							.setLength(distanceToTarget - currentLength);
						points << target;
						break;
					}

					points << pTo;
				}
			}
			else
			{
				if (distanceToTarget <= (currentLength + len))
				{
					const Vec2 target = pFrom + (pTo - pFrom)
						.setLength(distanceToTarget - currentLength);
					points << target;
					break;
				}

				points << pTo;
			}

			currentLength += len;
		}

		return points;
	}

	Polygon Quad::asPolygon() const
	{
		return Polygon({ p0, p1, p2, p3 }, {{ 0, 1, 3 }, { 3, 1, 2 }}, boundingRect(), SkipValidation::Yes);
	}

	bool Quad::leftClicked() const noexcept
	{
		return (MouseL.down() && mouseOver());
	}

	bool Quad::leftPressed() const noexcept
	{
		return (MouseL.pressed() && mouseOver());
	}

	bool Quad::leftReleased() const noexcept
	{
		return (MouseL.up() && mouseOver());
	}

	bool Quad::rightClicked() const noexcept
	{
		return (MouseR.down() && mouseOver());
	}

	bool Quad::rightPressed() const noexcept
	{
		return (MouseR.pressed() && mouseOver());
	}

	bool Quad::rightReleased() const noexcept
	{
		return (MouseR.up() && mouseOver());
	}

	bool Quad::mouseOver() const noexcept
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const Quad& Quad::paintFrame(Image& dst, const int32 thickness, const Color& color) const
	{
		LineString{ p0, p1, p2, p3 }.paintClosed(dst, thickness, color);

		return *this;
	}

	const Quad& Quad::overwriteFrame(Image& dst, const int32 thickness, const Color& color, const Antialiased antialiased) const
	{
		LineString{ p0, p1, p2, p3 }.overwriteClosed(dst, thickness, color, antialiased);

		return *this;
	}

	const Quad& Quad::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addQuad(FloatQuad{ p0, p1, p2, p3 }, color.toFloat4());

		return *this;
	}

	const Quad& Quad::draw(const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		SIV3D_ENGINE(Renderer2D)->addQuad(FloatQuad{ p0, p1, p2, p3 },
			{ color0.toFloat4(), color1.toFloat4(), color2.toFloat4(), color3.toFloat4() });

		return *this;
	}

	const Quad& Quad::drawFrame(double thickness, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addLineString(LineStyle::Default, &p0, 4, none,
			static_cast<float>(thickness), false, color.toFloat4(), CloseRing::Yes);

		return *this;
	}

	const Quad& Quad::drawFrame(double innerThickness, double outerThickness, const ColorF& color) const
	{
		const double offset = ((outerThickness - innerThickness) * 0.5);
		const Quad t = stretched(offset);

		SIV3D_ENGINE(Renderer2D)->addLineString(LineStyle::Default, &t.p0, 4, none,
			static_cast<float>(innerThickness + outerThickness),
			(outerThickness == 0.0), color.toFloat4(), CloseRing::Yes);

		return *this;
	}

	TexturedQuad Quad::operator ()(const Texture& texture) const
	{
		const Vec2 center = (p0 + p1 + p2 + p3) * 0.25;

		return{ texture,
			0.0f, 0.0f, 1.0f, 1.0f,
			*this,
			center };
	}

	TexturedQuad Quad::operator ()(const TextureRegion& textureRegion) const
	{
		const Vec2 center = ((p0 + p1 + p2 + p3) * 0.25);

		return{ textureRegion.texture,
			textureRegion.uvRect,
			*this,
			center };
	}

	void Formatter(FormatData& formatData, const Quad& value)
	{
		formatData.string.append(U"(("_sv);

		formatData.string.append(ToString(value.p0.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p0.y, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.p1.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p1.y, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.p2.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p2.y, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.p3.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p3.y, formatData.decimalPlaces.value));
		formatData.string.append(U"))"_sv);
	}
}
