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
# include "PointVector.hpp"
# include "Gamepad.hpp"
# include "DeadZone.hpp"

namespace s3d
{
	class ProController
	{
	private:

		const detail::Gamepad_impl& m_gamepad;

		DeadZone m_LStickDeadZone;

		DeadZone m_RStickDeadZone;

		bool m_isProController = false;

	public:

		[[nodiscard]] static bool IsProController(const detail::Gamepad_impl& gamepad)
		{
			return (gamepad.getInfo().vendorID == 0x57e) && (gamepad.getInfo().productID == 0x2009);
		}

		ProController() = default;

		explicit ProController(const detail::Gamepad_impl& gamepad,
			const DeadZone& left = { 0.016, 0.67, DeadZoneType::Circular },
			const DeadZone& right = { 0.016, 0.67, DeadZoneType::Circular })
			: m_gamepad(gamepad)		
			, m_LStickDeadZone(left)
			, m_RStickDeadZone(right)
			, m_isProController(IsProController(gamepad))
			, buttonA(InputDevice::Gamepad, 1, static_cast<uint8>(m_gamepad.userIndex))
			, buttonB(InputDevice::Gamepad, 0, static_cast<uint8>(m_gamepad.userIndex))
			, buttonX(InputDevice::Gamepad, 3, static_cast<uint8>(m_gamepad.userIndex))
			, buttonY(InputDevice::Gamepad, 2, static_cast<uint8>(m_gamepad.userIndex))
			, buttonL(InputDevice::Gamepad, 4, static_cast<uint8>(m_gamepad.userIndex))
			, buttonR(InputDevice::Gamepad, 5, static_cast<uint8>(m_gamepad.userIndex))
			, buttonZL(InputDevice::Gamepad, 6, static_cast<uint8>(m_gamepad.userIndex))
			, buttonZR(InputDevice::Gamepad, 7, static_cast<uint8>(m_gamepad.userIndex))
			, buttonMinus(InputDevice::Gamepad, 8, static_cast<uint8>(m_gamepad.userIndex))
			, buttonPlus(InputDevice::Gamepad, 9, static_cast<uint8>(m_gamepad.userIndex))
			, buttonLStick(InputDevice::Gamepad, 10, static_cast<uint8>(m_gamepad.userIndex))
			, buttonRStick(InputDevice::Gamepad, 11, static_cast<uint8>(m_gamepad.userIndex))
			, buttonHome(InputDevice::Gamepad, 12, static_cast<uint8>(m_gamepad.userIndex))
			, buttonScreenshot(InputDevice::Gamepad, 13, static_cast<uint8>(m_gamepad.userIndex))
			, povUp(InputDevice::Gamepad, 0x80, static_cast<uint8>(m_gamepad.userIndex))
			, povDown(InputDevice::Gamepad, 0x82, static_cast<uint8>(m_gamepad.userIndex))
			, povLeft(InputDevice::Gamepad, 0x83, static_cast<uint8>(m_gamepad.userIndex))
			, povRight(InputDevice::Gamepad, 0x81, static_cast<uint8>(m_gamepad.userIndex))
		{
		
		}

		[[nodiscard]] bool isConnected() const
		{
			return (m_isProController)
				&& m_gamepad.isConnected();
		}

		explicit operator bool() const
		{
			return isConnected();
		}

		Key buttonA;

		Key buttonB;

		Key buttonX;

		Key buttonY;

		Key buttonL;

		Key buttonR;

		Key buttonZL;

		Key buttonZR;

		Key buttonMinus;

		Key buttonPlus;

		Key buttonLStick;

		Key buttonRStick;

		Key buttonHome;

		Key buttonScreenshot;


		Key povUp;

		Key povDown;

		Key povLeft;

		Key povRight;

		[[nodiscard]] Optional<int32> povD8() const
		{
			return m_gamepad.povD8();
		}
		
		[[nodiscard]] Vec2 LStick() const
		{
			if (m_gamepad.axes.size() < 4)
			{
				return Vec2(0, 0);
			}

			Vec2 v(m_gamepad.axes[0], m_gamepad.axes[1]);

			if (m_LStickDeadZone.type == DeadZoneType::None)
			{
				return v;
			}
			
			m_LStickDeadZone.apply(v.x, v.y);

			return v;
		}

		[[nodiscard]] Vec2 RStick() const
		{
			if (m_gamepad.axes.size() < 4)
			{
				return Vec2(0, 0);
			}

			Vec2 v(m_gamepad.axes[3], m_gamepad.axes[2]);

			if (m_RStickDeadZone.type == DeadZoneType::None)
			{
				return v;
			}

			m_RStickDeadZone.apply(v.x, v.y);

			return v;
		}
	};
}
