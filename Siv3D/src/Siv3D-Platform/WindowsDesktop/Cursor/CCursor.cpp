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

# include <cmath>
# include <Siv3DEngine.hpp>
# include <Window/IWindow.hpp>
# include <Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Graphics.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Time.hpp>
# include <Mouse/CMouse.hpp>
# include "CCursor.hpp"

namespace s3d
{
	CCursor::CCursor()
	{

	}

	CCursor::~CCursor()
	{
		LOG_TRACE(U"CCursor::~CCursor()");
	}

	void CCursor::init()
	{
		LOG_TRACE(U"CCursor::init()");

		m_hWnd = static_cast<HWND>(Siv3DEngine::Get<ISiv3DWindow>()->getHandle());

		m_cursorStyles[FromEnum(CursorStyle::Arrow)] = ::LoadCursorW(nullptr, IDC_ARROW);
		m_cursorStyles[FromEnum(CursorStyle::IBeam)] = ::LoadCursorW(nullptr, IDC_IBEAM);
		m_cursorStyles[FromEnum(CursorStyle::Cross)] = ::LoadCursorW(nullptr, IDC_CROSS);
		m_cursorStyles[FromEnum(CursorStyle::Hand)] = ::LoadCursorW(nullptr, IDC_HAND);
		m_cursorStyles[FromEnum(CursorStyle::NotAllowed)] = ::LoadCursorW(nullptr, IDC_NO);
		m_cursorStyles[FromEnum(CursorStyle::ResizeUpDown)] = ::LoadCursorW(nullptr, IDC_SIZENS);
		m_cursorStyles[FromEnum(CursorStyle::ResizeLeftRight)] = ::LoadCursorW(nullptr, IDC_SIZEWE);
		m_cursorStyles[FromEnum(CursorStyle::Hidden)] = nullptr;

		::SetCursor(m_cursorStyles[0]);

		LOG_INFO(U"ℹ️ CCursor initialized");
	}

	void CCursor::update()
	{
		updateClip();

		const double dpiScaling = Graphics::GetDPIScaling();

		POINT screenPos;

		if (const auto touchPos = dynamic_cast<CMouse*>(Siv3DEngine::Get<ISiv3DMouse>())->getPrimaryTouchPos())
		{
			screenPos.x = touchPos->x;
			screenPos.y = touchPos->y;
		}
		else
		{
			::GetCursorPos(&screenPos);
		}

		POINT clientPos = screenPos;
		::ScreenToClient(m_hWnd, &clientPos);

		screenPos.x = static_cast<int32>(std::round(screenPos.x * dpiScaling));
		screenPos.y = static_cast<int32>(std::round(screenPos.y * dpiScaling));

		clientPos.x = static_cast<int32>(std::round(clientPos.x * dpiScaling));
		clientPos.y = static_cast<int32>(std::round(clientPos.y * dpiScaling));

		m_screen.update(screenPos.x, screenPos.y);
		m_client_raw.update(clientPos.x, clientPos.y);

		{
			if (Scene::GetScaleMode() == ScaleMode::AspectFit)
			{
				auto[s, viewRect] = Siv3DEngine::Get<ISiv3DRenderer2D>()->getLetterboxingTransform();
				m_transformScreen = Mat3x2::Scale(s).translated(viewRect.left, viewRect.top);
			}
			else
			{
				m_transformScreen = Mat3x2::Identity();
			}

			m_transformAll = m_transformLocal * m_transformCamera * m_transformScreen;
			m_transformAllInv = m_transformAll.inversed();
		}

		const Vec2 transformed = m_transformAllInv.transform(m_client_raw.current);
		m_client_transformedF.update(transformed.x, transformed.y);

		m_client_transformed.previous = m_client_transformedF.previous.asPoint();
		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();

		updateCursorStyle();

		{
			const uint64 time = Time::GetMillisec();
			{
				std::lock_guard lock(m_mutexMouseMove);
				
				if (m_buffer_internal)
				{
					m_buffer.append(m_buffer_internal);
					m_buffer_internal.clear();
				}
				else
				{
					m_buffer.emplace_back(m_client_raw.current, time);
				}
			}

			m_buffer.remove_if([=](const auto& info) { return (time - info.second) >= 1000; });
			m_bufferTransformed = m_buffer.map([=](std::pair<Point, uint64> info)
			{
				info.first = m_transformAllInv.transform(info.first).asPoint();
				return info;
			});
		}
	}

