//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Gamepad.hpp"
# include "DeadZone.hpp"

namespace s3d
{
	/// @brief Pro コントローラ用の Gamepad アダプタ
	class ProController
	{
	public:

		[[nodiscard]]
		static bool IsProController(const detail::Gamepad_impl& gamepad);

		SIV3D_NODISCARD_CXX20
		ProController() = default;

		SIV3D_NODISCARD_CXX20
		explicit ProController(const detail::Gamepad_impl& gamepad,
			const DeadZone& left = { 0.016, 0.67, DeadZoneType::Circular },
			const DeadZone& right = { 0.016, 0.67, DeadZoneType::Circular });

		SIV3D_NODISCARD_CXX20
		explicit ProController(size_t index);

		[[nodiscard]]
		bool isConnected() const;

		[[nodiscard]]
		explicit operator bool() const;

		Input buttonA;

		Input buttonB;

		Input buttonX;

		Input buttonY;

		Input buttonL;

		Input buttonR;

		Input buttonZL;

		Input buttonZR;

		Input buttonMinus;

		Input buttonPlus;

		Input buttonLStick;

		Input buttonRStick;

		Input buttonHome;

		Input buttonScreenshot;

		Input povUp;

		Input povDown;

		Input povLeft;

		Input povRight;

		[[nodiscard]]
		Optional<int32> povD8() const;

		[[nodiscard]]
		Vec2 LStick() const;

		[[nodiscard]]
		Vec2 RStick() const;

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

		[[nodiscard]]
		static ProControllerType GetControllerType(const GamepadInfo& info) noexcept;
	};
}
