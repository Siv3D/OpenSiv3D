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

# include <Siv3D/EngineError.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Monitor.hpp>
# include <Siv3D/Graphics.hpp>
# include <Siv3D/UserAction.hpp>
# include <Siv3DEngine.hpp>
# include <System/ISystem.hpp>
# include <Profiler/IProfiler.hpp>
# include <Graphics/IGraphics.hpp>
# include "CWindow.hpp"

namespace s3d
{
	namespace detail
	{
		void SetFullscreen(GLFWwindow* window, const Size& size)
		{
			int32 numMonitors;
			GLFWmonitor** monitors = ::glfwGetMonitors(&numMonitors);
			const size_t currentIndex = System::GetCurrentMonitorIndex();
			::glfwSetWindowMonitor(window, monitors[currentIndex], 0, 0, size.x, size.y, GLFW_DONT_CARE);
		}
		
		bool CheckFullscreenSize(const Size& size)
		{
			const Array<DisplayOutput> outputs = Graphics::EnumOutputs();
			const size_t currentIndex = System::GetCurrentMonitorIndex();
			
			if (currentIndex >= outputs.size())
			{
				return false;
			}
			
			for (const auto& displayMode : outputs[currentIndex].displayModes)
			{
				if (displayMode.size == size)
				{
					return true;
				}
			}
			
			return false;
		}
	}
	
	CWindow::CWindow()
	{

	}

	CWindow::~CWindow()
	{
		LOG_TRACE(U"CWindow::~CWindow()");
		
		::glfwTerminate();
	}

	void CWindow::init()
	{
		LOG_TRACE(U"CWindow::init()");
		
		::glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
		
		if (!::glfwInit())
		{
			throw EngineError(U"glfwInit() failed");
		}

		::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		::glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, Platform::DebugBuild ? GLFW_TRUE : GLFW_FALSE);
		::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_window = ::glfwCreateWindow(m_state.clientSize.x, m_state.clientSize.y,
									  m_titleText.narrow().c_str(), nullptr, nullptr);
		
		if (!m_window)
		{
			throw EngineError(U"glfwCreateWindow() failed. [OpenGL 4.1 is not supported]");
		}
		
		::glfwSetWindowSizeLimits(m_window, m_state.minimumSize.x, m_state.minimumSize.y, GLFW_DONT_CARE, GLFW_DONT_CARE);
		::glfwSetWindowUserPointer(m_window, this);
		::glfwSetWindowPosCallback(m_window, CWindow::OnMove);
		::glfwSetWindowSizeCallback(m_window, CWindow::OnResize);
		::glfwSetWindowIconifyCallback(m_window, CWindow::OnIconify);
		
		int32 windowPosX, windowPosY;
		::glfwGetWindowPos(m_window, &windowPosX, &windowPosY);
		m_state.bounds.pos.set(windowPosX, windowPosY);
		
		int32 windowSizeX, windowSizeY;
		::glfwGetWindowSize(m_window, &windowSizeX, &windowSizeY);
		m_state.bounds.size.set(windowSizeX, windowSizeY);
		
		float xScale, yScale;
		::glfwGetWindowContentScale(m_window, &xScale, &yScale);
		m_state.contentScale = std::max(xScale, yScale);
		
		int frameBufferWidth, frameBufferHeight;
		::glfwGetFramebufferSize(m_window, &frameBufferWidth, &frameBufferHeight);
		
		LOG_TRACE(U"Window bounds: {}"_fmt(m_state.bounds));
		LOG_TRACE(U"FrameBuffer size: {}"_fmt(Size(frameBufferWidth, frameBufferHeight)));
		
		::glfwMakeContextCurrent(m_window);
		::glfwSwapInterval(1);
		
