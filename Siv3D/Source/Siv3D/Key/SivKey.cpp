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
}
