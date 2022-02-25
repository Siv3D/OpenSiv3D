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

# pragma once
# include "Common.hpp"
# include "IEmitter2D.hpp"

namespace s3d
{
	struct CircleEmitter2D : IEmitter2D
	{
		double sourceRadius = 5.0;
		
		double r = 20.0;
		
		bool randomDirection = false;
		
		bool fromShell = false;

		Emission2D emit(const Vec2& emitterPosition, double startSpeed) override;

		void drawDebug(const Vec2& emitterPosition) const override;
	};
}
