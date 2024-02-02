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

# include <Siv3D/Common.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CCursor_Null.hpp"

namespace s3d
{
	CCursor_Null::CCursor_Null()
	{

	}

	CCursor_Null::~CCursor_Null()
	{
		LOG_SCOPED_TRACE(U"CCursor_Null::~CCursor_Null()");
	}

	void CCursor_Null::init()
	{
		LOG_SCOPED_TRACE(U"CCursor_Null::init()");
	}

	bool CCursor_Null::update()
	{
		return true;
	}

	const CursorState& CCursor_Null::getState() const noexcept
	{
		return m_state;
	}

	void CCursor_Null::setPos(const Point)
	{

	}

	const Mat3x2& CCursor_Null::getLocalTransform() const noexcept
	{
		return m_transformLocal;
	}

	const Mat3x2& CCursor_Null::getCameraTransform() const noexcept
	{
		return m_transformCamera;
	}

	const Mat3x2& CCursor_Null::getScreenTransform() const noexcept
	{
		return m_transformScreen;
	}

	void CCursor_Null::setLocalTransform(const Mat3x2&)
	{

	}

	void CCursor_Null::setCameraTransform(const Mat3x2&)
	{

	}

	void CCursor_Null::setScreenTransform(const Mat3x2&)
	{

	}

	bool CCursor_Null::isClippedToWindow() const noexcept
	{
		return false;
	}

	void CCursor_Null::clipToWindow(const bool)
	{

	}

	void CCursor_Null::requestStyle(const CursorStyle)
	{

	}

	void CCursor_Null::setDefaultStyle(const CursorStyle)
	{

	}

	bool CCursor_Null::registerCursor(const StringView, const Image&, const Point)
	{
		return true;
	}

	void CCursor_Null::requestStyle(StringView)
	{

	}

	void CCursor_Null::setCapture(const bool) noexcept
	{

	}

	bool CCursor_Null::isCaptured() const noexcept
	{
		return false;
	}
}
