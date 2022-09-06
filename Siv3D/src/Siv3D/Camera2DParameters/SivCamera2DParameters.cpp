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

# include <Siv3D/Camera2DParameters.hpp>

namespace s3d
{
	Camera2DParameters Camera2DParameters::Make(const CameraControl cameraControl)
	{
		Camera2DParameters params{
			.wheelScaleFactor	= 1.0,
			.grabSpeedFactor	= 0.0,
			.moveToUp		= {},
			.moveToLeft		= {},
			.moveToDown		= {},
			.moveToRight	= {},
			.zoomIn			= {},
			.zoomOut		= {},
		};

		if (cameraControl & CameraControl::WASDKeys)
		{
			params.moveToUp		= ([] { return KeyW.pressed(); });
			params.moveToLeft	= ([] { return KeyA.pressed(); });
			params.moveToDown	= ([] { return KeyS.pressed(); });
			params.moveToRight	= ([] { return KeyD.pressed(); });
		}

		if (cameraControl & CameraControl::UpDownKeys)
		{
			params.zoomIn	= ([] { return KeyUp.pressed(); });
			params.zoomOut	= ([] { return KeyDown.pressed(); });
		}

		if (cameraControl & CameraControl::RightClick)
		{
			params.grabSpeedFactor = 4.0;
		}

		if (cameraControl & CameraControl::Wheel)
		{
			params.wheelScaleFactor = 1.125;
		}
		
		return params;
	}

	Camera2DParameters Camera2DParameters::Default()
	{
		return{};
	}

	Camera2DParameters Camera2DParameters::MouseOnly()
	{
		return Make(CameraControl::Mouse);
	}

	Camera2DParameters Camera2DParameters::KeyboardOnly()
	{
		return Make(CameraControl::Keyboard);
	}

	Camera2DParameters Camera2DParameters::NoControl()
	{
		return Make(CameraControl::None_);
	}
}
