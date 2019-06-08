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

# include <Siv3D/EngineError.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Monitor.hpp>
# include <Siv3DEngine.hpp>
# include <Profiler/IProfiler.hpp>
# include <Graphics/IGraphics.hpp>
# include <Graphics/D3D11/CGraphics_D3D11.hpp>
# include "CWindow.hpp"
# include "HighDPI.hpp"

extern "C"
{
	extern int Siv3DHighDPIAwareness;
}

namespace s3d
{
	namespace detail
	{
		void SetDisplayInfoCheckCount(int32& displayInfoCheckCount)
		{
			displayInfoCheckCount = 3;
		}

		void UpdateDisplayInfo()
		{
			if (CGraphics_D3D11* pGraphics = dynamic_cast<CGraphics_D3D11*>(Siv3DEngine::Get<ISiv3DGraphics>()))
			{
				pGraphics->updateDisplayInfo();
			}
		}

		Size SetFullscreen(HWND hWnd, RECT& storedWindowRect, const uint32 baseWindowStyle)
		{
			Size result(0, 0);

			::GetWindowRect(hWnd, &storedWindowRect);
			::SetWindowLongW(hWnd, GWL_STYLE, baseWindowStyle & ~(WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME));

			RECT fullscreenWindowRect = {};

			if (const auto rect = Siv3DEngine::Get<ISiv3DGraphics>()->getFullscreenRect())
			{
				fullscreenWindowRect.left = rect->x;
				fullscreenWindowRect.top = rect->y;
				fullscreenWindowRect.right = (rect->x + rect->w);
				fullscreenWindowRect.bottom = (rect->y + rect->h);

				result = rect->size;
			}
			else
			{
				DEVMODE devMode = {};
				devMode.dmSize = sizeof(DEVMODE);
				::EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &devMode);

				fullscreenWindowRect = {
					devMode.dmPosition.x,
					devMode.dmPosition.y,
					devMode.dmPosition.x + static_cast<LONG>(devMode.dmPelsWidth),
					devMode.dmPosition.y + static_cast<LONG>(devMode.dmPelsHeight)
				};

				result.set(static_cast<int32>(devMode.dmPelsWidth), static_cast<int32>(devMode.dmPelsHeight));
			}

			::SetWindowPos(
				hWnd,
				HWND_TOPMOST,
				fullscreenWindowRect.left,
				fullscreenWindowRect.top,
				fullscreenWindowRect.right,
				fullscreenWindowRect.bottom,
				SWP_FRAMECHANGED | SWP_NOACTIVATE);

			::ShowWindow(hWnd, SW_MAXIMIZE);
			::ValidateRect(hWnd, nullptr); // disable WM_PAINT

			return result;
		}

		bool CheckFullscreenSize(const Size& targetSize)
		{
			DEVMODEW devMode = {};
			devMode.dmSize = sizeof(DEVMODEW);
			::EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &devMode);

			devMode.dmPelsWidth = targetSize.x;
			devMode.dmPelsHeight = targetSize.y;

