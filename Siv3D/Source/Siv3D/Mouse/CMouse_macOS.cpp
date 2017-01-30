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

		m_down.fill(false);
		m_pressed.fill(false);
		m_up.fill(false);
		
		return true;
	}

	void CMouse_macOS::update()
	{
		for (uint32 i = 0; i < MouseButtonCount; ++i)
		{
			const bool previousPressed = m_pressed[i];
			
			m_pressed[i] = (::glfwGetMouseButton(m_glfwWindow, i) == GLFW_PRESS);
			
			m_down[i] = !previousPressed && m_pressed[i];
			
			m_up[i] = previousPressed && !m_pressed[i];
		}
	}
	
	bool CMouse_macOS::down(const uint32 index) const
	{
		return m_down[index];
	}
	
	bool CMouse_macOS::pressed(const uint32 index) const
	{
		return m_pressed[index];
	}
	
	bool CMouse_macOS::up(const uint32 index) const
	{
		return m_up[index];
	}
}

# endif
