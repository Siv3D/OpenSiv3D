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
# include <array>
# include <Siv3D/Windows.hpp>
# include <Keyboard/IKeyboard.hpp>

namespace s3d
{
	class CKeyboard : public ISiv3DKeyboard
	{
	private:

		HWND m_hWnd = nullptr;

		std::array<InputState, KeyboardButtonCount> m_states;

		bool m_inputAttached = false;

	public:

		CKeyboard();

		~CKeyboard() override;

		void init() override;

		void update() override;

		bool down(uint32 index) const override;

		bool pressed(uint32 index) const override;

		bool up(uint32 index) const override;

		Duration pressedDuration(uint32 index) const override;
	};
}
