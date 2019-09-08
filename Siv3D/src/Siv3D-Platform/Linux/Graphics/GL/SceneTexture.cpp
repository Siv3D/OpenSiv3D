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

# include <Siv3DEngine.hpp>
# include "SceneTexture.hpp"

namespace s3d
{
	namespace detail
	{
		static GLuint LoadShaders(const FilePath& vsFilePath, const FilePath& psFilePath)
		{
			const std::string vsSource = TextReader(vsFilePath).readAll().toUTF8();
			const std::string psSource = TextReader(psFilePath).readAll().toUTF8();

			if (vsSource.empty() || psSource.empty())
			{
				return 0;
			}

			GLuint vertexShader = ::glCreateShader(GL_VERTEX_SHADER);
			{
				const char* vsSourcePtr = vsSource.c_str();

				::glShaderSource(vertexShader, 1, & vsSourcePtr, nullptr);
				::glCompileShader(vertexShader);

				GLint status = GL_FALSE, infoLogLength = 0;
				::glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
				::glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);

				if (infoLogLength > 0)
				{
					std::string logText(infoLogLength + 1, '\0');
					::glGetShaderInfoLog(vertexShader, infoLogLength, nullptr, logText.data());
					LOG_FAIL(U"VS: {0}"_fmt(Unicode::Widen(logText)));
				}
			}

			GLuint pixelShader = ::glCreateShader(GL_FRAGMENT_SHADER);
			{
				const char* psSourcePtr = psSource.c_str();

				::glShaderSource(pixelShader, 1, & psSourcePtr, nullptr);
				::glCompileShader(pixelShader);

				GLint status = GL_FALSE, infoLogLength = 0;
				::glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &status);
				::glGetShaderiv(pixelShader, GL_INFO_LOG_LENGTH, &infoLogLength);

				if (infoLogLength > 0)
				{
					std::string logText(infoLogLength + 1, '\0');
					::glGetShaderInfoLog(pixelShader, infoLogLength, nullptr, logText.data());
					LOG_FAIL(U"PS: {0}"_fmt(Unicode::Widen(logText)));
				}
			}

			GLuint program = ::glCreateProgram();
			{
				::glAttachShader(program, vertexShader);
				::glAttachShader(program, pixelShader);
				::glLinkProgram(program);

				GLint status = GL_FALSE, infoLogLength = 0;
				::glGetProgramiv(program, GL_LINK_STATUS, &status);
				::glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

				if (infoLogLength > 0)
				{
					std::string logText(infoLogLength + 1, '\0');
					::glGetProgramInfoLog(pixelShader, infoLogLength, nullptr, logText.data());
					LOG_FAIL(U"LINK: {0}"_fmt(Unicode::Widen(logText)));
				}
			}

			::glDetachShader(program, vertexShader);
			::glDetachShader(program, pixelShader);

			::glDeleteShader(vertexShader);
			::glDeleteShader(pixelShader);

