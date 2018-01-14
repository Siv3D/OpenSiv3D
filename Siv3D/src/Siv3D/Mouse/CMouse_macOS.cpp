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
# include "CMouse_macOS.hpp"
# include <Siv3D/Logger.hpp>

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
		
		m_buttonsInternal.fill(MouseButtonState::Released);

		::glfwSetScrollCallback(m_glfwWindow, OnScroll);
		
		::glfwSetMouseButtonCallback(m_glfwWindow, OnMouseButtonUpdated);

		LOG_INFO(U"ℹ️ Mouse initialized");
		
		return true;
	}

	void CMouse_macOS::update()
	{
		{
			std::lock_guard<std::mutex> lock(m_buttonMutex);

			for (uint32 i = 0; i < MouseButtonCount; ++i)
			{
				auto& state = m_buttonsInternal[i];
				
				const bool pressed = (state == MouseButtonState::Pressed) || (state == MouseButtonState::Tapped);
	
				m_states[i].update(pressed);
				
				if (state == MouseButtonState::Tapped)
				{
					state = MouseButtonState::Released;
				}
			}
		}
		
		{
			std::lock_guard<std::mutex> lock(m_scrollMutex);
		
			m_scroll = m_scrollInternal;
			
			m_scrollInternal.set(0.0, 0.0);
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
	
	const Vec2& CMouse_macOS::wheel() const
	{
		return m_scroll;
	}
	
	void CMouse_macOS::onScroll(const double v, const double h)
	{
		std::lock_guard<std::mutex> lock(m_scrollMutex);
		
		m_scrollInternal.moveBy(v, h);
	}
	
	void CMouse_macOS::OnScroll(const WindowHandle, const double h, const double v)
	{
		Siv3DEngine::GetMouse()->onScroll(h, -v);
	}
	
	void CMouse_macOS::onMouseButtonUpdated(const int32 index, const bool pressed)
	{
		std::lock_guard<std::mutex> lock(m_buttonMutex);
		
		auto& state = m_buttonsInternal[index];
		
		if(state == MouseButtonState::Released)
		{
			if(pressed)
			{
				state = MouseButtonState::Pressed;
			}
		}
		else if(state == MouseButtonState::Pressed)
		{
			if(!pressed)
			{
				state = MouseButtonState::Tapped;
			}
		}
		else
		{
			if(pressed)
			{
				state = MouseButtonState::Pressed;
			}
		}
	}
	
	void CMouse_macOS::OnMouseButtonUpdated(WindowHandle, const int button, const int action, int)
	{
		Siv3DEngine::GetMouse()->onMouseButtonUpdated(button, (action == GLFW_PRESS));
	}
}

# endif
