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
# include <Siv3D/Circular.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/MathConstants.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Geometry2D.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		//
		// http://imagingsolution.blog107.fc2.com/blog-entry-137.html
		//
		static Vec2 GetP(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3) noexcept
		{
			const double a = (p3.x - p2.x) * (p0.y - p2.y) - (p3.y - p2.y) * (p0.x - p2.x);
			const double b = (p3.x - p2.x) * (p2.y - p1.y) - (p3.y - p2.y) * (p2.x - p1.x);
			const double c = a / (a + b);
			return{ (p0.x + (p1.x - p0.x) * c), (p0.y + (p1.y - p0.y) * c) };
		}
	}

	Triangle::Triangle(const value_type sides, const value_type angle) noexcept
		: p0{ Circular(Math::InvSqrt3 * sides, angle) }
		, p1{ Circular(Math::InvSqrt3 * sides, 2.0 * Math::OneThirdPi + angle) }
		, p2{ Circular(Math::InvSqrt3 * sides, 4.0 * Math::OneThirdPi + angle) } {}

	Triangle Triangle::stretched(const value_type size) const noexcept
	{
		Line lines[3] =
		{
			{ p0, p1 }, { p1, p2 }, { p2, p0 }
		};

		for (auto& line : lines)
		{
			const Vec2 v = (line.end - line.begin).setLength(size);
			line.moveBy(v.y, -v.x);
		}

		const Vec2 t0 = detail::GetP(lines[2].begin, lines[2].end, lines[0].begin, lines[0].end);
		const Vec2 t1 = detail::GetP(lines[0].begin, lines[0].end, lines[1].begin, lines[1].end);
		const Vec2 t2 = detail::GetP(lines[1].begin, lines[1].end, lines[2].begin, lines[2].end);
		return{ t0, t1, t2 };
	}

	Triangle Triangle::rotatedAt(const position_type pos, value_type angle) const noexcept
	{
		const position_type a0 = (p0 - pos);
		const position_type a1 = (p1 - pos);
		const position_type a2 = (p2 - pos);
		const value_type s = std::sin(angle);
		const value_type c = std::cos(angle);
		const position_type x0{ (a0.x * c - a0.y * s), (a0.x * s + a0.y * c) };
		const position_type x1{ (a1.x * c - a1.y * s), (a1.x * s + a1.y * c) };
		const position_type x2{ (a2.x * c - a2.y * s), (a2.x * s + a2.y * c) };
		return{ (x0 + pos), (x1 + pos), (x2 + pos) };
	}

	Circle Triangle::getCircumscribedCircle() const noexcept
	{
		const double x0 = p0.x;
		const double y0 = p0.y;
		const double x1 = p1.x;
		const double y1 = p1.y;
		const double x2 = p2.x;
		const double y2 = p2.y;
		const double x0_2 = (x0 * x0);
		const double y0_2 = (y0 * y0);
		const double x1_2 = (x1 * x1);
		const double y1_2 = (y1 * y1);
		const double x2_2 = (x2 * x2);
		const double y2_2 = (y2 * y2);
		const double c = 2 * ((x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0));
		const Vec2 center
		{
			((y2 - y0) * (x1_2 - x0_2 + y1_2 - y0_2) + (y0 - y1) * (x2_2 - x0_2 + y2_2 - y0_2)) / c,
			((x0 - x2) * (x1_2 - x0_2 + y1_2 - y0_2) + (x1 - x0) * (x2_2 - x0_2 + y2_2 - y0_2)) / c
		};

		return{ center, center.distanceFrom(p0) };
	}

	Circle Triangle::getInscribedCircle() const noexcept
	{
		const double d0 = p2.distanceFrom(p1);
		const double d1 = p0.distanceFrom(p2);
		const double d2 = p1.distanceFrom(p0);
		const double perimeter = (d0 + d1 + d2);
		const Vec2 center{ (d0 * p0 + d1 * p1 + d2 * p2) / perimeter };
		const double area2 = std::abs((p0.x - p2.x) * (p1.y - p0.y) - (p0.x - p1.x) * (p2.y - p0.y));

		return{ center, (area2 / perimeter) };
	}

	LineString Triangle::outline(const CloseRing closeRing) const
	{
		if (closeRing)
		{
			return{ p0, p1, p2, p0 };
		}
		else
		{
			return{ p0, p1, p2 };
		}
	}

	LineString Triangle::outline(double distanceFromOrigin, double length) const
	{
		if (length <= 0.0)
		{
			distanceFromOrigin += length;
			length = -length;
		}

		constexpr size_t N = 3;
		const double lens[N] = {
			p0.distanceFrom(p1),
			p1.distanceFrom(p2),
			p2.distanceFrom(p0)
		};
		const double perim = (lens[0] + lens[1] + lens[2]);

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

	Polygon Triangle::asPolygon() const
	{
		return Polygon{ { p0, p1, p2 }, {{ 0, 1, 2 }}, boundingRect(), SkipValidation::Yes };
	}

	bool Triangle::leftClicked() const noexcept
	{
		return (MouseL.down() && mouseOver());
	}

	bool Triangle::leftPressed() const noexcept
	{
		return (MouseL.pressed() && mouseOver());
	}

	bool Triangle::leftReleased() const noexcept
	{
		return (MouseL.up() && mouseOver());
	}

	bool Triangle::rightClicked() const noexcept
	{
		return (MouseR.down() && mouseOver());
	}

	bool Triangle::rightPressed() const noexcept
	{
		return (MouseR.pressed() && mouseOver());
	}

	bool Triangle::rightReleased() const noexcept
	{
		return (MouseR.up() && mouseOver());
	}

	bool Triangle::mouseOver() const noexcept
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const Triangle& Triangle::paintFrame(Image& dst, const int32 thickness, const Color& color) const
	{
		LineString{ p0, p1, p2 }.paintClosed(dst, thickness, color);

		return *this;
	}

	const Triangle& Triangle::overwriteFrame(Image& dst, const int32 thickness, const Color& color, const Antialiased antialiased) const
	{
		LineString{ p0, p1, p2 }.overwriteClosed(dst, thickness, color, antialiased);

		return *this;
	}

	const Triangle& Triangle::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addTriangle({ p0, p1, p2 }, color.toFloat4());

		return *this;
	}

	const Triangle& Triangle::draw(const ColorF& color0, const ColorF& color1, const ColorF& color2) const
	{
		SIV3D_ENGINE(Renderer2D)->addTriangle(
			{ p0, p1, p2 },
			{ color0.toFloat4(), color1.toFloat4(), color2.toFloat4() });

		return *this;
	}

	const Triangle& Triangle::drawFrame(const double thickness, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addLineString(LineStyle::Default, &p0, 3, none,
			static_cast<float>(thickness), false, color.toFloat4(), CloseRing::Yes);

		return *this;
	}

	const Triangle& Triangle::drawFrame(const double innerThickness, const double outerThickness, const ColorF& color) const
	{
		const double offset = (outerThickness - innerThickness) * 0.5;
		const Triangle t = stretched(offset);

		SIV3D_ENGINE(Renderer2D)->addLineString(LineStyle::Default, &t.p0, 3, none,
			static_cast<float>(innerThickness + outerThickness),
			(outerThickness == 0.0), color.toFloat4(), CloseRing::Yes);

		return *this;
	}

	Triangle Triangle::FromPoints(const position_type& baseCenter, const position_type& top, const double baseLength) noexcept
	{
		Vec2 right = (top - baseCenter);
		
		right.set(-right.y, right.x).setLength(baseLength * 0.5);

		return{ top, (baseCenter + right), (baseCenter - right) };
	}

	void Formatter(FormatData& formatData, const Triangle& value)
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
		formatData.string.append(U"))"_sv);
	}
}
