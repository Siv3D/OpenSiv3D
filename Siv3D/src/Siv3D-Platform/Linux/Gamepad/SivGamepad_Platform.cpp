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

# include <Siv3D/Gamepad.hpp>
# include <Siv3D/Unicode.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

extern "C"
{
	GLFWAPI const char* siv3dGetJoystickInfo(int joy, unsigned* vendorID, unsigned* productID, unsigned* version);
}

namespace s3d
{
	namespace System
	{
		Array<GamepadInfo> EnumerateGamepads()
		{
			Array<GamepadInfo> results;
			
			unsigned vendorID = 0, productID = 0, version = 0;
			
			for (uint32 i = 0; i < Gamepad.MaxUserCount; ++i)
			{
				const char* name = siv3dGetJoystickInfo(i, &vendorID, &productID, &version);
				
				if (name)
				{
					GamepadInfo info;
					info.index = i;
					info.vendorID = vendorID;
					info.productID = productID;
					info.name = Unicode::Widen(name);
					results << info;
				}
			}
			
			return results;
		}
	}
}
