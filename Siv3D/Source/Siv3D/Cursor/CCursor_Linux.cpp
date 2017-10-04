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
# if defined(SIV3D_TARGET_LINUX)

# include <GL/glew.h>
# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "../../ThirdParty/GLFW/include/GLFW/glfw3native.h"
# include "../Siv3DEngine.hpp"
# include "CCursor_Linux.hpp"

// TODO : implemantation
void Linux_GetScreenCursorPos(double* xpos, double* ypos) { }

namespace s3d
{
	CCursor_Linux::CCursor_Linux()
	{

	}

	CCursor_Linux::~CCursor_Linux()
	{

	}

	bool CCursor_Linux::init()
	{
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();

		update();

		m_screen.previous = m_screen.current;
		m_client_raw.previous = m_client_raw.current;
		m_client_transformed.previous = m_client_transformed.current;
		m_client_transformedF.previous = m_client_transformedF.current;

		return true;
	}

	void CCursor_Linux::update()
	{
		// グラブ処理
		if (!m_grabbing_old && m_grabbing)
		{
			Display* display = ::glfwGetX11Display();
			Window window = ::glfwGetX11Window(m_glfwWindow);

			::XGrabPointer(display, window, True, 0,
				GrabModeAsync, GrabModeAsync, window, None, CurrentTime);
		}
		else if(m_grabbing_old && !m_grabbing)
		{
			Display* display = ::glfwGetX11Display();
			::XUngrabPointer(display, CurrentTime);
		}
		m_grabbing_old = m_grabbing;

		double clientX, clientY;
		::glfwGetCursorPos(m_glfwWindow, &clientX, &clientY);
		m_screen.previous = m_screen.current;
		m_screen.current.set(static_cast<int32>(clientX), static_cast<int32>(clientY));
		m_screen.delta = m_screen.current - m_screen.previous;

		m_client_raw.previous = m_client_raw.current;
		m_client_raw.current.set(static_cast<int32>(clientX), static_cast<int32>(clientY));
		m_client_raw.delta = m_client_raw.current - m_client_raw.previous;

		m_client_transformedF.previous = m_client_transformedF.current;
		m_client_transformedF.current = m_transformInv.transform(m_client_raw.current);
		m_client_transformedF.delta = m_client_transformedF.current - m_client_transformedF.previous;

		m_client_transformed.previous = m_client_transformedF.previous.asPoint();
		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();
	}

	const CursorState<Point>& CCursor_Linux::screen() const
	{
		return m_screen;
	}

	const CursorState<Point>& CCursor_Linux::clientRaw() const
	{
		return m_client_raw;
	}

	const CursorState<Vec2>& CCursor_Linux::clientTransformedF() const
	{
		return m_client_transformedF;
	}

	const CursorState<Point>& CCursor_Linux::clientTransformed() const
	{
		return m_client_transformed;
	}

	void CCursor_Linux::setPos(const int32 x, const int32 y)
	{
		// [Siv3D ToDo]
		// ::glfwSetCursorPos(m_glfwwindow, x, y);
	}

	void CCursor_Linux::setTransform(const Mat3x2& matrix)
	{
		if (!::memcmp(&m_transform, &matrix, sizeof(Mat3x2)))
		{
			return;
		}

		m_transform = matrix;
		m_transformInv = m_transform.inversed();

		m_client_transformedF.current = m_transformInv.transform(m_client_raw.current);
		m_client_transformedF.delta = m_client_transformedF.current - m_client_transformedF.previous;

		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();
	}

	const Mat3x2& CCursor_Linux::getTransform() const
	{
		return m_transform;
	}

	void CCursor_Linux::clipClientRect(bool grab)
	{
		m_grabbing = !m_grabbing;
	}

	void CCursor_Linux::clip(const Optional<Rect>& rect)
	{
		// OpenSiv3D for Linux doesn't support Cursor::Clip()
	}

	void CCursor_Linux::setStyle(CursorStyle style)
	{
		// [Siv3D ToDo]
	}

	CursorStyle CCursor_Linux::getStyle()
	{
		// [Siv3D ToDo]
		return CursorStyle::Default;
	}
}

# endif
