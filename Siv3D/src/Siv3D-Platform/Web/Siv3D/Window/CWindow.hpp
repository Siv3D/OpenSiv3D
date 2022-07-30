//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Window.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	class CWindow final : public ISiv3DWindow
	{
	private:
		
		GLFWwindow* m_window = nullptr;

		String m_title = String(Window::DefaultTitle);
		String m_actualTitle = String(SIV3D_BUILD(DEBUG) ? U"Siv3D App (Debug Build)"_sv : Window::DefaultTitle);

		WindowState m_state;
		bool m_resizingWindow = false;
		
		void updateState();
		
		static void OnMove(GLFWwindow* window, int x, int y);
		
		static void OnResize(GLFWwindow* window, int width, int height);
		
		static void OnFrameBufferSize(GLFWwindow* window, int width, int height);
		
		static void OnScalingChange(GLFWwindow* window, float sx, float sy);
		
		static void OnIconify(GLFWwindow* window, int iconified);
		
		static void OnMaximize(GLFWwindow* window, int maximized);
		
		static void OnFocus(GLFWwindow* window, int focused);
		
	public:

		CWindow();

		~CWindow() override;

		void init() override;
		
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
	};
}
