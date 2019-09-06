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

# include <Siv3D/SamplerState.hpp>
# include <Siv3D/EngineLog.hpp>
# include "PixelShader_GL.hpp"

namespace s3d
{
	PixelShader_GL::PixelShader_GL(Null)
	{
		m_initialized = true;
	}
	
	PixelShader_GL::~PixelShader_GL()
	{
		if (m_psProgram)
		{
			::glDeleteProgram(m_psProgram);
		}
	}
	
	PixelShader_GL::PixelShader_GL(const String& source)
	{
		// ピクセルシェーダプログラムを作成
		{
			const std::string sourceUTF8 = source.toUTF8();
			const char* pSource = sourceUTF8.c_str();
			m_psProgram = ::glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &pSource);
		}
		
		GLint status = GL_FALSE;
		::glGetProgramiv(m_psProgram, GL_LINK_STATUS, &status);
		
		GLint logLen = 0;
		::glGetProgramiv(m_psProgram, GL_INFO_LOG_LENGTH, &logLen);
		
		// ログメッセージ
		if (logLen > 4)
		{
			std::string log(logLen + 1, '\0');
			::glGetProgramInfoLog(m_psProgram, logLen, &logLen, &log[0]);
			LOG_FAIL(U"❌ Pixel shader compilation failed: {0}"_fmt(Unicode::Widen(log)));
		}
		
		if (status == GL_FALSE) // もしリンクに失敗していたら
		{
			::glDeleteProgram(m_psProgram);
			m_psProgram = 0;
		}
		
		if (m_psProgram)
		{
			for (uint32 slot = 0; slot < SamplerState::MaxSamplerCount; ++slot)
			{
				const String name = Format(U"Texture", slot);
				const std::string s = name.narrow();
				const GLint location = ::glGetUniformLocation(m_psProgram, s.c_str());
				
				if (location != -1)
				{
					LOG_DEBUG(U"{} location: {}"_fmt(name, location));
					m_textureIndices.emplace_back(slot, location);
				}
			}
		}
		
		m_initialized = (m_psProgram != 0);
	}
	
	bool PixelShader_GL::isInitialized() const noexcept
	{
		return m_initialized;
	}
	
	GLint PixelShader_GL::getProgram() const
	{
		return m_psProgram;
	}
	
	void PixelShader_GL::setPSSamplerUniform()
	{
		if (m_textureIndices)
		{
			::glUseProgram(m_psProgram);
			
			for (auto[slot, location] : m_textureIndices)
			{
				::glUniform1i(location, slot);
			}
			
			::glUseProgram(0);
		}
	}
	
	void PixelShader_GL::setUniformBlockBinding(const String& name, const GLuint index)
	{
		const GLuint blockIndex = ::glGetUniformBlockIndex(m_psProgram, name.narrow().c_str());
		
		if (blockIndex == GL_INVALID_INDEX)
		{
			LOG_FAIL(U"Uniform block `{}` not found"_fmt(name));
			return;
		}
		else
		{
			LOG_DEBUG(U"Uniform block `{}`: binding = {}"_fmt(name, index));
		}
		
		::glUniformBlockBinding(m_psProgram, blockIndex, index);
	}
	
	void PixelShader_GL::setUniformBlockBindings(const Array<BindingPoint>& bindingPoints)
	{
		for (auto[name, index] : bindingPoints)
		{
			setUniformBlockBinding(name, Shader::Internal::MakeUniformBlockBinding(ShaderStage::Pixel, index));
		}
	}
}
