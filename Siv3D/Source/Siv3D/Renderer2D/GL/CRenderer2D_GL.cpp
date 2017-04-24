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

# include "../../Siv3DEngine.hpp"
# include "../../Graphics/IGraphics.hpp"
# include "CRenderer2D_GL.hpp"
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/FloatQuad.hpp>
# include <Siv3D/Color.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/MathConstants.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr IndexType rectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };
		
		static constexpr IndexType rectFrameIndexTable[24] = { 0, 1, 2, 3, 2, 1, 0, 4, 1, 5, 1, 4, 5, 4, 7, 6, 7, 4, 3, 7, 2, 6, 2, 7 };
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
		
uniform vec4 g_transform[2];

void main()
{
	Color = VertexColor;
	gl_Position.xy	= g_transform[0].zw + VertexPosition.x * g_transform[0].xy + VertexPosition.y * g_transform[1].xy;
	gl_Position.zw	= g_transform[1].zw;
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
		
		::glEnable(GL_BLEND);
		::glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		::glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
		
		m_initialized = true;
		
		return true;
	}
	
	void CRenderer2D_GL::flush()
	{
		const Float2 currentRenderTargetSize = Siv3DEngine::GetGraphics()->getCurrentRenderTargetSize();
		const Mat3x2 currentMat = Mat3x2::Identity();
		const Mat3x2 currentScreen = Mat3x2::Screen(currentRenderTargetSize);
		const Mat3x2 matrix = currentMat * currentScreen;
		
		const float transform[8] =
		{
			matrix._11, matrix._12, matrix._31, matrix._32,
			matrix._21, matrix._22, 0.0f, 1.0f
		};
		
		GLuint uniformLocation = ::glGetUniformLocation(m_programHandle, "g_transform");
		
		::glUniform4fv(uniformLocation, 2, transform);
		
		for (size_t i = 0; i < m_spriteBatch.getBatchCount(); ++i)
		{
			const BatchDrawOffset batchDrawOffset = m_spriteBatch.setBuffers(i);
	
			::glDrawElements(GL_TRIANGLES, batchDrawOffset.indexCount, GL_UNSIGNED_INT, (uint32*)(nullptr) + batchDrawOffset.indexStartLocation);
		}
		
		::glBindVertexArray(0);

		m_spriteBatch.clear();
	}

	void CRenderer2D_GL::addTriangle(const Float2(&pts)[3], const Float4& color)
	{
		constexpr IndexType vertexSize = 3, indexSize = 3;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}

		pVertex[0].pos		= pts[0];
		pVertex[0].color	= color;

		pVertex[1].pos		= pts[1];
		pVertex[1].color	= color;

		pVertex[2].pos		= pts[2];
		pVertex[2].color	= color;

		pIndex[0] = indexOffset;
		pIndex[1] = indexOffset + 1;
		pIndex[2] = indexOffset + 2;
	}

	void CRenderer2D_GL::addTriangle(const Float2(&pts)[3], const Float4(&colors)[3])
	{
		constexpr IndexType vertexSize = 3, indexSize = 3;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}

		pVertex[0].pos		= pts[0];
		pVertex[0].color	= colors[0];

		pVertex[1].pos		= pts[1];
		pVertex[1].color	= colors[1];

		pVertex[2].pos		= pts[2];
		pVertex[2].color	= colors[2];

		pIndex[0] = indexOffset;
		pIndex[1] = indexOffset + 1;
		pIndex[2] = indexOffset + 2;
	}
	
	void CRenderer2D_GL::addRect(const FloatRect& rect, const Float4& color)
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}

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
	}
	
	void CRenderer2D_GL::addRect(const FloatRect& rect, const Float4(&colors)[4])
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}
		
		pVertex[0].pos.set(rect.left, rect.top);
		pVertex[0].color = colors[0];
		
		pVertex[1].pos.set(rect.right, rect.top);
		pVertex[1].color = colors[1];
		
		pVertex[2].pos.set(rect.left, rect.bottom);
		pVertex[2].color = colors[3];
		
		pVertex[3].pos.set(rect.right, rect.bottom);
		pVertex[3].color = colors[2];
		
		for (IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = indexOffset + detail::rectIndexTable[i];
		}
	}

	void CRenderer2D_GL::addRectFrame(const FloatRect& rect, float thickness, const Float4& color)
	{
		constexpr IndexType vertexSize = 8, indexSize = 24;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}

		pVertex[0].pos.set(rect.left - thickness, rect.top - thickness);
		pVertex[1].pos.set(rect.left, rect.top);
		pVertex[2].pos.set(rect.left - thickness, rect.bottom + thickness);
		pVertex[3].pos.set(rect.left, rect.bottom);
		pVertex[4].pos.set(rect.right + thickness, rect.top - thickness);
		pVertex[5].pos.set(rect.right, rect.top);
		pVertex[6].pos.set(rect.right + thickness, rect.bottom + thickness);
		pVertex[7].pos.set(rect.right, rect.bottom);

		for (size_t i = 0; i < 8; ++i)
		{
			(pVertex++)->color = color;
		}

		for (IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = indexOffset + detail::rectFrameIndexTable[i];
		}
	}

	// 仮の実装
	void CRenderer2D_GL::addCircle(const Float2& center, const float r, const Float4& color)
	{
		const float absR = std::abs(r);
		const float centerX = center.x;
		const float centerY = center.y;

		const IndexType quality = static_cast<IndexType>(std::min(absR * 0.225f + 18.0f, 255.0f));
		const IndexType vertexSize = quality + 1, indexSize = quality * 3;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}

		// 中心
		pVertex[0].pos.set(centerX, centerY);

		// 周
		const float radDelta = Math::TwoPiF / quality;

		for (IndexType i = 1; i <= quality; ++i)
		{
			const float rad = radDelta * (i - 1.0f);
			pVertex[i].pos.set(centerX + r * ::cosf(rad), centerY - r * ::sinf(rad));
		}

		for (size_t i = 0; i < vertexSize; ++i)
		{
			(pVertex++)->color = color;
		}

		for (IndexType i = 0; i < quality; ++i)
		{
			pIndex[i * 3 + 0] = indexOffset + (i + 0) + 1;
			pIndex[i * 3 + 1] = indexOffset;
			pIndex[i * 3 + 2] = indexOffset + (i + 1) % quality + 1;
		}
	}
	
	void CRenderer2D_GL::addQuad(const FloatQuad& quad, const Float4& color)
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}
		
		pVertex[0].pos		= quad.p[0];
		pVertex[0].color	= color;
		
		pVertex[1].pos		= quad.p[1];
		pVertex[1].color	= color;
		
		pVertex[2].pos		= quad.p[3];
		pVertex[2].color	= color;
		
		pVertex[3].pos		= quad.p[2];
		pVertex[3].color	= color;
		
		for (IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = indexOffset + detail::rectIndexTable[i];
		}
	}
	
	void CRenderer2D_GL::addQuad(const FloatQuad& quad, const Float4(&colors)[4])
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset))
		{
			return;
		}
		
		pVertex[0].pos		= quad.p[0];
		pVertex[0].color	= colors[0];
		
		pVertex[1].pos		= quad.p[1];
		pVertex[1].color	= colors[1];
		
		pVertex[2].pos		= quad.p[3];
		pVertex[2].color	= colors[3];
		
		pVertex[3].pos		= quad.p[2];
		pVertex[3].color	= colors[2];
		
		for (IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = indexOffset + detail::rectIndexTable[i];
		}
	}
}

# endif