			return SUCCEEDED(::ChangeDisplaySettingsW(&devMode, CDS_TEST));
		}
	}

	CWindow::CWindow()
	{

	}

	CWindow::~CWindow()
	{
		LOG_TRACE(U"CWindow::~CWindow()");

		if (!m_hWnd)
		{
			return;
		}

		::DestroyWindow(m_hWnd);

		for (int32 i = 0; i < 100; ++i)
		{
			MSG message = {};

			if (::PeekMessageW(&message, 0, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
				{
					LOG_TRACE(U"message.message == WM_QUIT");
					break;
				}

				::TranslateMessage(&message);
				::DispatchMessageW(&message);
			}
		}

		::UnregisterClassW(m_windowClassName.c_str(), m_hInstance);

		if (m_displayChanged)
		{
			::ChangeDisplaySettingsW(nullptr, 0);
			m_displayChanged = false;
		}
	}

	void CWindow::init()
	{
		LOG_TRACE(U"CWindow::init()");

		m_hInstance = ::GetModuleHandleW(nullptr);
		m_windowClassName = FileSystem::ModulePath().toWstr();

		SetHighDPIAwareness(Siv3DHighDPIAwareness);

		registerWindowClass();

		createWindow();

		LOG_INFO(U"ℹ️ CWindow initialized");
	}

	void CWindow::show(const bool show)
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

	void CWindow::update()
	{
		doResizeBackBuffer();
		doToggleFullscreen();

		if (m_displayInfoCheckCount > 0)
		{
			detail::UpdateDisplayInfo();
			--m_displayInfoCheckCount;
		}

		if constexpr (Platform::DebugBuild)
		{
			const String statistics = Siv3DEngine::Get<ISiv3DProfiler>()->getSimpleStatistics();
			const String titleText = m_title + U" (Debug Build) | " + statistics;

			if (titleText != m_titleText)
			{
				m_titleText = titleText;
				::SetWindowTextW(m_hWnd, m_titleText.toWstr().c_str());
			}
		}
	}

	void CWindow::setWindowTitle(const String& title)
	{
		if (m_title != title)
		{
			if constexpr (Platform::DebugBuild)
			{
				const String statistics = Siv3DEngine::Get<ISiv3DProfiler>()->getSimpleStatistics();
				m_titleText = title + U" (Debug Build) | " + statistics;
			}
			else
			{
				m_titleText = title;
			}

			m_title = title;

			::SetWindowTextW(m_hWnd, m_titleText.toWstr().c_str());
		}
	}

	const String& CWindow::getWindowTitle() const
	{
		return m_title;
	}

	void CWindow::updateWindowBounds(const Rect& rect)
	{
		LOG_TRACE(U"CWindow::updateWindowBounds(rect = {})"_fmt(rect));

		m_state.bounds = rect;

		::ValidateRect(m_hWnd, nullptr); // disable WM_PAINT
	}

	WindowState CWindow::getWindowState() const
	{
		return m_state;
	}

	void CWindow::setScaleMode(const ScaleMode scaleMode)
	{
		m_scaleMode = scaleMode;
	}

	ScaleMode CWindow::getScaleMode() const
	{
		return m_scaleMode;
	}

	void CWindow::setStyle(const WindowStyle style)
	{
		if (m_state.fullscreen)
		{
			m_state.style = style;
			setFullscreen(false, unspecified, WindowResizeOption::KeepSceneSize);
			return;
		}

		if (m_state.style == style)
		{
			return;
		}

		const auto current = m_state.style;
		const bool needResize = (current == WindowStyle::Frameless || style == WindowStyle::Frameless);

		m_state.style = style;

		::SetWindowLongW(m_hWnd, GWL_STYLE, getBaseWindowStyle());

		RECT windowRect{ 0, 0, m_state.clientSize.x, m_state.clientSize.y };
		::AdjustWindowRect(&windowRect, getBaseWindowStyle(), false);

		::SetWindowPos(
			m_hWnd,
			HWND_NOTOPMOST,
			m_state.bounds.x,
			m_state.bounds.y,
			(windowRect.right - windowRect.left),
			(windowRect.bottom - windowRect.top),
			(needResize ? 0 : SWP_NOSIZE) | SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_FRAMECHANGED);
		::ShowWindow(m_hWnd, SW_NORMAL);
	}

	Size CWindow::getClientSize() const
	{
		return m_state.clientSize;
	}

	Rect CWindow::getWindowBounds() const
	{
		return m_state.bounds;
	}

	void CWindow::setPos(const Point& pos)
	{
		if (m_state.fullscreen)
		{
			return;
		}

		::SetWindowPos(
			m_hWnd,
			HWND_TOPMOST,
			pos.x,
			pos.y,
			0,
			0,
			SWP_DEFERERASE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOSIZE);
	}

	bool CWindow::resizeClient(const Size& size, const WindowResizeOption option, const bool centering)
	{
		if ((option == WindowResizeOption::ResizeSceneSize)
			|| ((option == WindowResizeOption::UseDefaultScaleMode) && (m_scaleMode == ScaleMode::ResizeFill)))
		{
			Siv3DEngine::Get<ISiv3DGraphics>()->setSceneSize(size);
		}

		if (size == Siv3DEngine::Get<ISiv3DGraphics>()->getBackBufferSize())
		{
			return true;
		}

		LOG_TRACE(U"CWindow::resizeClient(size = {})"_fmt(size));

		const Size newSize(std::max(size.x, m_state.minimumSize.x), std::max(size.y, m_state.minimumSize.y));

		::SetWindowLongW(m_hWnd, GWL_STYLE, getBaseWindowStyle());

		RECT windowRect = { 0, 0, newSize.x, newSize.y };
		::AdjustWindowRect(&windowRect, getBaseWindowStyle(), FALSE);

		if (centering)
		{
			for (const auto& monitor : System::EnumerateActiveMonitors())
			{
				// プライマリモニターの中央に位置するようにウィンドウを配置
				// [Siv3D ToDo] より正確に
				if (monitor.isPrimary)
				{
					const Point offset = (monitor.workArea.size - Size(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top)) / 2;
					m_state.bounds.pos.set(std::max(monitor.workArea.x + offset.x, 0), std::max(monitor.workArea.y + offset.y, 0));
					break;
				}
			}

			m_state.bounds.setSize(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
		}

		::SetWindowPos(
			m_hWnd,
			HWND_NOTOPMOST,
			m_state.bounds.x,
			m_state.bounds.y,
			(windowRect.right - windowRect.left),
			(windowRect.bottom - windowRect.top),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		::ShowWindow(m_hWnd, SW_NORMAL);

		return true;
	}

	void CWindow::maximize()
	{
		::ShowWindow(m_hWnd, SW_MAXIMIZE);
	}

	void CWindow::restore()
	{
		::ShowWindow(m_hWnd, SW_RESTORE);
	}

	void CWindow::minimize()
	{
		::ShowWindow(m_hWnd, SW_MINIMIZE);
	}

	bool CWindow::setFullscreen(const bool fullscreen, const Optional<Size>& fullscreenResolution, const WindowResizeOption option)
	{
		LOG_TRACE(U"CWindow::setFullscreen({})"_fmt(fullscreen));

		const auto ResizeScene = [option, scaleMode = m_scaleMode](const Size& size)
		{
			if ((option == WindowResizeOption::ResizeSceneSize)
				|| ((option == WindowResizeOption::UseDefaultScaleMode) && (scaleMode == ScaleMode::ResizeFill)))
			{
				Siv3DEngine::Get<ISiv3DGraphics>()->setSceneSize(size);
			}
		};

		if (m_state.fullscreen == false) // 現在ウィンドウモード
		{
			// ウィンドウモードにする
			if (fullscreen == false) // 変更の必要なし
			{
				ResizeScene(m_state.clientSize);
				return true;
			}

			// フルスクリーンモードにする		
			if (!fullscreenResolution) // サイズ指定なし
			{
				const Size result = detail::SetFullscreen(m_hWnd, m_storedWindowRect, getBaseWindowStyle()); // フルスクリーンモードに
				detail::SetDisplayInfoCheckCount(m_displayInfoCheckCount);
				m_state.fullscreen = true;
				ResizeScene(result);
				return true;
			}

			const Size targetSize = fullscreenResolution.value();

			// 解像度指定あり		
			if (!detail::CheckFullscreenSize(targetSize)) // 非対応の解像度
			{
				return false;
			}

			// 対応している解像度
			if (!changeDisplayResolution(targetSize)) // 解像度変更失敗
			{
				return false;
			}

			// 解像度の変更を待機
			::Sleep(150);

			// 解像度変更に成功
			detail::SetFullscreen(m_hWnd, m_storedWindowRect, getBaseWindowStyle()); // フルスクリーンモードに
			detail::SetDisplayInfoCheckCount(m_displayInfoCheckCount);
			m_state.fullscreen = true;
			ResizeScene(targetSize);
			return true;
		}
		else // 現在フルスクリーン
		{
			// ウィンドウモードにする
			if (fullscreen == false)
			{
				const Size size(m_storedWindowRect.right - m_storedWindowRect.left, m_storedWindowRect.bottom - m_storedWindowRect.top);

				::SetWindowLongW(m_hWnd, GWL_STYLE, getBaseWindowStyle());
				::SetWindowPos(
					m_hWnd,
					HWND_NOTOPMOST,
					m_storedWindowRect.left,
					m_storedWindowRect.top,
					size.x,
					size.y,
					SWP_FRAMECHANGED | SWP_NOACTIVATE);

				::ShowWindow(m_hWnd, SW_NORMAL);
				::ValidateRect(m_hWnd, nullptr); // disable WM_PAINT

				if (m_displayChanged)
				{
					::ChangeDisplaySettingsW(nullptr, 0);
					m_displayChanged = false;
				}

				detail::SetDisplayInfoCheckCount(m_displayInfoCheckCount);
				m_state.fullscreen = false;
				ResizeScene(size);
				return true;
			}

			// フルスクリーンモードにする		
			if (!fullscreenResolution) // サイズ指定なし
			{
				ResizeScene(m_state.clientSize);
				return true; // 何も更新しない
			}

			const Size targetSize = fullscreenResolution.value();

			// サイズ指定あり
			if (!detail::CheckFullscreenSize(targetSize)) // 非対応の解像度
			{
				return false;
			}

			// 対応している解像度
			if (!changeDisplayResolution(targetSize)) // 解像度変更失敗
			{
				return false;
			}

			detail::SetDisplayInfoCheckCount(m_displayInfoCheckCount);
			ResizeScene(targetSize);
			return true;
		}
	}

	void* CWindow::getHandle() const
	{
		return m_hWnd;
	}

	bool CWindow::changeDisplayResolution(const Size& size)
	{
		DEVMODEW devMode = {};
		devMode.dmSize = sizeof(DEVMODEW);
		::EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &devMode);

		devMode.dmPelsWidth = size.x;
		devMode.dmPelsHeight = size.y;

		const bool result = SUCCEEDED(::ChangeDisplaySettingsW(&devMode, 0));

		if (result)
		{
			m_displayChanged = true;
		}

		return result;
	}

	void CWindow::requestBackBufferResizing(const Size& size, const bool minimized, const bool maximized)
	{
		LOG_TRACE(U"CWindow::requestBackBufferResizing()");

		if ((size != Siv3DEngine::Get<ISiv3DGraphics>()->getBackBufferSize()) && !minimized)
		{
			m_backBufferResizingRequest = size;
			LOG_TRACE(U"CWindow::m_backBufferResizingRequest = {}"_fmt(size));
		}

		if (!minimized)
		{
			m_state.clientSize = size;
		}

		m_state.minimized	= minimized;
		m_state.maximized	= maximized;
	}

	void CWindow::requestToggleFullscreen()
	{
		LOG_TRACE(U"CWindow::requestToggleFullscreen()");
		m_toggleFullscreenRequest = true;
	}

	void CWindow::registerWindowClass()
	{
		LOG_TRACE(U"CWindow::registerWindowClass()");

		WNDCLASSEX windowClass		= {};
		windowClass.cbSize			= sizeof(WNDCLASSEX);
		windowClass.style			= CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc		= WindowProc;
		windowClass.hInstance		= m_hInstance;
		windowClass.hIcon			= ::LoadIconW(m_hInstance, MAKEINTRESOURCEW(100));
		windowClass.hCursor			= nullptr;
		windowClass.hbrBackground	= static_cast<HBRUSH>(::GetStockObject(DKGRAY_BRUSH));
		windowClass.lpszClassName	= m_windowClassName.c_str();
		if (!::RegisterClassExW(&windowClass))
		{
			throw EngineError(U"RegisterClassExW() failed");
		}
	}

	void CWindow::createWindow()
	{
		LOG_TRACE(U"CWindow::createWindow()");

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
		m_state.titleBarHeight = ::GetSystemMetrics(SM_CYCAPTION);
		LOG_TRACE(U"CWindow::m_state.frameSize: {}, CWindow::m_state.titleBarHeight: {}"_fmt(m_state.frameSize, m_state.titleBarHeight));

		RECT windowRect = { 0, 0, m_state.clientSize.x, m_state.clientSize.y };
		::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

		for (const auto& monitor : System::EnumerateActiveMonitors())
		{
			// プライマリモニターの中央に位置するようにウィンドウを配置
			// [Siv3D ToDo] より正確に
			if (monitor.isPrimary)
			{
				const Point offset = (monitor.workArea.size - Size(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top)) / 2;
				m_state.bounds.pos.set(std::max(monitor.workArea.x + offset.x, 0), std::max(monitor.workArea.y + offset.y, 0));
				break;
			}
		}

		m_state.bounds.setSize(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

		m_hWnd = ::CreateWindowExW(
			0,
			m_windowClassName.c_str(),
			m_titleText.toWstr().c_str(),
			getBaseWindowStyle(),
			m_state.bounds.x,
			m_state.bounds.y,
			m_state.bounds.w,
			m_state.bounds.h,
			nullptr, // No parent window
			nullptr, // No menu
			m_hInstance,
			nullptr);

		if (!m_hWnd)
		{
			throw EngineError(U"CreateWindowExW() failed");
		}
	}

	void CWindow::doResizeBackBuffer()
	{
		if (!m_backBufferResizingRequest)
		{
			return;
		}

		const Size newBackBufferSize = m_backBufferResizingRequest.value();
		const Size currentSceneSize = Siv3DEngine::Get<ISiv3DGraphics>()->getSceneSize();
		const bool keepSceneSize = (m_scaleMode == ScaleMode::AspectFit);

		Siv3DEngine::Get<ISiv3DGraphics>()->resizeBuffers(newBackBufferSize, keepSceneSize ? currentSceneSize : newBackBufferSize);

		m_backBufferResizingRequest.reset();
	}

	void CWindow::doToggleFullscreen()
	{
		if (!m_toggleFullscreenRequest)
		{
			return;
		}

		LOG_TRACE(U"CWindow::doToggleFullscreen()");

		setFullscreen(!m_state.fullscreen, unspecified, WindowResizeOption::KeepSceneSize);
		
		m_toggleFullscreenRequest	= false;
	}

	uint32 CWindow::getBaseWindowStyle() const
	{
		switch (m_state.style)
		{
		case WindowStyle::Fixed:
			return WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);		
		case WindowStyle::Frameless:
			return WS_POPUP | WS_VISIBLE | WS_MINIMIZEBOX;
		case WindowStyle::Sizable:
		default:
			return WS_OVERLAPPEDWINDOW;
		}
	}
}
