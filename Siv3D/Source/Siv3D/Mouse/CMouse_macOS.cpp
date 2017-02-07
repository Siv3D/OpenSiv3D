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
# include "CMouse_macOS.hpp"

namespace s3d
{
	CMouse_macOS::CMouse_macOS()
	{

	}

	CMouse_macOS::~CMouse_macOS()
	{

	}

	bool CMouse_macOS::init()
	{
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();

		::glfwSetScrollCallback(m_glfwWindow, OnScroll);
		
		return true;
	}

	void CMouse_macOS::update()
	{
		for (uint32 i = 0; i < MouseButtonCount; ++i)
		{
			const bool pressed = (::glfwGetMouseButton(m_glfwWindow, i) == GLFW_PRESS);
	
			m_states[i].update(pressed);
		}
		
		{
			std::lock_guard<std::mutex> lock(m_scrollMutex);
		
			m_scroll = m_scrollInternal;
			
			m_scrollInternal.set(0, 0);
		}
	}
	
	bool CMouse_macOS::down(const uint32 index) const
	{
		return m_states[index].down;
	}
	
	bool CMouse_macOS::pressed(const uint32 index) const
	{
		return m_states[index].pressed;
	}
	
	bool CMouse_macOS::up(const uint32 index) const
	{
		return m_states[index].up;
	}

	MillisecondsF CMouse_macOS::pressedDuration(const uint32 index) const
	{
		return m_states[index].pressedDuration;
	}
	
	const Point& CMouse_macOS::wheel() const
	{
		return m_scroll;
	}
	
	void CMouse_macOS::onScroll(const int32 v, const int32 h)
	{
		std::lock_guard<std::mutex> lock(m_scrollMutex);
		
		m_scrollInternal.moveBy(v, h);
	}
	
	void CMouse_macOS::OnScroll(WindowHandle, double v, double h)
	{
		Siv3DEngine::GetMouse()->onScroll(static_cast<int32>(v * 10), static_cast<int32>(h * 10));
	}
}

# endif
