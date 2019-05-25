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

# include <Siv3D/Emitter2D.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/Circle.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Triangle.hpp>
# include <Siv3D/Random.hpp>
# include <Siv3D/RandomVec2.hpp>
# include <Siv3D/Math.hpp>

namespace s3d
{
	Emission2D CircleEmitter2D::emit(const Vec2& emitterPosition, const double startSpeed)
	{
		const Vec2 sourceOffset = RandomVec2(Circle(Vec2(0, 0), sourceRadius));

		Emission2D emission;

		if (fromShell)
		{
			const Vec2 v = RandomVec2();
			const Vec2 basePos = emitterPosition.movedBy(v * r);
			emission.position = basePos + sourceOffset;

			if (randomDirection)
			{
				emission.velocity = RandomVec2(startSpeed);
			}
			else
			{
				emission.velocity = (v * startSpeed);
			}
		}
		else
		{
			const Vec2 d = RandomVec2(Circle(Vec2(0, 0), r));
			emission.position = (d + emitterPosition) + sourceOffset;

			if (randomDirection)
			{
				emission.velocity = RandomVec2(startSpeed);
			}
			else
			{
				emission.velocity = (Vec2(d).setLength(startSpeed));
			}
		}

		return emission;
	}

	void CircleEmitter2D::drawDebug(const Vec2& emitterPosition) const
	{
		Circle(emitterPosition, r)
			.drawFrame(2.0, ColorF(1.0, 1.0, 0.0, 0.3));
	}


	Emission2D ArcEmitter2D::emit(const Vec2& emitterPosition, const double startSpeed)
	{
		const double a = Random(direction - angle * 0.5, direction + angle * 0.5);
		const double aR = Math::ToRadians(a);
		const Vec2 sourceOffset = RandomVec2(Circle(Vec2(0, 0), sourceRadius));

		Emission2D emission;

		if (fromShell)
		{
			const Vec2 basePos = emitterPosition.movedBy(Circular(r, aR));
			emission.position = basePos + sourceOffset;

			if (randomDirection)
			{
				emission.velocity = RandomVec2(startSpeed);
			}
			else
			{
				emission.velocity = Circular(startSpeed, aR).toFloat2();
			}
		}
		else
		{
			const Vec2 basePos = emitterPosition.movedBy(Circular(std::sqrt(Random()) * r, aR));
			emission.position = basePos + sourceOffset;

			if (randomDirection)
			{
				emission.velocity = RandomVec2(startSpeed);
			}
			else
			{
				emission.velocity = Circular(startSpeed, aR).toFloat2();
			}
		}

		return emission;
	}

	void ArcEmitter2D::drawDebug(const Vec2& emitterPosition) const
	{
		const double halfAngle = Abs(angle / 2.0);
		Circle(emitterPosition, r)
			.drawPie(ToRadians(direction - halfAngle), ToRadians(halfAngle * 2), ColorF(1.0, 1.0, 0.0, 0.3));
	}


	Emission2D RectEmitter2D::emit(const Vec2& emitterPosition, const double startSpeed)
	{
		const Vec2 sourceOffset = RandomVec2(Circle(Vec2(0, 0), sourceRadius));

		Emission2D emission;

		if (fromShell)
		{
			const double perimeter = (width + height) * 2.0;
			const double rnd = Random(perimeter);	
			const Vec2 topLeft = (Vec2(-width, -height) * 0.5);
			Vec2 d;

			if (rnd < width)
			{
				d = topLeft.movedBy(rnd, 0);
			}
			else if (rnd < (width + height))
			{
				d = topLeft.movedBy(width, (rnd - width));
			}
			else if (rnd < (width + height + width))
			{
				d = topLeft.movedBy(width - (rnd - width - height), height);
			}
			else
			{
				d = topLeft.movedBy(0, perimeter - rnd);
			}

			emission.position = (d + emitterPosition) + sourceOffset;

			if (randomDirection)
			{
				emission.velocity = RandomVec2(startSpeed);
			}
			else
			{
				emission.velocity = (Vec2(d).setLength(startSpeed));
			}
		}
		else
		{
			const Vec2 d = RandomVec2(RectF(Arg::center(0, 0), width, height));
			emission.position = (d + emitterPosition) + sourceOffset;

			if (randomDirection)
			{
				emission.velocity = RandomVec2(startSpeed);
			}
			else
			{
				emission.velocity = (Vec2(d).setLength(startSpeed));
			}
		}

		return emission;
	}

	void RectEmitter2D::drawDebug(const Vec2& emitterPosition) const
	{
		RectF(Arg::center = emitterPosition, width, height)
			.drawFrame(2.0, ColorF(1.0, 1.0, 0.0, 0.3));
	}


	PolygonEmitter2D::PolygonEmitter2D(const Polygon& polygon)
		: m_polygon(polygon)
	{
		if (!polygon)
		{
			return;
		}

		{
			Array<double> triangleAreas;

			for (size_t i = 0; i < polygon.num_triangles(); ++i)
			{
				triangleAreas << polygon.triangle(i).area();
			}

			m_triangleWeights = triangleAreas;
		}
	}

	Emission2D PolygonEmitter2D::emit(const Vec2& emitterPosition, double startSpeed)
	{
		if (!m_polygon)
		{
			return Emission2D{ emitterPosition, RandomVec2(startSpeed) };
		}

		const Vec2 sourceOffset = RandomVec2(Circle(Vec2(0, 0), sourceRadius));
		const size_t randomTriangleIndex = m_triangleWeights(GetDefaultRNG());
		const Triangle randomTriangle = m_polygon.triangle(randomTriangleIndex);
		const Vec2 randomPos = RandomVec2(randomTriangle);
		const Vec2 pos = emitterPosition + randomPos + sourceOffset;

		Emission2D emission;
		emission.position = pos;
		emission.velocity = RandomVec2(startSpeed);
		return emission;
	}

	void PolygonEmitter2D::drawDebug(const Vec2& emitterPosition) const
	{
		m_polygon.drawFrame(emitterPosition, 2.0, ColorF(1.0, 1.0, 0.0, 0.3));
	}
}
