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

# include <Siv3D/Key.hpp>
# include <Siv3DEngine.hpp>
# include <Mouse/IMouse.hpp>
# include <Keyboard/IKeyboard.hpp>
# include <Gamepad/IGamepad.hpp>
# include <XInput/IXInput.hpp>

namespace s3d
{
	bool Key::down() const
	{
		switch (m_device)
		{
		case InputDevice::Keyboard:
			return Siv3DEngine::Get<ISiv3DKeyboard>()->down(m_code);
		case InputDevice::Mouse:
			return Siv3DEngine::Get<ISiv3DMouse>()->down(m_code);
		case InputDevice::Gamepad:
			return Siv3DEngine::Get<ISiv3DGamepad>()->down(m_userIndex, m_code);
		case InputDevice::XInput:
			return Siv3DEngine::Get<ISiv3DXInput>()->down(m_userIndex, m_code);
		default:
			return false;
		}
	}

	bool Key::pressed() const
	{
		switch (m_device)
		{
		case InputDevice::Keyboard:
			return Siv3DEngine::Get<ISiv3DKeyboard>()->pressed(m_code);
		case InputDevice::Mouse:
			return Siv3DEngine::Get<ISiv3DMouse>()->pressed(m_code);
		case InputDevice::Gamepad:
			return Siv3DEngine::Get<ISiv3DGamepad>()->pressed(m_userIndex, m_code);
		case InputDevice::XInput:
			return Siv3DEngine::Get<ISiv3DXInput>()->pressed(m_userIndex, m_code);
		default:
			return false;
		}
	}

	bool Key::up() const
	{
		switch (m_device)
		{
		case InputDevice::Keyboard:
			return Siv3DEngine::Get<ISiv3DKeyboard>()->up(m_code);
		case InputDevice::Mouse:
			return Siv3DEngine::Get<ISiv3DMouse>()->up(m_code);
		case InputDevice::Gamepad:
			return Siv3DEngine::Get<ISiv3DGamepad>()->up(m_userIndex, m_code);
		case InputDevice::XInput:
			return Siv3DEngine::Get<ISiv3DXInput>()->up(m_userIndex, m_code);
		default:
			return false;
		}
	}

	Duration Key::pressedDuration() const
	{
		switch (m_device)
		{
		case InputDevice::Keyboard:
			return Siv3DEngine::Get<ISiv3DKeyboard>()->pressedDuration(m_code);
		case InputDevice::Mouse:
			return Siv3DEngine::Get<ISiv3DMouse>()->pressedDuration(m_code);
		case InputDevice::Gamepad:
			return Siv3DEngine::Get<ISiv3DGamepad>()->pressedDuration(m_userIndex, m_code);
		case InputDevice::XInput:
			return Siv3DEngine::Get<ISiv3DXInput>()->pressedDuration(m_userIndex, m_code);
		default:
			return Duration(0);
		}
	}

