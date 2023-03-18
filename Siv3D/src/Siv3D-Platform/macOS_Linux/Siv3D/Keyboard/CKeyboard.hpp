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

# pragma once
# include <Siv3D/Keyboard/IKeyboard.hpp>
# include <Siv3D/Input/InputState.hpp>
# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	class CKeyboard final : public ISiv3DKeyboard
	{
	private:

		GLFWwindow* m_window = nullptr;

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

		void clearInput(uint32 index) override;

		bool cleared(uint32 index) const override;

		Duration pressedDuration(uint32 index) const override;

		const String& name(uint32 index) const override;

		const Array<Input>& getAllInput() const noexcept override;

		Array<KeyEvent> getEvents() const noexcept override;
	};
}
