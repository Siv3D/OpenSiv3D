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
			switch (m_code)
			{
			case 0x00:
				return L"";
			case 0x03:
				return L"Cancel";
			case 0x08:
				return L"Backspace";
			case 0x09:
				return L"Tab";
			case 0x0C:
				return L"Clear";
			case 0x0D:
				return L"Enter";
			case 0x10:
				return L"Shift";
			case 0x11:
				return L"Control";
			case 0x12:
				return L"Alt";
			case 0x13:
				return L"Pause";
			case 0x1B:
				return L"Escape";
			case 0x20:
				return L"Space";
			case 0x21:
				return L"PageUp";
			case 0x22:
				return L"PageDown";
			case 0x23:
				return L"End";
			case 0x24:
				return L"Home";
			case 0x25:
				return L"Left";
			case 0x26:
				return L"Up";
			case 0x27:
				return L"Right";
			case 0x28:
				return L"Down";
			case 0x2C:
				return L"PrintScreen";
			case 0x2D:
				return L"Insert";
			case 0x2E:
				return L"Delete";
			case 0x30:
				return L"0";
			case 0x31:
				return L"1";
			case 0x32:
				return L"2";
			case 0x33:
				return L"3";
			case 0x34:
				return L"4";
			case 0x35:
				return L"5";
			case 0x36:
				return L"6";
			case 0x37:
				return L"7";
			case 0x38:
				return L"8";
			case 0x39:
				return L"9";
			case 0x41:
				return L"A";
			case 0x42:
				return L"B";
			case 0x43:
				return L"C";
			case 0x44:
				return L"D";
			case 0x45:
				return L"E";
			case 0x46:
				return L"F";
			case 0x47:
				return L"G";
			case 0x48:
				return L"H";
			case 0x49:
				return L"I";
			case 0x4A:
				return L"J";
			case 0x4B:
				return L"K";
			case 0x4C:
				return L"L";
			case 0x4D:
				return L"M";
			case 0x4E:
				return L"N";
			case 0x4F:
				return L"O";
			case 0x50:
				return L"P";
			case 0x51:
				return L"Q";
			case 0x52:
				return L"R";
			case 0x53:
				return L"S";
			case 0x54:
				return L"T";
			case 0x55:
				return L"U";
			case 0x56:
				return L"V";
			case 0x57:
				return L"W";
			case 0x58:
				return L"X";
			case 0x59:
				return L"Y";
			case 0x5A:
				return L"Z";
			case 0x60:
				return L"Numpad0";
			case 0x61:
				return L"Numpad1";
			case 0x62:
				return L"Numpad2";
			case 0x63:
				return L"Numpad3";
			case 0x64:
				return L"Numpad4";
			case 0x65:
				return L"Numpad5";
			case 0x66:
				return L"Numpad6";
			case 0x67:
				return L"Numpad7";
			case 0x68:
				return L"Numpad8";
			case 0x69:
				return L"Numpad9";
			case 0x6A:
				return L"Numpad*";
			case 0x6B:
				return L"Numpad+";
			case 0x6C:
				return L"NumpadEnter";
			case 0x6D:
				return L"Numpad-";
			case 0x6E:
				return L"Numpad.";
			case 0x6F:
				return L"Numpad/";
			case 0x70:
				return L"F1";
			case 0x71:
				return L"F2";
			case 0x72:
				return L"F3";
			case 0x73:
				return L"F4";
			case 0x74:
				return L"F5";
			case 0x75:
				return L"F6";
			case 0x76:
				return L"F7";
			case 0x77:
				return L"F8";
			case 0x78:
				return L"F9";
			case 0x79:
				return L"F10";
			case 0x7A:
				return L"F11";
			case 0x7B:
				return L"F12";
			case 0x7C:
				return L"F13";
			case 0x7D:
				return L"F14";
			case 0x7E:
				return L"F15";
			case 0x7F:
				return L"F16";
			case 0x80:
				return L"F17";
			case 0x81:
				return L"F18";
			case 0x82:
				return L"F19";
			case 0x83:
				return L"F20";
			case 0x84:
				return L"F21";
			case 0x85:
				return L"F22";
			case 0x86:
				return L"F23";
			case 0x87:
				return L"F24";
			case 0x90:
				return L"NumLock";
			case 0xA0:
				return L"LeftShift";
			case 0xA1:
				return L"RightShift";
			case 0xA2:
				return L"LeftControl";
			case 0xA3:
				return L"RightControl";
			case 0xA4:
				return L"LeftAlt";
			case 0xA5:
				return L"RightAlt";
			case 0xB0:
				return L"NextTrack";
			case 0xB1:
				return L"PreviousTrack";
			case 0xB2:
				return L"StopMedia";
			case 0xB3:
				return L"PlayPauseMedia";
			case 0xBA:
				return L";(US)";
			case 0xBB:
				return L"=(US)";
			case 0xBC:
				return L",";
			case 0xBD:
				return L"-";
			case 0xBE:
				return L".";
			case 0xBF:
				return L"/";
			case 0xC0:
				return L"`";
			case 0xD8:
				return L"Command";
			case 0xD9:
				return L"LeftCommand";
			case 0xDA:
				return L"RightCommand";
			case 0xDB:
				return L"[";
			case 0xDC:
				return L"\\(US)";
			case 0xDD:
				return L"]";
			case 0xDE:
				return L"'(US)";
			case 0xE2:
				return L"\\(JP)";
			}

			return L"Key-Unknown";
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

			return L"Mouse-Unknown";
		}
		else if (m_device == InputDevice::Gamepad)
		{
			return L"Gamepad-Unknown";
		}
		else if (m_device == InputDevice::XInput)
		{
			return L"XInput-Unknown";
		}

		return String(L"Unknown");
	}
}
