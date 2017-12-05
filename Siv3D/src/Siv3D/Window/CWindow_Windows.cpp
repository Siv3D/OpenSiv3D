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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/Monitor.hpp>
# include <Siv3D/Logger.hpp>
# include "../Siv3DEngine.hpp"
# include "CWindow_Windows.hpp"
# include "../System/ISystem.hpp"
//# include "../Mouse/IMouse.hpp"
//# include "../Mouse/CMouse_Windows.hpp"
//# include "../TextInput/ITextInput.hpp"

//# include "../Graphics/D3D11/CGraphics_D3D11.hpp"

namespace s3d
{
	namespace detail
	{
		LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
				case WM_CLOSE:
				{
					Siv3DEngine::GetSystem()->reportEvent(WindowEvent::CloseButton);

					return 0; // WM_DESTROY を発生させない
				}
				case WM_KILLFOCUS:
				{
					Siv3DEngine::GetSystem()->reportEvent(WindowEvent::Unfocus);

					break;
				}
				case WM_DESTROY:
				{
					::PostQuitMessage(0);

					return 0;
				}
				case WM_SIZING:
				{
					if (CWindow_Windows* window = dynamic_cast<CWindow_Windows*>(Siv3DEngine::GetWindow()))
					{
						window->requestResize();
					}

					break;
				}
				case WM_SIZE:
				{
					if (wParam == SIZE_RESTORED)
					{
						if (CWindow_Windows* window = dynamic_cast<CWindow_Windows*>(Siv3DEngine::GetWindow()))
						{
							window->requestResize();
						}

						return 0;
					}
					else if (wParam == SIZE_MINIMIZED)
					{
						break;
					}
					else if (wParam == SIZE_MAXIMIZED)
					{
						if (CWindow_Windows* window = dynamic_cast<CWindow_Windows*>(Siv3DEngine::GetWindow()))
						{
							window->requestResize();
						}

						return 0;
					}

					break;
				}
				case WM_KEYDOWN:
				{
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
				case WM_MOUSEWHEEL:
				{
					//Siv3DEngine::GetMouse()->onScroll(static_cast<short>(HIWORD(wParam)) / -double(WHEEL_DELTA), 0);

					return 0;
				}
				case WM_MOUSEHWHEEL:
				{
					//Siv3DEngine::GetMouse()->onScroll(0, static_cast<short>(HIWORD(wParam)) / double(WHEEL_DELTA));

					return 0;
				}
				case WM_CHAR:
				{
					//Siv3DEngine::GetTextInput()->pushChar(static_cast<uint32>(wParam));

					return 0;
				}
				case WM_UNICHAR:
				{
					if (wParam == UNICODE_NOCHAR)
					{
						return true;
					}

					//Siv3DEngine::GetTextInput()->pushChar(static_cast<uint32>(wParam));

					return 0;
				}
				case WM_TOUCH:
				{
					//if (const size_t num_inputs = LOWORD(wParam))
					//{
					//	Array<TOUCHINPUT> touchInputs(num_inputs);

					//	if (::GetTouchInputInfo(reinterpret_cast<HTOUCHINPUT>(lParam),
					//		static_cast<uint32>(touchInputs.size()), touchInputs.data(),
					//		sizeof(TOUCHINPUT)))
					//	{
					//		if (auto pMouse = dynamic_cast<CMouse_Windows*>(Siv3DEngine::GetMouse()))
					//		{
					//			pMouse->onTouchInput(touchInputs);
					//		}

					//		::CloseTouchInputHandle(reinterpret_cast<HTOUCHINPUT>(lParam));

					//		return 0;
					//	}
					//}

					break;
				}
				case WM_SYSCOMMAND:
				{
					switch (wParam & 0xffF0)
					{
					case SC_SCREENSAVE:
					case SC_MONITORPOWER:
						return 0;
					}

					break;
				}
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

		// 適当に残ったメッセージを処理
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

		LOG_INFO(U"ℹ️ Window destroyed");
	}

	bool CWindow_Windows::init()
	{
		initState();

		if (!registerWindowClass())
		{
			LOG_ERROR(U"🛑 Failed to register window class");

			return false;
		}

		if (!createWindow())
		{
			LOG_ERROR(U"🛑 Failed to create a window");

			return false;
		}

		LOG_INFO(U"ℹ️ Window initialized");

		return true;
	}

	void CWindow_Windows::show(const bool show)
	{
		if (show)
		{
			::ShowWindow(m_hWnd, SW_SHOW);

			::ValidateRect(m_hWnd, 0);

			::UpdateWindow(m_hWnd);

			::SetForegroundWindow(m_hWnd);
		}
		else
		{
			::ShowWindow(m_hWnd, SW_HIDE);		
		}
	}

	bool CWindow_Windows::update()
	{
		m_state.screenSize.set(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN));

		// ウィンドウが最小化、最大化されているかどうかチェック
		WINDOWPLACEMENT wpl = { sizeof(WINDOWPLACEMENT), };
		::GetWindowPlacement(m_hWnd, &wpl);

		m_state.showState = (wpl.showCmd == SW_SHOWMINIMIZED) ? ShowState::Minimized
			: (wpl.showCmd == SW_SHOWMAXIMIZED) ? ShowState::Maximized
			: ShowState::Normal;

		m_state.focused = (m_hWnd == ::GetForegroundWindow());
	
		// ウィンドウの大きさを更新
		RECT rc;
		::GetWindowRect(m_hWnd, &rc);
		m_state.pos.set(rc.left, rc.top);

