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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ShaderStatge.hpp>
# include <Siv3D/SamplerState.hpp>
# include "GLES3PixelShader.hpp"

namespace s3d
{
	GLES3PixelShader::GLES3PixelShader(Null)
	{
		m_initialized = true;
	}

	GLES3PixelShader::~GLES3PixelShader()
	{
		if (m_psProgram)
		{
			::glDeleteProgram(m_psProgram);
			m_psProgram = 0;
		}
	}

	GLES3PixelShader::GLES3PixelShader(const StringView source, const Array<ConstantBufferBinding>& bindings)
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
					LOG_TRACE(U"{} location: {}"_fmt(name, location));
					m_textureIndices.emplace_back(slot, location);
				}
			}

			setUniformBlockBindings(bindings);
		}

		m_initialized = (m_psProgram != 0);
	}

	bool GLES3PixelShader::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const Blob& GLES3PixelShader::getBinary() const noexcept
	{
		return m_binary;
	}

	GLint GLES3PixelShader::getProgram() const
	{
		return m_psProgram;
	}

	void GLES3PixelShader::setPSSamplerUniform()
	{
		if (not m_textureIndices)
		{
			return;
		}

		::glUseProgram(m_psProgram);

		for (auto [slot, location] : m_textureIndices)
		{
			::glUniform1i(location, slot);
		}

		::glUseProgram(0);
	}

	void GLES3PixelShader::setUniformBlockBinding(const String& name, const GLuint index)
	{
		const GLuint blockIndex = ::glGetUniformBlockIndex(m_psProgram, name.narrow().c_str());

		if (blockIndex == GL_INVALID_INDEX)
		{
			LOG_FAIL(U"Uniform block `{}` not found"_fmt(name));
			return;
		}

		const GLuint uniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Pixel, index);

		LOG_TRACE(U"Uniform block `{}`: binding = PS_{} ({})"_fmt(name, index, uniformBlockBinding));

		::glUniformBlockBinding(m_psProgram, blockIndex, uniformBlockBinding);
	}

	void GLES3PixelShader::setUniformBlockBindings(const Array<ConstantBufferBinding>& bindings)
	{
		for (const auto& binding : bindings)
		{
			setUniformBlockBinding(binding.name, binding.index);
		}
	}
}
