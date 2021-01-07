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

			m_splines.resize(points2.size() - 1);

			SplineLib::SplinesFromPoints(static_cast<int32>(points2.size()), points2.data(),
				static_cast<int32>(m_splines.size()), m_splines.data(), tension);

			m_splines.pop_back();
			m_splines.pop_front();

			m_isRing = true;
		}
		else
		{
			m_splines.resize(points.size() - 1);

			SplineLib::SplinesFromPoints(static_cast<int32>(points.size()), points.data(),
				static_cast<int32>(m_splines.size()), m_splines.data(), tension);
		}
	}

	RectF Spline2D::fastBoundingRect(const size_t i) const
	{
		const SplineLib::Bounds2f bb = SplineLib::FastBounds(m_splines[i]);
		return{ bb.min, (bb.max - bb.min) };
	}

	RectF Spline2D::boundingRect(const size_t i) const
	{
		const SplineLib::Bounds2f bb = SplineLib::ExactBounds(m_splines[i]);
		return{ bb.min, (bb.max - bb.min) };
	}

	double Spline2D::length(const size_t i, const double maxError) const
	{
		return SplineLib::Length(m_splines[i], 0.0, 1.0, maxError);
	}

	Vec2 Spline2D::position(const size_t i, const double t) const
	{
		return SplineLib::Position(m_splines[i], t);
	}

	Vec2 Spline2D::velocity(const size_t i, const double t) const
	{
		return SplineLib::Velocity(m_splines[i], t);
	}

	Vec2 Spline2D::acceleration(const size_t i, const double t) const
	{
		return SplineLib::Acceleration(m_splines[i], t);
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
			static_cast<int32>(m_splines.size()),
			m_splines.data(),
			&index);
		return{ static_cast<size_t>(index), t };
	}

	Array<std::pair<SplineIndex, SplineIndex>> Spline2D::findIntersections(const double tolerance) const
	{
		constexpr int32 maxResults = 1024;

		Array<int32[2]> indices(maxResults);
		Array<double[2]> ts(maxResults);

		const size_t num_intersections = SplineLib::FindSplineIntersections(
			static_cast<int32>(m_splines.size()),
			m_splines.data(), maxResults, indices.data(), ts.data(), tolerance);

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
			static_cast<int32>(m_splines.size()), m_splines.data(), dl))
		{
			return{ static_cast<size_t>(index), t };
		}
		else
		{
			SplineLib::ClampAgent(&index, &t, static_cast<int32>(m_splines.size()));
			return{ static_cast<size_t>(index), t };
		}
	}

	SplineIndex Spline2D::advanceWrap(SplineIndex si, double dl) const
	{
		int index = static_cast<int>(si.i);
		double t = si.t;

		if (SplineLib::AdvanceAgent(&index, &t,
			static_cast<int32>(m_splines.size()), m_splines.data(), dl))
		{
			return{ static_cast<size_t>(index), t };
		}
		else
		{
			SplineLib::WrapAgent(&index, &t, static_cast<int32>(m_splines.size()));
			return{ static_cast<size_t>(index), t };
		}
	}

	SplineIndex Spline2D::advanceMirror(SplineIndex si, double dl, int32& direction) const
	{
		int index = static_cast<int>(si.i);
		double t = si.t;

		if (SplineLib::AdvanceAgent(&index, &t,
			static_cast<int32>(m_splines.size()), m_splines.data(), dl))
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

		LineString points(quality * size() + 1);
		{
			const size_t s = size();
			const double tDelta = (1 / static_cast<double>(quality));
			const CSpline2* pSrc = m_splines.data();
			Vec2* pDst = points.data();

			for (size_t i = 0; i < s; ++i)
			{
				*pDst++ = SplineLib::Position0(*pSrc);

				for (int32 t = 1; t < quality; ++t)
				{
					*pDst++ = SplineLib::Position(*pSrc, (t * tDelta));
				}

				++pSrc;
			}

			*pDst = SplineLib::Position1(m_splines.back());
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

		asLineString(quality).draw(thickness, color);

		return *this;
	}
}
