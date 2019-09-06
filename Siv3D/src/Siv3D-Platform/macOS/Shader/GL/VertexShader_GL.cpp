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
	
	void VertexShader_GL::setUniformBlockBinding(const String& name, const GLuint index)
	{
		const GLuint blockIndex = ::glGetUniformBlockIndex(m_vsProgram, name.narrow().c_str());

		if (blockIndex == GL_INVALID_INDEX)
		{
			LOG_FAIL(U"Uniform block `{}` not found"_fmt(name));
			return;
		}
		
		::glUniformBlockBinding(m_vsProgram, blockIndex, index);
	}
	
	void VertexShader_GL::setUniformBlockBindings(const Array<BindingPoint>& bindingPoints)
	{
		for (auto[name, index] : bindingPoints)
		{
			setUniformBlockBinding(name, index);
		}
	}
}
