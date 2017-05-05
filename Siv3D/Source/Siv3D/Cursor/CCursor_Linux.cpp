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

		m_previousScreenPos = m_screenPos;
		m_previousClientPos = m_screenPos;
		m_screenDelta.set(0, 0);
		m_clientDelta.set(0, 0);

		return true;
	}

	void CCursor_Linux::update()
	{
		// [TODO] : 子ウィンドウを透明に描画できるようにする
		static Window grabWindow;
		static GC gc;
		if (m_clipRect)
		{
			Display* display = ::glfwGetX11Display();
			Window parent = ::glfwGetX11Window(m_glfwWindow);
			if(m_grabbing == false)
			{
				//子ウィンドウを作成しそのウィンドウ内にポインタをgrabする
				//Mapしていないウィンドウでgrabしようとすると失敗する
				//そのため子ウィンドウは透明にして見えなくする
				XVisualInfo vinfo;
				::XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &vinfo);
				::XSetWindowAttributes attr;
				attr.colormap = XCreateColormap(display, DefaultRootWindow(display), vinfo.visual, AllocNone);
				attr.background_pixmap = None;
				attr.border_pixel = 0;
				attr.background_pixel = 0;
				printf("depth : %d\n", vinfo.depth);

				grabWindow = ::XCreateWindow(display, parent,
					m_clipRect->x, m_clipRect->y, m_clipRect->w, m_clipRect->h, 0,
					vinfo.depth, InputOutput, vinfo.visual,
					CWColormap | CWBorderPixel | CWBackPixel, &attr);
				//gc = ::XCreateGC(display, grabWindow, 0, 0);
				::XMapSubwindows(display, parent);

				XWindowAttributes xwa;
				XGetWindowAttributes(display, grabWindow, &xwa);
				printf("depth : %d\n", xwa.depth);
			}
			else
			{
				//m_clipRectが変更された場合子ウィンドウもそれに合わせて変更する
				::XMoveResizeWindow(display, grabWindow,
					m_clipRect->x, m_clipRect->y, m_clipRect->w, m_clipRect->h);
			}

			::XGrabPointer(display, parent, True, 0,
				GrabModeAsync, GrabModeAsync, grabWindow, None, CurrentTime);

			m_grabbing = true;
		}
		else
		{
			if(m_grabbing == true)
			{
				Display* display = ::glfwGetX11Display();
				::XUngrabPointer(display, CurrentTime);
				::XDestroyWindow(display, grabWindow);
				m_grabbing = false;
			}
		}

		double clientX, clientY;
		::glfwGetCursorPos(m_glfwWindow, &clientX, &clientY);
		m_clientPos.set(static_cast<int32>(clientX), static_cast<int32>(clientY));
		m_previousClientPos = m_clientPos;

		m_screenPos.set(static_cast<int32>(clientX), static_cast<int32>(clientY));
		m_previousScreenPos = m_screenPos;
	}

	const Point& CCursor_Linux::previousScreenPos() const
	{
		return m_previousScreenPos;
	}

	const Point& CCursor_Linux::screenPos() const
	{
		return m_screenPos;
	}

	const Point& CCursor_Linux::screenDelta() const
	{
		return m_screenDelta;
	}

	const Point& CCursor_Linux::previousClientPos() const
	{
		return m_previousClientPos;
	}

	const Point& CCursor_Linux::clientPos() const
	{
		return m_previousClientPos;
	}

	const Point& CCursor_Linux::clientDelta() const
	{
		return m_clientDelta;
	}

	void CCursor_Linux::setPos(const int32 x, const int32 y)
	{
		::glfwSetCursorPos(m_glfwWindow, x, y);
	}

	void CCursor_Linux::clip(const Optional<Rect>& rect)
	{
		m_clipRect = rect;
	}
}

# endif
