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

namespace s3d
{
	inline Camera2DParameters Camera2DParameters::Default()
	{
		return{};
	}

	inline Camera2DParameters Camera2DParameters::MouseOnly()
	{
		return Make(CameraControl::Mouse);
	}

	inline Camera2DParameters Camera2DParameters::KeyboardOnly()
	{
		return Make(CameraControl::Keyboard);
	}

	inline Camera2DParameters Camera2DParameters::NoControl()
	{
		return Make(CameraControl::None_);
	}
}
