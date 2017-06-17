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
		m_previousClientPos_raw = m_screenPos;
		m_screenDelta.set(0, 0);

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
		m_clientPos_raw.set(clientPos.x, clientPos.y);
		m_previousClientPos_raw = m_clientPos_raw;

		m_clientPos_transformedVec2			= m_transformInv.transform(m_clientPos_raw);
		m_previousClientPos_transformedVec2	= m_transformInv.transform(m_previousClientPos_raw);
		
		m_clientPos_transformedPoint			= m_clientPos_transformedVec2.asPoint();
		m_previousClientPos_transformedPoint	= m_previousClientPos_transformedVec2.asPoint();

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
		return m_previousClientPos_transformedPoint;
	}

	const Point& CCursor_Windows::clientPos() const
	{
		return m_previousClientPos_transformedPoint;
	}

	Point CCursor_Windows::clientDelta() const
	{
		return m_clientPos_transformedPoint - m_previousClientPos_transformedPoint;
	}

	const Vec2& CCursor_Windows::previousClientPosF() const
	{
		return m_previousClientPos_transformedVec2;
	}

	const Vec2& CCursor_Windows::clientPosF() const
	{
		return m_previousClientPos_transformedVec2;
	}

	Vec2 CCursor_Windows::clientDeltaF() const
	{
		return m_clientPos_transformedVec2 - m_previousClientPos_transformedVec2;
	}

	void CCursor_Windows::setPos(const int32 x, const int32 y)
	{
		POINT point{ x, y };
		::ClientToScreen(m_hWnd, &point);
		::SetCursorPos(point.x, point.y);
		
		m_clientPos_raw.set(x, y);
		m_screenPos.set(point.x, point.y);

		m_clientPos_transformedVec2		= m_transformInv.transform(m_clientPos_raw);
		m_clientPos_transformedPoint	= m_clientPos_transformedVec2.asPoint();
	}

	void CCursor_Windows::setTransform(const Mat3x2& matrix)
	{
		if (!::memcmp(&m_transform, &matrix, sizeof(Mat3x2)))
		{
			return;
		}

		m_transform = matrix;
		m_transformInv = m_transform.inverse();

		m_clientPos_transformedVec2			= m_transformInv.transform(m_clientPos_raw);
		m_previousClientPos_transformedVec2	= m_transformInv.transform(m_previousClientPos_raw);
		
		m_clientPos_transformedPoint			= m_clientPos_transformedVec2.asPoint();
		m_previousClientPos_transformedPoint	= m_previousClientPos_transformedVec2.asPoint();
	}

	const Mat3x2& CCursor_Windows::getTransform() const
	{
		return m_transform;
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
