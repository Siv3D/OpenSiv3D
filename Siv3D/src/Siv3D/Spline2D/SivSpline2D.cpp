//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Spline2D.hpp>
# include <ThirdParty/SplineLib/Splines.h>

namespace s3d
{
	Spline2D::Spline2D(const Array<Vec2>& points, const double tension)
		: Spline2D(points, CloseRing::No, tension)
	{
		// do nothing
	}

	Spline2D::Spline2D(const Array<Vec2>& points, const CloseRing closeRing, double tension)
	{
		if (points.size() < 2)
		{
			return;
		}

		tension = Clamp(tension, -1.0, 1.0);

		if (closeRing)
		{
			Array<Vec2> points2(Arg::reserve = (points.size() + 3));
			points2.push_back(points.back());
			points2.append(points);
			points2.push_back(points.front());
			points2.push_back(points[1]);

			m_splinesBuffer.resize(points2.size() - 1);

			SplineLib::SplinesFromPoints(static_cast<int32>(points2.size()), points2.data(),
				static_cast<int32>(m_splinesBuffer.size()), m_splinesBuffer.data(), tension);

			m_ptr = &m_splinesBuffer[1];
			m_size = (m_splinesBuffer.size() - 2);

			m_isRing = true;
		}
		else
		{
			m_splinesBuffer.resize(points.size() - 1);

			SplineLib::SplinesFromPoints(static_cast<int32>(points.size()), points.data(),
				static_cast<int32>(m_splinesBuffer.size()), m_splinesBuffer.data(), tension);

			m_ptr = m_splinesBuffer.data();
			m_size = m_splinesBuffer.size();
		}
	}

	RectF Spline2D::fastBoundingRect(const size_t i) const
	{
		const SplineLib::Bounds2f bb = SplineLib::FastBounds(m_ptr[i]);
		return{ bb.min, (bb.max - bb.min) };
	}

	RectF Spline2D::boundingRect(const size_t i) const
	{
		const SplineLib::Bounds2f bb = SplineLib::ExactBounds(m_ptr[i]);
		return{ bb.min, (bb.max - bb.min) };
	}

	double Spline2D::length(const size_t i, const double maxError) const
	{
		return SplineLib::Length(m_ptr[i], maxError);
	}

	double Spline2D::length(const size_t i, const double t0, const double t1, const double maxError) const
	{
		return SplineLib::Length(m_ptr[i], t0, t1, maxError);
	}

	Vec2 Spline2D::position(const size_t i, const double t) const
	{
		return SplineLib::Position(m_ptr[i], t);
	}

	Vec2 Spline2D::velocity(const size_t i, const double t) const
	{
		return SplineLib::Velocity(m_ptr[i], t);
	}

	Vec2 Spline2D::acceleration(const size_t i, const double t) const
	{
		return SplineLib::Acceleration(m_ptr[i], t);
	}

	double Spline2D::curvature(const size_t i, const double t) const
	{
		return SplineLib::Curvature(m_ptr[i], t);
	}

	SplineIndex Spline2D::findNearest(const Vec2 pos) const
	{
		if (isEmpty())
		{
			throw std::out_of_range("Spline2D::findNearest() spline is empty");
		}

		int index = 0;
		const double t = SplineLib::FindClosestPoint(
			pos,
			static_cast<int32>(m_size),
			m_ptr,
			&index);
		return{ static_cast<size_t>(index), t };
	}

	Array<std::pair<SplineIndex, SplineIndex>> Spline2D::findIntersections(const double tolerance) const
	{
		constexpr int32 maxResults = 1024;

		Array<int32[2]> indices(maxResults);
		Array<double[2]> ts(maxResults);

		const size_t num_intersections = SplineLib::FindSplineIntersections(
			static_cast<int32>(m_size),
			m_ptr, maxResults, indices.data(), ts.data(), tolerance);

		Array<std::pair<SplineIndex, SplineIndex>> results(num_intersections);

		for (size_t i = 0; i < num_intersections; ++i)
		{
			results[i].first = { static_cast<size_t>(indices[i][0]), ts[i][0] };
			results[i].second = { static_cast<size_t>(indices[i][1]), ts[i][1] };
		}

		return results;
	}

	SplineIndex Spline2D::advance(const SplineIndex si, const double dl) const
	{
		int index = static_cast<int>(si.i);
		double t = si.t;

		if (SplineLib::AdvanceAgent(&index, &t,
			static_cast<int32>(m_size), m_ptr, dl))
		{
			return{ static_cast<size_t>(index), t };
		}
		else
		{
			SplineLib::ClampAgent(&index, &t, static_cast<int32>(m_size));
			return{ static_cast<size_t>(index), t };
		}
	}

