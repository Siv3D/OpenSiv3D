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
# include <functional>
# include "Common.hpp"
# include "Keyboard.hpp"
# include "CameraControl.hpp"

namespace s3d
{
	struct Camera2DParameters
	{
		double minScale = (1.0 / 128.0);
		
		double maxScale = 128.0;
		
		double scaleSmoothTime = 0.2;
		
		double positionSmoothTime = 0.2;

		// wheel
		double wheelScaleFactor = 1.125;

		// mouse
		double grabSpeedFactor = 4.0;

		// controls
		double controlScaleFactor = 2.0;
		
		double controlSpeedFactor = 400.0;

		std::function<bool()> moveToUp		= ([]{ return KeyW.pressed(); });
		
		std::function<bool()> moveToLeft	= ([]{ return KeyA.pressed(); });
		
		std::function<bool()> moveToDown	= ([]{ return KeyS.pressed(); });
		
		std::function<bool()> moveToRight	= ([]{ return KeyD.pressed(); });
		
		std::function<bool()> zoomIn		= ([]{ return KeyUp.pressed(); });
		
		std::function<bool()> zoomOut		= ([]{ return KeyDown.pressed(); });

		[[nodiscard]]
		static Camera2DParameters Make(CameraControl cameraControl);

		[[nodiscard]]
		static Camera2DParameters Default();

		[[nodiscard]]
		static Camera2DParameters MouseOnly();

		[[nodiscard]]
		static Camera2DParameters KeyboardOnly();

		[[nodiscard]]
		static Camera2DParameters NoControl();
	};
}

# include "detail/Camera2DParameters.ipp"