		LOG_INFO(U"ℹ️ CWindow initialized");
	}

	void CWindow::show(const bool)
	{

		
	}

	void CWindow::update()
	{
		if constexpr (Platform::DebugBuild)
		{
			const String statistics = Siv3DEngine::Get<ISiv3DProfiler>()->getSimpleStatistics();
			const String titleText = m_title + U" (Debug Build) | " + statistics;
			
			if (titleText != m_titleText)
			{
				m_titleText = titleText;
				::glfwSetWindowTitle(m_window, m_titleText.narrow().c_str());
			}
		}
		
		doResizeBackBuffer();
		doToggleFullscreen();
		
		::glfwPollEvents();
		
		if (::glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			Siv3DEngine::Get<ISiv3DSystem>()->reportUserActions(UserAction::AnyKeyDown | UserAction::EscapeKeyDown);
		}
		
		if (::glfwGetWindowAttrib(m_window, GLFW_FOCUSED) == GLFW_FALSE)
		{
			Siv3DEngine::Get<ISiv3DSystem>()->reportUserActions(UserAction::WindowDeactivated);
			//m_state.focused = false;
		}
		else
		{
			//m_state.focused = true;
		}
		
		if (::glfwWindowShouldClose(m_window))
		{
			Siv3DEngine::Get<ISiv3DSystem>()->reportUserActions(UserAction::CloseButtonClicked);

			::glfwSetWindowShouldClose(m_window, GLFW_FALSE);
		}
		
		float xScale, yScale;
		::glfwGetWindowContentScale(m_window, &xScale, &yScale);
		m_state.contentScale = std::max(xScale, yScale);

		if ((m_scaleMode == ScaleMode::ResizeFill) && (m_state.bounds.size != Siv3DEngine::Get<ISiv3DGraphics>()->getSceneSize()))
		{
			Siv3DEngine::Get<ISiv3DGraphics>()->setSceneSize(m_state.bounds.size);
		}
	}

	void CWindow::setWindowTitle(const String& title)
	{
		if (m_title != title)
		{
			if constexpr (Platform::DebugBuild)
			{
				const String statistics = Siv3DEngine::Get<ISiv3DProfiler>()->getSimpleStatistics();
				m_titleText = title + U" (Debug Build) | " + statistics;
			}
			else
			{
				m_titleText = title;
			}

			m_title = title;

			::glfwSetWindowTitle(m_window, m_titleText.narrow().c_str());
		}
	}

	const String& CWindow::getWindowTitle() const
	{
		return m_title;
	}

	void CWindow::updateWindowBounds(const Rect&)
	{
		// do nothing
	}

	WindowState CWindow::getWindowState() const
	{
		return m_state;
	}

	void CWindow::setScaleMode(const ScaleMode scaleMode)
	{
		m_scaleMode = scaleMode;
	}

	ScaleMode CWindow::getScaleMode() const
	{
		return m_scaleMode;
	}

	void CWindow::setStyle(const WindowStyle style)
	{
		if (m_state.fullscreen)
		{
			m_state.style = style;
			setFullscreen(false, unspecified);
			return;
		}

		if (m_state.style == style)
		{
			return;
		}

		if (style == WindowStyle::Fixed)
		{
			::glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, GLFW_FALSE);
			::glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_TRUE);
		}
		else if (style == WindowStyle::Sizable)
		{
			::glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, GLFW_TRUE);
			::glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_TRUE);
		}
		else if (style == WindowStyle::Frameless)
		{
			::glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, GLFW_FALSE);
			::glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_FALSE);
		}
		
		m_state.style = style;
	}

	Size CWindow::getClientSize() const
	{
		return m_state.clientSize;
	}

	Rect CWindow::getWindowBounds() const
	{
		return m_state.bounds;
	}

	void CWindow::setPos(const Point& pos)
	{
		if (m_state.fullscreen)
		{
			return;
		}

		::glfwSetWindowPos(m_window, pos.x, pos.y);
	}

	bool CWindow::resizeClient(const Size& size, const WindowResizeOption option, const bool centering)
	{
		if ((option == WindowResizeOption::ResizeSceneSize)
			|| ((option == WindowResizeOption::UseDefaultScaleMode) && (m_scaleMode == ScaleMode::ResizeFill)))
		{
			Siv3DEngine::Get<ISiv3DGraphics>()->setSceneSize(size);
		}

		if (size == Siv3DEngine::Get<ISiv3DGraphics>()->getBackBufferSize())
		{
			return true;
		}

		LOG_TRACE(U"CWindow::resizeClient(size = {})"_fmt(size));

		const Size newSize(std::max(size.x, m_state.minimumSize.x), std::max(size.y, m_state.minimumSize.y));

		::glfwSetWindowSize(m_window, newSize.x, newSize.y);

		Siv3DEngine::Get<ISiv3DGraphics>()->clear();

		if (centering)
		{
			if (const auto monitors = System::EnumerateActiveMonitors())
			{
				const Rect workArea = monitors[System::GetCurrentMonitorIndex()].workArea;
				const s3d::Size windowSize = m_state.bounds.size;

				Point pos = workArea.pos + (workArea.size - windowSize) / 2;

				if (pos.y < 0)
				{
					pos.y = 0;
				}
				
				setPos(pos);
			}
		}

		return true;
	}

	void CWindow::maximize()
	{
		::glfwMaximizeWindow(m_window);
	}
	
	void CWindow::restore()
	{
		::glfwRestoreWindow(m_window);
	}

	void CWindow::minimize()
	{
		::glfwIconifyWindow(m_window);
	}

	bool CWindow::setFullscreen(const bool fullscreen, const Optional<Size>& fullscreenResolution)
	{
		LOG_TRACE(U"CWindow::setFullscreen({})"_fmt(fullscreen));
		
		if (!m_state.fullscreen) // Windowed
		{
			if (!fullscreen) // to Windowed
			{
				return false;
			}
			
			if (!fullscreenResolution)
			{
				const size_t currentIndex = System::GetCurrentMonitorIndex();
				const Size size = System::EnumerateActiveMonitors()[currentIndex].displayRect.size;
				
				m_storedWindowRect = m_state.bounds;
				detail::SetFullscreen(m_window, size);
				m_state.fullscreen = true;
				return true;
			}
			
			const Size targetSize = fullscreenResolution.value();
			
			if (!detail::CheckFullscreenSize(targetSize))
			{
				return false;
			}
		
			m_storedWindowRect = m_state.bounds;
			detail::SetFullscreen(m_window, targetSize);
			m_state.fullscreen = true;
			return true;
		}
		else // Fullscreen
		{
			if (!fullscreen) // to Windowed
			{
				::glfwSetWindowMonitor(m_window, nullptr, m_storedWindowRect.x, m_storedWindowRect.y,
									   m_storedWindowRect.w, m_storedWindowRect.h, GLFW_DONT_CARE);
				m_state.fullscreen = false;
				return true;
			}
			
			if (!fullscreenResolution)
			{
				return true;
			}
			
			const Size targetSize = fullscreenResolution.value();
			
			if (!detail::CheckFullscreenSize(targetSize))
			{
				return false;
			}
			
			detail::SetFullscreen(m_window, targetSize);
			
			return true;
		}
	}

	void* CWindow::getHandle() const
	{
		return m_window;
	}
	
	bool CWindow::changeDisplayResolution(const Size&)
	{
		// [Siv3D ToDo]
		return (false);
	}

	void CWindow::requestBackBufferResizing(const Size& size, const bool minimized, const bool maximized)
	{
		LOG_TRACE(U"CWindow::requestBackBufferResizing()");

		if ((size != Siv3DEngine::Get<ISiv3DGraphics>()->getBackBufferSize()) && !minimized)
		{
			m_backBufferResizingRequest = size;
			LOG_TRACE(U"CWindow::m_backBufferResizingRequest = {}"_fmt(size));
		}

		if (!minimized)
		{
			m_state.clientSize = size;
		}

		m_state.minimized	= minimized;
		m_state.maximized	= maximized;
	}

	void CWindow::requestToggleFullscreen()
	{
		LOG_TRACE(U"CWindow::requestToggleFullscreen()");
		m_toggleFullscreenRequest = true;
	}

	void CWindow::doResizeBackBuffer()
	{
		if (!m_backBufferResizingRequest)
		{
			return;
		}

		const Size newBackBufferSize = m_backBufferResizingRequest.value();
		const Size currentSceneSize = Siv3DEngine::Get<ISiv3DGraphics>()->getSceneSize();
		const bool keepSceneSize = (m_scaleMode == ScaleMode::AspectFit);

		Siv3DEngine::Get<ISiv3DGraphics>()->resizeBuffers(newBackBufferSize, keepSceneSize ? currentSceneSize : newBackBufferSize);

		m_backBufferResizingRequest.reset();
	}

	void CWindow::doToggleFullscreen()
	{
		if (!m_toggleFullscreenRequest)
		{
			return;
		}

		LOG_TRACE(U"CWindow::doToggleFullscreen()");

		setFullscreen(!m_state.fullscreen, unspecified);
		
		m_toggleFullscreenRequest	= false;
	}
	
	void CWindow::OnMove(GLFWwindow* window, int x, int y)
	{
		CWindow* pWindow = static_cast<CWindow*>(::glfwGetWindowUserPointer(window));
		pWindow->m_state.bounds.setPos(x, y);
		
		LOG_TRACE(U"Window pos: {}"_fmt(pWindow->m_state.bounds.pos));
	}
	
	void CWindow::OnResize(GLFWwindow* window, int width, int height)
	{
		CWindow* pWindow = static_cast<CWindow*>(::glfwGetWindowUserPointer(window));
		pWindow->m_state.bounds.setSize(width, height);
		pWindow->m_state.clientSize.set(width, height);
		
		LOG_TRACE(U"Window size: {}"_fmt(pWindow->m_state.bounds.size));
	}
	
	void CWindow::OnIconify(GLFWwindow* window, int iconified)
	{
		CWindow* pWindow = static_cast<CWindow*>(::glfwGetWindowUserPointer(window));
		pWindow->m_state.minimized = (iconified == GLFW_TRUE);
		pWindow->m_state.maximized = false;
		
		LOG_TRACE(U"Window minimized: {}"_fmt(pWindow->m_state.minimized));
	}
}
