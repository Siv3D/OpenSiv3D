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

# include <GL/glew.h>
# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "../Siv3DEngine.hpp"
# include "CCursor_macOS.hpp"
# include <Siv3D/Optional.hpp>

void macOS_GetScreenCursorPos(double* xpos, double* ypos);

namespace s3d
{
	namespace detail
	{
		Point CursorScreenPos_macOS();
		
		void CursorSetPos_macOS(int32 x, int32 y);
	}
	
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
		if (m_clipRect)
		{
			// [Siv3D ToDo]
		}
		
		m_screenPos = detail::CursorScreenPos_macOS();
		m_screenDelta = m_screenPos - m_previousScreenPos;
		m_previousScreenPos = m_screenPos;

		double clientX, clientY;
		::glfwGetCursorPos(m_glfwWindow, &clientX, &clientY);
		m_clientPos.set(static_cast<int32>(clientX), static_cast<int32>(clientY));
		m_clientDelta = m_clientPos - m_previousClientPos;
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
		const Point screenPos = Point(x, y) + (m_screenPos - m_clientPos);
		
		detail::CursorSetPos_macOS(screenPos.x, screenPos.y);
		
		m_clientPos.set(x, y);
		m_screenPos.set(screenPos);
	}

	void CCursor_macOS::clip(const Optional<Rect>& rect)
	{
		m_clipRect = rect;
	}
}

# endif
