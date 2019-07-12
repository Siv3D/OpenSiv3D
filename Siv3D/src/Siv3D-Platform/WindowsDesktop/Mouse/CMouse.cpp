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
# include <Keyboard/IKeyboard.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CMouse.hpp"

namespace s3d
{
	namespace detail
	{
		constexpr uint32 buttonIndex[6] = { 1, 2, 4, 5, 6 };
	}

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

		m_hWnd = static_cast<HWND>(Siv3DEngine::Get<ISiv3DWindow>()->getHandle());

		if (::GetSystemMetrics(SM_DIGITIZER) & NID_MULTI_INPUT)
		{
			LOG_INFO(U"ℹ️ An input digitizer with support for multiple inputs found");

			::RegisterTouchWindow(m_hWnd, TWF_WANTPALM);

			m_touchAvailable = true;
		}

		LOG_INFO(U"ℹ️ CMouse initialized");
	}

	void CMouse::update()
	{
		const auto keyboard = Siv3DEngine::Get<ISiv3DKeyboard>();

		for (size_t i = 0; i < std::size(detail::buttonIndex); ++i)
		{
			if (i == 0)
			{
				std::lock_guard lock(m_touchMutex);

				const bool pressed = keyboard->pressed(detail::buttonIndex[i]) || m_primaryTouchPos.has_value();

				m_states[i].update(pressed);
			}
			else
			{
				const bool pressed = keyboard->pressed(detail::buttonIndex[i]);

				m_states[i].update(pressed);
			}
		}

		{
			std::lock_guard lock(m_scrollMutex);

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

	void CMouse::onMouseButtonUpdated(int32, bool)
	{

	}

	void CMouse::onTouchInput(const Array<TOUCHINPUT>& touchInputs)
	{
		std::lock_guard lock(m_touchMutex);

		for (size_t i = 0; i < touchInputs.size(); ++i)
		{
			if (!m_currentPrimaryTouchID && !(touchInputs[i].dwFlags & TOUCHEVENTF_UP))
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
					const POINT screenPos = { touchInput.x / 100, touchInput.y / 100 };

					m_primaryTouchPos.emplace(screenPos.x, screenPos.y);
				}
			}
		}
	}

	Optional<Point> CMouse::getPrimaryTouchPos()
	{
		std::lock_guard lock(m_touchMutex);

		return m_primaryTouchPos;
	}
}
