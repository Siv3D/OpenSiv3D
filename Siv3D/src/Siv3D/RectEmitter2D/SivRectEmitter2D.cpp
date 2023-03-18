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

# include <Siv3D/RectEmitter2D.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/RandomVec2.hpp>

namespace s3d
{
	Emission2D RectEmitter2D::emit(const Vec2& emitterPosition, const double startSpeed)
	{
		const Vec2 sourceOffset = RandomVec2(Circle{ Vec2{ 0, 0 }, sourceRadius });

		Emission2D emission;

		if (fromShell)
		{
			const double perimeter = (width + height) * 2.0;
			const double rnd = Random(perimeter);
			const Vec2 topLeft = (Vec2{ -width, -height } * 0.5);
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
				emission.velocity = d.withLength(startSpeed);
			}
		}
		else
		{
			const Vec2 d = RandomVec2(RectF{ Arg::center(0, 0), width, height });
			emission.position = (d + emitterPosition) + sourceOffset;

			if (randomDirection)
			{
				emission.velocity = RandomVec2(startSpeed);
			}
			else
			{
				emission.velocity = d.withLength(startSpeed);
			}
		}

		return emission;
	}

	void RectEmitter2D::drawDebug(const Vec2& emitterPosition) const
	{
		RectF{ Arg::center = emitterPosition, width, height }
			.drawFrame(2.0, ColorF{ 1.0, 1.0, 0.0, 0.3 });
	}
}
