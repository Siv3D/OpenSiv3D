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
# include "../Siv3DEngine.hpp"
# include "CMouse_Linux.hpp"
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CMouse_Linux::CMouse_Linux()
	{

	}

	CMouse_Linux::~CMouse_Linux()
	{

	}

	bool CMouse_Linux::init()
	{
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();

		::glfwSetScrollCallback(m_glfwWindow, OnScroll);

		LOG_INFO(U"ℹ️ Mouse initialized");

		return true;
	}

	void CMouse_Linux::update()
	{
		for (uint32 i = 0; i < MouseButtonCount; ++i)
		{
			const bool pressed = (::glfwGetMouseButton(m_glfwWindow, i) == GLFW_PRESS);
	
			m_states[i].update(pressed);
		}

		{
			std::lock_guard<std::mutex> lock(m_scrollMutex);

			m_scroll = m_scrollInternal;

			m_scrollInternal.set(0.0, 0.0);
		}
	}
	
	bool CMouse_Linux::down(const uint32 index) const
	{
		return m_states[index].down;
	}
	
	bool CMouse_Linux::pressed(const uint32 index) const
	{
		return m_states[index].pressed;
	}
	
	bool CMouse_Linux::up(const uint32 index) const
	{
		return m_states[index].up;
	}

	MillisecondsF CMouse_Linux::pressedDuration(const uint32 index) const
	{
		return m_states[index].pressedDuration;
	}

	const Vec2& CMouse_Linux::wheel() const
	{
		return m_scroll;
	}

	void CMouse_Linux::onScroll(const double v, const double h)
	{
		std::lock_guard<std::mutex> lock(m_scrollMutex);

		m_scrollInternal.moveBy(v, h);
	}

	void CMouse_Linux::OnScroll(const WindowHandle, const double h, const double v)
	{
		Siv3DEngine::GetMouse()->onScroll(h, -v);
	}
}

# endif
