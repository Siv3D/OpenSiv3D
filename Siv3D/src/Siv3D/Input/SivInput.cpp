//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Input.hpp>
# include <Siv3D/Keyboard/IKeyboard.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	String Input::name() const
	{
		switch (m_deviceType)
		{
		case InputDeviceType::Keyboard:
			return SIV3D_ENGINE(Keyboard)->name(m_code);
		case InputDeviceType::Mouse:
		case InputDeviceType::Gamepad:
		case InputDeviceType::XInput:
		default:
			return {};
		}
	}

	bool Input::down() const
	{
		switch (m_deviceType)
		{
		case InputDeviceType::Keyboard:
			return SIV3D_ENGINE(Keyboard)->down(m_code);
		case InputDeviceType::Mouse:
		case InputDeviceType::Gamepad:
		case InputDeviceType::XInput:
		default:
			return false;
		}
	}

	bool Input::pressed() const
	{
		switch (m_deviceType)
		{
		case InputDeviceType::Keyboard:
			return SIV3D_ENGINE(Keyboard)->pressed(m_code);
		case InputDeviceType::Mouse:
		case InputDeviceType::Gamepad:
		case InputDeviceType::XInput:
		default:
			return false;
		}
	}

	bool Input::up() const
	{
		switch (m_deviceType)
		{
		case InputDeviceType::Keyboard:
			return SIV3D_ENGINE(Keyboard)->up(m_code);
		case InputDeviceType::Mouse:
		case InputDeviceType::Gamepad:
		case InputDeviceType::XInput:
		default:
			return false;
		}
	}

	Duration Input::pressedDuration() const
	{
		switch (m_deviceType)
		{
		case InputDeviceType::Keyboard:
			return SIV3D_ENGINE(Keyboard)->pressedDuration(m_code);
		case InputDeviceType::Mouse:
		case InputDeviceType::Gamepad:
		case InputDeviceType::XInput:
		default:
			return Duration{ 0 };
		}
	}
}
