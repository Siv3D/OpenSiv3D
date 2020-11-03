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
# include <Siv3D/Image.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CCursor.hpp"

namespace s3d
{
	namespace detail
	{
		static Point CursorScreenPos_Linux(GLFWwindow* window)
		{
			::Window root, win;
			int wx, wy, rx, ry;
			unsigned int mask;

			::Display* display = ::glfwGetX11Display();
			::Window windowHandle = ::glfwGetX11Window(window);
			::XQueryPointer(display, windowHandle, &root, &win, &rx, &ry, &wx, &wy, &mask);

			return{ rx, ry };
		}
	
		static Vec2 GetClientCursorPos(GLFWwindow* window)
		{
			double clientX, clientY;
			::glfwGetCursorPos(window, &clientX, &clientY);
			return{ clientX, clientY };
		}
	}

	CCursor::CCursor()
	{

	}

	CCursor::~CCursor()
	{
		LOG_SCOPED_TRACE(U"CCursor::~CCursor()");

		m_customCursors.clear();

		for (auto& systemCursor : m_systemCursors)
		{
			::glfwDestroyCursor(systemCursor);
			systemCursor = nullptr;
		}
	}

	void CCursor::init()
	{
		LOG_SCOPED_TRACE(U"CCursor::init()");

		m_window = static_cast<GLFWwindow*>(SIV3D_ENGINE(Window)->getHandle());

		m_systemCursors[FromEnum(CursorStyle::Arrow)]			= ::glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::IBeam)]			= ::glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::Cross)]			= ::glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::Hand)]			= ::glfwCreateStandardCursor(GLFW_POINTING_HAND_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::NotAllowed)]		= ::glfwCreateStandardCursor(GLFW_NOT_ALLOWED_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::ResizeUpDown)]	= ::glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::ResizeLeftRight)]	= ::glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		m_systemCursors[FromEnum(CursorStyle::Hidden)]			= nullptr;

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

		const Vec2 clientPos = detail::GetClientCursorPos(m_window);
		const Point screenPos = detail::CursorScreenPos_Linux(m_window);
		
		const Vec2 frameBufferSize = SIV3D_ENGINE(Window)->getState().frameBufferSize;
		const Vec2 virtualSize = SIV3D_ENGINE(Window)->getState().virtualSize;
		const double uiScaling = (frameBufferSize.x / virtualSize.x);
		
		m_state.update(clientPos.asPoint(), clientPos / uiScaling, screenPos);

		{
			if (m_currentCursor != m_requestedCursor)
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
		
		Array pixels = image.asArray();
		GLFWimage cursorImage;
		cursorImage.width	= image.width();
		cursorImage.height	= image.height();
		cursorImage.pixels	= (uint8*)pixels.data();
		 
		if (GLFWcursor* cursor = ::glfwCreateCursor(&cursorImage, hotSpot.x, hotSpot.y))
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
}
