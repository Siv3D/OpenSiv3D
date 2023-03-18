//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
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
		: m_gamepadUserIndex{ gamepad.playerIndex }
		, m_proControllerType{ GetControllerType(gamepad.getInfo()) }
		, m_LStickDeadZone{ left }
		, m_RStickDeadZone{ right }
	{
		if (m_proControllerType != ProControllerType::Invalid)
		{
			buttonA = Input{ InputDeviceType::Gamepad, 1, static_cast<uint8>(gamepad.playerIndex) };
			buttonB = Input{ InputDeviceType::Gamepad, 0, static_cast<uint8>(gamepad.playerIndex) };
			buttonX = Input{ InputDeviceType::Gamepad, 3, static_cast<uint8>(gamepad.playerIndex) };
			buttonY = Input{ InputDeviceType::Gamepad, 2, static_cast<uint8>(gamepad.playerIndex) };
			buttonL = Input{ InputDeviceType::Gamepad, 4, static_cast<uint8>(gamepad.playerIndex) };
			buttonR = Input{ InputDeviceType::Gamepad, 5, static_cast<uint8>(gamepad.playerIndex) };
			buttonZL = Input{ InputDeviceType::Gamepad, 6, static_cast<uint8>(gamepad.playerIndex) };
			buttonZR = Input{ InputDeviceType::Gamepad, 7, static_cast<uint8>(gamepad.playerIndex) };
			buttonMinus = Input{ InputDeviceType::Gamepad, 8, static_cast<uint8>(gamepad.playerIndex) };
			buttonPlus = Input{ InputDeviceType::Gamepad, 9, static_cast<uint8>(gamepad.playerIndex) };
			buttonLStick = Input{ InputDeviceType::Gamepad, 10, static_cast<uint8>(gamepad.playerIndex) };
			buttonRStick = Input{ InputDeviceType::Gamepad, 11, static_cast<uint8>(gamepad.playerIndex) };
			buttonHome = Input{ InputDeviceType::Gamepad, 12, static_cast<uint8>(gamepad.playerIndex) };
			buttonScreenshot = Input{ InputDeviceType::Gamepad, 13, static_cast<uint8>(gamepad.playerIndex) };
			povUp = Input{ InputDeviceType::Gamepad, 0x80, static_cast<uint8>(gamepad.playerIndex) };
			povDown = Input{ InputDeviceType::Gamepad, 0x82, static_cast<uint8>(gamepad.playerIndex) };
			povLeft = Input{ InputDeviceType::Gamepad, 0x83, static_cast<uint8>(gamepad.playerIndex) };
			povRight = Input{ InputDeviceType::Gamepad, 0x81, static_cast<uint8>(gamepad.playerIndex) };
		}
	}

	ProController::ProController(const size_t index)
	{
		size_t count = 0;

		for (size_t i = 0; i < Gamepad.MaxPlayerCount; ++i)
		{
			const auto& gamepad = Gamepad(i);

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
			&& Gamepad(*m_gamepadUserIndex).isConnected();
	}

	ProController::operator bool() const
	{
		return isConnected();
	}

	Optional<int32> ProController::povD8() const
	{
		if (not m_gamepadUserIndex)
		{
			return none;
		}

		return Gamepad(*m_gamepadUserIndex).povD8();
	}

	Vec2 ProController::LStick() const
	{
		if (not m_gamepadUserIndex)
		{
			return{ 0.0, 0.0 };
		}

		const auto gamepad = Gamepad(*m_gamepadUserIndex);

		if (gamepad.axes.size() < 4)
		{
			return{ 0.0, 0.0 };
		}

		Vec2 v{ gamepad.axes[0], gamepad.axes[1] };

		if (m_LStickDeadZone.type == DeadZoneType::None_)
		{
			return v;
		}

		return m_LStickDeadZone(v);
	}

	Vec2 ProController::RStick() const
	{
		if (not m_gamepadUserIndex)
		{
			return{ 0.0, 0.0 };
		}

		const auto gamepad = Gamepad(*m_gamepadUserIndex);

		if (gamepad.axes.size() < 4)
		{
			return{ 0.0, 0.0 };
		}

		Vec2 v{ gamepad.axes[2], gamepad.axes[3] };

		if (m_RStickDeadZone.type == DeadZoneType::None_)
		{
			return v;
		}

		return m_RStickDeadZone(v);
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
