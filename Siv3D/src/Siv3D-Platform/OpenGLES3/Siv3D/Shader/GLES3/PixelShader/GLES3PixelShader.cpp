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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/ShaderStage.hpp>
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
		if (m_pixelShader)
		{
			::glDeleteShader(m_pixelShader);
			m_pixelShader = 0;
		}
	}

	GLES3PixelShader::GLES3PixelShader(const StringView source, const Array<ConstantBufferBinding>& bindings)
	{
		m_pixelShader = ::glCreateShader(GL_FRAGMENT_SHADER);

		if (not m_pixelShader) {
			LOG_FAIL(U"❌ Pixel shader compilation failed: failed to create shader.");
		}

        // シェーダのコンパイル
		{
			const std::string sourceUTF8 = source.toUTF8();
			const char* pSource = sourceUTF8.c_str();

			::glShaderSource(m_pixelShader, 1, &pSource, NULL);
			::glCompileShader(m_pixelShader);

			GLint status = GL_FALSE;
			::glGetShaderiv(m_pixelShader, GL_COMPILE_STATUS, &status);

			GLint logLen = 0;
			::glGetShaderiv(m_pixelShader, GL_INFO_LOG_LENGTH, &logLen);	

			// ログメッセージ
			if (logLen > 4)
			{
				std::string log(logLen + 1, '\0');
				::glGetShaderInfoLog(m_pixelShader, logLen, &logLen, &log[0]);
				LOG_FAIL(U"❌ Pixel shader compilation failed: " + Unicode::Widen(log));
			}	

            if (status == GL_FALSE) {
                ::glDeleteShader(m_pixelShader);
                m_pixelShader = 0;
            }
		}
	
		if (m_pixelShader != 0)
		{
			setUniformBlockBindings(bindings);
		}
		
		m_initialized = (m_pixelShader != 0);
	}

	bool GLES3PixelShader::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const Blob& GLES3PixelShader::getBinary() const noexcept
	{
		return m_binary;
	}

	GLint GLES3PixelShader::getShader() const
	{
		return m_pixelShader;
	}

	void GLES3PixelShader::setPSSamplerUniforms()
	{
		if (not m_textureIndices)
		{
			return;
		}

		for (auto [slot, location] : m_textureIndices)
		{
			::glUniform1i(location, slot);
		}
	}

	void GLES3PixelShader::bindUniformBlocks(GLuint program)
	{
		// Constant Buffer Uniforms
		for (auto[name, index] : m_constantBufferBindings)
		{
			const GLuint blockIndex = ::glGetUniformBlockIndex(program, name.narrow().c_str());
		
			if (blockIndex == GL_INVALID_INDEX)
			{
				LOG_FAIL(U"Uniform block `{}` not found"_fmt(name));
				return;
			}

			::glUniformBlockBinding(program, blockIndex, index);
		}

		// Sampler Uniforms
		for (uint32 slot = 0; slot < SamplerState::MaxSamplerCount; ++slot)
		{
			const GLuint samplerSlot = Shader::Internal::MakeSamplerSlot(ShaderStage::Pixel, slot);
			const String name = Format(U"Texture", samplerSlot);
			const std::string s = name.narrow();
			const GLint location = ::glGetUniformLocation(program, s.c_str());

			if (location != -1)
			{
				LOG_TRACE(U"{} location: {}"_fmt(name, location));
				m_textureIndices.emplace_back(samplerSlot, location);
			}
		}
	}

	void GLES3PixelShader::setUniformBlockBinding(const String& name, const GLuint index)
	{
		const GLuint uniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Pixel, index);

		LOG_TRACE(U"Uniform block `{}`: binding = PS_{} ({})"_fmt(name, index, uniformBlockBinding));

		ConstantBufferBinding cbBinding;

		cbBinding.name = name;
		cbBinding.index = uniformBlockBinding;

		m_constantBufferBindings << cbBinding;
	}

	void GLES3PixelShader::setUniformBlockBindings(const Array<ConstantBufferBinding>& bindings)
	{
		for (const auto& binding : bindings)
		{
			setUniformBlockBinding(binding.name, binding.index);
		}
	}
}
