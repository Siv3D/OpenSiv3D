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
# include <Siv3D/Fwd.hpp>

namespace s3d
{	
	class ISiv3DWindow
	{
	public:

		static ISiv3DWindow* Create();

		virtual ~ISiv3DWindow() = default;

		virtual void init() = 0;

		virtual void show(bool show) = 0;

		virtual void update() = 0;

		virtual void setWindowTitle(const String& title) = 0;

		virtual const String& getWindowTitle() const = 0;

		virtual void updateWindowBounds(const Rect& rect) = 0;

		virtual WindowState getWindowState() const = 0;

		virtual void setScaleMode(ScaleMode scaleMode) = 0;

		virtual ScaleMode getScaleMode() const = 0;

		virtual void setStyle(WindowStyle style) = 0;

		virtual Size getClientSize() const = 0;

		virtual Rect getWindowBounds() const = 0;

		virtual void setPos(const Point& pos) = 0;

		virtual bool resizeClient(const Size& size, WindowResizeOption option, bool centering) = 0;

		virtual void maximize() = 0;
		
		virtual void restore() = 0;

		virtual void minimize() = 0;

		virtual bool setFullscreen(bool fullscreen, const Optional<Size>& fullscreenResolution) = 0;

		virtual void* getHandle() const = 0;

		virtual bool changeDisplayResolution(const Size& size) = 0;

		virtual void requestBackBufferResizing(const Size& size, bool minimized, bool maximized) = 0;

		virtual void requestToggleFullscreen() = 0;
	};
}
