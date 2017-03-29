//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include <Siv3D/String.hpp>
# include <Siv3D/Window.hpp>
# include "IWindow.hpp"

namespace s3d
{
	class CWindow_Linux : public ISiv3DWindow
	{
	private:

		WindowHandle m_glfwWindow = nullptr;

		WindowState m_state;	
		
	public:

		CWindow_Linux();

		~CWindow_Linux() override;

		bool init() override;
		
		bool update() override;
		
		WindowHandle getHandle() const override;

		void setTitle(const String& title, bool forceUpdate) override;

		const WindowState& getState() const override;

		void setPos(const Point& pos) override;

		void updateClientSize(const Size& size) override;
	};
}

# endif
