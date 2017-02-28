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
# include "CKeyboard_macOS.hpp"

namespace s3d
{
	CKeyboard_macOS::CKeyboard_macOS()
	{

	}

	CKeyboard_macOS::~CKeyboard_macOS()
	{

	}

	bool CKeyboard_macOS::init()
	{
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();

		return true;
	}

	void CKeyboard_macOS::update()
	{
		//for (uint32 i = 0; i < KeyboardButtonCount; ++i)
		//{
		//	const bool pressed = (::glfwGetKeyboardButton(m_glfwWindow, i) == GLFW_PRESS);
	
		//	m_states[i].update(pressed);
		//}
	}
	
	bool CKeyboard_macOS::down(const uint32 index) const
	{
		return m_states[index].down;
	}
	
	bool CKeyboard_macOS::pressed(const uint32 index) const
	{
		return m_states[index].pressed;
	}
	
	bool CKeyboard_macOS::up(const uint32 index) const
	{
		return m_states[index].up;
	}

	MillisecondsF CKeyboard_macOS::pressedDuration(const uint32 index) const
	{
		return m_states[index].pressedDuration;
	}
}

# endif
