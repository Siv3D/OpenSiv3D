//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "CRenderer2D_GL.hpp"
# include <Siv3D/Vertex2D.hpp>

namespace s3d
{
	CRenderer2D_GL::CRenderer2D_GL()
	{

	}

	CRenderer2D_GL::~CRenderer2D_GL()
	{
		if (m_initialized)
		{
			::glDeleteVertexArrays(1, &m_vao);
			::glDeleteBuffers(1, &m_indexBuffer);
			::glDeleteBuffers(1, &m_vertexBuffer);
		
			::glDeleteProgram(m_programHandle);
			::glDeleteShader(m_pixelShader);
			::glDeleteShader(m_vertexShader);
		}
	}

	bool CRenderer2D_GL::init()
	{
		m_vertexShader = ::glCreateShader(GL_VERTEX_SHADER);
		
		const char* vsCode =
R"(
#version 410
		
in vec2 VertexPosition;
in vec2 Tex;
in vec4 VertexColor;

out vec4 Color;

void main()
{
	Color = VertexColor;
	gl_Position = vec4(VertexPosition, 0.0, 1.0);
}
)";
		
		::glShaderSource(m_vertexShader, 1, &vsCode, nullptr);
		
		::glCompileShader(m_vertexShader);

		GLint result;
		::glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &result);
		
		if (result == GL_FALSE)
		{
			return false;
		}
		
	
		
		m_pixelShader = ::glCreateShader(GL_FRAGMENT_SHADER);
		
		const char* psCode =
		R"(
#version 410
		
in vec4 Color;

out vec4 FragColor;
		
void main()
{
	FragColor = Color;
}
)";
		
		::glShaderSource(m_pixelShader, 1, &psCode, nullptr);
		
		::glCompileShader(m_pixelShader);

		::glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &result);
		
		if (result == GL_FALSE)
		{
			return false;
		}
		
		m_programHandle = ::glCreateProgram();
		
		if (!m_programHandle)
		{
			return false;
		}
		
		::glAttachShader(m_programHandle, m_vertexShader);
		::glAttachShader(m_programHandle, m_pixelShader);
		
		::glBindAttribLocation(m_programHandle, 0, "VertexPosition");
		::glBindAttribLocation(m_programHandle, 1, "Tex");
		::glBindAttribLocation(m_programHandle, 2, "VertexColor");
		::glBindFragDataLocation(m_programHandle, 0, "FragColor");
		
		::glLinkProgram(m_programHandle);
		
		GLint status;
		::glGetProgramiv(m_programHandle, GL_LINK_STATUS, &status);
		
		if (status == GL_FALSE)
		{
			return false;
		}
		
		::glUseProgram(m_programHandle);
		
		::glGenBuffers(1, &m_vertexBuffer);
		::glGenBuffers(1, &m_indexBuffer);
		
		::glGenVertexArrays(1, &m_vao);
		
		::glBindVertexArray(m_vao);
		{
			::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			::glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * VertexBufferSize, nullptr, GL_DYNAMIC_DRAW);

			::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (GLubyte*)0);
			::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (GLubyte*)8);
			::glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (GLubyte*)16);
		
			::glEnableVertexAttribArray(0);
			::glEnableVertexAttribArray(1);
			::glEnableVertexAttribArray(2);
			
			::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * IndexBufferSize, nullptr, GL_DYNAMIC_DRAW);
		}
		::glBindVertexArray(0);
		
		m_initialized = true;
		
		return true;
	}
	
	void CRenderer2D_GL::flush()
	{
		const size_t vertexSize = 4;
		const size_t indexSize = 6;
		
		static int frame = 0;
		++frame;
		
		const float f = sin(frame / 100.0f);
		
		const Vertex2D vertices[vertexSize] = {
			{Float2(-0.8f,  f), Float2(0.0f,  0.0f), Float4( 1.0f, 0.5f, 0.2f, 1.0f)},
			{Float2(-0.8f,  0.0f), Float2(0.0f,  0.0f), Float4( 1.0f, 1.0f, 1.0f, 1.0f)},
			{Float2( 0.0f,  0.8f), Float2(0.0f,  0.0f), Float4( 1.0f, 0.5f, 0.2f, 1.0f)},
			{Float2( 0.0f,  0.0f), Float2(0.0f,  0.0f), Float4( 1.0f, 1.0f, 1.0f, 1.0f)},
		};
		
	
		::glBindVertexArray(m_vao);
		
		
		if (m_vertexWritePos + vertexSize > VertexBufferSize)
		{
			m_vertexWritePos = 0;
		}
		
		const uint32 vertexOffset = m_vertexWritePos;
		{
			void* pDst = ::glMapBufferRange(GL_ARRAY_BUFFER, sizeof(Vertex2D) * m_vertexWritePos, sizeof(Vertex2D) * vertexSize,
											GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			
			::memcpy(pDst, vertices, sizeof(Vertex2D) * vertexSize);
			
			::glUnmapBuffer(GL_ARRAY_BUFFER);
		}
		m_vertexWritePos += vertexSize;		
		
		
		
		if (m_indexWritePos + indexSize > IndexBufferSize)
		{
			m_indexWritePos = 0;
		}

		uint32 indices[indexSize] = { 0, 1, 2, 1, 2, 3 };
		
		for (auto& index : indices)
		{
			index += vertexOffset;
		}
		
		const uint32 indexOffset = m_indexWritePos;
		{
			void* pDst = ::glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * m_indexWritePos, sizeof(uint32) * indexSize,
						 GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
		
			::memcpy(pDst, indices, sizeof(uint32) * indexSize);
		
			::glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		}
		m_indexWritePos += indexSize;
		
		
		
		::glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (uint32*)(nullptr) + indexOffset);

		
		::glBindVertexArray(0);
	}
	
	void CRenderer2D_GL::addRect(const FloatRect& rect, const Float4& color)
	{
		
	}
}

# endif
