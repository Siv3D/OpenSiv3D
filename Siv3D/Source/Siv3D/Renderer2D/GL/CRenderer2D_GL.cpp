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
# include <Siv3D/PointVector.hpp>

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
			::glDeleteBuffers(2, m_vbo);
		
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
#version 400
		
in vec3 VertexPosition;
in vec3 VertexColor;

out vec3 Color;

void main()
{
	Color = VertexColor;
	gl_Position = vec4(VertexPosition, 1.0);
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
#version 400
		
in vec3 Color;

out vec4 FragColor;
		
void main()
{
	FragColor = vec4(Color, 1.0);
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
		::glBindAttribLocation(m_programHandle, 1, "VertexColor");
		
		::glLinkProgram(m_programHandle);
		
		GLint status;
		::glGetProgramiv(m_programHandle, GL_LINK_STATUS, &status);
		
		if (status == GL_FALSE)
		{
			return false;
		}
		
		::glUseProgram(m_programHandle);
		
		::glGenBuffers(2, m_vbo);
		
		::glGenVertexArrays(1, &m_vao);

		
		
		m_initialized = true;
		
		return true;
	}
	
	void CRenderer2D_GL::flush()
	{
		const Float3 positions[6] = {
			Float3(-0.8f,  0.8f, 0.0f),
			Float3(-0.8f,  0.0f, 0.0f),
			Float3( 0.0f,  0.8f, 0.0f),
			
			Float3(-0.8f,  0.0f, 0.0f),
			Float3( 0.0f,  0.8f, 0.0f),
			Float3( 0.0f,  0.0f, 0.0f),
		};
		
		const Float3 colors[6] = {
			Float3( 1.0f, 0.5f, 0.2f),
			Float3( 1.0f, 1.0f, 1.0f),
			Float3( 1.0f, 0.5f, 0.2f),
			
			Float3( 1.0f, 1.0f, 1.0f),
			Float3( 1.0f, 0.5f, 0.2f),
			Float3( 1.0f, 1.0f, 1.0f),
		};
		
		::glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
		::glBufferData(GL_ARRAY_BUFFER, sizeof(Float3) * 6, positions, GL_STATIC_DRAW);
		
		::glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
		::glBufferData(GL_ARRAY_BUFFER, sizeof(Float3) * 6, colors, GL_STATIC_DRAW);
		
		::glEnableVertexAttribArray(0);
		::glEnableVertexAttribArray(1);
		
		::glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
		::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		
		::glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
		::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		
		::glBindVertexArray(m_vao);
		::glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

# endif
