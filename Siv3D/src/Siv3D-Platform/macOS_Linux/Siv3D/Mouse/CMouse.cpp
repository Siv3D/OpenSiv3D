//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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

		m_hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());
	}

	void CMouse::update()
	{
		m_allInputs.clear();
	}

	bool CMouse::down(const uint32 index) const
	{
		assert(index < InputState::MouseButtonCount);
		return m_states[index].down;
	}

	bool CMouse::pressed(const uint32 index) const
	{
		assert(index < InputState::MouseButtonCount);
		return m_states[index].pressed;
	}

	bool CMouse::up(const uint32 index) const
	{
		assert(index < InputState::MouseButtonCount);
		return m_states[index].up;
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

	}

	void CMouse::onScroll(const double v, const double h)
	{

	}
}
