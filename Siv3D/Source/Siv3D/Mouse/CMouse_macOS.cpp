//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "../Siv3DEngine.hpp"
# include "CMouse_macOS.hpp"

namespace s3d
{
	CMouse_macOS::CMouse_macOS()
	{

	}

	CMouse_macOS::~CMouse_macOS()
	{

	}

	bool CMouse_macOS::init()
	{
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();

		return true;
	}

	void CMouse_macOS::update()
	{
	
	}
}

# endif
