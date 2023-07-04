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

# include "CRenderer_GLES3.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/Mesh/IMesh.hpp>
# include <Siv3D/Renderer2D/GLES3/CRenderer2D_GLES3.hpp>
# include <Siv3D/Renderer3D/GLES3/CRenderer3D_GLES3.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		/*
		static void GLDebugMessageARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const GLvoid* userParam)
		{
			// [Siv3D ToDo] Linux でのデバッグ用
		}
		
		static void GLDebugMessageAMD(GLuint id, GLuint category, GLenum severity, GLsizei length, const GLchar *message, GLvoid* userParam)
		{
			// [Siv3D ToDo] Linux でのデバッグ用
		}
		*/
	}

	CRenderer_GLES3::CRenderer_GLES3()
	{
	
	}

	CRenderer_GLES3::~CRenderer_GLES3()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GLES3::~CRenderer_GLES3()");
	}

	EngineOption::Renderer CRenderer_GLES3::getRendererType() const noexcept
	{
		return EngineOption::Renderer::WebGL2;
	}	

	void CRenderer_GLES3::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GLES3::init()");
		
		pRenderer2D = static_cast<CRenderer2D_GLES3*>(SIV3D_ENGINE(Renderer2D));
		pRenderer3D = static_cast<CRenderer3D_GLES3*>(SIV3D_ENGINE(Renderer3D));
		m_window = static_cast<GLFWwindow*>(SIV3D_ENGINE(Window)->getHandle());
		
		::glfwMakeContextCurrent(m_window);
		// [BUGBUG] calling this without mainloop emits runtime error
		// ::glfwSwapInterval(1);
		
		::glewExperimental = GL_TRUE;
		if (::glewInit() != GLEW_OK)
		{
			throw EngineError(U"glewInit() failed");
		}
		
		if (SIV3D_BUILD(DEBUG) && GLEW_ARB_debug_output)
		{
			//::glDebugMessageCallbackARB(detail::GLDebugMessageARB, nullptr);
			LOG_INFO(U"ℹ️ GLEW_ARB_debug_output available");
		}
		else if (SIV3D_BUILD(DEBUG) && GLEW_AMD_debug_output)
		{
			//::glDebugMessageCallbackAMD(detail::GLDebugMessageAMD, nullptr);
			LOG_INFO(U"ℹ️ GLEW_AMD_debug_output available");
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

		m_backBuffer		= std::make_unique<GLES3BackBuffer>();
		m_blendState		= std::make_unique<GLES3BlendState>();
		m_rasterizerState	= std::make_unique<GLES3RasterizerState>();
		m_depthStencilState = std::make_unique<GLES3DepthStencilState>();
		m_samplerState		= std::make_unique<GLES3SamplerState>();
		
		pTexture = static_cast<CTexture_GLES3*>(SIV3D_ENGINE(Texture));
		pTexture->init();

		SIV3D_ENGINE(Shader)->init();
		SIV3D_ENGINE(Mesh)->init();

		clear();
	}

	StringView CRenderer_GLES3::getName() const
	{
		static constexpr StringView name(U"WebGL2");
		return name;
	}	

	void CRenderer_GLES3::clear()
	{
		m_backBuffer->clear(GLES3ClearTarget::Scene);
		
		const auto& windowState = SIV3D_ENGINE(Window)->getState();

		if (const Size frameBufferSize = windowState.frameBufferSize; 
			(frameBufferSize != m_backBuffer->getBackBufferSize()))
		{
			m_backBuffer->setBackBufferSize(frameBufferSize);

			if (windowState.sizeMove)
			{
				// sleep
			}
		}	
	}

	void CRenderer_GLES3::flush()
	{
		// Scene に 3D, 2D 描画
		{
			pRenderer3D->flush();
			pRenderer2D->flush();
			m_backBuffer->unbind();
		}

		// ウィンドウに Scene を描画
		{
			m_backBuffer->updateFromSceneBuffer();
		}
	}

	bool CRenderer_GLES3::present()
	{
		::glfwSwapBuffers(m_window);
		
		if constexpr (SIV3D_BUILD(DEBUG))
		{
			//CheckGLError();
		}

		return true;
	}

	void CRenderer_GLES3::setVSyncEnabled(const bool enabled)
	{
		if (m_vSyncEnabled == enabled)
		{
			return;
		}

		m_vSyncEnabled = enabled;

		// ::glfwSwapInterval(static_cast<int32>(m_vSyncEnabled));
	}

	bool CRenderer_GLES3::isVSyncEnabled() const
	{
		return m_vSyncEnabled;
	}

	void CRenderer_GLES3::captureScreenshot()
	{
		m_backBuffer->capture();
	}

	const Image& CRenderer_GLES3::getScreenCapture() const
	{
		return m_backBuffer->getScreenCapture();
	}

	void CRenderer_GLES3::setSceneResizeMode(const ResizeMode resizeMode)
	{
		m_backBuffer->setSceneResizeMode(resizeMode);
	}

	ResizeMode CRenderer_GLES3::getSceneResizeMode() const noexcept
	{
		return m_backBuffer->getSceneResizeMode();
	}

	void CRenderer_GLES3::setSceneBufferSize(const Size size)
	{
		m_backBuffer->setSceneBufferSize(size);
	}

	Size CRenderer_GLES3::getSceneBufferSize() const noexcept
	{
		return m_backBuffer->getSceneBufferSize();
	}

	void CRenderer_GLES3::setSceneTextureFilter(const TextureFilter textureFilter)
	{
		m_backBuffer->setSceneTextureFilter(textureFilter);
	}

	TextureFilter CRenderer_GLES3::getSceneTextureFilter() const noexcept
	{
		return m_backBuffer->getSceneTextureFilter();
	}

	void CRenderer_GLES3::setBackgroundColor(const ColorF& color)
	{
		m_backBuffer->setBackgroundColor(color);
	}

	const ColorF& CRenderer_GLES3::getBackgroundColor() const noexcept
	{
		return m_backBuffer->getBackgroundColor();
	}

	void CRenderer_GLES3::setLetterboxColor(const ColorF& color)
	{
		m_backBuffer->setLetterboxColor(color);
	}

	const ColorF& CRenderer_GLES3::getLetterboxColor() const noexcept
	{
		return m_backBuffer->getLetterBoxColor();
	}

	std::pair<float, RectF> CRenderer_GLES3::getLetterboxComposition() const noexcept
	{
		return m_backBuffer->getLetterboxComposition();
	}

	void CRenderer_GLES3::updateSceneSize()
	{
		m_backBuffer->updateSceneSize();
	}

	GLES3BackBuffer& CRenderer_GLES3::getBackBuffer() noexcept
	{
		return *m_backBuffer;
	}

	GLES3BlendState& CRenderer_GLES3::getBlendState() noexcept
	{
		return *m_blendState;
	}

	GLES3RasterizerState& CRenderer_GLES3::getRasterizerState() noexcept
	{
		return *m_rasterizerState;
	}

	GLES3DepthStencilState& CRenderer_GLES3::getDepthStencilState() noexcept
	{
		return *m_depthStencilState;
	}

	GLES3SamplerState& CRenderer_GLES3::getSamplerState() noexcept
	{
		return *m_samplerState;
	}
}
