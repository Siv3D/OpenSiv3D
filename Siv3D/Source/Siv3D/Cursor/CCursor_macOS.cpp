//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "../Siv3DEngine.hpp"
# include "CCursor_macOS.hpp"

void macOS_GetScreenCursorPos(double* xpos, double* ypos);

namespace s3d
{
	CCursor_macOS::CCursor_macOS()
	{

	}

	CCursor_macOS::~CCursor_macOS()
	{

	}

	bool CCursor_macOS::init()
	{
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();

		update();

		m_previousScreenPos = m_screenPos;
		m_previousClientPos = m_screenPos;
		m_screenDelta.set(0, 0);
		m_clientDelta.set(0, 0);

		return true;
	}

	void CCursor_macOS::update()
	{
		double screenX, screenY;
		macOS_GetScreenCursorPos(&screenX, &screenY);
		m_screenPos.set(static_cast<int32>(screenX), static_cast<int32>(screenY));
		m_previousScreenPos = m_screenPos;

		double clientX, clientY;
		::glfwGetCursorPos(m_glfwWindow, &clientX, &clientY);
		m_clientPos.set(static_cast<int32>(clientX), static_cast<int32>(clientY));
		m_previousClientPos = m_clientPos;
	}

	const Point& CCursor_macOS::previousScreenPos() const
	{
		return m_previousScreenPos;
	}

	const Point& CCursor_macOS::screenPos() const
	{
		return m_screenPos;
	}

	const Point& CCursor_macOS::screenDelta() const
	{
		return m_screenDelta;
	}

	const Point& CCursor_macOS::previousClientPos() const
	{
		return m_previousClientPos;
	}

	const Point& CCursor_macOS::clientPos() const
	{
		return m_previousClientPos;
	}

	const Point& CCursor_macOS::clientDelta() const
	{
		return m_clientDelta;
	}

	void CCursor_macOS::setPos(const int32 x, const int32 y)
	{

	}

	void CCursor_macOS::clip(const Optional<Rect>& rect)
	{
		m_clipRect = rect;
	}
}

# endif
