//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Key.hpp>
# include "../Siv3DEngine.hpp"
# include "../Mouse/IMouse.hpp"
# include "../Keyboard/IKeyboard.hpp"

namespace s3d
{
	bool Key::down() const
	{
		switch (m_device)
		{
		case InputDevice::Keyboard:
			return Siv3DEngine::GetKeyboard()->down(m_code);
		case InputDevice::Mouse:
			return Siv3DEngine::GetMouse()->down(m_code);
		case InputDevice::Gamepad:
			return false;
		default: // InputDevice::XInput
			return false;
		}
	}

	bool Key::pressed() const
	{
		switch (m_device)
		{
		case InputDevice::Keyboard:
			return Siv3DEngine::GetKeyboard()->pressed(m_code);
		case InputDevice::Mouse:
			return Siv3DEngine::GetMouse()->pressed(m_code);
		case InputDevice::Gamepad:
			return false;
		default: // InputDevice::XInput
			return false;
		}
	}

	bool Key::up() const
	{
		switch (m_device)
		{
		case InputDevice::Keyboard:
			return Siv3DEngine::GetKeyboard()->up(m_code);
		case InputDevice::Mouse:
			return Siv3DEngine::GetMouse()->up(m_code);
		case InputDevice::Gamepad:
			return false;
		default: // InputDevice::XInput
			return false;
		}
	}

	MillisecondsF Key::pressedDuration() const
	{
		switch (m_device)
		{
		case InputDevice::Keyboard:
			return Siv3DEngine::GetKeyboard()->pressedDuration(m_code);
		case InputDevice::Mouse:
			return Siv3DEngine::GetMouse()->pressedDuration(m_code);
		case InputDevice::Gamepad:
			return MillisecondsF(0);
		default: // InputDevice::XInput
			return MillisecondsF(0);
		}
	}

	String Key::name() const
	{
		if (m_device == InputDevice::Keyboard)
		{
			return L"Key";
		}
		else if (m_device == InputDevice::Mouse)
		{
			switch (m_code)
			{
			case 0:
				return L"MouseLeft";
			case 1:
				return L"MouseRight";
			case 2:
				return L"MouseMiddle";
			case 3:
				return L"MouseX1";
			case 4:
				return L"MouseX2";
			case 5:
				return L"MouseX3";
			case 6:
				return L"MouseX4";
			case 7:
				return L"MouseX5";
			}
		}

		return String(L"Unknown");
	}
}
