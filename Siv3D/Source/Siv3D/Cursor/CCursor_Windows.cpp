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

		m_cursorStyles[size_t(CursorStyle::Arrow)] = ::LoadCursorW(nullptr, IDC_ARROW);
		m_cursorStyles[size_t(CursorStyle::IBeam)] = ::LoadCursorW(nullptr, IDC_IBEAM);
		m_cursorStyles[size_t(CursorStyle::Cross)] = ::LoadCursorW(nullptr, IDC_CROSS);
		m_cursorStyles[size_t(CursorStyle::Hand)] = ::LoadCursorW(nullptr, IDC_HAND);
		m_cursorStyles[size_t(CursorStyle::NotAllowed)] = ::LoadCursorW(nullptr, IDC_NO);
		m_cursorStyles[size_t(CursorStyle::ResizeUpDown)] = ::LoadCursorW(nullptr, IDC_SIZENS);
		m_cursorStyles[size_t(CursorStyle::ResizeLeftRight)] = ::LoadCursorW(nullptr, IDC_SIZEWE);
		m_cursorStyles[size_t(CursorStyle::Hidden)] = nullptr;

		::SetCursor(m_cursorStyles[0]);

		return true;
	}

	void CCursor_Windows::update()
	{
		updateClip();

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

		::SetCursor(m_cursorStyles[static_cast<size_t>(m_curerntCursorStyle)]);
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

	void CCursor_Windows::setPos(const int32 x, const int32 y)
	{
		POINT point{ x, y };
		::ClientToScreen(m_hWnd, &point);
		::SetCursorPos(point.x, point.y);
		
		m_clientPos.set(x, y);
		m_screenPos.set(point.x, point.y);
	}

	void CCursor_Windows::clipClientRect(const bool clip)
	{
		if (clip != m_clipClientRect)
		{
			updateClip();
		}

		m_clipClientRect = clip;
	}

	void CCursor_Windows::clip(const Optional<Rect>& rect)
	{
		m_clipRect = rect;
	}

	void CCursor_Windows::setStyle(const CursorStyle style)
	{
		if (style == m_curerntCursorStyle)
		{
			return;
		}

		::SetCursor(m_cursorStyles[static_cast<size_t>(style)]);

		m_curerntCursorStyle = style;
	}

	CursorStyle CCursor_Windows::getStyle()
	{
		return m_curerntCursorStyle;
	}

	void CCursor_Windows::updateClip()
	{
		if (m_clipRect)
		{
			POINT leftTop{ m_clipRect->x, m_clipRect->y };
			::ClientToScreen(m_hWnd, &leftTop);

			RECT clipRect{ leftTop.x, leftTop.y,
				leftTop.x + std::max(m_clipRect->w - 1, 0),
				leftTop.y + std::max(m_clipRect->h - 1, 0) };
			::ClipCursor(&clipRect);
		}
		else if (m_clipClientRect)
		{
			RECT clientRect;
			::GetClientRect(m_hWnd, &clientRect);

			POINT leftTop{ clientRect.left, clientRect.top };
			::ClientToScreen(m_hWnd, &leftTop);

			RECT clipRect{ leftTop.x, leftTop.y,
				leftTop.x + std::max<int32>(clientRect.right - 1, 0),
				leftTop.y + std::max<int32>(clientRect.bottom - 1, 0) };
			::ClipCursor(&clipRect);
		}
		else
		{
			::ClipCursor(nullptr);
		}
	}
}

# endif
