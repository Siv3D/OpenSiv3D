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
# include "CCursor_Windows.hpp"
# include "../Mouse/CMouse_Windows.hpp"
# include <Siv3D/Logger.hpp>

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

		m_screen.previous = m_screen.current;
		m_client_raw.previous = m_client_raw.current;
		m_client_transformed.previous = m_client_transformed.current;
		m_client_transformedF.previous = m_client_transformedF.current;

		m_cursorStyles[size_t(CursorStyle::Arrow)] = ::LoadCursorW(nullptr, IDC_ARROW);
		m_cursorStyles[size_t(CursorStyle::IBeam)] = ::LoadCursorW(nullptr, IDC_IBEAM);
		m_cursorStyles[size_t(CursorStyle::Cross)] = ::LoadCursorW(nullptr, IDC_CROSS);
		m_cursorStyles[size_t(CursorStyle::Hand)] = ::LoadCursorW(nullptr, IDC_HAND);
		m_cursorStyles[size_t(CursorStyle::NotAllowed)] = ::LoadCursorW(nullptr, IDC_NO);
		m_cursorStyles[size_t(CursorStyle::ResizeUpDown)] = ::LoadCursorW(nullptr, IDC_SIZENS);
		m_cursorStyles[size_t(CursorStyle::ResizeLeftRight)] = ::LoadCursorW(nullptr, IDC_SIZEWE);
		m_cursorStyles[size_t(CursorStyle::Hidden)] = nullptr;

		::SetCursor(m_cursorStyles[0]);

		LOG_INFO(U"ℹ️ Cursor initialized");

		return true;
	}

	void CCursor_Windows::update()
	{
		updateClip();

		POINT screenPos;

		if (const auto touchPos = dynamic_cast<CMouse_Windows*>(Siv3DEngine::GetMouse())->getPrimaryTouchPos())
		{
			screenPos.x = touchPos->x;
			screenPos.y = touchPos->y;
		}
		else
		{
			::GetCursorPos(&screenPos);
		}
		
		m_screen.previous = m_screen.current;
		m_screen.current.set(screenPos.x, screenPos.y);
		m_screen.delta = m_screen.current - m_screen.previous;

		POINT clientPos = screenPos;
		::ScreenToClient(m_hWnd, &clientPos);
		m_client_raw.previous = m_client_raw.current;
		m_client_raw.current.set(clientPos.x, clientPos.y);
		m_client_raw.delta = m_client_raw.current - m_client_raw.previous;

		m_client_transformedF.previous = m_client_transformedF.current;
		m_client_transformedF.current = m_transformAllInv.transform(m_client_raw.current);
		m_client_transformedF.delta = m_client_transformedF.current - m_client_transformedF.previous;

		m_client_transformed.previous = m_client_transformedF.previous.asPoint();
		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();

		updateCursorStyle();
	}

	const CursorState<Point>& CCursor_Windows::screen() const
	{
		return m_screen;
	}

	const CursorState<Point>& CCursor_Windows::clientRaw() const
	{
		return m_client_raw;
	}

	const CursorState<Vec2>& CCursor_Windows::clientTransformedF() const
	{
		return m_client_transformedF;
	}

	const CursorState<Point>& CCursor_Windows::clientTransformed() const
	{
		return m_client_transformed;
	}

	void CCursor_Windows::setPos(const int32 x, const int32 y)
	{
		POINT point{ x, y };
		::ClientToScreen(m_hWnd, &point);
		::SetCursorPos(point.x, point.y);
		
		m_screen.current.set(point.x, point.y);
		m_screen.delta = m_screen.current - m_screen.previous;

		m_client_raw.current.set(x, y);
		m_client_raw.delta = m_client_raw.current - m_client_raw.previous;

		m_client_transformedF.current = m_transformAllInv.transform(m_client_raw.current);
		m_client_transformedF.delta = m_client_transformedF.current - m_client_transformedF.previous;

		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();
	}

	void CCursor_Windows::setTransformLocal(const Mat3x2& matrix)
	{
		if (!::memcmp(&m_transformLocal, &matrix, sizeof(Mat3x2)))
		{
			return;
		}

		m_transformLocal = matrix;

		m_transformAll = m_transformLocal * m_transformCamera * m_transformScreen;
		m_transformAllInv = m_transformAll.inversed();

		m_client_transformedF.previous = m_transformAllInv.transform(m_client_raw.previous);
		m_client_transformedF.current = m_transformAllInv.transform(m_client_raw.current);
		m_client_transformedF.delta = m_client_transformedF.current - m_client_transformedF.previous;

		m_client_transformed.previous = m_client_transformedF.previous.asPoint();
		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();
	}

	void CCursor_Windows::setTransformCamera(const Mat3x2& matrix)
	{
		if (!::memcmp(&m_transformCamera, &matrix, sizeof(Mat3x2)))
		{
			return;
		}

		m_transformCamera = matrix;

		m_transformAll = m_transformLocal * m_transformCamera * m_transformScreen;
		m_transformAllInv = m_transformAll.inversed();

		m_client_transformedF.previous = m_transformAllInv.transform(m_client_raw.previous);
		m_client_transformedF.current = m_transformAllInv.transform(m_client_raw.current);
		m_client_transformedF.delta = m_client_transformedF.current - m_client_transformedF.previous;

		m_client_transformed.previous = m_client_transformedF.previous.asPoint();
		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();
	}

	void CCursor_Windows::setTransformScreen(const Mat3x2& matrix)
	{
		if (!::memcmp(&m_transformScreen, &matrix, sizeof(Mat3x2)))
		{
			return;
		}

		m_transformScreen = matrix;

		m_transformAll = m_transformLocal * m_transformCamera * m_transformScreen;
		m_transformAllInv = m_transformAll.inversed();

		m_client_transformedF.previous = m_transformAllInv.transform(m_client_raw.previous);
		m_client_transformedF.current = m_transformAllInv.transform(m_client_raw.current);
		m_client_transformedF.delta = m_client_transformedF.current - m_client_transformedF.previous;

		m_client_transformed.previous = m_client_transformedF.previous.asPoint();
		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();
	}

	const Mat3x2& CCursor_Windows::getTransformLocal() const
	{
		return m_transformLocal;
	}

	const Mat3x2& CCursor_Windows::getTransformCamera() const
	{
		return m_transformCamera;
	}

	const Mat3x2& CCursor_Windows::getTransformScreen() const
	{
		return m_transformScreen;
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

	void CCursor_Windows::requestStyle(const CursorStyle style)
	{
		m_requestedCursorStyle = style;
	}

	void CCursor_Windows::setDefaultStyle(const CursorStyle style)
	{
		m_defaultCursorStyle = style;
	}

	void CCursor_Windows::applyStyleImmediately(const CursorStyle style)
	{
		m_curerntCursorStyle = style;

		::SetCursor(m_cursorStyles[static_cast<size_t>(style)]);
	}

	CursorStyle CCursor_Windows::getRequestedStyle()
	{
		return m_requestedCursorStyle;
	}

	CursorStyle CCursor_Windows::getDefaultStyle()
	{
		return m_defaultCursorStyle;
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

	void CCursor_Windows::updateCursorStyle()
	{
		if (!Cursor::OnClientRect())
		{
			m_curerntCursorStyle = CursorStyle::Default;

			return;
		}

		if (m_curerntCursorStyle != m_requestedCursorStyle)
		{
			m_curerntCursorStyle = m_requestedCursorStyle;

			::SetCursor(m_cursorStyles[static_cast<size_t>(m_curerntCursorStyle)]);
		}

		m_requestedCursorStyle = m_defaultCursorStyle;
	}
}

# endif
