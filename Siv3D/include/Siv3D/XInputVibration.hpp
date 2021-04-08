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

# pragma once
# include "Common.hpp"

namespace s3d
{
	struct XInputVibration
	{
		double leftMotor = 0.0;

		double rightMotor = 0.0;

		double leftTrigger = 0.0;

		double rightTrigger = 0.0;
	};
}
