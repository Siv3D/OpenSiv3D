//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

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

		String m_currentTitle = L"Siv3D App";
		
	public:

		CWindow_macOS();

		~CWindow_macOS() override;

		bool init() override;
		
		bool update() override;
		
		WindowHandle getHandle() const override;

		void setTitle(const String& title) override;
	};
}

# endif
