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
# include <Siv3D/Scene.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3DEngine.hpp>
# include <Window/IWindow.hpp>
# include <Renderer2D/IRenderer2D.hpp>
# include "CCursor.hpp"
# import  <Cocoa/Cocoa.h>

namespace s3d
{
	namespace detail
	{
		Point CursorScreenPos_macOS()
		{
			const int32 screenHeight = [[NSScreen mainScreen] frame].size.height;
			const NSPoint screenPos = [NSEvent mouseLocation];
			return Point(static_cast<int32>(screenPos.x), static_cast<int32>(screenHeight - screenPos.y));
		}
		
		void CursorSetPos_macOS(const int32 x, const int32 y)
		{
			CGPoint globalPos;
			globalPos.x = x;
			globalPos.y = y;
			CGWarpMouseCursorPosition(globalPos);
		}
		
		void CursorSetStyle_macOS(const CursorStyle style)
		{
			static id hiddenCursor;
			
			switch (style)
			{
				case CursorStyle::Arrow:
					[[NSCursor arrowCursor] set];
					break;
				case CursorStyle::IBeam:
					[[NSCursor IBeamCursor] set];
					break;
				case CursorStyle::Cross:
					[[NSCursor crosshairCursor] set];
					break;
				case CursorStyle::Hand:
					[[NSCursor pointingHandCursor] set];
					break;
				case CursorStyle::NotAllowed:
					[[NSCursor operationNotAllowedCursor] set];
					break;
				case CursorStyle::ResizeUpDown:
					[[NSCursor resizeUpDownCursor] set];
					break;
				case CursorStyle::ResizeLeftRight:
					[[NSCursor resizeLeftRightCursor] set];
					break;
				case CursorStyle::Hidden:
					if (hiddenCursor == nil)
					{
						NSImage* data = [[NSImage alloc] initWithSize:NSMakeSize(16, 16)];
						hiddenCursor = [[NSCursor alloc] initWithImage:data
															   hotSpot:NSZeroPoint];
						[data release];
					}
					[(NSCursor*) hiddenCursor set];
					break;
			}
		}
	}
	
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

		m_window = static_cast<GLFWwindow*>(Siv3DEngine::Get<ISiv3DWindow>()->getHandle());

		LOG_INFO(U"ℹ️ CCursor initialized");
	}

	void CCursor::update()
	{
		if (m_clipToWindow)
		{
			// [Siv3D ToDo]
		}
		
		const Point screenPos = detail::CursorScreenPos_macOS();
		double clientX, clientY;
		::glfwGetCursorPos(m_window, &clientX, &clientY);
		const Vec2 clientPos(clientX, clientY);
		
		m_screen.update(screenPos.x, screenPos.y);
		m_client_raw.update(clientPos.x, clientPos.y);
		
		{
			if (Scene::GetScaleMode() == ScaleMode::AspectFit)
			{
				auto[s, viewRect] = Siv3DEngine::Get<ISiv3DRenderer2D>()->getLetterboxingTransform();
				const double contentScale = Window::GetState().contentScale;
				m_transformScreen = Mat3x2::Scale(s / contentScale).translated(viewRect.left / contentScale, viewRect.top / contentScale);
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
		// do nothing
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
		const Point screenPos = pos + (m_screen.current - m_client_raw.current);
		detail::CursorSetPos_macOS(screenPos.x, screenPos.y);
		
		m_screen.update(screenPos.x, screenPos.y);
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
		
		detail::CursorSetStyle_macOS(style);
	}

	CursorStyle CCursor::getRequestedStyle() const
	{
		return m_requestedCursorStyle;
	}

	CursorStyle CCursor::getDefaultStyle() const
	{
		return m_defaultCursorStyle;
	}

	void CCursor::updateCursorStyle()
	{
		if (!Cursor::OnClientRect())
		{
			return;
		}
		
		/*
		if (m_requestedCursorStyle != m_defaultCursorStyle)
		{
			detail::CursorSetStyle_macOS(m_requestedCursorStyle);
		}
		else
		{
			detail::CursorSetStyle_macOS(m_defaultCursorStyle);
		}*/
		
		
		if (!Cursor::OnClientRect())
		{
			m_curerntCursorStyle = CursorStyle::Default;
			return;
		}
		
		if (m_curerntCursorStyle != m_requestedCursorStyle)
		{
			m_curerntCursorStyle = m_requestedCursorStyle;
			detail::CursorSetStyle_macOS(m_requestedCursorStyle);
		}
		else
		{
			// workaround
			detail::CursorSetStyle_macOS(m_requestedCursorStyle);
		}
		
		m_requestedCursorStyle = m_defaultCursorStyle;
	}
}
