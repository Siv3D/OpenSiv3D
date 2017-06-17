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
# include <Siv3D/Window.hpp>

void macOS_GetScreenCursorPos(double* xpos, double* ypos);

namespace s3d
{
	namespace detail
	{
		Point CursorScreenPos_macOS();
		
		void CursorSetPos_macOS(int32 x, int32 y);
		
		void CursorSetStyle_macOS(CursorStyle style);
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
		m_previousClientPos_raw = m_screenPos;
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
		m_clientPos_raw.set(static_cast<int32>(clientX), static_cast<int32>(clientY));
		m_previousClientPos_raw = m_clientPos_raw;

		m_clientPos_transformedVec2			= m_transformInv.transform(m_clientPos_raw);
		m_previousClientPos_transformedVec2	= m_transformInv.transform(m_previousClientPos_raw);
		
		m_clientPos_transformedPoint			= m_clientPos_transformedVec2.asPoint();
		m_previousClientPos_transformedPoint	= m_previousClientPos_transformedVec2.asPoint();
		
		if (Window::ClientRect().intersects(m_clientPos) && m_curerntCursorStyle != CursorStyle::Default)
		{
			detail::CursorSetStyle_macOS(m_curerntCursorStyle);
		}
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

	Point CCursor_macOS::clientDelta() const
	{
		return m_clientPos_transformedPoint - m_previousClientPos_transformedPoint;
	}

	const Vec2& CCursor_macOS::previousClientPosF() const
	{
		return m_previousClientPos_transformedVec2;
	}

	const Vec2& CCursor_macOS::clientPosF() const
	{
		return m_previousClientPos_transformedVec2;
	}

	Vec2 CCursor_macOS::clientDeltaF() const
	{
		return m_clientPos_transformedVec2 - m_previousClientPos_transformedVec2;
	}

	void CCursor_macOS::setPos(const int32 x, const int32 y)
	{
		const Point screenPos = Point(x, y) + (m_screenPos - m_clientPos);
		
		detail::CursorSetPos_macOS(screenPos.x, screenPos.y);
		
		m_clientPos_raw.set(x, y);
		m_screenPos.set(screenPos);

		m_clientPos_transformedVec2		= m_transformInv.transform(m_clientPos_raw);
		m_clientPos_transformedPoint	= m_clientPos_transformedVec2.asPoint();

	}

	void CCursor_macOS::setTransform(const Mat3x2& matrix)
	{
		if (!::memcmp(&m_transform, &matrix, sizeof(Mat3x2)))
		{
			return;
		}

		m_transform = matrix;
		m_transformInv = m_transform.inverse();

		m_clientPos_transformedVec2 = m_transformInv.transform(m_clientPos_raw);
		m_previousClientPos_transformedVec2 = m_transformInv.transform(m_previousClientPos_raw);

		m_clientPos_transformedPoint = m_clientPos_transformedVec2.asPoint();
		m_previousClientPos_transformedPoint = m_previousClientPos_transformedVec2.asPoint();
	}

	const Mat3x2& CCursor_macOS::getTransform() const
	{
		return m_transform;
	}

	void CCursor_macOS::clip(const Optional<Rect>& rect)
	{
		m_clipRect = rect;
	}

	void CCursor_macOS::setStyle(CursorStyle style)
	{
		if (style == m_curerntCursorStyle)
		{
			return;
		}
		
		detail::CursorSetStyle_macOS(style);
		
		m_curerntCursorStyle = style;
	}

	CursorStyle CCursor_macOS::getStyle()
	{
		return m_curerntCursorStyle;
	}
}

# endif
