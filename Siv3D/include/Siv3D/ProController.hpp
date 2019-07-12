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

		enum class ProControllerType
		{
			Invalid,

			ProController,
		};

		Optional<uint32> m_gamepadUserIndex;

		ProControllerType m_proControllerType = ProControllerType::Invalid;

		DeadZone m_LStickDeadZone;

		DeadZone m_RStickDeadZone;

		[[nodiscard]] static ProControllerType GetControllerType(const GamepadInfo& info) noexcept;

	public:

		[[nodiscard]] static bool IsProController(const detail::Gamepad_impl& gamepad);

		ProController() = default;

		explicit ProController(const detail::Gamepad_impl& gamepad,
			const DeadZone& left = { 0.016, 0.67, DeadZoneType::Circular },
			const DeadZone& right = { 0.016, 0.67, DeadZoneType::Circular });

		explicit ProController(size_t index);

		[[nodiscard]] bool isConnected() const;

		explicit operator bool() const;

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

		[[nodiscard]] Optional<int32> povD8() const;
		
		[[nodiscard]] Vec2 LStick() const;

		[[nodiscard]] Vec2 RStick() const;
	};
}
