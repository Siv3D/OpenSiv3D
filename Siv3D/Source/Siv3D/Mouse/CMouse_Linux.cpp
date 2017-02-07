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
# if defined(SIV3D_TARGET_LINUX)

# include <GLFW/glfw3.h>
# include "../Siv3DEngine.hpp"
# include "CMouse_Linux.hpp"

namespace s3d
{
	CMouse_Linux::CMouse_Linux()
	{

	}

	CMouse_Linux::~CMouse_Linux()
	{

	}

	bool CMouse_Linux::init()
	{
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();

		return true;
	}

	void CMouse_Linux::update()
	{
		for (uint32 i = 0; i < MouseButtonCount; ++i)
		{
			const bool pressed = (::glfwGetMouseButton(m_glfwWindow, i) == GLFW_PRESS);
	
			m_states[i].update(pressed);
		}
	}
	
	bool CMouse_Linux::down(const uint32 index) const
	{
		return m_states[index].down;
	}
	
	bool CMouse_Linux::pressed(const uint32 index) const
	{
		return m_states[index].pressed;
	}
	
	bool CMouse_Linux::up(const uint32 index) const
	{
		return m_states[index].up;
	}

	MillisecondsF CMouse_Linux::pressedDuration(const uint32 index) const
	{
		return m_states[index].pressedDuration;
	}
}

# endif