	String Key::name() const
	{
		if (m_device == InputDevice::Keyboard)
		{
			switch (m_code)
			{
			case 0x00:
				return U"";
			case 0x03:
				return U"Cancel";
			case 0x08:
				return U"Backspace";
			case 0x09:
				return U"Tab";
			case 0x0C:
				return U"Clear";
			case 0x0D:
				return U"Enter";
			case 0x10:
				return U"Shift";
			case 0x11:
				return U"Control";
			case 0x12:
				return U"Alt";
			case 0x13:
				return U"Pause";
			case 0x1B:
				return U"Escape";
			case 0x20:
				return U"Space";
			case 0x21:
				return U"PageUp";
			case 0x22:
				return U"PageDown";
			case 0x23:
				return U"End";
			case 0x24:
				return U"Home";
			case 0x25:
				return U"←";
			case 0x26:
				return U"↑";
			case 0x27:
				return U"→";
			case 0x28:
				return U"↓";
			case 0x2C:
				return U"PrintScreen";
			case 0x2D:
				return U"Insert";
			case 0x2E:
				return U"Delete";
			case 0x30:
				return U"0";
			case 0x31:
				return U"1";
			case 0x32:
				return U"2";
			case 0x33:
				return U"3";
			case 0x34:
				return U"4";
			case 0x35:
				return U"5";
			case 0x36:
				return U"6";
			case 0x37:
				return U"7";
			case 0x38:
				return U"8";
			case 0x39:
				return U"9";
			case 0x41:
				return U"A";
			case 0x42:
				return U"B";
			case 0x43:
				return U"C";
			case 0x44:
				return U"D";
			case 0x45:
				return U"E";
			case 0x46:
				return U"F";
			case 0x47:
				return U"G";
			case 0x48:
				return U"H";
			case 0x49:
				return U"I";
			case 0x4A:
				return U"J";
			case 0x4B:
				return U"K";
			case 0x4C:
				return U"L";
			case 0x4D:
				return U"M";
			case 0x4E:
				return U"N";
			case 0x4F:
				return U"O";
			case 0x50:
				return U"P";
			case 0x51:
				return U"Q";
			case 0x52:
				return U"R";
			case 0x53:
				return U"S";
			case 0x54:
				return U"T";
			case 0x55:
				return U"U";
			case 0x56:
				return U"V";
			case 0x57:
				return U"W";
			case 0x58:
				return U"X";
			case 0x59:
				return U"Y";
			case 0x5A:
				return U"Z";
			case 0x60:
				return U"Numpad0";
			case 0x61:
				return U"Numpad1";
			case 0x62:
				return U"Numpad2";
			case 0x63:
				return U"Numpad3";
			case 0x64:
				return U"Numpad4";
			case 0x65:
				return U"Numpad5";
			case 0x66:
				return U"Numpad6";
			case 0x67:
				return U"Numpad7";
			case 0x68:
				return U"Numpad8";
			case 0x69:
				return U"Numpad9";
			case 0x6A:
				return U"Numpad*";
			case 0x6B:
				return U"Numpad+";
			case 0x6C:
				return U"NumpadEnter";
			case 0x6D:
				return U"Numpad-";
			case 0x6E:
				return U"Numpad.";
			case 0x6F:
				return U"Numpad/";
			case 0x70:
				return U"F1";
			case 0x71:
				return U"F2";
			case 0x72:
				return U"F3";
			case 0x73:
				return U"F4";
			case 0x74:
				return U"F5";
			case 0x75:
				return U"F6";
			case 0x76:
				return U"F7";
			case 0x77:
				return U"F8";
			case 0x78:
				return U"F9";
			case 0x79:
				return U"F10";
			case 0x7A:
				return U"F11";
			case 0x7B:
				return U"F12";
			case 0x7C:
				return U"F13";
			case 0x7D:
				return U"F14";
			case 0x7E:
				return U"F15";
			case 0x7F:
				return U"F16";
			case 0x80:
				return U"F17";
			case 0x81:
				return U"F18";
			case 0x82:
				return U"F19";
			case 0x83:
				return U"F20";
			case 0x84:
				return U"F21";
			case 0x85:
				return U"F22";
			case 0x86:
				return U"F23";
			case 0x87:
				return U"F24";
			case 0x90:
				return U"NumLock";
			case 0xA0:
				return U"LeftShift";
			case 0xA1:
				return U"RightShift";
			case 0xA2:
				return U"LeftControl";
			case 0xA3:
				return U"RightControl";
			case 0xA4:
				return U"LeftAlt";
			case 0xA5:
				return U"RightAlt";
			case 0xB0:
				return U"NextTrack";
			case 0xB1:
				return U"PreviousTrack";
			case 0xB2:
				return U"StopMedia";
			case 0xB3:
				return U"PlayPauseMedia";
			case 0xBA:
				return U";(US)";
			case 0xBB:
				return U"=(US)";
			case 0xBC:
				return U",";
			case 0xBD:
				return U"-";
			case 0xBE:
				return U".";
			case 0xBF:
				return U"/";
			case 0xC0:
				return U"`";
			case 0xD8:
				return U"Command";
			case 0xD9:
				return U"LeftCommand";
			case 0xDA:
				return U"RightCommand";
			case 0xDB:
				return U"[";
			case 0xDC:
				return U"\\(US)";
			case 0xDD:
				return U"]";
			case 0xDE:
				return U"'(US)";
			case 0xE2:
				return U"\\(JP)";
			}

			return U"Key-Unknown";
		}
		else if (m_device == InputDevice::Mouse)
		{
			switch (m_code)
			{
			case 0:
				return U"MouseLeft";
			case 1:
				return U"MouseRight";
			case 2:
				return U"MouseMiddle";
			case 3:
				return U"MouseX1";
			case 4:
				return U"MouseX2";
			case 5:
				return U"MouseX3";
			case 6:
				return U"MouseX4";
			case 7:
				return U"MouseX5";
			}

			return U"Mouse-Unknown";
		}
		else if (m_device == InputDevice::Gamepad)
		{
			if (InRange<uint8>(m_code, 0x80, 0x83))
			{
				static const String names[4] =
				{
					U"Up",
					U"Right",
					U"Down",
					U"Left",
				};

				return U"Gamepad-POV_" + names[m_code - 0x80];
			}

			return U"Gamepad-Button" + ToString(m_code);
		}
		else if (m_device == InputDevice::XInput)
		{
			if (m_code >= 16)
			{
				return U"XInput-Unknown";
			}

			static const String names[16] =
			{
				U"Dpad_Up",
				U"Dpad_Down",
				U"Dpad_Left",
				U"Dpad_Right",
				U"Start",
				U"Back",
				U"LT",
				U"RT",
				U"LB",
				U"RB",
				U"Unknown",
				U"Unknown",
				U"A",
				U"B",
				U"X",
				U"Y",
			};

			return U"XInput-" + names[m_code];
		}
		else
		{
			return U"(Unmapped)";
		}
	}

	void Formatter(FormatData& formatData, const Key& key)
	{
		formatData.string.append(key.name());
	}
}
