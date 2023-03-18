//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Common.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "CMouse.hpp"

namespace s3d
{
	CMouse::CMouse()
	{

	}

	CMouse::~CMouse()
	{
		LOG_SCOPED_TRACE(U"CMouse::~CMouse()");
	}

	void CMouse::init()
	{
		LOG_SCOPED_TRACE(U"CMouse::init()");

		m_window = static_cast<GLFWwindow*>(SIV3D_ENGINE(Window)->getHandle());

		m_buttonsInternal.fill(MouseButtonState::Released);

		if (m_window)
		{
			::glfwSetScrollCallback(m_window, OnScroll);
		
			::glfwSetMouseButtonCallback(m_window, OnMouseButtonUpdated);		
		}
	}

	void CMouse::update()
	{
		{
			std::lock_guard lock{ m_buttonMutex };
			
			for (uint32 i = 0; i < InputState::MouseButtonCount; ++i)
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
			std::lock_guard lock{ m_scrollMutex };
			
			m_scroll = std::exchange(m_scrollInternal, Vec2{ 0, 0 });
		}

		{
			m_allInputs.clear();

			for (uint32 i = 0; i < InputState::MouseButtonCount; ++i)
			{
				const auto& state = m_states[i];

				if (state.pressed() || state.up())
				{
					m_allInputs.emplace_back(InputDeviceType::Mouse, static_cast<uint8>(i));
				}
			}
		}
	}

	bool CMouse::down(const uint32 index) const
	{
		assert(index < InputState::MouseButtonCount);
		return m_states[index].down();
	}

	bool CMouse::pressed(const uint32 index) const
	{
		assert(index < InputState::MouseButtonCount);
		return m_states[index].pressed();
	}

	bool CMouse::up(const uint32 index) const
	{
		assert(index < InputState::MouseButtonCount);
		return m_states[index].up();
	}

	void CMouse::clearInput(const uint32 index)
	{
		assert(index < InputState::MouseButtonCount);
		m_states[index].clearInput();
	}

	bool CMouse::cleared(const uint32 index) const
	{
		assert(index < InputState::MouseButtonCount);
		return m_states[index].cleared();
	}

	Duration CMouse::pressedDuration(const uint32 index) const
	{
		assert(index < InputState::MouseButtonCount);
		return m_states[index].pressedDuration;
	}

	const Array<Input>& CMouse::getAllInput() const noexcept
	{
		return m_allInputs;
	}

	const Vec2& CMouse::wheel() const noexcept
	{
		return m_scroll;
	}

	void CMouse::onMouseButtonUpdated(const int32 index, const bool pressed)
	{
		std::lock_guard lock{ m_buttonMutex };
		
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

	void CMouse::onScroll(const double x, const double y)
	{
		std::lock_guard lock{ m_scrollMutex };
		
		m_scrollInternal.moveBy(x, y);
	}

	void CMouse::OnMouseButtonUpdated(GLFWwindow*, const int button, const int action, int)
	{
		SIV3D_ENGINE(Mouse)->onMouseButtonUpdated(button, (action == GLFW_PRESS));
	}

	void CMouse::OnScroll(GLFWwindow*, const double xOffset, const double yOffset)
	{
		SIV3D_ENGINE(Mouse)->onScroll(-xOffset, -yOffset);
	}
}
