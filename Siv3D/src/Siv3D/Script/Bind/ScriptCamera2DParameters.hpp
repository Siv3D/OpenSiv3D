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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Camera2DParameters.hpp>

namespace s3d
{
	struct ScriptCamera2DParameters
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

		// CameraControl
		double type = FromEnum(CameraControl::Default);

		Camera2DParameters asCamera2DParameters() const
		{
			Camera2DParameters cp = Camera2DParameters::Make(ToEnum<CameraControl>(static_cast<uint8>(type)));
			cp.minScale = minScale;
			cp.maxScale = maxScale;
			cp.scaleSmoothTime = scaleSmoothTime;
			cp.positionSmoothTime = positionSmoothTime;
			cp.wheelScaleFactor = wheelScaleFactor;
			cp.grabSpeedFactor = grabSpeedFactor;
			cp.controlScaleFactor = controlScaleFactor;
			cp.controlSpeedFactor = controlSpeedFactor;
			return cp;
		}
	};
}