			return program;
		}
	}

	SceneTexture::SceneTexture()
	{

	}

	SceneTexture::~SceneTexture()
	{
	# if defined(SIV3D_USE_MULTISAMPLE)

		if (m_msTexture)
		{
			::glDeleteTextures(1, &m_msTexture);
			m_msTexture = 0;
		}

		if (m_msFrameBuffer)
		{
			::glDeleteFramebuffers(1, &m_msFrameBuffer);
			m_msFrameBuffer = 0;
		}

		if (m_resolvedTexture)
		{
			::glDeleteTextures(1, &m_resolvedTexture);
			m_resolvedTexture = 0;
		}

		if (m_resolvedFrameBuffer)
		{
			::glDeleteFramebuffers(1, &m_resolvedFrameBuffer);
			m_resolvedFrameBuffer = 0;
		}

	# else

		if (m_texture)
		{
			::glDeleteTextures(1, &m_texture);
			m_texture = 0;
		}

		if (m_frameBuffer)
		{
			::glDeleteFramebuffers(1, &m_frameBuffer);
			m_frameBuffer = 0;
		}

	# endif

		if (m_copyProgram)
		{
			::glDeleteProgram(m_copyProgram);
			m_copyProgram = 0;
		}

		if (m_vertexArray)
		{
			::glDeleteVertexArrays(1, &m_vertexArray);
			m_vertexArray = 0;
		}
	}

	bool SceneTexture::init()
	{
	# if defined(SIV3D_USE_MULTISAMPLE)

		::glGenFramebuffers(1, &m_msFrameBuffer);
		::glGenFramebuffers(1, &m_resolvedFrameBuffer);

		::glGenTextures(1, &m_msTexture);
		::glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_msTexture);
		::glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, m_size.x, m_size.y, GL_FALSE);

		::glGenTextures(1, &m_resolvedTexture);
		::glBindTexture(GL_TEXTURE_2D, m_resolvedTexture);
		::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		::glBindFramebuffer(GL_FRAMEBUFFER, m_msFrameBuffer);
		::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_msTexture, 0);
		if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			return false;
		}

		::glBindFramebuffer(GL_FRAMEBUFFER, m_resolvedFrameBuffer);
		::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_resolvedTexture, 0);
		if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			return false;
		}

	# else

		::glGenFramebuffers(1, &m_frameBuffer);
		::glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

		::glGenTextures(1, &m_texture);
		::glBindTexture(GL_TEXTURE_2D, m_texture);
		::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		::glBindFramebuffer(GL_FRAMEBUFFER, m_texture);
		::glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture, 0);
		if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			return false;
		}
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);

	# endif

		m_copyProgram = detail::LoadShaders(Resource(U"engine/shader/fullscreen_triangle.vert"), Resource(U"engine/shader/fullscreen_triangle.frag"));
		if (!m_copyProgram)
		{
			return false;
		}
		m_locationTexture = ::glGetUniformLocation(m_copyProgram, "Texture0");

		::glGenVertexArrays(1, &m_vertexArray);
		::glBindVertexArray(m_vertexArray);

		::glGenSamplers(1, &m_sampler);
		::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return true;
	}

	void SceneTexture::clear(const ColorF& color)
	{
	# if defined(SIV3D_USE_MULTISAMPLE)

		::glBindFramebuffer(GL_FRAMEBUFFER, m_msFrameBuffer);

	# else

		::glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

	# endif

		::glClearColor(
					   static_cast<float>(color.r),
					   static_cast<float>(color.g),
					   static_cast<float>(color.b),
					   1.0f);
		::glClear(GL_COLOR_BUFFER_BIT);
	}

	const Size& SceneTexture::getSize() const noexcept
	{
		return m_size;
	}

	void SceneTexture::resize(const Size& size, const ColorF& clearColor)
	{
		if (size == m_size)
		{
			return;
		}

	# if defined(SIV3D_USE_MULTISAMPLE)

		::glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_msTexture);
		::glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, size.x, size.y, GL_FALSE);

		::glBindTexture(GL_TEXTURE_2D, m_resolvedTexture);
		::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	# else

		::glBindTexture(GL_TEXTURE_2D, m_texture);
		::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	# endif

		m_size = size;

		clear(clearColor);
	}

	void SceneTexture::bindSceneFrameBuffer()
	{
	# if defined(SIV3D_USE_MULTISAMPLE)

		::glBindFramebuffer(GL_FRAMEBUFFER, m_msFrameBuffer);

	# else

		::glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

	# endif
	}

	void SceneTexture::resolve(const bool linearFilter)
	{
	# if defined(SIV3D_USE_MULTISAMPLE)

		::glBindFramebuffer(GL_READ_FRAMEBUFFER, m_msFrameBuffer);
		::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_resolvedFrameBuffer);
		::glBlitFramebuffer(0, 0, m_size.x, m_size.y, 0, 0, m_size.x, m_size.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		auto[s, viewRect] = Siv3DEngine::Get<ISiv3DRenderer2D>()->getLetterboxingTransform();
		::glViewport(viewRect.left, viewRect.top, viewRect.right, viewRect.bottom);

		::glUseProgram(m_copyProgram);
		{
			::glActiveTexture(GL_TEXTURE0);
			::glBindTexture(GL_TEXTURE_2D, m_resolvedTexture);
			::glUniform1i(m_locationTexture, 0);
			::glBindSampler(0, m_sampler);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST);

			::glBindVertexArray(m_vertexArray);
			{
				::glBindBuffer(GL_ARRAY_BUFFER, 0);
				::glDrawArrays(GL_TRIANGLES, 0, 3);
			}
			::glBindVertexArray(0);
		}
		::glUseProgram(0);

		Siv3DEngine::Get<ISiv3DProfiler>()->reportDrawcalls(1, 1);

	# else

		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		auto[s, viewRect] = Siv3DEngine::Get<ISiv3DRenderer2D>()->getLetterboxingTransform();
		::glViewport(viewRect.left, viewRect.top, viewRect.right, viewRect.bottom);
		::glBindSampler(0, 0);

		::glUseProgram(m_copyProgram);
		{
			::glActiveTexture(GL_TEXTURE0);
			::glBindTexture(GL_TEXTURE_2D, m_texture);
			::glUniform1i(m_locationTexture, 0);

			::glBindVertexArray(m_vertexArray);
			{
				::glBindBuffer(GL_ARRAY_BUFFER, 0);
				::glDrawArrays(GL_TRIANGLES, 0, 3);
			}
			::glBindVertexArray(0);
		}
		::glUseProgram(0);

		Siv3DEngine::Get<ISiv3DProfiler>()->reportDrawcalls(1, 1);

	# endif
	}

	void SceneTexture::requestCapture()
	{
		m_screenCaptureRequested = true;
	}

	bool SceneTexture::hasCaptureRequest() const noexcept
	{
		return m_screenCaptureRequested;
	}

	void SceneTexture::capture()
	{
		m_screenCaptureRequested = false;

		if (m_size != m_image.size())
		{
			m_image.resize(m_size);
		}

		::glBindFramebuffer(GL_FRAMEBUFFER, m_resolvedFrameBuffer);
		{
			::glReadPixels(0, 0, m_size.x, m_size.y, GL_RGBA, GL_UNSIGNED_BYTE, m_image.data());
		}
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_image.flip();
	}

	const Image& SceneTexture::getImage() const
	{
		return m_image;
	}
}
