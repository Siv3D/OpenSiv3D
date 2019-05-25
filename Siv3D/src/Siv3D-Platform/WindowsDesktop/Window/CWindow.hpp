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

# pragma once
# include <string>
# include <Siv3D/Window.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Windows.hpp>
# include <Window/IWindow.hpp>

namespace s3d
{
	class CWindow : public ISiv3DWindow
	{
	private:

		HWND m_hWnd = nullptr;
		HINSTANCE m_hInstance = nullptr;
		std::wstring m_windowClassName;
		String m_title		= U"Siv3D App";
		String m_titleText	= Platform::DebugBuild ? U"Siv3D App (Debug Build)" : U"Siv3D App";
		bool m_displayChanged = false;

		// Internal state
		WindowState m_state;
		ScaleMode m_scaleMode = Scene::DefaultScaleMode;
		RECT m_storedWindowRect	= { 0, 0, 0, 0 }; // フルスクリーンからウィンドウモードに復帰するときのウィンドウサイズ

		int32 m_displayInfoCheckCount = 0;

		Optional<Size> m_backBufferResizingRequest;
		bool m_toggleFullscreenRequest = false;

		void registerWindowClass();

		void createWindow();

		void doResizeBackBuffer();

		void doToggleFullscreen();

		uint32 getBaseWindowStyle() const;

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	public:

		CWindow();

		~CWindow() override;

		void init() override;

		void show(bool show) override;

		void update() override;

		void setWindowTitle(const String& title) override;

		const String& getWindowTitle() const override;

		void updateWindowBounds(const Rect& rect) override;

		WindowState getWindowState() const override;

		void setScaleMode(ScaleMode scaleMode) override;

		ScaleMode getScaleMode() const override;

		void setStyle(WindowStyle style) override;

		Size getClientSize() const override;

		Rect getWindowBounds() const override;

		void setPos(const Point& pos) override;

		bool resizeClient(const Size& size, WindowResizeOption option, bool centering) override;

		void maximize() override;

		void restore() override;

		void minimize() override;

		bool setFullscreen(bool fullscreen, const Optional<Size>& fullscreenResolution) override;

		void* getHandle() const override;

		bool changeDisplayResolution(const Size& size) override;

		void requestBackBufferResizing(const Size& size, bool minimized, bool maximized) override;

		void requestToggleFullscreen() override;
	};
}
