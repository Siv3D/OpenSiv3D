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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/System.hpp>
# include "../Siv3DEngine.hpp"
# include "CWindow_Windows.hpp"
# include "../System/ISystem.hpp"

namespace s3d
{
	namespace detail
	{
		LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_CLOSE:

				Siv3DEngine::GetSystem()->reportEvent(WindowEvent::CloseButton);

				return 0; // WM_DESTROY を発生させない

			case WM_DESTROY:

				::PostQuitMessage(0);

				return 0;

			case WM_KEYDOWN:

				if (wParam == VK_ESCAPE)
				{
					Siv3DEngine::GetSystem()->reportEvent(WindowEvent::AnyKey | WindowEvent::EscapeKey);
				}
				else if (VK_BACK <= wParam) // マウス以外のキー入力
				{
					Siv3DEngine::GetSystem()->reportEvent(WindowEvent::AnyKey);
				}

				break;
			}

			return ::DefWindowProcW(hWnd, message, wParam, lParam);
		}
	}

	CWindow_Windows::CWindow_Windows()
	{

	}

	CWindow_Windows::~CWindow_Windows()
	{
		::UnregisterClassW(m_windowClassName.c_str(), ::GetModuleHandleW(nullptr));
	}

	bool CWindow_Windows::init()
	{
		if (!registerWindowClass())
		{
			return false;
		}

		if (!createWindow())
		{
			return false;
		}

		return true;
	}
	
	bool CWindow_Windows::update()
	{
		return true;
	}

	void CWindow_Windows::destroy()
	{
		::DestroyWindow(m_hWnd);
	}

	bool CWindow_Windows::registerWindowClass()
	{
		m_windowClassName = FileSystem::ModulePath();

		WNDCLASSEXW windowClass{};
		windowClass.cbSize			= sizeof(WNDCLASSEXW);
		windowClass.style			= CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc		= detail::WindowProc;
		windowClass.hInstance		= ::GetModuleHandleW(nullptr);
		windowClass.hIcon			= ::LoadIconW(::GetModuleHandleW(nullptr), MAKEINTRESOURCEW(100));
		windowClass.hCursor			= ::LoadCursorW(nullptr, IDC_ARROW);
		windowClass.hbrBackground	= static_cast<HBRUSH>(::GetStockObject(DKGRAY_BRUSH));
		windowClass.lpszClassName	= m_windowClassName.c_str();

		if (!::RegisterClassExW(&windowClass))
		{
			return false;
		}

		return true;
	}

	bool CWindow_Windows::createWindow()
	{
		const DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		const DWORD exStyle = WS_EX_ACCEPTFILES;

		RECT windowRect = { 0, 0, 640, 480 };
		::AdjustWindowRectEx(&windowRect, style, FALSE, exStyle);

		m_hWnd = ::CreateWindowExW(
			exStyle,
			m_windowClassName.c_str(),
			L"Siv3D App",
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			nullptr,
			nullptr,
			::GetModuleHandleW(nullptr),
			nullptr
		);

		if (!m_hWnd)
		{
			return false;
		}

		::ShowWindow(m_hWnd, SW_SHOW);

		return true;
	}
}

# endif
