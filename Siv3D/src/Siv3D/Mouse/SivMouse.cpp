//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3DEngine.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/PointVector.hpp>
# include "IMouse.hpp"

namespace s3d
{
	namespace Mouse
	{
		double Wheel()
		{
			return Siv3DEngine::Get<ISiv3DMouse>()->wheel().y;
		}
		
		double WheelH()
		{
			return Siv3DEngine::Get<ISiv3DMouse>()->wheel().x;
		}
	}
}
