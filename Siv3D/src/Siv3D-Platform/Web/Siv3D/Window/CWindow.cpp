//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineOptions.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Utility.hpp>
# include <Siv3D/UserAction.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/Monitor.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/Profiler/IProfiler.hpp>
# include <Siv3D/UserAction/IUserAction.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "CWindow.hpp"

namespace s3d
{
	namespace detail
	{
		__attribute__((import_name("siv3dRequestFullscreen")))
		extern void siv3dRequestFullscreen();
		__attribute__((import_name("siv3dExitFullscreen")))
		extern void siv3dExitFullscreen();

		static void ErrorCallback(const int error, const char* description)
		{
			std::cerr << U"Error: {}. "_fmt(error) << description << '\n';
		}
	}

	CWindow::CWindow()
	{
	}

	CWindow::~CWindow()
	{
		LOG_SCOPED_TRACE(U"CWindow::~CWindow()");
		
		::glfwTerminate();
	}

	void CWindow::init()
	{
		LOG_SCOPED_TRACE(U"CWindow::init()");
		
		::glfwSetErrorCallback(detail::ErrorCallback);

		if (!::glfwInit())
		{
			throw EngineError(U"glfwInit() failed");
		}
		
		const bool useWebGPU =  (g_engineOptions.renderer == EngineOption::Renderer::WebGPU);

		if (useWebGPU)
		{
			// WebGPU
			::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		}
		else
		{
			// OpenGL ES 3.0
			::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
			::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			::glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, SIV3D_BUILD(DEBUG) ? GLFW_TRUE : GLFW_FALSE);
			
			::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}
	
		// ウィンドウを作成
		{
			m_window = ::glfwCreateWindow(m_state.virtualSize.x, m_state.virtualSize.y,
										  m_actualTitle.narrow().c_str(), nullptr, nullptr);
			
			if (!m_window)
			{
				throw EngineError(U"glfwCreateWindow() failed. Your browser seems not to support WebGL 2.0, please enable WebGL 2.0.");
			}
		}
		
		::glfwSetWindowSizeLimits(m_window, m_state.minFrameBufferSize.x, m_state.minFrameBufferSize.y,
								  GLFW_DONT_CARE, GLFW_DONT_CARE);
		::glfwSetWindowUserPointer(m_window, this);
		::glfwSetWindowPosCallback(m_window, CWindow::OnMove);
		::glfwSetWindowSizeCallback(m_window, CWindow::OnResize);
		::glfwSetFramebufferSizeCallback(m_window, CWindow::OnFrameBufferSize);
		// ::glfwSetWindowContentScaleCallback(m_window, CWindow::OnScalingChange);
		::glfwSetWindowIconifyCallback(m_window, CWindow::OnIconify);
		// ::glfwSetWindowMaximizeCallback(m_window, CWindow::OnMaximize);
		::glfwSetWindowFocusCallback(m_window, CWindow::OnFocus);
		
