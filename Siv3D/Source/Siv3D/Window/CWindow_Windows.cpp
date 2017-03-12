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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/System.hpp>
# include "../Siv3DEngine.hpp"
# include "CWindow_Windows.hpp"
# include "../System/ISystem.hpp"
# include "../Mouse/IMouse.hpp"

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

			case WM_MOUSEWHEEL:

				Siv3DEngine::GetMouse()->onScroll(static_cast<short>(HIWORD(wParam)) / -double(WHEEL_DELTA), 0);

				return 0;

			case WM_MOUSEHWHEEL:

				Siv3DEngine::GetMouse()->onScroll(0, static_cast<short>(HIWORD(wParam)) / double(WHEEL_DELTA));

				return 0;
			}

			return ::DefWindowProcW(hWnd, message, wParam, lParam);
		}
	}

	CWindow_Windows::CWindow_Windows()
	{

	}

	CWindow_Windows::~CWindow_Windows()
	{
		if (!m_hWnd)
		{
			return;
		}

		::DestroyWindow(m_hWnd);

		for (int32 i = 0; i < 16; ++i)
		{
			MSG message;

			if (::PeekMessageW(&message, 0, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
				{
					break;
				}
				else
				{
					::TranslateMessage(&message);

					::DispatchMessageW(&message);
				}
			}
		}

		::UnregisterClassW(m_windowClassName.c_str(), ::GetModuleHandleW(nullptr));
	}

	bool CWindow_Windows::init()
	{
		initState();

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

	WindowHandle CWindow_Windows::getHandle() const
	{
		return m_hWnd;
	}

	void CWindow_Windows::setTitle(const String& title, const bool forceUpdate)
	{
		if (!forceUpdate && title == m_state.title)
		{
			return;
		}

		m_state.title = title;

		::SetWindowTextW(m_hWnd, m_state.title.c_str());
	}
	
	const WindowState& CWindow_Windows::getState() const
	{
		return m_state;
	}

	void CWindow_Windows::initState()
	{
		m_windowClassName = FileSystem::ModulePath();

		m_style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

		m_state.clientSize.set(Window::DefaultClientSize.x, Window::DefaultClientSize.y);
		m_state.screenSize.set(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN));
		m_state.title = L"Siv3D App";

		RECT windowRect = { 0, 0, m_state.clientSize.x, m_state.clientSize.y };
		::AdjustWindowRectEx(&windowRect, m_style, FALSE, 0);

		m_state.windowSize.set(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

		if (const int addedBorder = ::GetSystemMetrics(SM_CXPADDEDBORDER))
		{
			m_state.frameSize.x = ::GetSystemMetrics(SM_CXFRAME) + addedBorder;
			m_state.frameSize.y = ::GetSystemMetrics(SM_CYFRAME) + addedBorder;
		}
		else
		{
			m_state.frameSize.x = ::GetSystemMetrics(SM_CXFIXEDFRAME);
			m_state.frameSize.y = ::GetSystemMetrics(SM_CYFIXEDFRAME);
		}

		m_state.titleBarHeight = ::GetSystemMetrics(SM_CYCAPTION) + m_state.frameSize.y;

		updateTaskbarState();
		{
			Point offset{ 0, 0 }, size{ 0, 0 };

			if (m_state.taskbarPos % 2)
			{
				size.x = m_state.taskbarRect.w;
			}
			else
			{
				size.y = m_state.taskbarRect.h;
			}

			if (m_state.taskbarPos == 2)
			{
				offset.y = m_state.taskbarRect.h;
			}
			else if (m_state.taskbarPos == 1)
			{
				offset.x = m_state.taskbarRect.w;
			}

			const Point pos = ((m_state.screenSize - size) - m_state.windowSize) / 2 + offset;

			m_state.pos.set(std::max(pos.x, 0), std::max(pos.y, 0));
		}
	}
	
	void CWindow_Windows::updateTaskbarState()
	{
		APPBARDATA barData{};
		barData.cbSize = sizeof(APPBARDATA);
		barData.hWnd = m_hWnd;
		::SHAppBarMessage(ABM_GETTASKBARPOS, &barData);

		m_state.taskbarRect.setPos(barData.rc.left, barData.rc.top);
		m_state.taskbarRect.setSize(barData.rc.right - barData.rc.left, barData.rc.bottom - barData.rc.top);

		if (m_state.screenSize.x <= m_state.taskbarRect.w) // 上か下
		{
			if (m_state.taskbarRect.y <= 0) // 上
			{
				m_state.taskbarPos = 2;
			}
			else
			{
				m_state.taskbarPos = 0;
			}
		}
		else // 左か右
		{
			if (m_state.taskbarRect.x <= 0) // 左
			{
				m_state.taskbarPos = 1;
			}
			else
			{
				m_state.taskbarPos = 3;
			}
		}
	}

	bool CWindow_Windows::registerWindowClass()
	{
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
		m_hWnd = ::CreateWindowExW(
			0,
			m_windowClassName.c_str(),
			m_state.title.c_str(),
			m_style,
			m_state.pos.x,
			m_state.pos.y,
			m_state.windowSize.x,
			m_state.windowSize.y,
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
