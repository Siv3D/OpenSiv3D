//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/JoyCon.hpp>

namespace s3d
{
	bool JoyCon::IsJoyCon(const detail::Gamepad_impl& gamepad) noexcept
	{
		return (GetControllerType(gamepad.getInfo()) != ControllerType::Invalid);
	}

	bool JoyCon::IsJoyConL(const detail::Gamepad_impl& gamepad) noexcept
	{
		return (GetControllerType(gamepad.getInfo()) == ControllerType::JoyConL);
	}

	bool JoyCon::IsJoyConR(const detail::Gamepad_impl& gamepad) noexcept
	{
		return (GetControllerType(gamepad.getInfo()) == ControllerType::JoyConR);
	}

	JoyCon::JoyCon(const detail::Gamepad_impl& gamepad)
		: m_gamepadUserIndex(gamepad.userIndex)
		, m_type(GetControllerType(gamepad.getInfo()))
		, button0(InputDevice::Gamepad, 0, static_cast<uint8>(gamepad.userIndex))
		, button1(InputDevice::Gamepad, 1, static_cast<uint8>(gamepad.userIndex))
		, button2(InputDevice::Gamepad, 2, static_cast<uint8>(gamepad.userIndex))
		, button3(InputDevice::Gamepad, 3, static_cast<uint8>(gamepad.userIndex))
		, buttonSL(InputDevice::Gamepad, 4, static_cast<uint8>(gamepad.userIndex))
		, buttonSR(InputDevice::Gamepad, 5, static_cast<uint8>(gamepad.userIndex))
		, buttonMinus(InputDevice::Gamepad, 8, static_cast<uint8>(gamepad.userIndex))
		, buttonPlus(InputDevice::Gamepad, 9, static_cast<uint8>(gamepad.userIndex))
		, buttonHome(InputDevice::Gamepad, 12, static_cast<uint8>(gamepad.userIndex))
		, buttonScreenshot(InputDevice::Gamepad, 13, static_cast<uint8>(gamepad.userIndex))
		, buttonLR(InputDevice::Gamepad, 14, static_cast<uint8>(gamepad.userIndex))
		, buttonZLZR(InputDevice::Gamepad, 15, static_cast<uint8>(gamepad.userIndex))
	{
		if (isJoyConL())
		{
			buttonStick = Key(InputDevice::Gamepad, 10, static_cast<uint8>(gamepad.userIndex));
		}
		else if (isJoyConR())
		{
			buttonStick = Key(InputDevice::Gamepad, 11, static_cast<uint8>(gamepad.userIndex));
		}
	}

	JoyCon JoyCon::JoyConL(const size_t index)
	{
		size_t count = 0;

		for (size_t i = 0; i < Gamepad.MaxUserCount; ++i)
		{
			const auto gamepad = Gamepad(i);

			if (JoyCon::IsJoyConL(gamepad))
			{
				if (count == index)
				{
					return JoyCon(gamepad);
				}

				++count;
			}
		}

		return JoyCon();
	}

	JoyCon JoyCon::JoyConR(const size_t index)
	{
		size_t count = 0;

		for (size_t i = 0; i < Gamepad.MaxUserCount; ++i)
		{
			const auto gamepad = Gamepad(i);

			if (JoyCon::IsJoyConR(gamepad))
			{
				if (count == index)
				{
					return JoyCon(gamepad);
				}

				++count;
			}
		}

		return JoyCon();
	}

	bool JoyCon::isConnected() const noexcept
	{
		return (m_type != ControllerType::Invalid) && m_gamepadUserIndex
			&& Gamepad(m_gamepadUserIndex.value()).isConnected();
	}

	JoyCon::operator bool() const noexcept
	{
		return isConnected();
	}

	bool JoyCon::isJoyConL() const noexcept
	{
		return (m_type == ControllerType::JoyConL);
	}

	bool JoyCon::isJoyConR() const noexcept
	{
		return (m_type == ControllerType::JoyConR);
	}

	Optional<int32> JoyCon::povD8() const noexcept
	{
		if (!m_gamepadUserIndex)
		{
			return none;
		}

		return Gamepad(m_gamepadUserIndex.value()).povD8();
	}

	JoyCon::ControllerType JoyCon::GetControllerType(const GamepadInfo& info) noexcept
	{
		if (info.vendorID == 0x57e)
		{
			if (info.productID == 0x2006)
			{
				return ControllerType::JoyConL;
			}
			else if (info.productID == 0x2007)
			{
				return ControllerType::JoyConR;
			}
		}

		return ControllerType::Invalid;
	}
}
