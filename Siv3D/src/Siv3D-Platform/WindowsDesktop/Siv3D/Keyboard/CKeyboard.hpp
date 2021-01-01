//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Keyboard/IKeyboard.hpp>
# include <Siv3D/Input/InputState.hpp>
# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	class CKeyboard final : public ISiv3DKeyboard
	{
	private:

		HWND m_hWnd = nullptr;

		bool m_inputAttached = false;

		std::array<String, InputState::KeyCount> m_names;

		std::array<InputState, InputState::KeyCount> m_states;

		Array<Input> m_allInputs;

	public:

		CKeyboard();

		~CKeyboard() override;

		void init() override;

		void update() override;

		bool down(uint32 index) const override;

		bool pressed(uint32 index) const override;

		bool up(uint32 index) const override;

		Duration pressedDuration(uint32 index) const override;

		const String& name(uint32 index) const override;

		const Array<Input>& getAllInput() const noexcept override;
	};
}
