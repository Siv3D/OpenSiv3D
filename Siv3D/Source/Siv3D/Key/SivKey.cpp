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

namespace s3d
{
	bool Key::down() const
	{
		if (m_device == InputDevice::Mouse)
		{
			return Siv3DEngine::GetMouse()->down(m_code);
		}

		return false;
	}

	bool Key::pressed() const
	{
		if (m_device == InputDevice::Mouse)
		{
			return Siv3DEngine::GetMouse()->pressed(m_code);
		}

		return false;
	}

	bool Key::up() const
	{
		if (m_device == InputDevice::Mouse)
		{
			return Siv3DEngine::GetMouse()->up(m_code);
		}

		return false;
	}

	MillisecondsF Key::pressedDuration() const
	{
		if (m_device == InputDevice::Mouse)
		{
			return Siv3DEngine::GetMouse()->pressedDuration(m_code);
		}

		return MillisecondsF(0);
	}

	String Key::name() const
	{
		if (m_device == InputDevice::Mouse)
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