		updateState();
	}

	void CWindow::update()
	{
		::glfwPollEvents();
		
		updateState();

		if (::glfwWindowShouldClose(m_window))
		{
			SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::CloseButtonClicked);
			::glfwSetWindowShouldClose(m_window, GLFW_FALSE);
		}
		
		if constexpr (SIV3D_BUILD(DEBUG))
		{
			setWindowTitle(m_title);
		}
	}

	void CWindow::setWindowTitle(const String& title)
	{
		String newActualTitle = title;
		
		if constexpr (SIV3D_BUILD(DEBUG))
		{
			const String statistics = SIV3D_ENGINE(Profiler)->getSimpleStatistics();
			newActualTitle += U" (Debug Build) | ";
			newActualTitle += statistics;
		}

		if (m_actualTitle != newActualTitle)
		{
			::glfwSetWindowTitle(m_window, newActualTitle.narrow().c_str());
			m_actualTitle.swap(newActualTitle);
		}

		m_title = title;
	}

	const String& CWindow::getWindowTitle() const noexcept
	{
		return m_title;
	}

	void* CWindow::getHandle() const noexcept
	{
		return m_window;
	}

	const WindowState& CWindow::getState() const noexcept
	{
		return m_state;
	}

	void CWindow::setStyle(const WindowStyle style)
	{
		LOG_TRACE(U"CWindow::setStyle(style = {})"_fmt(FromEnum(style)));
		
		if (m_state.fullscreen)
		{
			m_state.style = style;
			//setFullscreen(false, unspecified, WindowResizeOption::KeepSceneSize);
			return;
		}

		if (m_state.style == style)
		{
			return;
		}

		// [Siv3DWeb NoSupport]
		// if (style == WindowStyle::Fixed)
		// {
		// 	::glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, GLFW_FALSE);
		// 	::glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_TRUE);
		// }
		// else if (style == WindowStyle::Sizable)
		// {
		// 	::glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, GLFW_TRUE);
		// 	::glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_TRUE);
		// }
		// else if (style == WindowStyle::Frameless)
		// {
		// 	::glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, GLFW_FALSE);
		// 	::glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_FALSE);
		// }

		m_state.style = style;
	}

	void CWindow::setPos(const Point& pos)
	{
		LOG_TRACE(U"CWindow::setPos(pos = {})"_fmt(pos));

		if (m_state.fullscreen)
		{
			return;
		}
		
		::glfwSetWindowPos(m_window, pos.x, pos.y + m_state.titleBarHeight);
	}

	void CWindow::maximize()
	{
		LOG_TRACE(U"CWindow::maximize()");

		if (m_state.style == WindowStyle::Fixed)
		{
			//LOG_FAIL(U"A window with WindowStyle::Fixed cannot be maximized");
			return;
		}
		
		::glfwMaximizeWindow(m_window);
	}

	void CWindow::restore()
	{
		LOG_TRACE(U"CWindow::restore()");
		::glfwRestoreWindow(m_window);
	}

	void CWindow::minimize()
	{
		LOG_TRACE(U"CWindow::minimize()");
		::glfwIconifyWindow(m_window);
	}

	bool CWindow::resizeByVirtualSize(const Size& virtualSize)
	{
		LOG_TRACE(U"CWindow::resizeByVirtualSize({})"_fmt(virtualSize));

		m_resizingWindow = true;
		{
			::glfwSetWindowSize(m_window, virtualSize.x, virtualSize.y);
		}
		m_resizingWindow = false;

		return true;
	}

	bool CWindow::resizeByFrameBufferSize(const Size& frameBufferSize)
	{
		LOG_TRACE(U"CWindow::resizeByFrameBufferSize({})"_fmt(frameBufferSize));
		
		const double scaling = m_state.scaling;
		const Size newVirtualSize = (frameBufferSize * (1.0 / scaling)).asPoint();
		return resizeByVirtualSize(newVirtualSize);
	}

	void CWindow::setMinimumFrameBufferSize(const Size& size)
	{
		LOG_TRACE(U"CWindow::setMinimumFrameBufferSize({})"_fmt(size));
		
		m_state.minFrameBufferSize = size;
		::glfwSetWindowSizeLimits(m_window, size.x, size.y, GLFW_DONT_CARE, GLFW_DONT_CARE);
	}
	
	void CWindow::setFullscreen(const bool fullscreen, size_t monitorIndex)
	{
		LOG_TRACE(U"CWindow::setFullscreen(fullscreen = {}, monitorIndex = {})"_fmt(fullscreen, monitorIndex));

		if (fullscreen == m_state.fullscreen)
		{
			return;
		}
		
		if (m_state.fullscreen == false) // 現在ウィンドウモード
		{
			detail::siv3dRequestFullscreen();
		}
		else
		{
			detail::siv3dExitFullscreen();
		}
		
		m_state.fullscreen = fullscreen;

		if (Scene::GetResizeMode() != ResizeMode::Keep)
		{
			SIV3D_ENGINE(Renderer)->updateSceneSize();
		}
	}

	void CWindow::setToggleFullscreenEnabled(bool) {}
	
	bool CWindow::isToggleFullscreenEnabled() const
	{
		return false;
	}

	void CWindow::setTaskbarProgressBar(double)
	{
		// do nothing
	}

	void CWindow::updateState()
	{
		// frameBufferSize
		::glfwGetFramebufferSize(m_window, &m_state.frameBufferSize.x, &m_state.frameBufferSize.y);

		// scaling
		float xScale = 1.0f, yScale = 1.0f;
		// [Siv3DWeb ToDo]
		// ::glfwGetWindowContentScale(m_window, &xScale, &yScale);
		m_state.scaling = Max(xScale, yScale);
		
		// titleBarHeight
		// [Siv3D ToDo]
		
		// bounds
		int32 windowPosX, windowPosY, windowSizeX, windowSizeY;
		::glfwGetWindowPos(m_window, &windowPosX, &windowPosY);
		::glfwGetWindowSize(m_window, &windowSizeX, &windowSizeY);
		
		m_state.bounds.pos = Size(windowPosX, (windowPosY - m_state.titleBarHeight));
		m_state.bounds.size = Size(windowSizeX, (windowSizeY + m_state.titleBarHeight));
				
		// minimized
		m_state.maximized = (::glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) == GLFW_TRUE);
		
		// maximized
		m_state.maximized = (::glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED) == GLFW_TRUE)
			&& (m_state.style == WindowStyle::Sizable);
		
		// focused
		m_state.focused = (::glfwGetWindowAttrib(m_window, GLFW_FOCUSED) == GLFW_TRUE);

		// sizeMove
		m_state.sizeMove = false; // [Siv3D ToDo]
	}

	void CWindow::OnMove(GLFWwindow* window, const int x, const int y)
	{
		LOG_TRACE(U"CWindow::OnMove({})"_fmt(Point(x, y)));
		
		CWindow* pWindow = static_cast<CWindow*>(::glfwGetWindowUserPointer(window));
		pWindow->m_state.bounds.pos = Point(x, y);
	}

	void CWindow::OnResize(GLFWwindow* window, const int width, const int height)
	{
		LOG_TRACE(U"CWindow::OnResize({})"_fmt(Size(width, height)));
		
		CWindow* pWindow = static_cast<CWindow*>(::glfwGetWindowUserPointer(window));
		pWindow->m_state.bounds.size = Size(width, height);

		if (pWindow->m_state.style == WindowStyle::Sizable || pWindow->m_resizingWindow)
		{
			pWindow->m_state.virtualSize = Size(width, height);
		}
	}

	void CWindow::OnFrameBufferSize(GLFWwindow* window, const int width, const int height)
	{
		LOG_TRACE(U"CWindow::OnFrameBufferSize({})"_fmt(Size(width, height)));
		
		CWindow* pWindow = static_cast<CWindow*>(::glfwGetWindowUserPointer(window));
		pWindow->m_state.frameBufferSize = Size(width, height);
		//pWindow->m_state.clientSize.set(width, height);
	}

	void CWindow::OnScalingChange(GLFWwindow* window, const float sx, const float sy)
	{
		LOG_TRACE(U"CWindow::OnScalingChange({}, {})"_fmt(sx, sy));
		
		CWindow* pWindow = static_cast<CWindow*>(::glfwGetWindowUserPointer(window));
		
		pWindow->m_state.scaling = Max(sx, sy);
	}

	void CWindow::OnIconify(GLFWwindow* window, const int iconified)
	{
		LOG_TRACE(U"CWindow::OnIconify({})"_fmt((iconified == GLFW_TRUE)));
		
		CWindow* pWindow = static_cast<CWindow*>(::glfwGetWindowUserPointer(window));
		
		if (iconified)
		{
			pWindow->m_state.minimized = true;
			pWindow->m_state.maximized = false;
		}
		else
		{
			pWindow->m_state.minimized = false;
			pWindow->m_state.maximized = false;
		}
	}

	void CWindow::OnMaximize(GLFWwindow* window, const int maximized)
	{
		LOG_TRACE(U"CWindow::OnMaximize({})"_fmt((maximized == GLFW_TRUE)));
		
		CWindow* pWindow = static_cast<CWindow*>(::glfwGetWindowUserPointer(window));
		
		if (maximized)
		{
			pWindow->m_state.minimized = false;
			pWindow->m_state.maximized = true;
		}
		else
		{
			pWindow->m_state.minimized = false;
			pWindow->m_state.maximized = false;
		}
	}

	void CWindow::OnFocus(GLFWwindow* window, const int focused)
	{
		LOG_TRACE(U"CWindow::OnFocus({})"_fmt((focused == GLFW_TRUE)));
		
		CWindow* pWindow = static_cast<CWindow*>(::glfwGetWindowUserPointer(window));
		pWindow->m_state.focused = (focused == GLFW_TRUE);
		
		if (!focused)
		{
			SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::WindowDeactivated);
		}
	}
}
