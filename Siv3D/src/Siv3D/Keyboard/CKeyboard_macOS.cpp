﻿//-----------------------------------------------
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

# include <GL/glew.h>
# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "../Siv3DEngine.hpp"
# include "CKeyboard_macOS.hpp"
# include "../System/ISystem.hpp"
# include <Siv3D/System.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		constexpr std::pair<uint8, uint16> KeyConversionTable[]
		{
			{ 0x03, 0 },
			{ 0x08, GLFW_KEY_BACKSPACE },
			{ 0x09, GLFW_KEY_TAB },
			{ 0x0C, 0 },
			{ 0x0D, GLFW_KEY_ENTER },
			{ 0x10, 0 }, // shift
			{ 0x11, 0 }, // control
			{ 0x12, 0 }, // alt
			{ 0x13, GLFW_KEY_PAUSE },
			{ 0x1B, GLFW_KEY_ESCAPE },
			{ 0x20, GLFW_KEY_SPACE },
			{ 0x21, GLFW_KEY_PAGE_UP },
			{ 0x22, GLFW_KEY_PAGE_DOWN },
			{ 0x23, GLFW_KEY_END },
			{ 0x24, GLFW_KEY_HOME },
			{ 0x25, GLFW_KEY_LEFT },
			{ 0x26, GLFW_KEY_UP },
			{ 0x27, GLFW_KEY_RIGHT },
			{ 0x28, GLFW_KEY_DOWN },
			{ 0x2C, GLFW_KEY_PRINT_SCREEN },
			{ 0x2D, GLFW_KEY_INSERT },
			{ 0x2E, GLFW_KEY_DELETE },
			{ 0x30, GLFW_KEY_0 },
			{ 0x31, GLFW_KEY_1 },
			{ 0x32, GLFW_KEY_2 },
			{ 0x33, GLFW_KEY_3 },
			{ 0x34, GLFW_KEY_4 },
			{ 0x35, GLFW_KEY_5 },
			{ 0x36, GLFW_KEY_6 },
			{ 0x37, GLFW_KEY_7 },
			{ 0x38, GLFW_KEY_8 },
			{ 0x39, GLFW_KEY_9 },
			{ 0x41, GLFW_KEY_A },
			{ 0x42, GLFW_KEY_B },
			{ 0x43, GLFW_KEY_C },
			{ 0x44, GLFW_KEY_D },
			{ 0x45, GLFW_KEY_E },
			{ 0x46, GLFW_KEY_F },
			{ 0x47, GLFW_KEY_G },
			{ 0x48, GLFW_KEY_H },
			{ 0x49, GLFW_KEY_I },
			{ 0x4A, GLFW_KEY_J },
			{ 0x4B, GLFW_KEY_K },
			{ 0x4C, GLFW_KEY_L },
			{ 0x4D, GLFW_KEY_M },
			{ 0x4E, GLFW_KEY_N },
			{ 0x4F, GLFW_KEY_O },
			{ 0x50, GLFW_KEY_P },
			{ 0x51, GLFW_KEY_Q },
			{ 0x52, GLFW_KEY_R },
			{ 0x53, GLFW_KEY_S },
			{ 0x54, GLFW_KEY_T },
			{ 0x55, GLFW_KEY_U },
			{ 0x56, GLFW_KEY_V },
			{ 0x57, GLFW_KEY_W },
			{ 0x58, GLFW_KEY_X },
			{ 0x59, GLFW_KEY_Y },
			{ 0x5A, GLFW_KEY_Z },
			{ 0x60, GLFW_KEY_KP_0 },
			{ 0x61, GLFW_KEY_KP_1 },
			{ 0x62, GLFW_KEY_KP_2 },
			{ 0x63, GLFW_KEY_KP_3 },
			{ 0x64, GLFW_KEY_KP_4 },
			{ 0x65, GLFW_KEY_KP_5 },
			{ 0x66, GLFW_KEY_KP_6 },
			{ 0x67, GLFW_KEY_KP_7 },
			{ 0x68, GLFW_KEY_KP_8 },
			{ 0x69, GLFW_KEY_KP_9 },
			{ 0x6A, GLFW_KEY_KP_MULTIPLY },
			{ 0x6B, GLFW_KEY_KP_ADD },
			{ 0x6C, GLFW_KEY_KP_ENTER },
			{ 0x6D, GLFW_KEY_KP_SUBTRACT },
			{ 0x6E, GLFW_KEY_KP_DECIMAL },
			{ 0x6F, GLFW_KEY_KP_DIVIDE },
			{ 0x70, GLFW_KEY_F1 },
			{ 0x71, GLFW_KEY_F2 },
			{ 0x72, GLFW_KEY_F3 },
			{ 0x73, GLFW_KEY_F4 },
			{ 0x74, GLFW_KEY_F5 },
			{ 0x75, GLFW_KEY_F6 },
			{ 0x76, GLFW_KEY_F7 },
			{ 0x77, GLFW_KEY_F8 },
			{ 0x78, GLFW_KEY_F9 },
			{ 0x79, GLFW_KEY_F10 },
			{ 0x7A, GLFW_KEY_F11 },
			{ 0x7B, GLFW_KEY_F12 },
			{ 0x7C, GLFW_KEY_F13 },
			{ 0x7D, GLFW_KEY_F14 },
			{ 0x7E, GLFW_KEY_F15 },
			{ 0x7F, GLFW_KEY_F16 },
			{ 0x80, GLFW_KEY_F17 },
			{ 0x81, GLFW_KEY_F18 },
			{ 0x82, GLFW_KEY_F19 },
			{ 0x83, GLFW_KEY_F20 },
			{ 0x84, GLFW_KEY_F21 },
			{ 0x85, GLFW_KEY_F22 },
			{ 0x86, GLFW_KEY_F23 },
			{ 0x87, GLFW_KEY_F24 },
			{ 0x90, GLFW_KEY_NUM_LOCK },
			{ 0xA0, GLFW_KEY_LEFT_SHIFT },
			{ 0xA1, GLFW_KEY_RIGHT_SHIFT },
			{ 0xA2, GLFW_KEY_LEFT_CONTROL },
			{ 0xA3, GLFW_KEY_RIGHT_CONTROL },
			{ 0xA4, GLFW_KEY_LEFT_ALT },
			{ 0xA5, GLFW_KEY_RIGHT_ALT },
			{ 0xB0, 0 }, // media next track
			{ 0xB1, 0 }, // media previous track
			{ 0xB2, 0 }, // media stop
			{ 0xB3, 0 }, // media play/pause
			{ 0xBA, GLFW_KEY_APOSTROPHE }, // ? [Siv3D TODO]
			{ 0xBB, GLFW_KEY_SEMICOLON }, // ? [Siv3D TODO]
			{ 0xBC, GLFW_KEY_COMMA },
			{ 0xBD, GLFW_KEY_MINUS },
			{ 0xBE, GLFW_KEY_PERIOD },
			{ 0xBF, GLFW_KEY_SLASH },
			{ 0xC0, GLFW_KEY_GRAVE_ACCENT }, // ? [Siv3D TODO]
			{ 0xD8, 0 }, // command
			{ 0xD9, GLFW_KEY_LEFT_SUPER },
			{ 0xDA, GLFW_KEY_RIGHT_SUPER },
			{ 0xDB, GLFW_KEY_LEFT_BRACKET }, // ? [Siv3D TODO]
			{ 0xDC, GLFW_KEY_BACKSLASH }, // ? [Siv3D TODO]
			{ 0xDD, GLFW_KEY_RIGHT_BRACKET }, // ? [Siv3D TODO]
			{ 0xDE, 0 }, // ? [Siv3D TODO]
			{ 0xE2, 0 }, // ? [Siv3D TODO]
		};
	}
	
	CKeyboard_macOS::CKeyboard_macOS()
	{

	}

	CKeyboard_macOS::~CKeyboard_macOS()
	{

	}

	bool CKeyboard_macOS::init()
	{
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();

		LOG_INFO(U"ℹ️ Keyboard initialized");

		return true;
	}

	void CKeyboard_macOS::update()
	{
		bool anyKeyDown = false;

		const char* keys = ::glfwGetKeysSiv3D(m_glfwWindow);

		for (const auto& keyPair : detail::KeyConversionTable)
		{
			const bool pressed = (keys[keyPair.second] == GLFW_PRESS);
			
			m_states[keyPair.first].update(pressed);

			anyKeyDown |= m_states[keyPair.first].down;
		}
		
		const bool shiftPressed =
			(keys[GLFW_KEY_LEFT_SHIFT] == GLFW_PRESS) || (keys[GLFW_KEY_RIGHT_SHIFT] == GLFW_PRESS);
		
		m_states[0x10].update(shiftPressed);
		
		const bool controlPressed =
			(keys[GLFW_KEY_LEFT_CONTROL] == GLFW_PRESS) || (keys[GLFW_KEY_RIGHT_CONTROL] == GLFW_PRESS);

		m_states[0x11].update(controlPressed);
		
		const bool altPressed =
			(keys[GLFW_KEY_LEFT_ALT] == GLFW_PRESS) || (keys[GLFW_KEY_RIGHT_ALT] == GLFW_PRESS);
		
		m_states[0x12].update(altPressed);
		
		const bool commandPressed =
			(keys[GLFW_KEY_LEFT_SUPER] == GLFW_PRESS) || (keys[GLFW_KEY_RIGHT_SUPER] == GLFW_PRESS);
		
		m_states[0xD8].update(commandPressed);

		if (anyKeyDown)
		{
			Siv3DEngine::GetSystem()->reportEvent(WindowEvent::AnyKey);
		}
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
