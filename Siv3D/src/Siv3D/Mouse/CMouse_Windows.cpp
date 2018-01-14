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
# if defined(SIV3D_TARGET_WINDOWS)

# include "../Siv3DEngine.hpp"
# include "../Window/IWindow.hpp"
# include "../Keyboard/IKeyboard.hpp"
# include "CMouse_Windows.hpp"
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		constexpr uint32 buttonIndex[6] = { 1, 2, 4, 5, 6 };
	}

	CMouse_Windows::CMouse_Windows()
	{

	}

	CMouse_Windows::~CMouse_Windows()
	{

	}

	bool CMouse_Windows::init()
	{
		m_hWnd = Siv3DEngine::GetWindow()->getHandle();

		if (::GetSystemMetrics(SM_DIGITIZER) & NID_MULTI_INPUT)
		{
			::RegisterTouchWindow(m_hWnd, TWF_WANTPALM);

			m_touchAvailable = true;
		}

		LOG_INFO(U"ℹ️ Mouse initialized");

		return true;
	}

	void CMouse_Windows::update()
	{
		const auto keyboard = Siv3DEngine::GetKeyboard();

		for (size_t i = 0; i < std::size(detail::buttonIndex); ++i)
		{
			if (i == 0)
			{
				std::lock_guard<std::mutex> lock(m_touchMutex);

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
			std::lock_guard<std::mutex> lock(m_scrollMutex);

			m_scroll = m_scrollInternal;

			m_scrollInternal.set(0.0, 0.0);
		}
	}

	bool CMouse_Windows::down(const uint32 index) const
	{
		return m_states[index].down;
	}

	bool CMouse_Windows::pressed(const uint32 index) const
	{
		return m_states[index].pressed;
	}

	bool CMouse_Windows::up(const uint32 index) const
	{
		return m_states[index].up;
	}

	MillisecondsF CMouse_Windows::pressedDuration(const uint32 index) const
	{
		return m_states[index].pressedDuration;
	}
	
	const Vec2& CMouse_Windows::wheel() const
	{
		return m_scroll;
	}
	
	void CMouse_Windows::onScroll(const double v, const double h)
	{
		std::lock_guard<std::mutex> lock(m_scrollMutex);
		
		m_scrollInternal.moveBy(h, v);
	}

	void CMouse_Windows::onTouchInput(const Array<TOUCHINPUT>& touchInputs)
	{
		std::lock_guard<std::mutex> lock(m_touchMutex);

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

	Optional<Point> CMouse_Windows::getPrimaryTouchPos()
	{
		std::lock_guard<std::mutex> lock(m_touchMutex);

		return m_primaryTouchPos;
	}
}

# endif
