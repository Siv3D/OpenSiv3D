//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/DLL.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/ResizeMode.hpp>
# include <Siv3D/Optional.hpp>
# include <ShObjIdl_core.h>

namespace s3d
{
	class CWindow final : public ISiv3DWindow
	{
	private:

		HWND m_hWnd = nullptr;
		HINSTANCE m_hInstance = nullptr;
		std::wstring m_windowClassName;
		HDEVNOTIFY m_deviceNotificationHandle = nullptr;

		LibraryHandle m_user32 = nullptr;
		decltype(GetSystemMetricsForDpi)* m_pGetSystemMetricsForDpi = nullptr;
		decltype(AdjustWindowRectExForDpi)* m_pAdjustWindowRectExForDpi = nullptr;

		String m_title = String(Window::DefaultTitle);
		String m_actualTitle = String(SIV3D_BUILD(DEBUG) ? U"Siv3D App (Debug Build)"_sv : Window::DefaultTitle);

		WindowState m_state;
		uint32 m_dpi = USER_DEFAULT_SCREEN_DPI;
		Size m_border = Size(0, 0);
		Size m_targetWindowPos = Point(0, 0);
		RECT m_storedWindowRect = { 0, 0, 0, 0 }; // フルスクリーンからウィンドウモードに復帰するときのウィンドウサイズ
		Optional<ResizeMode> m_oldResizeMode;
		bool m_toggleFullscreenEnabled = true;
		bool m_toggleFullscreenRequest = false;
		bool m_showWindowCalled = false;

		ComPtr<ITaskbarList3> m_taskbar;

		int32 getSystemMetrics(int32 index) const;

		Rect adjustWindowRect(const Point& pos, const Size& size, int32 windowStyleFlags) const;

		void setWindowPos(const Rect& rect, UINT flags);

	public:

		CWindow();

		~CWindow() override;

		void init() override;

		void destroy();

		void update() override;

		void setWindowTitle(const String& title) override;

		const String& getWindowTitle() const noexcept override;

		void* getHandle() const noexcept override;

		const WindowState& getState() const noexcept override;

		void setStyle(WindowStyle style) override;

		void setPos(const Point& pos) override;

		void maximize() override;

		void restore() override;

		void minimize() override;

		bool resizeByVirtualSize(const Size& virtualSize) override;

		bool resizeByFrameBufferSize(const Size& frameBufferSize) override;

		void setMinimumFrameBufferSize(const Size& size) override;

		void setFullscreen(bool fullscreen, size_t monitorIndex) override;

		void setToggleFullscreenEnabled(bool enabled) override;

		bool isToggleFullscreenEnabled() const override;

		void show() override;

		void setTaskbarProgressBar(double progress0_1) override;


		void setFullscreen(bool fullscreen, size_t monitorIndex, bool skipSceneResize);

		void onResize(bool minimized, bool maximized);

		void onFocus(bool focused);

		void onFrameBufferResize(const Size& size);

		void onDPIChange(uint32 dpi, const Point& suggestedPos);

		void onBoundsUpdate();

		void onMinMaxInfo(LPMINMAXINFO pMinMaxInfo);

		void onEnterSizeMove();

		void onExitSizeMove();

		void requestToggleFullscreen();
	};
}
