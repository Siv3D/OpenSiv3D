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
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DWindow
	{
	public:

		static ISiv3DWindow* Create();

		virtual ~ISiv3DWindow() = default;

		virtual void init() = 0;

		virtual void update() = 0;

		virtual void setWindowTitle(const String& title) = 0;

		virtual const String& getWindowTitle() const noexcept = 0;

		virtual void* getHandle() const noexcept = 0;

		virtual const WindowState& getState() const noexcept = 0;

		virtual void setStyle(WindowStyle style) = 0;

		virtual void setPos(const Point& pos) = 0;

		virtual void maximize() = 0;

		virtual void restore() = 0;

		virtual void minimize() = 0;

		virtual bool resizeByVirtualSize(const Size& virtualSize) = 0;

		virtual bool resizeByFrameBufferSize(const Size& frameBufferSize) = 0;

		virtual void setMinimumFrameBufferSize(const Size& size) = 0;

		virtual void setFullscreen(bool fullscreen, size_t monitorIndex) = 0;

		virtual void setToggleFullscreenEnabled(bool enabled) = 0;

		virtual bool isToggleFullscreenEnabled() const = 0;

		virtual void show() {}

		virtual void setTaskbarProgressBar(double progress0_1) = 0;
	};
}
