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

# include <Siv3D/EngineLog.hpp>
# include "VertexShader_GL.hpp"

namespace s3d
{
	VertexShader_GL::VertexShader_GL(Null)
	{
		m_initialized = true;
	}
	
	VertexShader_GL::~VertexShader_GL()
	{
		if (m_vsProgram)
		{
			::glDeleteProgram(m_vsProgram);
		}
	}
	
	VertexShader_GL::VertexShader_GL(const String& source)
	{
		// 頂点シェーダプログラムを作成
		{
			const std::string sourceUTF8 = source.toUTF8();
			const char* pSource = sourceUTF8.c_str();
			m_vsProgram = ::glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &pSource);
		}
		
		GLint status = GL_FALSE;
		::glGetProgramiv(m_vsProgram, GL_LINK_STATUS, &status);
		
		GLint logLen = 0;
		::glGetProgramiv(m_vsProgram, GL_INFO_LOG_LENGTH, &logLen);
		
		// ログメッセージ
		if (logLen > 4)
		{
			std::string log(logLen + 1, '\0');
			::glGetProgramInfoLog(m_vsProgram, logLen, &logLen, &log[0]);
			LOG_FAIL(U"❌ Vertex shader compilation failed: {0}"_fmt(Unicode::Widen(log)));
		}
		
		if (status == GL_FALSE) // もしリンクに失敗していたら
		{
			::glDeleteProgram(m_vsProgram);
			m_vsProgram = 0;
		}
		
		m_initialized = (m_vsProgram != 0);
	}
	
	bool VertexShader_GL::isInitialized() const noexcept
	{
		return m_initialized;
	}
	
	GLint VertexShader_GL::getProgram() const
	{
		return m_vsProgram;
	}
	
	GLuint VertexShader_GL::getUniformBlockIndex(const char* const name)
	{
		return ::glGetUniformBlockIndex(m_vsProgram, name);
	}
	
	void VertexShader_GL::setUniformBlockBinding(const char* const name, GLuint index)
	{
		::glUniformBlockBinding(m_vsProgram, getUniformBlockIndex(name), index);
	}
}
