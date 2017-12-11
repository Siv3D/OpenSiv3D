//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include <GL/glew.h>
# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include <Siv3D/String.hpp>
# include <Siv3D/Window.hpp>
# include "IWindow.hpp"

namespace s3d
{
	class CWindow_macOS : public ISiv3DWindow
	{
	private:

		WindowHandle m_glfwWindow = nullptr;

		WindowState m_state;

		Size m_baseSize = Window::DefaultClientSize;
		
	public:

		CWindow_macOS();

		~CWindow_macOS() override;

		bool init() override;

		void show(bool show) override;
		
		bool update() override;
		
		WindowHandle getHandle() const override;

		void setTitle(const String& title, bool forceUpdate) override;
		
		const WindowState& getState() const override;

		void setPos(const Point& pos) override;
		
		void updateClientSize(bool fullScreen, const Size& size) override;

		void setBaseSize(const Size& size) override;

		Size getBaseSize() const override;
	};
}

# endif
