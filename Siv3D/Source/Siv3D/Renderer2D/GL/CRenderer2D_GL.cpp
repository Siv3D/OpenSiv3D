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
# include "../../Graphics/GL/CGraphics_GL.hpp"
# include "CRenderer2D_GL.hpp"
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/FloatQuad.hpp>
# include <Siv3D/Color.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/MathConstants.hpp>
# include <Siv3D/BlendState.hpp>
# include <Siv3D/Logger.hpp>
# include "../../ConstantBuffer/GL/GLConstantBuffer.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr IndexType rectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };
		
		static constexpr IndexType rectFrameIndexTable[24] = { 0, 1, 2, 3, 2, 1, 0, 4, 1, 5, 1, 4, 5, 4, 7, 6, 7, 4, 3, 7, 2, 6, 2, 7 };

		static constexpr IndexType CalculateCircleFrameQuality(const float size) noexcept
		{
			if (size <= 1.0f)
			{
				return 4;
			}
			else if (size <= 6.0f)
			{
				return 7;
			}
			else if (size <= 8.0f)
			{
				return 11;
			}
			else
			{
				return static_cast<IndexType>(std::min(size * 0.225f + 18.0f, 255.0f));
			}
		}
	}
		
	CRenderer2D_GL::CRenderer2D_GL()
	{

	}

	CRenderer2D_GL::~CRenderer2D_GL()
	{
		if (m_initialized)
		{
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
		
layout(location = 0) in vec2 VertexPosition;
layout(location = 1) in vec2 Tex;
layout(location = 2) in vec4 VertexColor;

layout(location = 0) out vec4 Color;
		
layout(std140) uniform SpriteCB
{
	vec4 g_transform[2];
};

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
		
layout(location = 0) in vec4 Color;

layout(location = 0) out vec4 FragColor;
		
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

		if (!m_shaderProgram.init())
		{
			return false;
		}
		
		m_shaderProgram.attach(m_vertexShader);
		m_shaderProgram.attach(m_pixelShader);

		if (!m_shaderProgram.link())
		{
			return false;
		}
		
		m_shaderProgram.setUniformBlockBinding(m_cbSprite.Name(), m_cbSprite.BindingPoint());
		
		m_shaderProgram.use();

		if (!m_spriteBatch.init())
		{
			return false;
		}

		m_commandManager.reset();
		
		m_initialized = true;
		
		return true;
	}
	
	void CRenderer2D_GL::flush()
	{
		CGraphics_GL* const graphics = dynamic_cast<CGraphics_GL* const>(Siv3DEngine::GetGraphics());
		
		const Size currentRenderTargetSize = Siv3DEngine::GetGraphics()->getCurrentRenderTargetSize();
		
		size_t batchIndex = 0;
		BatchDrawOffset batchDrawOffset;
		
		const Byte* commandPointer = m_commandManager.getCommandBuffer();
		
		//Log(L"----");
		
		for (size_t commandIndex = 0; commandIndex < m_commandManager.getCount(); ++commandIndex)
		{
			const GLRender2DCommandHeader* header = static_cast<const GLRender2DCommandHeader*>(static_cast<const void*>(commandPointer));
			
			switch (header->instruction)
			{
				case GLRender2DInstruction::Nop:
				{
					//Log(L"Nop");
					break;
				}
				case GLRender2DInstruction::Draw:
				{
					const auto* command = static_cast<const GLRender2DCommand<GLRender2DInstruction::Draw>*>(static_cast<const void*>(commandPointer));
					
					//Log(L"Draw: ", command->indexSize);
					::glDrawElements(GL_TRIANGLES, command->indexSize, GL_UNSIGNED_INT, (uint32*)(nullptr) + batchDrawOffset.indexStartLocation);

					batchDrawOffset.indexStartLocation += command->indexSize;
					
					break;
				}
				case GLRender2DInstruction::NextBatch:
				{
					//Log(L"NextBatch: ", batchIndex);
					batchDrawOffset = m_spriteBatch.setBuffers(batchIndex);
					++batchIndex;
					break;
				}
				case GLRender2DInstruction::BlendState:
				{
					const auto* command = static_cast<const GLRender2DCommand<GLRender2DInstruction::BlendState>*>(static_cast<const void*>(commandPointer));
					
					//Log(L"BlendState");
					graphics->getBlendState()->set(command->blendState);
					break;
				}
				case GLRender2DInstruction::Viewport:
				{
					const auto* command = static_cast<const GLRender2DCommand<GLRender2DInstruction::Viewport>*>(static_cast<const void*>(commandPointer));
					
					Rect viewport;
					
					if (command->viewport)
					{
						//Log(L"Viewport: ", *command->viewport);
						viewport = command->viewport.value();
					}
					else
					{
						//Log(L"Viewport reset: ", Rect(0, 0, currentRenderTargetSize));
						viewport.x = 0;
						viewport.y = 0;
						viewport.w = static_cast<float>(currentRenderTargetSize.x);
						viewport.h = static_cast<float>(currentRenderTargetSize.y);
					}
					
					::glViewport(viewport.x, currentRenderTargetSize.y - viewport.h - viewport.y, viewport.w, viewport.h);
					
					const Mat3x2 currentMat = Mat3x2::Identity();
					const Mat3x2 currentScreen = Mat3x2::Screen(viewport.w, viewport.h);
					const Mat3x2 matrix = currentMat * currentScreen;

					m_cbSprite->transform[0].set(matrix._11, matrix._12, matrix._31, matrix._32);
					m_cbSprite->transform[1].set(matrix._21, matrix._22, 0.0f, 1.0f);
					m_cbSprite._internal_update();

					::glBindBufferBase(GL_UNIFORM_BUFFER, m_cbSprite.BindingPoint(), m_cbSprite.base()._detail()->getHandle());
					
					break;
				}
			}
			
			commandPointer += header->commandSize;
		}
		
		::glBindVertexArray(0);

		m_spriteBatch.clear();
		
		m_commandManager.reset();
	}

	void CRenderer2D_GL::setBlendState(const BlendState& state)
	{
		m_commandManager.pushBlendState(state);
	}
	
	BlendState CRenderer2D_GL::getBlendState() const
	{
		return m_commandManager.getCurrentBlendState();
	}
	
	void CRenderer2D_GL::setViewport(const Optional<Rect>& viewport)
	{
		m_commandManager.pushViewport(viewport);
	}
	
	Optional<Rect> CRenderer2D_GL::getViewport() const
	{
		return m_commandManager.getCurrentViewport();
	}
	
	void CRenderer2D_GL::addTriangle(const Float2(&pts)[3], const Float4& color)
	{
		constexpr IndexType vertexSize = 3, indexSize = 3;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
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
		
		m_commandManager.pushDraw(indexSize);
	}

	void CRenderer2D_GL::addTriangle(const Float2(&pts)[3], const Float4(&colors)[3])
	{
		constexpr IndexType vertexSize = 3, indexSize = 3;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
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
		
		m_commandManager.pushDraw(indexSize);
	}
	
	void CRenderer2D_GL::addRect(const FloatRect& rect, const Float4& color)
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
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
		
		m_commandManager.pushDraw(indexSize);
	}
	
	void CRenderer2D_GL::addRect(const FloatRect& rect, const Float4(&colors)[4])
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))		{
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
		
		m_commandManager.pushDraw(indexSize);
	}

	void CRenderer2D_GL::addRectFrame(const FloatRect& rect, float thickness, const Float4& color)
	{
		constexpr IndexType vertexSize = 8, indexSize = 24;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
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
		
		m_commandManager.pushDraw(indexSize);
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

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
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
		
		m_commandManager.pushDraw(indexSize);
	}

	void CRenderer2D_GL::addCircleFrame(const Float2& center, float r, float thickness, const Float4& color)
	{
		const float rt = r + thickness;
		const IndexType quality = detail::CalculateCircleFrameQuality(rt);
		const IndexType vertexSize = quality * 2, indexSize = quality * 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
		{
			return;
		}

		const float centerX = center.x;
		const float centerY = center.y;
		const float radDelta = Math::TwoPiF / quality;

		for (IndexType i = 0; i < quality; ++i)
		{
			const float rad = radDelta * (i - 1.0f);
			const float c = std::cosf(rad);
			const float s = std::sinf(rad);

			pVertex->pos.set(centerX + rt * c, centerY - rt * s);
			pVertex->color = color;
			++pVertex;

			pVertex->pos.set(centerX + r * c, centerY - r * s);
			pVertex->color = color;
			++pVertex;
		}

		for (IndexType i = 0; i < quality; ++i)
		{
			for (IndexType k = 0; k < 6; ++k)
			{
				pIndex[i * 6 + k] = indexOffset + (i * 2 + detail::rectIndexTable[k]) % (quality * 2);
			}
		}
		
		m_commandManager.pushDraw(indexSize);
	}

	void CRenderer2D_GL::addCircleFrame(const Float2& center, float r, float thickness, const Float4& innerColor, const Float4& outerColor)
	{
		const float rt = r + thickness;
		const IndexType quality = detail::CalculateCircleFrameQuality(rt);
		const IndexType vertexSize = quality * 2, indexSize = quality * 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
		{
			return;
		}

		const float centerX = center.x;
		const float centerY = center.y;
		const float radDelta = Math::TwoPiF / quality;

		for (IndexType i = 0; i < quality; ++i)
		{
			const float rad = radDelta * (i - 1.0f);
			const float c = std::cosf(rad);
			const float s = std::sinf(rad);

			pVertex->pos.set(centerX + rt * c, centerY - rt * s);
			pVertex->color = outerColor;
			++pVertex;

			pVertex->pos.set(centerX + r * c, centerY - r * s);
			pVertex->color = innerColor;
			++pVertex;
		}

		for (IndexType i = 0; i < quality; ++i)
		{
			for (IndexType k = 0; k < 6; ++k)
			{
				pIndex[i * 6 + k] = indexOffset + (i * 2 + detail::rectIndexTable[k]) % (quality * 2);
			}
		}
		
		m_commandManager.pushDraw(indexSize);
	}

	void CRenderer2D_GL::addEllipse(const Float2& center, float a, float b, const Float4& color)
	{
		const float majorAxis = std::max(std::abs(a), std::abs(b));
		const IndexType quality = static_cast<IndexType>(std::min(majorAxis * 0.225f + 18.0f, 255.0f));
		const IndexType vertexSize = quality + 1, indexSize = quality * 3;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
		{
			return;
		}

		const float centerX = center.x;
		const float centerY = center.y;

		// 中心
		pVertex[0].pos.set(centerX, centerY);

		// 周
		const float radDelta = Math::TwoPiF / quality;

		for (IndexType i = 1; i <= quality; ++i)
		{
			const float rad = radDelta * (i - 1.0f);
			pVertex[i].pos.set(centerX + a * std::cos(rad), centerY - b * std::sin(rad));
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

		m_commandManager.pushDraw(indexSize);
	}

	void CRenderer2D_GL::addEllipseFrame(const Float2& center, float a, float b, float thickness, const Float4& color)
	{
		const float at = a + thickness;
		const float bt = b + thickness;
		const float majorT = std::max(std::abs(at), std::abs(bt));
		const IndexType quality = detail::CalculateCircleFrameQuality(majorT);
		const IndexType vertexSize = quality * 2, indexSize = quality * 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;

		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
		{
			return;
		}

		const float centerX = center.x;
		const float centerY = center.y;
		const float radDelta = Math::TwoPiF / quality;

		for (IndexType i = 0; i < quality; ++i)
		{
			const float rad = radDelta * (i - 1.0f);
			const float c = std::cosf(rad);
			const float s = std::sinf(rad);

			pVertex->pos.set(centerX + a * c, centerY - b * s);
			pVertex->color = color;
			++pVertex;

			pVertex->pos.set(centerX + at * c, centerY - bt * s);
			pVertex->color = color;
			++pVertex;
		}

		for (IndexType i = 0; i < quality; ++i)
		{
			for (IndexType k = 0; k < 6; ++k)
			{
				pIndex[i * 6 + k] = indexOffset + (i * 2 + detail::rectIndexTable[k]) % (quality * 2);
			}
		}

		m_commandManager.pushDraw(indexSize);
	}

	void CRenderer2D_GL::addQuad(const FloatQuad& quad, const Float4& color)
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
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
		
		m_commandManager.pushDraw(indexSize);
	}
	
	void CRenderer2D_GL::addQuad(const FloatQuad& quad, const Float4(&colors)[4])
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
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
		
		m_commandManager.pushDraw(indexSize);
	}
}

# endif