		//CGraphics_D3D11* graphics = dynamic_cast<CGraphics_D3D11*>(Siv3DEngine::GetGraphics());
		//const auto shouldResize = graphics->shouldResize();
		//const bool resizeRequest = std::exchange(m_resizeRequest, false);

		//if (resizeRequest && shouldResize)
		//{
		//	RECT wnRec;
		//	::GetWindowRect(m_hWnd, &wnRec);
		//	RECT area{ 0, 0, wnRec.right - wnRec.left, wnRec.bottom - wnRec.top };
		//	m_state.windowSize.set(area.right - area.left, area.bottom - area.top);
		//	m_state.clientSize.set(wnRec.right - wnRec.left, wnRec.bottom - wnRec.top);

		//	// ウィンドウの枠やタイトルバーの幅を再度取得
		//	if (const int32 addedBorder = ::GetSystemMetrics(SM_CXPADDEDBORDER))
		//	{
		//		m_state.frameSize.x = ::GetSystemMetrics(SM_CXFRAME) + addedBorder;
		//		m_state.frameSize.y = ::GetSystemMetrics(SM_CYFRAME) + addedBorder;
		//	}
		//	else
		//	{
		//		m_state.frameSize.x = ::GetSystemMetrics(SM_CXFIXEDFRAME);
		//		m_state.frameSize.y = ::GetSystemMetrics(SM_CYFIXEDFRAME);
		//	}

		//	m_state.titleBarHeight = ::GetSystemMetrics(SM_CYCAPTION) + m_state.frameSize.y;

		//	if (!(m_style & WS_POPUP))
		//	{
		//		m_state.clientSize -= { m_state.frameSize.x * 2, m_state.frameSize.y + m_state.titleBarHeight };
		//	}

		//	const Size availableSize = m_state.clientSize;

		//	graphics->resizeTargetWindowed(availableSize);

		//	m_resizeRequest = false;

		//	::SetWindowPos(m_hWnd, nullptr, wnRec.left, wnRec.top, m_state.windowSize.x, m_state.windowSize.y, SWP_DEFERERASE | SWP_NOOWNERZORDER | SWP_NOZORDER);
		//}

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

		if constexpr (SIV3D_IS_DEBUG)
		{
			const String titleDebug = m_state.title + U" [Debug Build]";

			::SetWindowTextW(m_hWnd, titleDebug.toWstr().c_str());
		}
		else
		{
			::SetWindowTextW(m_hWnd, m_state.title.toWstr().c_str());
		}
	}
	
	const WindowState& CWindow_Windows::getState() const
	{
		return m_state;
	}

	void CWindow_Windows::setPos(const Point& pos)
	{
		m_state.pos.set(pos);

		::SetWindowPos(
			m_hWnd,
			nullptr,
			pos.x,
			pos.y,
			0,
			0,
			SWP_DEFERERASE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOSIZE
		);
	}

	void CWindow_Windows::updateClientSize(const bool fullScreen, const Size& size)
	{
		m_state.clientSize = size;
		m_state.fullScreen = fullScreen;

		RECT windowRect = { 0, 0, size.x, size.y };
		::AdjustWindowRectEx(&windowRect, m_style, FALSE, 0);
		m_state.windowSize.set(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

		if (!fullScreen)
		{
			::SetWindowPos(m_hWnd, nullptr, m_state.pos.x, m_state.pos.y, m_state.windowSize.x, m_state.windowSize.y, SWP_DEFERERASE | SWP_NOOWNERZORDER | SWP_NOZORDER);
		}
	}

	void CWindow_Windows::setBaseSize(const Size& size)
	{
		m_baseSize = size;
	}

	Size CWindow_Windows::getBaseSize() const
	{
		return m_baseSize;
	}

	void CWindow_Windows::requestResize()
	{
		m_resizeRequest = true;
	}

	void CWindow_Windows::initState()
	{
		// ウィンドウクラス名として実行ファイルのパスを使用
		m_windowClassName = FileSystem::ModulePath().toWstr();

		m_style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

		m_state.screenSize.set(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN));
		m_state.clientSize.set(Window::DefaultClientSize);
		m_state.title = SIV3D_IS_DEBUG ? U"Siv3D App [Debug Build]" : U"Siv3D App";
		m_state.showState = ShowState::Normal;
		m_state.focused = false;

		RECT windowRect = { 0, 0, m_state.clientSize.x, m_state.clientSize.y };
		::AdjustWindowRectEx(&windowRect, m_style, FALSE, 0);
		m_state.windowSize.set(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

		// ウィンドウの枠やタイトルバーの幅を取得
		if (const int32 addedBorder = ::GetSystemMetrics(SM_CXPADDEDBORDER))
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

		m_state.pos.set(100, 100);

		for (const auto& monitor : System::EnumActiveMonitors())
		{
			// プライマリモニターの中央に位置するようにウィンドウを配置
			if (monitor.isPrimary)
			{
				const int32 xOffset = (monitor.workArea.w - m_state.windowSize.x) / 2;
				const int32 yOffset = (monitor.workArea.h - m_state.windowSize.y) / 2;
				m_state.pos.set(std::max(monitor.workArea.x + xOffset, 0), std::max(monitor.workArea.y + yOffset, 0));
				break;
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
		windowClass.hCursor			= nullptr;
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
			m_state.title.toWstr().c_str(),
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

		//::ShowWindow(m_hWnd, SW_SHOW);

		return true;
	}
}

# endif
