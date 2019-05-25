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
# include <Keyboard/IKeyboard.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

namespace s3d
{
	class CKeyboard : public ISiv3DKeyboard
	{
	private:

		GLFWwindow* m_glfwWindow = nullptr;
		
		std::array<InputState, KeyboardButtonCount> m_states;

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
