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
				return S3DSTR("");
			case 0x03:
				return S3DSTR("Cancel");
			case 0x08:
				return S3DSTR("Backspace");
			case 0x09:
				return S3DSTR("Tab");
			case 0x0C:
				return S3DSTR("Clear");
			case 0x0D:
				return S3DSTR("Enter");
			case 0x10:
				return S3DSTR("Shift");
			case 0x11:
				return S3DSTR("Control");
			case 0x12:
				return S3DSTR("Alt");
			case 0x13:
				return S3DSTR("Pause");
			case 0x1B:
				return S3DSTR("Escape");
			case 0x20:
				return S3DSTR("Space");
			case 0x21:
				return S3DSTR("PageUp");
			case 0x22:
				return S3DSTR("PageDown");
			case 0x23:
				return S3DSTR("End");
			case 0x24:
				return S3DSTR("Home");
			case 0x25:
				return S3DSTR("Left");
			case 0x26:
				return S3DSTR("Up");
			case 0x27:
				return S3DSTR("Right");
			case 0x28:
				return S3DSTR("Down");
			case 0x2C:
				return S3DSTR("PrintScreen");
			case 0x2D:
				return S3DSTR("Insert");
			case 0x2E:
				return S3DSTR("Delete");
			case 0x30:
				return S3DSTR("0");
			case 0x31:
				return S3DSTR("1");
			case 0x32:
				return S3DSTR("2");
			case 0x33:
				return S3DSTR("3");
			case 0x34:
				return S3DSTR("4");
			case 0x35:
				return S3DSTR("5");
			case 0x36:
				return S3DSTR("6");
			case 0x37:
				return S3DSTR("7");
			case 0x38:
				return S3DSTR("8");
			case 0x39:
				return S3DSTR("9");
			case 0x41:
				return S3DSTR("A");
			case 0x42:
				return S3DSTR("B");
			case 0x43:
				return S3DSTR("C");
			case 0x44:
				return S3DSTR("D");
			case 0x45:
				return S3DSTR("E");
			case 0x46:
				return S3DSTR("F");
			case 0x47:
				return S3DSTR("G");
			case 0x48:
				return S3DSTR("H");
			case 0x49:
				return S3DSTR("I");
			case 0x4A:
				return S3DSTR("J");
			case 0x4B:
				return S3DSTR("K");
			case 0x4C:
				return S3DSTR("L");
			case 0x4D:
				return S3DSTR("M");
			case 0x4E:
				return S3DSTR("N");
			case 0x4F:
				return S3DSTR("O");
			case 0x50:
				return S3DSTR("P");
			case 0x51:
				return S3DSTR("Q");
			case 0x52:
				return S3DSTR("R");
			case 0x53:
				return S3DSTR("S");
			case 0x54:
				return S3DSTR("T");
			case 0x55:
				return S3DSTR("U");
			case 0x56:
				return S3DSTR("V");
			case 0x57:
				return S3DSTR("W");
			case 0x58:
				return S3DSTR("X");
			case 0x59:
				return S3DSTR("Y");
			case 0x5A:
				return S3DSTR("Z");
			case 0x60:
				return S3DSTR("Numpad0");
			case 0x61:
				return S3DSTR("Numpad1");
			case 0x62:
				return S3DSTR("Numpad2");
			case 0x63:
				return S3DSTR("Numpad3");
			case 0x64:
				return S3DSTR("Numpad4");
			case 0x65:
				return S3DSTR("Numpad5");
			case 0x66:
				return S3DSTR("Numpad6");
			case 0x67:
				return S3DSTR("Numpad7");
			case 0x68:
				return S3DSTR("Numpad8");
			case 0x69:
				return S3DSTR("Numpad9");
			case 0x6A:
				return S3DSTR("Numpad*");
			case 0x6B:
				return S3DSTR("Numpad+");
			case 0x6C:
				return S3DSTR("NumpadEnter");
			case 0x6D:
				return S3DSTR("Numpad-");
			case 0x6E:
				return S3DSTR("Numpad.");
			case 0x6F:
				return S3DSTR("Numpad/");
			case 0x70:
				return S3DSTR("F1");
			case 0x71:
				return S3DSTR("F2");
			case 0x72:
				return S3DSTR("F3");
			case 0x73:
				return S3DSTR("F4");
			case 0x74:
				return S3DSTR("F5");
			case 0x75:
				return S3DSTR("F6");
			case 0x76:
				return S3DSTR("F7");
			case 0x77:
				return S3DSTR("F8");
			case 0x78:
				return S3DSTR("F9");
			case 0x79:
				return S3DSTR("F10");
			case 0x7A:
				return S3DSTR("F11");
			case 0x7B:
				return S3DSTR("F12");
			case 0x7C:
				return S3DSTR("F13");
			case 0x7D:
				return S3DSTR("F14");
			case 0x7E:
				return S3DSTR("F15");
			case 0x7F:
				return S3DSTR("F16");
			case 0x80:
				return S3DSTR("F17");
			case 0x81:
				return S3DSTR("F18");
			case 0x82:
				return S3DSTR("F19");
			case 0x83:
				return S3DSTR("F20");
			case 0x84:
				return S3DSTR("F21");
			case 0x85:
				return S3DSTR("F22");
			case 0x86:
				return S3DSTR("F23");
			case 0x87:
				return S3DSTR("F24");
			case 0x90:
				return S3DSTR("NumLock");
			case 0xA0:
				return S3DSTR("LeftShift");
			case 0xA1:
				return S3DSTR("RightShift");
			case 0xA2:
				return S3DSTR("LeftControl");
			case 0xA3:
				return S3DSTR("RightControl");
			case 0xA4:
				return S3DSTR("LeftAlt");
			case 0xA5:
				return S3DSTR("RightAlt");
			case 0xB0:
				return S3DSTR("NextTrack");
			case 0xB1:
				return S3DSTR("PreviousTrack");
			case 0xB2:
				return S3DSTR("StopMedia");
			case 0xB3:
				return S3DSTR("PlayPauseMedia");
			case 0xBA:
				return S3DSTR(";(US)");
			case 0xBB:
				return S3DSTR("=(US)");
			case 0xBC:
				return S3DSTR(",");
			case 0xBD:
				return S3DSTR("-");
			case 0xBE:
				return S3DSTR(".");
			case 0xBF:
				return S3DSTR("/");
			case 0xC0:
				return S3DSTR("`");
			case 0xD8:
				return S3DSTR("Command");
			case 0xD9:
				return S3DSTR("LeftCommand");
			case 0xDA:
				return S3DSTR("RightCommand");
			case 0xDB:
				return S3DSTR("[");
			case 0xDC:
				return S3DSTR("\\(US)");
			case 0xDD:
				return S3DSTR("]");
			case 0xDE:
				return S3DSTR("'(US)");
			case 0xE2:
				return S3DSTR("\\(JP)");
			}

			return S3DSTR("Key-Unknown");
		}
		else if (m_device == InputDevice::Mouse)
		{
			switch (m_code)
			{
			case 0:
				return S3DSTR("MouseLeft");
			case 1:
				return S3DSTR("MouseRight");
			case 2:
				return S3DSTR("MouseMiddle");
			case 3:
				return S3DSTR("MouseX1");
			case 4:
				return S3DSTR("MouseX2");
			case 5:
				return S3DSTR("MouseX3");
			case 6:
				return S3DSTR("MouseX4");
			case 7:
				return S3DSTR("MouseX5");
			}

			return S3DSTR("Mouse-Unknown");
		}
		else if (m_device == InputDevice::Gamepad)
		{
			return S3DSTR("Gamepad-Unknown");
		}
		else if (m_device == InputDevice::XInput)
		{
			return S3DSTR("XInput-Unknown");
		}

		return S3DSTR("Unknown");
	}
}
