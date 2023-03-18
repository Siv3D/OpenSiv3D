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

# include <Siv3D/ArcEmitter2D.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/RandomVec2.hpp>
# include <Siv3D/Circular.hpp>

namespace s3d
{
	Emission2D ArcEmitter2D::emit(const Vec2& emitterPosition, const double startSpeed)
	{
		const double a = Random(direction - angle * 0.5, direction + angle * 0.5);
		const double aR = Math::ToRadians(a);
		const Vec2 sourceOffset = RandomVec2(Circle{ Vec2{0, 0}, sourceRadius });

		Emission2D emission;

		if (fromShell)
		{
			const Vec2 basePos = emitterPosition.movedBy(Circular{ r, aR }.fastToVec2());
			emission.position = (basePos + sourceOffset);

			if (randomDirection)
			{
				emission.velocity = RandomVec2(startSpeed);
			}
			else
			{
				emission.velocity = Circular{ startSpeed, aR }.fastToVec2();
			}
		}
		else
		{
			const Vec2 basePos = emitterPosition.movedBy(Circular{ std::sqrt(Random()) * r, aR }.fastToVec2());
			emission.position = (basePos + sourceOffset);

			if (randomDirection)
			{
				emission.velocity = RandomVec2(startSpeed);
			}
			else
			{
				emission.velocity = Circular{ startSpeed, aR }.fastToVec2();
			}
		}

		return emission;
	}

	void ArcEmitter2D::drawDebug(const Vec2& emitterPosition) const
	{
		const double halfAngle = Abs(angle / 2.0);
		Circle{ emitterPosition, r }
			.drawPie(Math::ToRadians(direction - halfAngle), Math::ToRadians(halfAngle * 2), ColorF{ 1.0, 1.0, 0.0, 0.3 });
	}
}
