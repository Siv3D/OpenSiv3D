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
#include <Siv3D/FloatRect.hpp>
#include <Siv3D/Color.hpp>
#include <Siv3D/Mat3x2.hpp>
#include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr IndexType rectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };
	}
	
	CRenderer2D_GL::CRenderer2D_GL()
	{

	}

	CRenderer2D_GL::~CRenderer2D_GL()
	{
		if (m_initialized)
		{		
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
		
		
		if (!m_spriteBatch.init())
		{
			return false;
		}
		
		
		m_initialized = true;
		
		return true;
	}
	
	void CRenderer2D_GL::flush()
	{
		const std::pair<uint32, uint32> vi = m_spriteBatch.setBuffers();
	
		::glDrawElements(GL_TRIANGLES, m_drawIndexCount, GL_UNSIGNED_INT, (uint32*)(nullptr) + vi.second);

		::glBindVertexArray(0);
		 
		m_drawIndexCount = 0;
		
		m_spriteBatch.clear();
	}
	
	void CRenderer2D_GL::addRect(const FloatRect& _rect, const Float4& color)
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}
		
		const Mat3x2 currentMat = Mat3x2::Identity();
		const Mat3x2 currentScreen = Mat3x2::Screen(640, 480);
		const Mat3x2 matrix = currentMat * currentScreen;
		
		Float2 lt = matrix.transform(Float2(_rect.left, _rect.top));
		Float2 rb = matrix.transform(Float2(_rect.right, _rect.bottom));
		
		FloatRect rect;
		rect.left = lt.x;
		rect.top = lt.y;
		rect.right = rb.x;
		rect.bottom = rb.y;
		
		pVertex[0].pos.set(rect.left, rect.top);
		pVertex[0].color = color;
		
		pVertex[1].pos.set(rect.right, rect.top);
		pVertex[1].color = color;
		
		pVertex[2].pos.set(rect.left, rect.bottom);
		pVertex[2].color = color;
		
		pVertex[3].pos.set(rect.right, rect.bottom);
		pVertex[3].color = color;
		
		for (IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = indexOffset + detail::rectIndexTable[i];
		}
		
		m_drawIndexCount += indexSize;
	}
}

# endif
