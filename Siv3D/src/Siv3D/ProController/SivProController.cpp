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

# include <Siv3D/ProController.hpp>

namespace s3d
{
	bool ProController::IsProController(const detail::Gamepad_impl& gamepad)
	{
		return (gamepad.getInfo().vendorID == 0x57e) && (gamepad.getInfo().productID == 0x2009);
	}

	ProController::ProController(const detail::Gamepad_impl& gamepad, const DeadZone& left, const DeadZone& right)
		: m_gamepadUserIndex(gamepad.userIndex)
		, m_proControllerType(GetControllerType(gamepad.getInfo()))
		, m_LStickDeadZone(left)
		, m_RStickDeadZone(right)
	{
		if (m_proControllerType != ProControllerType::Invalid)
		{
			buttonA = Key(InputDevice::Gamepad, 1, static_cast<uint8>(gamepad.userIndex));
			buttonB = Key(InputDevice::Gamepad, 0, static_cast<uint8>(gamepad.userIndex));
			buttonX = Key(InputDevice::Gamepad, 3, static_cast<uint8>(gamepad.userIndex));
			buttonY = Key(InputDevice::Gamepad, 2, static_cast<uint8>(gamepad.userIndex));
			buttonL = Key(InputDevice::Gamepad, 4, static_cast<uint8>(gamepad.userIndex));
			buttonR = Key(InputDevice::Gamepad, 5, static_cast<uint8>(gamepad.userIndex));
			buttonZL = Key(InputDevice::Gamepad, 6, static_cast<uint8>(gamepad.userIndex));
			buttonZR = Key(InputDevice::Gamepad, 7, static_cast<uint8>(gamepad.userIndex));
			buttonMinus = Key(InputDevice::Gamepad, 8, static_cast<uint8>(gamepad.userIndex));
			buttonPlus = Key(InputDevice::Gamepad, 9, static_cast<uint8>(gamepad.userIndex));
			buttonLStick = Key(InputDevice::Gamepad, 10, static_cast<uint8>(gamepad.userIndex));
			buttonRStick = Key(InputDevice::Gamepad, 11, static_cast<uint8>(gamepad.userIndex));
			buttonHome = Key(InputDevice::Gamepad, 12, static_cast<uint8>(gamepad.userIndex));
			buttonScreenshot = Key(InputDevice::Gamepad, 13, static_cast<uint8>(gamepad.userIndex));
			povUp = Key(InputDevice::Gamepad, 0x80, static_cast<uint8>(gamepad.userIndex));
			povDown = Key(InputDevice::Gamepad, 0x82, static_cast<uint8>(gamepad.userIndex));
			povLeft = Key(InputDevice::Gamepad, 0x83, static_cast<uint8>(gamepad.userIndex));
			povRight = Key(InputDevice::Gamepad, 0x81, static_cast<uint8>(gamepad.userIndex));
		}
	}

	ProController::ProController(const size_t index)
	{
		size_t count = 0;

		for (size_t i = 0; i < Gamepad.MaxUserCount; ++i)
		{
			const auto gamepad = Gamepad(i);

			if (ProController::IsProController(gamepad))
			{
				if (count == index)
				{
					*this = ProController(gamepad);
					return;
				}

				++count;
			}
		}
	}

	bool ProController::isConnected() const
	{
		return (m_proControllerType != ProControllerType::Invalid) && m_gamepadUserIndex
			&& Gamepad(m_gamepadUserIndex.value()).isConnected();
	}

	ProController::operator bool() const
	{
		return isConnected();
	}

	Optional<int32> ProController::povD8() const
	{
		if (!m_gamepadUserIndex)
		{
			return none;
		}

		return Gamepad(m_gamepadUserIndex.value()).povD8();
	}

	Vec2 ProController::LStick() const
	{
		if (!m_gamepadUserIndex)
		{
			return Vec2(0, 0);
		}

		const auto gamepad = Gamepad(m_gamepadUserIndex.value());

		if (gamepad.axes.size() < 4)
		{
			return Vec2(0, 0);
		}

		Vec2 v(gamepad.axes[0], gamepad.axes[1]);

		if (m_LStickDeadZone.type == DeadZoneType::None)
		{
			return v;
		}

		m_LStickDeadZone.apply(v.x, v.y);

		return v;
	}

	Vec2 ProController::RStick() const
	{
		if (!m_gamepadUserIndex)
		{
			return Vec2(0, 0);
		}

		const auto gamepad = Gamepad(m_gamepadUserIndex.value());

		if (gamepad.axes.size() < 4)
		{
			return Vec2(0, 0);
		}

		Vec2 v(gamepad.axes[3], gamepad.axes[2]);

		if (m_RStickDeadZone.type == DeadZoneType::None)
		{
			return v;
		}

		m_RStickDeadZone.apply(v.x, v.y);

		return v;
	}

	ProController::ProControllerType ProController::GetControllerType(const GamepadInfo& info) noexcept
	{
		if (info.vendorID == 0x57e)
		{
			if (info.productID == 0x2009)
			{
				return ProControllerType::ProController;
			}
		}

		return ProControllerType::Invalid;
	}
}
