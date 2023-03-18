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
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include "WGLContext.hpp"

namespace s3d
{
	WGLContext::~WGLContext()
	{
		destroy();
	}

	void WGLContext::init(HWND hWnd)
	{
		m_hWnd = hWnd;

		constexpr PIXELFORMATDESCRIPTOR pixelFormatDesc =
		{
			.nSize			= sizeof(PIXELFORMATDESCRIPTOR),
			.nVersion		= 1,
			.dwFlags		= (PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER),
			.iPixelType		= PFD_TYPE_RGBA,
			.cColorBits		= 32,
			.cDepthBits		= 0,
			.cStencilBits	= 0,
			.iLayerType		= PFD_MAIN_PLANE,
		};

		LOG_TRACE(U"GetDC()");
		m_hDC = ::GetDC(m_hWnd);

		if (!m_hDC)
		{
			throw EngineError(U"GetDC() failed");
		}

		LOG_TRACE(U"ChoosePixelFormat()");
		const int32 pixelFormat = ::ChoosePixelFormat(m_hDC, &pixelFormatDesc);

		if (pixelFormat == 0)
		{
			throw EngineError(U"ChoosePixelFormat() failed");
		}

		LOG_TRACE(U"SetPixelFormat()");
		if (!::SetPixelFormat(m_hDC, pixelFormat, &pixelFormatDesc))
		{
			throw EngineError(U"SetPixelFormat() failed");
		}

		LOG_TRACE(U"wglCreateContext()");
		m_glContext = ::wglCreateContext(m_hDC);

		makeCurrent();

		LOG_TRACE(U"glewInit()");
		if (GLenum err = ::glewInit();
			err != GLEW_OK)
		{
			throw EngineError(U"glewInit() failed");
		}

		const String renderer = Unicode::Widen(reinterpret_cast<const char*>(::glGetString(GL_RENDERER)));
		const String vendor = Unicode::Widen(reinterpret_cast<const char*>(::glGetString(GL_VENDOR)));
		const String version = Unicode::Widen(reinterpret_cast<const char*>(::glGetString(GL_VERSION)));
		const String glslVersion = Unicode::Widen(reinterpret_cast<const char*>(::glGetString(GL_SHADING_LANGUAGE_VERSION)));

		GLint major = 0, minor = 0;
		::glGetIntegerv(GL_MAJOR_VERSION, &major);
		::glGetIntegerv(GL_MINOR_VERSION, &minor);

		GLint maxUniformSize = 0, maxUniformBindings = 0;
		::glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxUniformSize);
		::glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &maxUniformBindings);

		LOG_INFO(U"renderer: {}"_fmt(renderer));
		LOG_INFO(U"vendor: {}"_fmt(vendor));
		LOG_INFO(U"version: {}"_fmt(version));
		LOG_INFO(U"glslVersion: {}"_fmt(glslVersion));
		LOG_INFO(U"GL_MAJOR_VERSION: {}"_fmt(major));
		LOG_INFO(U"GL_MINOR_VERSION: {}"_fmt(minor));
		LOG_INFO(U"GL_MAX_UNIFORM_BLOCK_SIZE: {}"_fmt(maxUniformSize));
		LOG_INFO(U"GL_MAX_UNIFORM_BUFFER_BINDINGS: {}"_fmt(maxUniformBindings));
	}

	void WGLContext::destroy()
	{
		if (m_glContext)
		{
			::wglMakeCurrent(nullptr, nullptr);
			::wglDeleteContext(m_glContext);
			m_glContext = nullptr;
		}

		if (m_hDC)
		{
			::ReleaseDC(m_hWnd, m_hDC);
			m_hDC = nullptr;
		}
	}

	void WGLContext::makeCurrent()
	{
		LOG_TRACE(U"wglMakeCurrent()");
		if (!::wglMakeCurrent(m_hDC, m_glContext))
		{
			throw EngineError(U"wglMakeCurrent() failed");
		}
	}

	void WGLContext::swapBuffers()
	{
		::SwapBuffers(m_hDC);
	}
}
