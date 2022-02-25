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
# include "Optional.hpp"
# include "Unspecified.hpp"
# include "ColorHSV.hpp"

namespace s3d
{
	class JoyCon
	{
	public:

		struct ButtonGuide
		{
			bool button0 = false;

			bool button1 = false;

			bool button2 = false;

			bool button3 = false;

			bool buttonSL = false;

			bool buttonSR = false;

			bool buttonMinus = false;

			bool buttonPlus = false;

			bool buttonStick = false;

			bool buttonHome = false;

			bool buttonScreenshot = false;

			bool buttonLR = false;

			bool buttonZLZR = false;

			Optional<int32> povD8;
		};

		[[nodiscard]]
		static bool IsJoyCon(const detail::Gamepad_impl& gamepad) noexcept;

		[[nodiscard]]
		static bool IsJoyConL(const detail::Gamepad_impl& gamepad) noexcept;

		[[nodiscard]]
		static bool IsJoyConR(const detail::Gamepad_impl& gamepad) noexcept;

		SIV3D_NODISCARD_CXX20
		JoyCon() = default;

		SIV3D_NODISCARD_CXX20
		explicit JoyCon(const detail::Gamepad_impl& gamepad);

		[[nodiscard]]
		bool isConnected() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool isJoyConL() const noexcept;

		[[nodiscard]]
		bool isJoyConR() const noexcept;

		Input button0;	// L-Left / R-A

		Input button1;	// L-Down / R-X

		Input button2;	// L-Up / R-B

		Input button3;	// L-Right / R-Y

		Input buttonSL;

		Input buttonSR;

		Input buttonMinus;

		Input buttonPlus;

		Input buttonStick;

		Input buttonHome;

		Input buttonScreenshot;

		Input buttonLR;

		Input buttonZLZR;

		[[nodiscard]]
		Optional<int32> povD8() const noexcept;

		const JoyCon& drawShadowAt(const Vec2& center, double size, double angle = 0.0, bool covered = true, double offset = 0.5, double blurRadius = 1.0, double spread = 0.5, const ColorF& color = ColorF{ 0.0, 0.3 }) const;

		const JoyCon& drawAt(const Vec2& center, double size, double angle = 0.0, bool covered = true, const Optional<ColorF>& color = unspecified, const ColorF& colorPushed = ColorF{ 1.0, 0.8, 0.5 }) const;

		const JoyCon& drawGuidedAt(const ButtonGuide& guide, const Vec2& center, double size, double angle = 0.0, bool covered = true, const Optional<ColorF>& color = ColorF{ 0.0, 0.75, 0.9 }, const ColorF& colorPushed = ColorF{ 1.0, 0.8, 0.5 }, const ColorF& guideColor = ColorF{ 1.0, 0.7, 0.6 }) const;

		static void DrawLShadowAt(const Vec2& center, double size, double angle = 0.0, bool covered = true, double offset = 0.5, double blurRadius = 1.0, double spread = 0.5, const ColorF& color = ColorF{ 0.0, 0.3 });

		static void DrawLAt(const Vec2& center, double size, double angle = 0.0, bool covered = true, const ColorF& color = ColorF{ 0.0, 0.75, 0.9 }, const ColorF& colorPushed = ColorF{ 1.0, 0.8, 0.5 });

		static void DrawLGuidedAt(const ButtonGuide& guide, const Vec2& center, double size, double angle = 0.0, bool covered = true, const ColorF& color = ColorF{ 1.0, 0.4, 0.3 }, const ColorF& colorPushed = ColorF{ 1.0, 0.8, 0.5 }, const ColorF& guideColor = ColorF{ 1.0, 0.7, 0.6 });

		static void DrawRShadowAt(const Vec2& center, double size, double angle = 0.0, bool covered = true, double offset = 0.5, double blurRadius = 1.0, double spread = 0.5, const ColorF& color = ColorF{ 0.0, 0.3 });

		static void DrawRAt(const Vec2& center, double size, double angle = 0.0, bool covered = true, const ColorF& color = ColorF{ 1.0, 0.4, 0.3 }, const ColorF& colorPushed = ColorF{ 1.0, 0.8, 0.5 });

		static void DrawRGuidedAt(const ButtonGuide& guide, const Vec2& center, double size, double angle = 0.0, bool covered = true, const ColorF& color = ColorF{ 0.0, 0.75, 0.9 }, const ColorF& colorPushed = ColorF{ 1.0, 0.8, 0.5 }, const ColorF& guideColor = ColorF{ 1.0, 0.7, 0.6 });

	private:

		enum class JoyConType
		{
			Invalid,

			JoyConL,

			JoyConR,
		};

		Optional<uint32> m_gamepadUserIndex;

		JoyConType m_joyconType = JoyConType::Invalid;

		[[nodiscard]]
		static JoyConType GetControllerType(const GamepadInfo& info) noexcept;
	};

	[[nodiscard]]
	JoyCon JoyConL(size_t index);

	[[nodiscard]]
	JoyCon JoyConR(size_t index);
}