	SplineIndex Spline2D::advanceWrap(SplineIndex si, double dl) const
	{
		int index = static_cast<int>(si.i);
		double t = si.t;

		if (SplineLib::AdvanceAgent(&index, &t,
			static_cast<int32>(m_size), m_ptr, dl))
		{
			return{ static_cast<size_t>(index), t };
		}
		else
		{
			SplineLib::WrapAgent(&index, &t, static_cast<int32>(m_size));
			return{ static_cast<size_t>(index), t };
		}
	}

	SplineIndex Spline2D::advanceMirror(SplineIndex si, double dl, int32& direction) const
	{
		int index = static_cast<int>(si.i);
		double t = si.t;

		if (SplineLib::AdvanceAgent(&index, &t,
			static_cast<int32>(m_size), m_ptr, dl))
		{
			direction = ((dl >= 0) ? 1 : -1);
			return{ static_cast<size_t>(index), t };
		}
		else
		{
			direction = ((dl < 0) ? 1 : -1);
			SplineLib::ReverseAgent(&index, &t);
			return{ static_cast<size_t>(index), t };
		}
	}

	LineString Spline2D::asLineString(int32 quality) const
	{
		if (isEmpty())
		{
			return{};
		}

		quality = Max(2, quality);

		LineString points(quality * m_size + 1);
		{
			const size_t s = m_size;
			const double tDelta = (1 / static_cast<double>(quality));
			const CSpline2* pSrc = m_ptr;
			Vec2* pDst = points.data();

			for (size_t i = 0; i < s; ++i)
			{
				*pDst++ = SplineLib::Position0(*pSrc);

				for (int32 k = 1; k < quality; ++k)
				{
					const double t = (k * tDelta);
					*pDst++ = SplineLib::Position(*pSrc, t);
				}

				++pSrc;
			}

			*pDst = SplineLib::Position1(m_ptr[(m_size - 1)]);
		}

		return points;
	}

	Polygon Spline2D::calculateBuffer(const double distance, const int32 quality, const int32 bufferQuality) const
	{
		if (m_isRing)
		{
			if (LineString points = asLineString(quality))
			{
				points.pop_front();
				return points.calculateBufferClosed(distance, bufferQuality);
			}
			else
			{
				return{};
			}
		}
		else
		{
			return asLineString(quality).calculateBuffer(distance, bufferQuality);
		}
	}

	const Spline2D& Spline2D::draw(const ColorF& color, const int32 quality) const
	{
		return draw(1.0, color, quality);
	}

	const Spline2D& Spline2D::draw(const double thickness, const ColorF& color, const int32 quality) const
	{
		if (isEmpty())
		{
			return *this;
		}

		if (LineString points = asLineString(quality))
		{
			if (m_isRing)
			{
				points.pop_back();
				points.drawClosed(thickness, color);
			}
			else
			{
				points.draw(thickness, color);
			}
		}

		return *this;
	}

	const Spline2D& Spline2D::draw(const double thickness, std::function<ColorF(SplineIndex)> colorFunc, int32 quality) const
	{
		if (isEmpty())
		{
			return *this;
		}

		quality = Max(2, quality);

		const size_t num_points = (quality * m_size + (not m_isRing));
		LineString points(num_points);
		Array<ColorF> colors(num_points);
		{
			const size_t s = m_size;
			const double tDelta = (1 / static_cast<double>(quality));
			const CSpline2* pSrc = m_ptr;
			Vec2* pDst = points.data();
			ColorF* pDstColor = colors.data();

			for (size_t i = 0; i < s; ++i)
			{
				*pDst++ = SplineLib::Position0(*pSrc);
				*pDstColor++ = colorFunc({ i, 0.0 });

				for (int32 k = 1; k < quality; ++k)
				{
					const double t = (k * tDelta);
					*pDst++ = SplineLib::Position(*pSrc, t);
					*pDstColor++ = colorFunc({ i, t });
				}

				++pSrc;
			}

			if (not m_isRing)
			{
				*pDst = SplineLib::Position1(m_ptr[(m_size - 1)]);
				*pDstColor++ = colorFunc({ (s - 1), 1.0 });
			}
		}

		if (m_isRing)
		{
			points.drawClosed(thickness, colors);
		}
		else
		{
			points.draw(thickness, colors);
		}

		return *this;
	}
}
