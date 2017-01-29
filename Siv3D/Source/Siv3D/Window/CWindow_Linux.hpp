//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include <Siv3D/String.hpp>
# include "IWindow.hpp"

namespace s3d
{
	class CWindow_Linux : public ISiv3DWindow
	{
	private:

		WindowHandle m_glfwWindow = nullptr;

		String m_currentTitle = L"Siv3D App";
		
	public:

		CWindow_Linux();

		~CWindow_Linux() override;

		bool init() override;
		
		bool update() override;
		
		WindowHandle getHandle() const override;

		void setTitle(const String& title) override;
	};
}

# endif
