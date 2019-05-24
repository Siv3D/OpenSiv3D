//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3DEngine.hpp>
# include <Window/IWindow.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CMouse.hpp"

namespace s3d
{
	CMouse::CMouse()
	{

	}

	CMouse::~CMouse()
	{
		LOG_TRACE(U"CMouse::~CMouse()");
	}

	void CMouse::init()
	{
		LOG_TRACE(U"CMouse::init()");

		m_glfwWindow = static_cast<GLFWwindow*>(Siv3DEngine::Get<ISiv3DWindow>()->getHandle());
		
		m_buttonsInternal.fill(MouseButtonState::Released);
		
		::glfwSetScrollCallback(m_glfwWindow, OnScroll);
		
		::glfwSetMouseButtonCallback(m_glfwWindow, OnMouseButtonUpdated);

		LOG_INFO(U"ℹ️ CMouse initialized");
	}

	void CMouse::update()
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

	bool CMouse::down(const uint32 index) const
	{
		return m_states[index].down;
	}

	bool CMouse::pressed(const uint32 index) const
	{
		return m_states[index].pressed;
	}

	bool CMouse::up(const uint32 index) const
	{
		return m_states[index].up;
	}

	Duration CMouse::pressedDuration(const uint32 index) const
	{
		return m_states[index]._pressedDuration;
	}
	
	const Vec2& CMouse::wheel() const
	{
		return m_scroll;
	}
	
	void CMouse::onScroll(const double v, const double h)
	{
		std::lock_guard lock(m_scrollMutex);
		
		m_scrollInternal.moveBy(h, v);
	}

	void CMouse::onMouseButtonUpdated(const int32 index, const bool pressed)
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
	
	void CMouse::OnScroll(GLFWwindow*, const double h, const double v)
	{
		Siv3DEngine::Get<ISiv3DMouse>()->onScroll(h, -v);
	}
	
	void CMouse::OnMouseButtonUpdated(GLFWwindow*, const int button, const int action, int)
	{
		Siv3DEngine::Get<ISiv3DMouse>()->onMouseButtonUpdated(button, (action == GLFW_PRESS));
	}
}
