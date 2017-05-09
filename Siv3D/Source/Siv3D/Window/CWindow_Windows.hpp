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
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Siv3D/String.hpp>
# include <Siv3D/Window.hpp>
# include "IWindow.hpp"

namespace s3d
{
	class CWindow_Windows : public ISiv3DWindow
	{
	private:

		HWND m_hWnd = nullptr;

		String m_windowClassName;

		uint32 m_style = 0;
		
		WindowState m_state;

		bool m_resizeRequest = false;

		void initState();

		bool registerWindowClass();

		bool createWindow();

	public:

		CWindow_Windows();

		~CWindow_Windows() override;

		bool init() override;
		
		bool update() override;

		WindowHandle getHandle() const override;

		void setTitle(const String& title, bool forceUpdate) override;
		
		const WindowState& getState() const override;

		void setPos(const Point& pos) override;

		void updateClientSize(bool fullScreen, const Size& size) override;

		void requestResize();
	};
}

# endif
