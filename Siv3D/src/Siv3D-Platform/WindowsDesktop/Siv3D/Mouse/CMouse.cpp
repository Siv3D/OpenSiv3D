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
# include <Siv3D/Keyboard/IKeyboard.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "CMouse.hpp"

namespace s3d
{
	namespace detail
	{
		constexpr std::array<uint32, 6> ButtonVKs = { 1, 2, 4, 5, 6 };
	}

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

		m_hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());

		if (::GetSystemMetrics(SM_DIGITIZER) & NID_MULTI_INPUT)
		{
			m_touchAvailable = true;
		}
	}

	void CMouse::update()
	{
		const auto keyboard = SIV3D_ENGINE(Keyboard);

		for (size_t i = 0; i < detail::ButtonVKs.size(); ++i)
		{
			bool pressed = keyboard->pressed(detail::ButtonVKs[i]);

			if (i == 0)
			{
				std::lock_guard lock{ m_touchMutex };

				pressed |= m_primaryTouchPos.has_value();
			}
			
			m_states[i].update(pressed);
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

	void CMouse::onMouseButtonUpdated(const int32, const bool)
	{
		// do nothing
	}

	void CMouse::onScroll(const double x, const double y)
	{
		std::lock_guard lock{ m_scrollMutex };

		m_scrollInternal.moveBy(x, y);
	}

	void CMouse::onTouchInput(const Array<TOUCHINPUT>& touchInputs)
	{
		std::lock_guard lock{ m_touchMutex };

		for (size_t i = 0; i < touchInputs.size(); ++i)
		{
			if (!m_currentPrimaryTouchID
				&& !(touchInputs[i].dwFlags & TOUCHEVENTF_UP))
			{
				m_currentPrimaryTouchID = touchInputs[i].dwID;
				break;
			}

			if (touchInputs[0].dwFlags & TOUCHEVENTF_UP)
			{
				m_currentPrimaryTouchID.reset();
			}
		}

		m_primaryTouchPos.reset();

		if (m_currentPrimaryTouchID)
		{
			for (const auto& touchInput : touchInputs)
			{
				if (touchInput.dwID == m_currentPrimaryTouchID)
				{
					const POINT screenPos{ touchInput.x / 100, touchInput.y / 100 };
					m_primaryTouchPos.emplace(screenPos.x, screenPos.y);
				}
			}
		}
	}

	Optional<Point> CMouse::getPrimaryTouchPos()
	{
		std::lock_guard lock{ m_touchMutex };

		return m_primaryTouchPos;
	}
}
