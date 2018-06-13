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

		Optional<uint32> m_gamepadUserIndex;

		ControllerType m_type = ControllerType::Invalid;

		[[nodiscard]] static ControllerType GetControllerType(const GamepadInfo& info) noexcept;

	public:

		[[nodiscard]] static bool IsJoyCon(const detail::Gamepad_impl& gamepad) noexcept;

		[[nodiscard]] static bool IsJoyConL(const detail::Gamepad_impl& gamepad) noexcept;

		[[nodiscard]] static bool IsJoyConR(const detail::Gamepad_impl& gamepad) noexcept;

		JoyCon() = default;

		explicit JoyCon(const detail::Gamepad_impl& gamepad);

		[[nodiscard]] static JoyCon JoyConL(size_t index);

		[[nodiscard]] static JoyCon JoyConR(size_t index);

		[[nodiscard]] bool isConnected() const noexcept;

		[[nodiscard]] explicit operator bool() const noexcept;

		[[nodiscard]] bool isJoyConL() const noexcept;

		[[nodiscard]] bool isJoyConR() const noexcept;

		Key button0;	// L-Left / R-A

		Key button1;	// L-Down / R-X

		Key button2;	// L-Up / R-B

		Key button3;	// L-Right / R-Y

		Key buttonSL;

		Key buttonSR;

		Key buttonMinus;

		Key buttonPlus;

		Key buttonStick;

		Key buttonHome;

		Key buttonScreenshot;

		Key buttonLR;

		Key buttonZLZR;

		[[nodiscard]] Optional<int32> povD8() const noexcept;
	};
}
