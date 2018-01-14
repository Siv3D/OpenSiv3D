//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "IMouse.hpp"
# include <Siv3D/Mouse.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	namespace Mouse
	{
		double Wheel()
		{
			return Siv3DEngine::GetMouse()->wheel().y;
		}
		
		double WheelH()
		{
			return Siv3DEngine::GetMouse()->wheel().x;
		}
	}
}
