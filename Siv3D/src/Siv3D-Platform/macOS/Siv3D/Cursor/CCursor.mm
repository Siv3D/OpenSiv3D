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
# include <Siv3D/Image.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CCursor.hpp"
# import  <Cocoa/Cocoa.h>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static Point GetScreenPos()
		{
			@autoreleasepool
			{
				NSScreen* mainScreen = [NSScreen mainScreen];
				const int32 screenHeight = [mainScreen frame].size.height;
				const float scaleFactor = [mainScreen backingScaleFactor];
				const float scaledHeight = (screenHeight * scaleFactor);
				const NSPoint screenPos = [NSEvent mouseLocation];
				return Vec2(screenPos.x * scaleFactor, scaledHeight - (screenPos.y * scaleFactor)).asPoint();
			}
		}
	
		[[nodiscard]]
		static Vec2 GetClientCursorPos(GLFWwindow* window)
		{
			double clientX, clientY;
			::glfwGetCursorPos(window, &clientX, &clientY);
			return{ clientX, clientY };
		}

		[[nodiscard]]
		static GLFWcursor* CreateCursor(const Image& image, const Point hotSpot)
		{
			Array pixels = image.asArray();
			GLFWimage cursorImage;
			cursorImage.width	= image.width();
			cursorImage.height	= image.height();
			cursorImage.pixels	= (uint8*)pixels.data();

			return ::glfwCreateCursor(&cursorImage, hotSpot.x, hotSpot.y);
		}
	}

	CCursor::CCursor()
		: m_systemCursors{}
	{

	}

	CCursor::~CCursor()
	{
		LOG_SCOPED_TRACE(U"CCursor::~CCursor()");
		
		m_customCursors.clear();

		for (auto& systemCursor : m_systemCursors)
		{
			if (systemCursor)
			{
				::glfwDestroyCursor(systemCursor);
				systemCursor = nullptr;
			}
		}
	}

	void CCursor::init()
	{
		LOG_SCOPED_TRACE(U"CCursor::init()");
		
		m_window = static_cast<GLFWwindow*>(SIV3D_ENGINE(Window)->getHandle());

		{
			const Vec2 clientPos = detail::GetClientCursorPos(m_window);
			const Point screenPos = detail::GetScreenPos();
			
			const Vec2 frameBufferSize = SIV3D_ENGINE(Window)->getState().frameBufferSize;
			const Vec2 virtualSize = SIV3D_ENGINE(Window)->getState().virtualSize;
			const double uiScaling = (frameBufferSize.x / virtualSize.x);
			
			m_state.update(clientPos.asPoint(), clientPos / uiScaling, screenPos);
		}

		m_systemCursors[FromEnum(CursorStyle::Arrow)]			= ::glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::IBeam)]			= ::glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::Cross)]			= ::glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::Hand)]			= ::glfwCreateStandardCursor(GLFW_POINTING_HAND_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::NotAllowed)]		= ::glfwCreateStandardCursor(GLFW_NOT_ALLOWED_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::ResizeUpDown)]	= ::glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::ResizeLeftRight)]	= ::glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::ResizeNWSE)]		= ::glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::ResizeNESW)]		= ::glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::ResizeAll)]		= ::glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::Hidden)]			= detail::CreateCursor(Image{ 16, 16, Color{ 0, 0 } }, Point::Zero());

		m_currentCursor		= m_systemCursors[FromEnum(CursorStyle::Arrow)];
		m_defaultCursor		= m_currentCursor;
		m_requestedCursor	= m_defaultCursor;
	}

	bool CCursor::update()
	{
		if (m_clipToWindow)
		{
			// [Siv3D ToDo]
		}

		{
			auto [s, viewRect]	= SIV3D_ENGINE(Renderer)->getLetterboxComposition();
			m_transformScreen	= Mat3x2::Scale(s).translated(viewRect.pos);
			m_transformAll		= (m_transformLocal * m_transformCamera * m_transformScreen);
			m_transformAllInv	= m_transformAll.inverse();
		}

		{
			const Vec2 clientRawPos = detail::GetClientCursorPos(m_window);
			const Point screenPos = detail::GetScreenPos();
			const Vec2 clientPos = m_transformAllInv.transformPoint(clientRawPos);

			m_state.update(clientRawPos.asPoint(), clientPos.asPoint(), screenPos);
		}
	
		{
			if (not Cursor::OnClientRect())
			{
				m_requestedCursor = m_systemCursors[FromEnum(CursorStyle::Arrow)];
			}
			
			{
				m_currentCursor = m_requestedCursor;

				::glfwSetCursor(m_window, m_currentCursor);
			}

			m_requestedCursor = m_defaultCursor;
		}
		
		return true;
	}

	const CursorState& CCursor::getState() const noexcept
	{
		return m_state;
	}

	void CCursor::setPos(const Point pos)
	{
		::glfwSetCursorPos(m_window, pos.x, pos.y);
	}

	const Mat3x2& CCursor::getLocalTransform() const noexcept
	{
		return m_transformLocal;
	}

	const Mat3x2& CCursor::getCameraTransform() const noexcept
	{
		return m_transformCamera;
	}

	const Mat3x2& CCursor::getScreenTransform() const noexcept
	{
		return m_transformScreen;
	}

	void CCursor::setLocalTransform(const Mat3x2& matrix)
	{
		if (m_transformLocal == matrix)
		{
			return;
		}

		m_transformLocal	= matrix;
		m_transformAll		= (m_transformLocal * m_transformCamera * m_transformScreen);
		m_transformAllInv	= m_transformAll.inverse();

		m_state.vec2.previous	= m_transformAllInv.transformPoint(m_state.raw.previous);
		m_state.vec2.current	= m_transformAllInv.transformPoint(m_state.raw.current);
		m_state.vec2.delta		= (m_state.vec2.current - m_state.vec2.previous);

		m_state.point.previous	= m_state.vec2.previous.asPoint();
		m_state.point.current	= m_state.vec2.current.asPoint();
		m_state.point.delta		= m_state.vec2.delta.asPoint();
	}

	void CCursor::setCameraTransform(const Mat3x2& matrix)
	{
		if (m_transformCamera == matrix)
		{
			return;
		}

		m_transformCamera	= matrix;
		m_transformAll		= (m_transformLocal * m_transformCamera * m_transformScreen);
		m_transformAllInv	= m_transformAll.inverse();

		m_state.vec2.previous	= m_transformAllInv.transformPoint(m_state.raw.previous);
		m_state.vec2.current	= m_transformAllInv.transformPoint(m_state.raw.current);
		m_state.vec2.delta		= (m_state.vec2.current - m_state.vec2.previous);

		m_state.point.previous	= m_state.vec2.previous.asPoint();
		m_state.point.current	= m_state.vec2.current.asPoint();
		m_state.point.delta		= m_state.vec2.delta.asPoint();
	}

	void CCursor::setScreenTransform(const Mat3x2& matrix)
	{
		if (m_transformScreen == matrix)
		{
			return;
		}

		m_transformScreen	= matrix;
		m_transformAll		= (m_transformLocal * m_transformCamera * m_transformScreen);
		m_transformAllInv	= m_transformAll.inverse();

		m_state.vec2.previous	= m_transformAllInv.transformPoint(m_state.raw.previous);
		m_state.vec2.current	= m_transformAllInv.transformPoint(m_state.raw.current);
		m_state.vec2.delta		= (m_state.vec2.current - m_state.vec2.previous);

		m_state.point.previous	= m_state.vec2.previous.asPoint();
		m_state.point.current	= m_state.vec2.current.asPoint();
		m_state.point.delta		= m_state.vec2.delta.asPoint();
	}

	bool CCursor::isClippedToWindow() const noexcept
	{
		return m_clipToWindow;
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
		m_requestedCursor = m_systemCursors[FromEnum(style)];
	}

	void CCursor::setDefaultStyle(const CursorStyle style)
	{
		m_defaultCursor = m_systemCursors[FromEnum(style)];
	}

	bool CCursor::registerCursor(const StringView name, const Image& image, const Point hotSpot)
	{
		if (m_customCursors.contains(name))
		{
			return false;
		}

		if (GLFWcursor* cursor = detail::CreateCursor(image, hotSpot))
		{
			m_customCursors.emplace(name, unique_resource{ cursor, CursorDeleter });
			return true;
		}
		else
		{
			return false;
		}
	}

	void CCursor::requestStyle(const StringView name)
	{
		if (auto it = m_customCursors.find(name);
			it != m_customCursors.end())
		{
			m_requestedCursor = it->second.get();
		}
	}

	void CCursor::setCapture(const bool captured) noexcept
	{
		m_captured = captured;
	}

	bool CCursor::isCaptured() const noexcept
	{
		return m_captured;
	}
}
