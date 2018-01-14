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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <array>
# include <Siv3D/Windows.hpp>
# include "IKeyboard.hpp"

namespace s3d
{
	class CKeyboard_Windows : public ISiv3DKeyboard
	{
	private:

		HWND m_hWnd = nullptr;

		std::array<InputState, KeyboardButtonCount> m_states;

		bool m_inputAttached = false;

	public:

		CKeyboard_Windows();

		~CKeyboard_Windows() override;

		bool init() override;

		void update() override;

		bool down(uint32 index) const override;

		bool pressed(uint32 index) const override;

		bool up(uint32 index) const override;

		MillisecondsF pressedDuration(uint32 index) const override;
	};
}

# endif
