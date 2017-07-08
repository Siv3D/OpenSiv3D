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

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "LineString.hpp"
# include "Geometry2D.hpp"

namespace s3d
{
	/// <summary>
	/// 3 次ベジェ曲線
	/// </summary>
	struct Bezier3
	{
		Vec2 p0, p1, p2, p3;

		Bezier3() = default;

		constexpr Bezier3(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2, const Vec2& _p3) noexcept
			: p0(_p0)
			, p1(_p1)
			, p2(_p2)
			, p3(_p3) {}

		constexpr Vec2 getPos(const double t) const noexcept
		{
			return (1 - t)*(1 - t)*(1 - t)*p0 + 3 * (1 - t)*(1 - t)*t*p1 + 3 * (1 - t)*t*t*p2 + t*t*t*p3;
		}

		Vec2 getTangent(const double t) const noexcept
		{
			return (-3 * p0*(1 - t) * (1 - t) +
				p1*(3 * (1 - t)*(1 - t) - 6 * (1 - t) *t) +
				p2*(6 * (1 - t)*t - 3 * t * t) + 3 * p3*t * t).normalized();
		}

		LineString getLineString(const uint32 quality = 24) const
		{
			return getLineString(0.0, 1.0, quality);
		}

		LineString getLineString(double start, double end, uint32 quality = 24) const;

		template <class Shape2DType>
		bool intersects(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::Intersect(*this, shape)))
		{
			return Geometry2D::Intersect(*this, shape);
		}

		template <class Shape2DType>
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::IntersectAt(*this, shape)))
		{
			return Geometry2D::IntersectAt(*this, shape);
		}

		// paint, overpaint
	
		void draw(const ColorF& color = Palette::White) const
		{
			return draw(1.0, color);
		}

		void draw(double thickness, const ColorF& color = Palette::White) const;
	};

	struct Bezier3Path
	{
	private:

		Vec2 m_v0, m_v1, m_v2;

		double m_t = 0.0;

	public:

		Bezier3Path() = default;

		explicit constexpr Bezier3Path(const Bezier3& bezier) noexcept
			: m_v0(-3 * bezier.p0 + 9 * bezier.p1 - 9 * bezier.p2 + 3 * bezier.p3)
			, m_v1(6 * bezier.p0 - 12 * bezier.p1 + 6 * bezier.p2)
			, m_v2(-3 * bezier.p0 + 3 * bezier.p1) {}

		constexpr void setT(const double t) noexcept
		{
			m_t = t;
		}

		constexpr double getT() const noexcept
		{
			return m_t;
		}

		double advance(double distance, int32 quality = 8) noexcept
		{
			for (int i = 0; i < quality; ++i)
			{
				m_t = m_t + (distance / quality) / (m_t * m_t * m_v0 + m_t * m_v1 + m_v2).length();
			}

			return m_t;
		}
	};
}
