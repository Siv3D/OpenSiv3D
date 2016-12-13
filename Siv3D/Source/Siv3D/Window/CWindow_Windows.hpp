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
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Siv3D/String.hpp>
# include "IWindow.hpp"

namespace s3d
{
	class CWindow_Windows : public ISiv3DWindow
	{
	private:

		HWND m_hWnd = nullptr;

		String m_windowClassName;

		bool registerWindowClass();

		bool createWindow();

	public:

		CWindow_Windows();

		~CWindow_Windows() override;

		bool init() override;
		
		bool update() override;

		void destroy() override;
	};
}

# endif
