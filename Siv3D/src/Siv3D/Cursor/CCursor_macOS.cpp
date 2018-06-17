//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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
# include <Siv3D/Logger.hpp>

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

		m_screen.previous = m_screen.current;
		m_client_raw.previous = m_client_raw.current;
		m_client_transformed.previous = m_client_transformed.current;
		m_client_transformedF.previous = m_client_transformedF.current;

		LOG_INFO(U"ℹ️ Cursor initialized");

		return true;
	}

	void CCursor_macOS::update()
	{
		if (m_clipRect)
		{
			// [Siv3D ToDo]
		}
		
		m_screen.previous = m_screen.current;
		m_screen.current = detail::CursorScreenPos_macOS();
		m_screen.delta = m_screen.current - m_screen.previous;

		double clientX, clientY;
		::glfwGetCursorPos(m_glfwWindow, &clientX, &clientY);
		m_client_raw.previous = m_client_raw.current;
		m_client_raw.current.set(static_cast<int32>(clientX), static_cast<int32>(clientY));
		m_client_raw.delta = m_client_raw.current - m_client_raw.previous;

		m_client_transformedF.previous = m_client_transformedF.current;
		m_client_transformedF.current = m_transformAllInv.transform(m_client_raw.current);
		m_client_transformedF.delta = m_client_transformedF.current - m_client_transformedF.previous;

		m_client_transformed.previous = m_client_transformedF.previous.asPoint();
		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();

		updateCursorStyle();
	}

	const CursorState<Point>& CCursor_macOS::screen() const
	{
		return m_screen;
	}

	const CursorState<Point>& CCursor_macOS::clientRaw() const
	{
		return m_client_raw;
	}

	const CursorState<Vec2>& CCursor_macOS::clientTransformedF() const
	{
		return m_client_transformedF;
	}

	const CursorState<Point>& CCursor_macOS::clientTransformed() const
	{
		return m_client_transformed;
	}

	void CCursor_macOS::setPos(const int32 x, const int32 y)
	{
		const Point screenPos = Point(x, y) + (m_screen.current - m_client_raw.current);
		
		detail::CursorSetPos_macOS(screenPos.x, screenPos.y);
		
		m_screen.current = screenPos;
		m_screen.delta = m_screen.current - m_screen.previous;

		m_client_raw.current.set(x, y);
		m_client_raw.delta = m_client_raw.current - m_client_raw.previous;

		m_client_transformedF.current = m_transformAllInv.transform(m_client_raw.current);
		m_client_transformedF.delta = m_client_transformedF.current - m_client_transformedF.previous;

		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();
	}

	void CCursor_macOS::setTransformLocal(const Mat3x2& matrix)
	{
		if (!::memcmp(&m_transformLocal, &matrix, sizeof(Mat3x2)))
		{
			return;
		}

		m_transformLocal = matrix;

		m_transformAll = m_transformLocal * m_transformCamera * m_transformScreen;
		m_transformAllInv = m_transformAll.inversed();

		m_client_transformedF.previous = m_transformAllInv.transform(m_client_raw.previous);
		m_client_transformedF.current = m_transformAllInv.transform(m_client_raw.current);
		m_client_transformedF.delta = m_client_transformedF.current - m_client_transformedF.previous;

		m_client_transformed.previous = m_client_transformedF.previous.asPoint();
		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();
	}

	void CCursor_macOS::setTransformCamera(const Mat3x2& matrix)
	{
		if (!::memcmp(&m_transformCamera, &matrix, sizeof(Mat3x2)))
		{
			return;
		}

		m_transformCamera = matrix;

		m_transformAll = m_transformLocal * m_transformCamera * m_transformScreen;
		m_transformAllInv = m_transformAll.inversed();

		m_client_transformedF.previous = m_transformAllInv.transform(m_client_raw.previous);
		m_client_transformedF.current = m_transformAllInv.transform(m_client_raw.current);
		m_client_transformedF.delta = m_client_transformedF.current - m_client_transformedF.previous;

		m_client_transformed.previous = m_client_transformedF.previous.asPoint();
		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();
	}

	void CCursor_macOS::setTransformScreen(const Mat3x2& matrix)
	{
		if (!::memcmp(&m_transformScreen, &matrix, sizeof(Mat3x2)))
		{
			return;
		}

		m_transformScreen = matrix;

		m_transformAll = m_transformLocal * m_transformCamera * m_transformScreen;
		m_transformAllInv = m_transformAll.inversed();

		m_client_transformedF.previous = m_transformAllInv.transform(m_client_raw.previous);
		m_client_transformedF.current = m_transformAllInv.transform(m_client_raw.current);
		m_client_transformedF.delta = m_client_transformedF.current - m_client_transformedF.previous;

		m_client_transformed.previous = m_client_transformedF.previous.asPoint();
		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();
	}

	const Mat3x2& CCursor_macOS::getTransformLocal() const
	{
		return m_transformLocal;
	}

	const Mat3x2& CCursor_macOS::getTransformCamera() const
	{
		return m_transformCamera;
	}

	const Mat3x2& CCursor_macOS::getTransformScreen() const
	{
		return m_transformScreen;
	}

	void CCursor_macOS::clip(const Optional<Rect>& rect)
	{
		m_clipRect = rect;
	}

	void CCursor_macOS::requestStyle(const CursorStyle style)
	{
		m_requestedCursorStyle = style;
	}

	void CCursor_macOS::setDefaultStyle(const CursorStyle style)
	{
		m_defaultCursorStyle = style;
	}

	void CCursor_macOS::applyStyleImmediately(const CursorStyle style)
	{
		m_curerntCursorStyle = style;

		detail::CursorSetStyle_macOS(style);
	}

	CursorStyle CCursor_macOS::getRequestedStyle()
	{
		return m_requestedCursorStyle;
	}

	CursorStyle CCursor_macOS::getDefaultStyle()
	{
		return m_defaultCursorStyle;
	}

	void CCursor_macOS::updateCursorStyle()
	{
		if (Window::ClientRect().intersects(m_client_raw.current))
		{
			if (m_curerntCursorStyle != m_requestedCursorStyle)
			{
				m_curerntCursorStyle = m_requestedCursorStyle;

				detail::CursorSetStyle_macOS(m_curerntCursorStyle);
			}
		}

		m_requestedCursorStyle = m_defaultCursorStyle;
	}
}

# endif
