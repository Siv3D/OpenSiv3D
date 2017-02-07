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
# if defined(SIV3D_TARGET_WINDOWS)

# include "../Siv3DEngine.hpp"
# include "../Window/IWindow.hpp"
# include "CCursor_Windows.hpp"

namespace s3d
{
	CCursor_Windows::CCursor_Windows()
	{

	}

	CCursor_Windows::~CCursor_Windows()
	{

	}

	bool CCursor_Windows::init()
	{
		m_hWnd = Siv3DEngine::GetWindow()->getHandle();

		update();

		m_previousScreenPos = m_screenPos;
		m_previousClientPos = m_screenPos;
		m_screenDelta.set(0, 0);
		m_clientDelta.set(0, 0);

		return true;
	}

	void CCursor_Windows::update()
	{
		POINT screenPos;

		::GetCursorPos(&screenPos);
		m_screenPos.set(screenPos.x, screenPos.y);
		m_screenDelta = m_screenPos - m_previousScreenPos;
		m_previousScreenPos = m_screenPos;

		POINT clientPos = screenPos;
		::ScreenToClient(m_hWnd, &clientPos);
		m_clientPos.set(clientPos.x, clientPos.y);
		m_clientDelta = m_clientPos - m_previousClientPos;
		m_previousClientPos = m_clientPos;
	}

	const Point& CCursor_Windows::previousScreenPos() const
	{
		return m_previousScreenPos;
	}

	const Point& CCursor_Windows::screenPos() const
	{
		return m_screenPos;
	}

	const Point& CCursor_Windows::screenDelta() const
	{
		return m_screenDelta;
	}

	const Point& CCursor_Windows::previousClientPos() const
	{
		return m_previousClientPos;
	}

	const Point& CCursor_Windows::clientPos() const
	{
		return m_previousClientPos;
	}

	const Point& CCursor_Windows::clientDelta() const
	{
		return m_clientDelta;
	}
}

# endif
