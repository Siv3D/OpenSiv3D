//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Line.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/MathConstants.hpp>
# include <Siv3D/XXHash.hpp>
# include <Siv3D/ByteArrayViewAdapter.hpp>
# include <Siv3D/Shape2D.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>

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

	Line Line::stretched(const value_type length) const noexcept
	{
		const position_type v = vector().setLength(length);

		return Line(begin - v, end + v);
	}

	Line Line::stretched(const value_type lengthBegin, const value_type lengthEnd) const noexcept
	{
		const position_type v = vector().normalized();

		return Line(begin - v * lengthBegin, end + v * lengthEnd);
	}

	Line::value_type Line::length() const noexcept
	{
		return begin.distanceFrom(end);
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

	RectF Line::boundingRect() const noexcept
	{
		const auto[x1, x2] = std::minmax(begin.x, end.x);
		const auto[y1, y2] = std::minmax(begin.y, end.y);
		return RectF(x1, y1, x2 - x1, y2 - y1);
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
	
	const Line& Line::paintArrow(Image& dst, const double width, const Vec2& headSize, const Color& color) const
	{
		Shape2D::Arrow(begin, end, width, headSize).asPolygon().paint(dst, color);

		return *this;
	}

	const Line& Line::overwriteArrow(Image& dst, const double width, const Vec2& headSize, const Color& color) const
	{
		Shape2D::Arrow(begin, end, width, headSize).asPolygon().overwrite(dst, color);

		return *this;
	}

	const Line& Line::draw(const ColorF& color) const
	{
		return draw(LineStyle::Default, 1.0, color);
	}

	const Line& Line::draw(const ColorF& colorBegin, const ColorF& colorEnd) const
	{
		return draw(LineStyle::Default, 1.0, colorBegin, colorEnd);
	}

	const Line& Line::draw(double thickness, const ColorF& color) const
	{
		return draw(LineStyle::Default, thickness, color);
	}

	const Line& Line::draw(double thickness, const ColorF& colorBegin, const ColorF& colorEnd) const
	{
		return draw(LineStyle::Default, thickness, colorBegin, colorEnd);
	}

	const Line& Line::draw(const LineStyle& style, double thickness, const ColorF& color) const
	{
		const Float4 colorF = color.toFloat4();

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addLine(style, begin, end, static_cast<float>(thickness), { colorF, colorF });

		return *this;
	}

	const Line& Line::draw(const LineStyle& style, double thickness, const ColorF& colorBegin, const ColorF& colorEnd) const
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->addLine(style, begin, end, static_cast<float>(thickness),
		{
			colorBegin.toFloat4(),
			colorEnd.toFloat4()
		});

		return *this;
	}

	const Line& Line::drawArrow(double width, const Vec2& headSize, const ColorF& color) const
	{
		Shape2D::Arrow(begin, end, width, headSize).draw(color);

		return *this;
	}

	void Formatter(FormatData& formatData, const Line& value)
	{
		formatData.string.push_back(U'(');
		Formatter(formatData, value.begin);
		formatData.string.append(U", "_sv);
		Formatter(formatData, value.end);
		formatData.string.push_back(U')');
	}
}
