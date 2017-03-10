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
}

# endif
