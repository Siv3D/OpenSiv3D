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
# include "GLES3VertexShader.hpp"

namespace s3d
{
	GLES3VertexShader::GLES3VertexShader(Null)
	{
		m_initialized = true;
	}

	GLES3VertexShader::~GLES3VertexShader()
	{
		if (m_vertexShader)
		{
			::glDeleteShader(m_vertexShader);
			m_vertexShader = 0;
		}
	}

	GLES3VertexShader::GLES3VertexShader(const StringView source, const Array<ConstantBufferBinding>& bindings)
	{
		// 頂点シェーダプログラムを作成
		m_vertexShader = ::glCreateShader(GL_VERTEX_SHADER);

		if (!m_vertexShader) {
			LOG_FAIL(U"❌ Vertex shader compilation failed: failed to create shader.");
		}

        // シェーダのコンパイル
		{
			String sourceData { source };

			for (uint32 slot = 0; slot < SamplerState::MaxSamplerCount; ++slot)
			{
				const GLuint samplerSlot = Shader::Internal::MakeSamplerSlot(ShaderStage::Vertex, slot);
				const String oldName = Format(U"Texture", slot);
				const String newName = Format(U"Texture", samplerSlot);
				
				sourceData.replace(oldName, newName);
			}

			const std::string sourceUTF8 = sourceData.toUTF8();
			const char* pSource = sourceUTF8.c_str();

			::glShaderSource(m_vertexShader, 1, &pSource, NULL);
			::glCompileShader(m_vertexShader);

			GLint status = GL_FALSE;
			::glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &status);
			
			GLint logLen = 0;
			::glGetShaderiv(m_vertexShader, GL_INFO_LOG_LENGTH, &logLen);	

			// ログメッセージ
			if (logLen > 4)
			{
				std::string log(logLen + 1, '\0');
				::glGetShaderInfoLog(m_vertexShader, logLen, &logLen, &log[0]);
				LOG_FAIL(U"❌ Vertex shader compilation failed: " + Unicode::Widen(log));
			}	

            if (status == GL_FALSE) {
                ::glDeleteShader(m_vertexShader);
                m_vertexShader = 0;
            }
		}

		if (m_vertexShader != 0)
		{
			setUniformBlockBindings(bindings);
		}
		
		m_initialized = (m_vertexShader != 0);
	}

	bool GLES3VertexShader::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const Blob& GLES3VertexShader::getBinary() const noexcept
	{
		return m_binary;
	}

	GLuint GLES3VertexShader::getShader() const
	{
		return m_vertexShader;
	}

	void GLES3VertexShader::setVSSamplerUniforms()
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

	void GLES3VertexShader::bindUniformBlocks(GLuint program)
	{
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
			const GLuint samplerSlot = Shader::Internal::MakeSamplerSlot(ShaderStage::Vertex, slot);
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

	void GLES3VertexShader::setUniformBlockBinding(const StringView name, const GLuint index)
	{
		const GLuint uniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Vertex, index);

		LOG_TRACE(U"Uniform block `{}`: binding = VS_{} ({})"_fmt(name, index, uniformBlockBinding));

		ConstantBufferBinding cbBinding;

		cbBinding.name = name;
		cbBinding.index = uniformBlockBinding;

		m_constantBufferBindings << cbBinding;
	}

	void GLES3VertexShader::setUniformBlockBindings(const Array<ConstantBufferBinding>& bindings)
	{
		for (const auto& binding : bindings)
		{
			setUniformBlockBinding(binding.name, binding.index);
		}
	}
}
