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

namespace s3d
{
	inline Camera2DParameters Camera2DParameters::Default()
	{
		return{};
	}

	inline Camera2DParameters Camera2DParameters::MouseOnly()
	{
		return{
			.moveToUp		= {},
			.moveToLeft		= {},
			.moveToDown		= {},
			.moveToRight	= {},
			.zoomIn			= {},
			.zoomOut		= {},
		};
	}

	inline Camera2DParameters Camera2DParameters::KeyboardOnly()
	{
		return{
			.wheelScaleFactor	= 1.0,
			.grabSpeedFactor	= 0.0,
		};
	}

	inline Camera2DParameters Camera2DParameters::NoControl()
	{
		return{
			.wheelScaleFactor	= 1.0,
			.grabSpeedFactor	= 0.0,
			.moveToUp		= {},
			.moveToLeft		= {},
			.moveToDown		= {},
			.moveToRight	= {},
			.zoomIn			= {},
			.zoomOut		= {},
		};
	}
}
