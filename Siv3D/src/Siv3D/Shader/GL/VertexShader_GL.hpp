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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <GL/glew.h>
# include "../../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	class VertexShader_GL
	{
	private:
		
		GLuint m_vsProgram = 0;
		
		bool m_initialized = false;

	public:

		struct Null {};

		VertexShader_GL() = default;

		VertexShader_GL(Null)
		{
			m_initialized = true;
		}
		
		~VertexShader_GL()
		{
			if (m_vsProgram)
			{
				::glDeleteProgram(m_vsProgram);
			}
		}

		VertexShader_GL(const String& source)
		{
			const std::string sourceUTF8 = source.toUTF8();
			
			const char* pSource = sourceUTF8.c_str();
			
			m_vsProgram = ::glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &pSource);
			
			GLint status = GL_FALSE;
			
			::glGetProgramiv(m_vsProgram, GL_LINK_STATUS, &status);
			
			GLint logLen = 0;
			
			::glGetProgramiv(m_vsProgram, GL_INFO_LOG_LENGTH, &logLen);
			
			if (logLen > 4)
			{
				std::string log(logLen + 1, '\0');
				
				::glGetProgramInfoLog(m_vsProgram, logLen, &logLen, &log[0]);
				
				LOG_FAIL(U"❌ Vertex shader compilation failed: {0}"_fmt(Unicode::Widen(log)));
			}
			
			if (status == GL_FALSE)
			{
				::glDeleteProgram(m_vsProgram);
				
				m_vsProgram = 0;
			}
			
			m_initialized = m_vsProgram != 0;
		}

		bool isInitialized() const noexcept
		{
			return m_initialized;
		}

		GLint getProgram() const
		{
			return m_vsProgram;
		}

		GLuint getUniformBlockIndex(const char* const name)
		{
			return ::glGetUniformBlockIndex(m_vsProgram, name);
		}
		
		void setUniformBlockBinding(const char* const name, GLuint index)
		{
			::glUniformBlockBinding(m_vsProgram, getUniformBlockIndex(name), index);
		}
		
		ByteArrayView getView() const;
	};
}

# endif
