//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/PolygonEmitter2D.hpp>
# include <Siv3D/RandomVec2.hpp>

namespace s3d
{
	PolygonEmitter2D::PolygonEmitter2D(Polygon&& polygon)
		: m_polygon{ std::move(polygon) }
	{
		if (not m_polygon)
		{
			return;
		}

		{
			Array<double> triangleAreas(m_polygon.num_triangles());

			for (size_t i = 0; i < m_polygon.num_triangles(); ++i)
			{
				triangleAreas[i] = m_polygon.triangle(i).area();
			}

			m_triangleWeights = triangleAreas;
		}
	}

	PolygonEmitter2D::PolygonEmitter2D(const Polygon& polygon)
		: PolygonEmitter2D{ Polygon{ polygon } } {}

	Emission2D PolygonEmitter2D::emit(const Vec2& emitterPosition, double startSpeed)
	{
		if (not m_polygon)
		{
			return Emission2D{ emitterPosition, RandomVec2(startSpeed) };
		}

		const Vec2 sourceOffset = RandomVec2(Circle{ Vec2{ 0, 0 }, sourceRadius });
		const size_t randomTriangleIndex = m_triangleWeights(GetDefaultRNG());
		const Triangle randomTriangle = m_polygon.triangle(randomTriangleIndex);
		const Vec2 randomPos = RandomVec2(randomTriangle);
		const Vec2 pos = (emitterPosition + randomPos + sourceOffset);

		Emission2D emission;
		emission.position = pos;
		emission.velocity = RandomVec2(startSpeed);
		return emission;
	}

	void PolygonEmitter2D::drawDebug(const Vec2& emitterPosition) const
	{
		m_polygon.drawFrame(emitterPosition, 2.0, ColorF{ 1.0, 1.0, 0.0, 0.3 });
	}
}
