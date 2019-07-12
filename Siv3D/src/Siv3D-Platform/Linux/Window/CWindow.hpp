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
# include <Window/IWindow.hpp>

# include <GL/glew.h>
# include <GLFW/glfw3.h>

namespace s3d
{
	class CWindow : public ISiv3DWindow
	{
	private:
		
		GLFWwindow* m_window = nullptr;

		String m_title		= U"Siv3D App";
		String m_titleText	= Platform::DebugBuild ? U"Siv3D App (Debug Build)" : U"Siv3D App";

		// Internal state
		WindowState m_state;
		ScaleMode m_scaleMode = Scene::DefaultScaleMode;
		Rect m_storedWindowRect = Rect(m_state.clientSize);

		Optional<Size> m_backBufferResizingRequest;
		bool m_toggleFullscreenRequest = false;

		void doResizeBackBuffer();

		void doToggleFullscreen();
		
		static void OnMove(GLFWwindow* window, int x, int y);
		
		static void OnResize(GLFWwindow* window, int width, int height);
		
		static void OnIconify(GLFWwindow* window, int iconified);

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

		bool setFullscreen(bool fullscreen, const Optional<Size>& fullscreenResolution, WindowResizeOption option) override;

		void* getHandle() const override;

		bool changeDisplayResolution(const Size& size) override;

		void requestBackBufferResizing(const Size& size, bool minimized, bool maximized) override;

		void requestToggleFullscreen() override;
	};
}
