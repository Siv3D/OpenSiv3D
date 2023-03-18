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
# include <Siv3D/Window.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Window/IWindow.hpp>

namespace s3d
{
	class CWindow_Null final : public ISiv3DWindow
	{
	private:
		
		String m_title{ Window::DefaultTitle };
		
		WindowState m_state;

	public:

		CWindow_Null();

		~CWindow_Null() override;

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

		bool resizeByVirtualSize(const Size& size) override;

		bool resizeByFrameBufferSize(const Size& size) override;

		void setMinimumFrameBufferSize(const Size& size) override;

		void setFullscreen(bool fullscreen, size_t monitorIndex) override;

		void setToggleFullscreenEnabled(bool enabled) override;

		bool isToggleFullscreenEnabled() const override;

		void setTaskbarProgressBar(double progress0_1) override;
	};
}
