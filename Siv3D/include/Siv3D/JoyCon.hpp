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

# pragma once
# include "Fwd.hpp"
# include "Gamepad.hpp"

namespace s3d
{
	class JoyCon
	{
	private:

		enum class ControllerType
		{
			Invalid,

			JoyConL,

			JoyConR,
		};

		const detail::Gamepad_impl& m_gamepad;

		ControllerType m_type = ControllerType::Invalid;

		static ControllerType GetControllerType(const GamepadInfo& info)
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

	public:

		static bool IsJoyCon(const detail::Gamepad_impl& gamepad)
		{
			return (GetControllerType(gamepad.getInfo()) != ControllerType::Invalid);
		}

		static bool IsJoyConL(const detail::Gamepad_impl& gamepad)
		{
			return (GetControllerType(gamepad.getInfo()) == ControllerType::JoyConL);
		}

		static bool IsJoyConR(const detail::Gamepad_impl& gamepad)
		{
			return (GetControllerType(gamepad.getInfo()) == ControllerType::JoyConR);
		}

		JoyCon() = default;

		explicit JoyCon(const detail::Gamepad_impl& gamepad)
			: m_gamepad(gamepad)
			, m_type(GetControllerType(m_gamepad.getInfo()))
			, button0(InputDevice::Gamepad, 0, static_cast<uint8>(m_gamepad.userIndex))
			, button1(InputDevice::Gamepad, 1, static_cast<uint8>(m_gamepad.userIndex))
			, button2(InputDevice::Gamepad, 2, static_cast<uint8>(m_gamepad.userIndex))
			, button3(InputDevice::Gamepad, 3, static_cast<uint8>(m_gamepad.userIndex))
			, buttonSL(InputDevice::Gamepad, 4, static_cast<uint8>(m_gamepad.userIndex))
			, buttonSR(InputDevice::Gamepad, 5, static_cast<uint8>(m_gamepad.userIndex))
			, buttonMinus(InputDevice::Gamepad, 8, static_cast<uint8>(m_gamepad.userIndex))
			, buttonPlus(InputDevice::Gamepad, 9, static_cast<uint8>(m_gamepad.userIndex))
			, buttonHome(InputDevice::Gamepad, 12, static_cast<uint8>(m_gamepad.userIndex))
			, buttonScreenshot(InputDevice::Gamepad, 13, static_cast<uint8>(m_gamepad.userIndex))
			, buttonLR(InputDevice::Gamepad, 14, static_cast<uint8>(m_gamepad.userIndex))
			, buttonZLZR(InputDevice::Gamepad, 15, static_cast<uint8>(m_gamepad.userIndex))
		{
			if (isJoyConL())
			{
				buttonStick = Key(InputDevice::Gamepad, 10, static_cast<uint8>(m_gamepad.userIndex));
			}
			else if (isJoyConR())
			{
				buttonStick = Key(InputDevice::Gamepad, 11, static_cast<uint8>(m_gamepad.userIndex));
			}
		}

		bool isConnected() const
		{
			return (m_type != ControllerType::Invalid)
				&& m_gamepad.isConnected();
		}

		bool isJoyConL() const
		{
			return (m_type == ControllerType::JoyConL);
		}

		bool isJoyConR() const
		{
			return (m_type == ControllerType::JoyConR);
		}

		Key button0;

		Key button1;

		Key button2;

		Key button3;

		Key buttonSL;

		Key buttonSR;

		Key buttonMinus;

		Key buttonPlus;

		Key buttonStick;

		Key buttonHome;

		Key buttonScreenshot;

		Key buttonLR;

		Key buttonZLZR;

		Optional<int32> povD8() const
		{
			return m_gamepad.povD8();
		}
	};
}