	void CCursor::onMouseMove(const int32 x, const int32 y)
	{
		std::lock_guard lock(m_mutexMouseMove);

		const uint64 time = Time::GetMillisec();

		m_buffer_internal.emplace_back(Point(x, y), time);
	}

	void CCursor::onAltPressed()
	{
		m_altPressed = true;
	}

	const CursorState<Point>& CCursor::screen() const
	{
		return m_screen;
	}

	const CursorState<Point>& CCursor::clientRaw() const
	{
		return m_client_raw;
	}

	const CursorState<Vec2>& CCursor::clientTransformedF() const
	{
		return m_client_transformedF;
	}

	const CursorState<Point>& CCursor::clientTransformed() const
	{
		return m_client_transformed;
	}

	const Array<std::pair<Point, uint64>>& CCursor::getBufferTransformed() const
	{
		return m_bufferTransformed;
	}

	void CCursor::setPos(const Point& pos)
	{
		const double dpiScaling = Graphics::GetDPIScaling();

		POINT point{ static_cast<int32>(pos.x / dpiScaling), static_cast<int32>(pos.y / dpiScaling) };
		::ClientToScreen(m_hWnd, &point);
		::SetCursorPos(point.x, point.y);

		m_screen.update(point.x, point.y);
		m_client_raw.update(pos.x, pos.y);

		const Vec2 transformed = m_transformAllInv.transform(m_client_raw.current);
		m_client_transformedF.update(transformed.x, transformed.y);

		m_client_transformed.previous = m_client_transformedF.previous.asPoint();
		m_client_transformed.current = m_client_transformedF.current.asPoint();
		m_client_transformed.delta = m_client_transformedF.delta.asPoint();
	}

	void CCursor::setLocalTransform(const Mat3x2& matrix)
	{
		if (m_transformLocal == matrix)
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

	void CCursor::setCameraTransform(const Mat3x2& matrix)
	{
		if (m_transformCamera == matrix)
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

	void CCursor::setScreenTransform(const Mat3x2& matrix)
	{
		if (m_transformScreen == matrix)
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

	const Mat3x2& CCursor::getLocalTransform() const
	{
		return m_transformLocal;
	}

	const Mat3x2& CCursor::getCameraTransform() const
	{
		return m_transformCamera;
	}

	const Mat3x2& CCursor::getScreenTransform() const
	{
		return m_transformScreen;
	}

	void CCursor::clipToWindow(const bool clip)
	{
		if (clip == m_clipToWindow)
		{
			return;
		}

		m_clipToWindow = clip;

		updateClip();
	}

	void CCursor::requestStyle(const CursorStyle style)
	{
		m_requestedCursorStyle = style;
	}

	void CCursor::setDefaultStyle(const CursorStyle style)
	{
		m_defaultCursorStyle = style;
	}

	void CCursor::applyStyleImmediately(const CursorStyle style)
	{
		m_curerntCursorStyle = style;

		::SetCursor(m_cursorStyles[FromEnum(style)]);
	}

	CursorStyle CCursor::getRequestedStyle() const
	{
		return m_requestedCursorStyle;
	}

	CursorStyle CCursor::getDefaultStyle() const
	{
		return m_defaultCursorStyle;
	}

	void CCursor::updateClip()
	{
		if (m_clipToWindow)
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

	void CCursor::updateCursorStyle()
	{
		if (m_altPressed)
		{
			m_curerntCursorStyle = CursorStyle::Default;
			m_altPressed = false;
		}

		if (!Cursor::OnClientRect())
		{
			m_curerntCursorStyle = CursorStyle::Default;
			return;
		}

		if (m_curerntCursorStyle != m_requestedCursorStyle)
		{
			m_curerntCursorStyle = m_requestedCursorStyle;
			::SetCursor(m_cursorStyles[FromEnum(m_curerntCursorStyle)]);
		}

		m_requestedCursorStyle = m_defaultCursorStyle;
	}
}
