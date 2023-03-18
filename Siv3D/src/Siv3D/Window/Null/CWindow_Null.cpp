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

# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CWindow_Null.hpp"

namespace s3d
{
	CWindow_Null::CWindow_Null()
	{
		// do nothing
	}

	CWindow_Null::~CWindow_Null()
	{
		LOG_SCOPED_TRACE(U"CWindow_Null::~CWindow_Null()");
	}

	void CWindow_Null::init()
	{
		LOG_SCOPED_TRACE(U"CWindow_Null::init()");
	}

	void CWindow_Null::update()
	{
		// do nothing
	}

	void CWindow_Null::setWindowTitle(const String& title)
	{
		m_title = title;
	}

	const String& CWindow_Null::getWindowTitle() const noexcept
	{
		return m_title;
	}

	void* CWindow_Null::getHandle() const noexcept
	{
		return nullptr;
	}

	const WindowState& CWindow_Null::getState() const noexcept
	{
		return m_state;
	}

	void CWindow_Null::setStyle([[maybe_unused]] const WindowStyle style)
	{
		LOG_TRACE(U"CWindow_Null::setStyle(style = {})"_fmt(FromEnum(style)));
	}

	void CWindow_Null::setPos([[maybe_unused]] const Point& pos)
	{
		LOG_TRACE(U"CWindow_Null::setPos(pos = {})"_fmt(pos));
	}

	void CWindow_Null::maximize()
	{
		LOG_TRACE(U"CWindow_Null::maximize()");
	}

	void CWindow_Null::restore()
	{
		LOG_TRACE(U"CWindow_Null::restore()");
	}

	void CWindow_Null::minimize()
	{
		LOG_TRACE(U"CWindow_Null::minimize()");
	}

	bool CWindow_Null::resizeByVirtualSize([[maybe_unused]] const Size& size)
	{
		LOG_TRACE(U"CWindow_Null::resizeByVirtualSize(size = {})"_fmt(size));
		
		return true;
	}

	bool CWindow_Null::resizeByFrameBufferSize([[maybe_unused]] const Size& size)
	{
		LOG_TRACE(U"CWindow_Null::resizeByFrameBufferSize(size = {})"_fmt(size));

		return true;
	}

	void CWindow_Null::setMinimumFrameBufferSize([[maybe_unused]] const Size& size)
	{
		LOG_TRACE(U"CWindow_Null::setMinimumFrameBufferSize(size = {})"_fmt(size));
	}

	void CWindow_Null::setFullscreen([[maybe_unused]] const bool fullscreen, [[maybe_unused]] const size_t monitorIndex)
	{
		LOG_TRACE(U"CWindow_Null::setFullscreen(fullscreen = {}, monitorIndex = {})"_fmt(fullscreen, monitorIndex));
	}

	void CWindow_Null::setToggleFullscreenEnabled(bool) {}
	
	bool CWindow_Null::isToggleFullscreenEnabled() const
	{
		return false;
	}

	void CWindow_Null::setTaskbarProgressBar(double)
	{
		// do nothing
	}
}
