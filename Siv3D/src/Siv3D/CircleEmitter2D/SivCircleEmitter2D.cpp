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

# include <Siv3D/CircleEmitter2D.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/RandomVec2.hpp>

namespace s3d
{
	Emission2D CircleEmitter2D::emit(const Vec2& emitterPosition, const double startSpeed)
	{
		const Vec2 sourceOffset = RandomVec2(Circle{ Vec2{ 0, 0 }, sourceRadius });

		Emission2D emission;

		if (fromShell)
		{
			const Vec2 v = RandomVec2();
			const Vec2 basePos = emitterPosition.movedBy(v * r);
			emission.position = (basePos + sourceOffset);

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
			const Vec2 d = RandomVec2(Circle{ Vec2{0, 0}, r });
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

	void CircleEmitter2D::drawDebug(const Vec2& emitterPosition) const
	{
		Circle{ emitterPosition, r }
			.drawFrame(2.0, ColorF{ 1.0, 1.0, 0.0, 0.3 });
	}
}
