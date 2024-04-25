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
# include <Siv3D/Unicode.hpp>
# include <Siv3D/UserAction.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/UserAction/IUserAction.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Keyboard/FallbackKeyName.hpp>
# include "CKeyboard.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static String GetKeyName(const uint32 vk)
		{
			uint32 scanCode = ::MapVirtualKeyW(vk, MAPVK_VK_TO_VSC);

			if (scanCode)
			{
				switch (vk)
				{
				case VK_PRIOR:
				case VK_NEXT:
				case VK_END:
				case VK_HOME:
				case VK_LEFT:
				case VK_UP:
				case VK_RIGHT:
				case VK_DOWN:
				case VK_INSERT:
				case VK_DELETE:
				case VK_DIVIDE:
				case VK_NUMLOCK:
					scanCode |= 0x100;
					break;
				}
			}

			wchar_t buffer[128] = {};

			if (const int length = ::GetKeyNameTextW(static_cast<LONG>(scanCode << 16), buffer, _countof(buffer)))
			{
				return Unicode::FromWstring(std::wstring_view{ buffer, static_cast<size_t>(length) });
			}
			else if (detail::FallbackKeyNames[vk])
			{
				return String{ detail::FallbackKeyNames[vk] };
			}
			else
			{
				return U"{:#04x}"_fmt(vk);
			}
		}
	}

	CKeyboard::CKeyboard()
	{

	}

	CKeyboard::~CKeyboard()
	{
		LOG_SCOPED_TRACE(U"CKeyboard::~CKeyboard()");
	}

	void CKeyboard::init()
	{
		LOG_SCOPED_TRACE(U"CKeyboard::init()");

		m_hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());

		for (uint32 vk = 0; vk < m_names.size(); ++vk)
		{
			m_names[vk] = detail::GetKeyName(vk);
		}
	}

	void CKeyboard::update()
	{
		if (not m_inputAttached)
		{
			if (not ::AttachThreadInput(::GetWindowThreadProcessId(m_hWnd, nullptr), ::GetCurrentThreadId(), TRUE))
			{
				LOG_ERROR(U"✖ AttachThreadInput() failed");
			}

			m_inputAttached = true;
		}

		{
			std::lock_guard lock{ m_eventMutex };

			if (100 < m_events.size())
			{
				m_events.erase(m_events.begin(), m_events.begin() + (m_events.size() - 100));
			}
		}

		const bool windowFocused = SIV3D_ENGINE(Window)->getState().focused;

		{
			m_allInputs.clear();

			if (uint8 buf[256] = {};
				::GetKeyboardState(buf))
			{
				static_assert(InputState::KeyCount == _countof(buf));

				for (size_t i = 0; i < _countof(buf); ++i)
				{
					const bool pressed = (windowFocused && ((buf[i] >> 7) & 0x1));

					auto& state = m_states[i];
					state.update(pressed);

					if ((state.pressed() || state.up())
						&& InRange<size_t>(i, VK_BACK, 0xEF))
					{
						m_allInputs.emplace_back(InputDeviceType::Keyboard, static_cast<uint8>(i));
					}
				}
			}
		}

		if (windowFocused)
		{
			if (m_states[VK_ESCAPE].down())
			{
				SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::AnyKeyDown | UserAction::EscapeKeyDown);
			}
			else
			{
				for (const auto& input : m_allInputs)
				{
					if (input.down())
					{
						SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::AnyKeyDown);
						break;
					}
				}
			}

			for (uint32 vk = VK_LBUTTON; vk <= VK_XBUTTON2; ++vk)
			{
				if (m_states[vk].down())
				{
					SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::MouseButtonDown);
					break;
				}
			}
		}
	}

	bool CKeyboard::down(const uint32 index) const
	{
		assert(index < InputState::KeyCount);
		return m_states[index].down();
	}

	bool CKeyboard::pressed(const uint32 index) const
	{
		assert(index < InputState::KeyCount);
		return m_states[index].pressed();
	}

	bool CKeyboard::up(const uint32 index) const
	{
		assert(index < InputState::KeyCount);
		return m_states[index].up();
	}

	void CKeyboard::clearInput(const uint32 index)
	{
		assert(index < InputState::KeyCount);
		m_states[index].clearInput();
	}

	bool CKeyboard::cleared(const uint32 index) const
	{
		assert(index < InputState::KeyCount);
		return m_states[index].cleared();
	}

	Duration CKeyboard::pressedDuration(const uint32 index) const
	{
		assert(index < InputState::KeyCount);
		return m_states[index].pressedDuration;
	}

	const String& CKeyboard::name(const uint32 index) const
	{
		assert(index < InputState::KeyCount);
		return m_names[index];
	}

	const Array<Input>& CKeyboard::getAllInput() const noexcept
	{
		return m_allInputs;
	}

	Array<KeyEvent> CKeyboard::getEvents() const noexcept
	{
		std::lock_guard lock{ m_eventMutex };

		return m_events;
	}

	void CKeyboard::onKeyEvent(const uint8 code, const bool down, const bool up)
	{
		std::lock_guard lock{ m_eventMutex };

		m_events.emplace_back(Time::GetMillisec(), ++m_eventIndex, code, down, up);
	}
}
