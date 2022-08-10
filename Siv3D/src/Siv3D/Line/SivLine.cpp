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
# include <Siv3D/Hash.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/Shape2D.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

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

			const uint64 h1 = Hash::FNV1a(line.begin);
			const uint64 h2 = Hash::FNV1a(line.end);

			if (h1 > h2)
			{
				line.reverse();
			}
		}

		[[nodiscard]]
		static bool IsZero(const double x) noexcept
		{
			return (std::abs(x) < 1e-10);
		}
	}

	Line::Line(const value_type x0, const value_type y0, Arg::angle_<value_type> angle, const value_type length) noexcept
		: begin{ x0, y0 }
		, end{ begin + Circular{ length, angle.value() } } {}

	Line::Line(const position_type origin, Arg::angle_<value_type> angle, const value_type length) noexcept
		: begin{ origin }
		, end{ origin + Circular{ length, angle.value() } } {}

	RectF Line::boundingRect() const noexcept
	{
		const auto [x1, x2] = std::minmax(begin.x, end.x);
		const auto [y1, y2] = std::minmax(begin.y, end.y);
		return{ x1, y1, (x2 - x1), (y2 - y1) };
	}

	Line Line::extractLine(double distanceFromOrigin, double length) const noexcept
	{
		if (length <= 0.0)
		{
			distanceFromOrigin += length;
			length = -length;
		}

		return{ position(Math::Saturate(distanceFromOrigin)), position(Math::Saturate(distanceFromOrigin + length)) };
	}

	Line::position_type Line::closest(const position_type pos) const noexcept
	{
		Vec2 v = (end - begin);
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
	Optional<Line::position_type> Line::intersectsAt(const Line& other) const
	{
		const Vec2 r = end - begin;
		const Vec2 s = other.end - other.begin;
		const Vec2 qp = other.begin - begin;
		const double rxs = r.x * s.y - r.y * s.x;
		const double qpxr = qp.x * r.y - qp.y * r.x;
		const double qpxs = qp.x * s.y - qp.y * s.x;

		if (detail::IsZero(rxs))
		{
			if (detail::IsZero(qpxr) && detail::IsZero(qpxs))
			{
				const double qpr = qp.dot(r);
				const double q2pr = (other.end - begin).dot(r);
				const double pqs = (begin - other.begin).dot(s);
				const double p2qs = (end - other.begin).dot(s);

				const double rr = r.dot(r);
				const bool rrIsZero = detail::IsZero(rr);
				const double ss = s.dot(s);
				const bool ssIsZero = detail::IsZero(ss);

				if (rrIsZero && ssIsZero && detail::IsZero(qp.dot(qp)))
				{
					// The two lines are both zero length and in the same position
					return begin;
				}

				if ((not rrIsZero) && ((0 <= qpr && qpr <= rr) || (0 <= q2pr && q2pr <= rr)))
				{
					// Two lines are overlapping
					if (ssIsZero)
					{
						return other.begin;
					}
					else
					{
						return Line::position_type{ Math::QNaN, Math::QNaN };
					}
				}

				if ((not ssIsZero) && ((0 <= pqs && pqs <= ss) || (0 <= p2qs && p2qs <= ss)))
				{
					// Two lines are overlapping
					if (rrIsZero)
					{
						return begin;
					}
					else
					{
						return Line::position_type{ Math::QNaN, Math::QNaN };
					}
				}

				// Two lines are collinear but disjoint.
				return none;
			}

			// Two lines are parallel and non-intersecting.
			return none;
		}
		else
		{
			const double t = qpxs / rxs;
			const double u = qpxr / rxs;
			if ((0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0))
			{
				// An intersection was found
				return begin + t * r;
			}

			// Two line segments are not parallel but do not intersect
			return none;
		}
	}

	Optional<Line::position_type> Line::intersectsAtPrecise(const Line& other) const
	{
		if (*this == other)
		{
			return Line::position_type{ Math::QNaN, Math::QNaN };
		}

		Line a(*this), b(other);
		detail::AlignLine(a);
		detail::AlignLine(b);

		const uint64 h1 = Hash::FNV1a(a);
		const uint64 h2 = Hash::FNV1a(b);

		if (h1 <= h2)
		{
			return a.intersectsAt(b);
		}
		else
		{
			return b.intersectsAt(a);
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

	const Line& Line::paintDoubleHeadedArrow(Image& dst, const double width, const Vec2& headSize, const Color& color) const
	{
		Shape2D::DoubleHeadedArrow(begin, end, width, headSize).asPolygon().paint(dst, color);

		return *this;
	}

	const Line& Line::overwriteDoubleHeadedArrow(Image& dst, const double width, const Vec2& headSize, const Color& color) const
	{
		Shape2D::DoubleHeadedArrow(begin, end, width, headSize).asPolygon().overwrite(dst, color);

		return *this;
	}

	const Line& Line::draw(const ColorF& color) const
	{
		const Float4 colorF = color.toFloat4();
		
		SIV3D_ENGINE(Renderer2D)->addLine(LineStyle::Default, begin, end, 1.0f, { colorF, colorF });
		
		return *this;
	}

	const Line& Line::draw(const ColorF& colorBegin, const ColorF& colorEnd) const
	{
		SIV3D_ENGINE(Renderer2D)->addLine(LineStyle::Default, begin, end, 1.0f, { colorBegin.toFloat4(), colorEnd.toFloat4() });
		
		return *this;
	}

	const Line& Line::draw(const double thickness, const ColorF& color) const
	{
		const Float4 colorF = color.toFloat4();

		SIV3D_ENGINE(Renderer2D)->addLine(LineStyle::Default, begin, end, static_cast<float>(thickness), { colorF, colorF });

		return *this;
	}

	const Line& Line::draw(const LineStyle& style, const double thickness, const ColorF& color) const
	{
		const Float4 colorF = color.toFloat4();

		SIV3D_ENGINE(Renderer2D)->addLine(style, begin, end, static_cast<float>(thickness), { colorF, colorF });

		return *this;
	}

	const Line& Line::draw(const LineStyle& style, const double thickness, const ColorF& colorBegin, const ColorF& colorEnd) const
	{
		SIV3D_ENGINE(Renderer2D)->addLine(style, begin, end, static_cast<float>(thickness), { colorBegin.toFloat4(), colorEnd.toFloat4() });

		return *this;
	}

	const Line& Line::draw(const double thickness, const ColorF& colorBegin, const ColorF& colorEnd) const
	{
		SIV3D_ENGINE(Renderer2D)->addLine(LineStyle::Default, begin, end, static_cast<float>(thickness), { colorBegin.toFloat4(), colorEnd.toFloat4() });

		return *this;
	}

	const Line& Line::drawArrow(const double width, const SizeF& headSize, const ColorF& color) const
	{
		Shape2D::Arrow(begin, end, width, headSize).draw(color);

		return *this;
	}

	const Line& Line::drawDoubleHeadedArrow(const double width, const SizeF& headSize, const ColorF& color) const
	{
		Shape2D::DoubleHeadedArrow(begin, end, width, headSize).draw(color);

		return *this;
	}

	void Formatter(FormatData& formatData, const Line& value)
	{
		formatData.string.append(U"(("_sv);
		formatData.string.append(ToString(value.begin.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.begin.y, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);
		formatData.string.append(ToString(value.end.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.end.y, formatData.decimalPlaces.value));
		formatData.string.append(U"))"_sv);
	}
}
