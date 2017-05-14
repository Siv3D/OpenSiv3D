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

# include <Siv3D/Line.hpp>
# include <Siv3D/MathConstants.hpp>
# include <Siv3D/XXHash.hpp>
# include <Siv3D/Shape2D.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	namespace detail
	{
		static void AlignLine(Line& line)
		{
			if (line.begin == line.end)
			{
				return;
			}

			for (uint64 seed = 0; ; ++seed)
			{
				const uint64 h1 = Hash::XXHash(line.begin, seed);
				const uint64 h2 = Hash::XXHash(line.end, seed);

				if (h1 < h2)
				{
					break;
				}
				else if (h1 > h2)
				{
					line.reverse();
					break;
				}
			}
		}

		static bool IsZero(const double x) noexcept
		{
			return std::abs(x) < 1e-10;
		}
	}

	Line::position_type Line::closest(const position_type& pos) const noexcept
	{
		Vec2 v = end - begin;
		const double d = v.length();
		
		if (d == 0.0)
		{
			return begin;
		}
		
		v /= d;
		const double t = v.dot(pos - begin);
		
		if (t < 0.0)
		{
			return begin;
		}
		
		if (t > d)
		{
			return end;
		}
		
		return begin + v * t;
	}
	
	//
	// `Line::intersectsAt()` is based on
	// https://www.codeproject.com/Tips/862988/Find-the-Intersection-Point-of-Two-Line-Segments
	//
	// Licenced with the Code Project Open Licence (CPOL)
	// http://www.codeproject.com/info/cpol10.aspx
	//
	Optional<Line::position_type> Line::intersectsAt(const Line& line) const
	{
		const Vec2 r = end - begin;
		const Vec2 s = line.end - line.begin;
		const Vec2 qp = line.begin - begin;
		const double rxs = r.x * s.y - r.y * s.x;
		const double qpxr = qp.x * r.y - qp.y * r.x;
		const double qpxs = qp.x * s.y - qp.y * s.x;
		const bool rxsIsZero = detail::IsZero(rxs);

		if (rxsIsZero && detail::IsZero(qpxr))
		{
			const double qpr = qp.dot(r);
			const double pqs = (begin - line.begin).dot(s);

			if ((0 <= qpr && qpr <= r.dot(r)) || (0 <= pqs && pqs <= s.dot(s)))
			{
				// Two lines are overlapping			
				return Line::position_type(Math::QNaN, Math::QNaN);
			}

			// Two lines are collinear but disjoint.
			return none;
		}
		
		if (rxsIsZero && !detail::IsZero(qpxr))
		{
			// Two lines are parallel and non-intersecting.
			return none;
		}

		const double t = qpxs / rxs;
		const double u = qpxr / rxs;

		if (!rxsIsZero && (0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0))
		{
			// An intersection was found
			return begin + t * r;
		}

		// Two line segments are not parallel but do not intersect
		return none;
	}

	Optional<Line::position_type> Line::intersectsAtPrecise(const Line& line) const
	{
		if (*this == line)
		{
			return Line::position_type(Math::QNaN, Math::QNaN);
		}

		Line a(*this), b(line);
		detail::AlignLine(a);
		detail::AlignLine(b);

		for (uint64 seed = 0; ; ++seed)
		{
			const uint64 h1 = Hash::XXHash(a, seed);
			const uint64 h2 = Hash::XXHash(b, seed);

			if (h1 < h2)
			{
				return a.intersectsAt(b);
			}
			else if(h1 > h2)
			{
				return b.intersectsAt(a);
			}
		}
	}

	const Line& Line::draw(const LineStyle style, double thickness, const ColorF& color) const
	{
		const Float4 colorF(color.r, color.g, color.b, color.a);

		Siv3DEngine::GetRenderer2D()->addLine(style, begin, end, static_cast<float>(thickness), { colorF, colorF });

		return *this;
	}

	const Line& Line::draw(const LineStyle style, double thickness, const ColorF(&colors)[2]) const
	{
		Siv3DEngine::GetRenderer2D()->addLine(style, begin, end, static_cast<float>(thickness),
		{
			Float4(colors[0].r, colors[0].g, colors[0].b, colors[0].a),
			Float4(colors[1].r, colors[1].g, colors[1].b, colors[1].a)
		});

		return *this;
	}

	const Line& Line::drawArrow(double width, const Vec2& headSize, const ColorF& color) const
	{
		Shape2D::Arrow(begin, end, width, headSize).draw(color);

		return *this;
	}
}
