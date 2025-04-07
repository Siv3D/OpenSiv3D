﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "Emission2D.hpp"

namespace s3d
{
	struct IEmitter2D
	{
		virtual ~IEmitter2D() = default;

		virtual Emission2D emit(const Vec2& emitterPosition, double startSpeed) = 0;

		virtual void drawDebug(const Vec2& emitterPosition) const = 0;
	};
}
