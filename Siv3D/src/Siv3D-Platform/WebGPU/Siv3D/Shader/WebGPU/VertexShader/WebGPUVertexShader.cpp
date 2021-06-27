//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ShaderStage.hpp>
# include "WebGPUVertexShader.hpp"

namespace s3d
{
	WebGPUVertexShader::WebGPUVertexShader(Null)
	{
		m_initialized = true;
	}

	WebGPUVertexShader::~WebGPUVertexShader()
	{
		if (m_vertexShader)
		{
			::glDeleteShader(m_vertexShader);
			m_vertexShader = 0;
		}
	}

	WebGPUVertexShader::WebGPUVertexShader(const StringView source, const Array<ConstantBufferBinding>& bindings)
	{
		// 頂点シェーダプログラムを作成
		m_vertexShader = ::glCreateShader(GL_VERTEX_SHADER);

		if (!m_vertexShader) {
			LOG_FAIL(U"❌ Vertex shader compilation failed: failed to create shader.");
		}

        // シェーダのコンパイル
		{
			const std::string sourceUTF8 = source.toUTF8();
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
				LOG_FAIL(U"❌ Vertex shader compilation failed: {0}"_fmt(Unicode::Widen(log)));
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

	bool WebGPUVertexShader::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const Blob& WebGPUVertexShader::getBinary() const noexcept
	{
		return m_binary;
	}

	GLuint WebGPUVertexShader::getShader() const
	{
		return m_vertexShader;
	}

	void WebGPUVertexShader::bindUniformBlocks(GLuint program)
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
	}

	void WebGPUVertexShader::setUniformBlockBinding(const StringView name, const GLuint index)
	{
		const GLuint uniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Vertex, index);

		LOG_TRACE(U"Uniform block `{}`: binding = VS_{} ({})"_fmt(name, index, uniformBlockBinding));

		ConstantBufferBinding cbBinding;

		cbBinding.name = name;
		cbBinding.index = uniformBlockBinding;

		m_constantBufferBindings << cbBinding;
	}

	void WebGPUVertexShader::setUniformBlockBindings(const Array<ConstantBufferBinding>& bindings)
	{
		for (const auto& binding : bindings)
		{
			setUniformBlockBinding(binding.name, binding.index);
		}
	}
}
