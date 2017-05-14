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
		
		static IndexType CalculateCirclePieQuality(float size, float angle)
		{
			const float rate = std::min(std::abs(angle) / (Math::TwoPiF) * 2.0f, 1.0f);
			
			IndexType quality;
			
			if (size <= 1.0f)
			{
				quality = 4;
			}
			else if (size <= 6.0f)
			{
				quality = 7;
			}
			else if (size <= 8.0f)
			{
				quality = 11;
			}
			else
			{
				quality = static_cast<IndexType>(std::min(size * 0.225f + 18.0f, 255.0f));
			}
			
			return static_cast<IndexType>(std::max(quality * rate, 3.0f));
		}
	}
		
	CRenderer2D_GL::CRenderer2D_GL()
	{

	}

	CRenderer2D_GL::~CRenderer2D_GL()
	{
		if (m_sampler)
		{
			::glDeleteSamplers(1, &m_sampler);
		}
	}

	bool CRenderer2D_GL::init()
	{
		if (!m_pipeline.init())
		{
			return false;
		}
		
		if (!m_spriteBatch.init())
		{
			return false;
		}

		m_commandManager.reset();
		
		::glGenSamplers(1, &m_sampler);
		::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
		::glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		::glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		::glBindSampler(0, m_sampler);
		
		return true;
	}
	
	void CRenderer2D_GL::flush()
	{
		CGraphics_GL* const graphics = dynamic_cast<CGraphics_GL* const>(Siv3DEngine::GetGraphics());
		CShader_GL* const shader = dynamic_cast<CShader_GL* const>(Siv3DEngine::GetShader());
		
		const Size currentRenderTargetSize = Siv3DEngine::GetGraphics()->getCurrentRenderTargetSize();
		
		size_t batchIndex = 0;
		BatchDrawOffset batchDrawOffset;
		
		const Byte* commandPointer = m_commandManager.getCommandBuffer();
		
		//Log(L"----");
	
		m_pipeline.setVS(shader->getVSProgram(shader->getStandardVS(0).id()));
		m_pipeline.setPS(shader->getPSProgram(shader->getStandardPS(0).id()));
		
		m_pipeline.use();
		
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
					::glDrawElementsBaseVertex(GL_TRIANGLES, command->indexSize, GL_UNSIGNED_INT, (uint32*)(nullptr) + batchDrawOffset.indexStartLocation, batchDrawOffset.vertexStartLocation);
					
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
				case GLRender2DInstruction::RasterizerState:
				{
					const auto* command = static_cast<const GLRender2DCommand<GLRender2DInstruction::RasterizerState>*>(static_cast<const void*>(commandPointer));
					
					//Log(L"RasterizerState");
					graphics->getRasterizerState()->set(command->rasterizerState);
					break;
				}
				case GLRender2DInstruction::SamplerState:
				{
					const auto* command = static_cast<const GLRender2DCommand<GLRender2DInstruction::SamplerState>*>(static_cast<const void*>(commandPointer));
					
					//Log(L"SamplerState");
					graphics->getSamplerState()->set(command->slot, command->samplerState);
					break;
				}
				case GLRender2DInstruction::ScissorRect:
				{
					const auto* command = static_cast<const GLRender2DCommand<GLRender2DInstruction::ScissorRect>*>(static_cast<const void*>(commandPointer));
					
					//Log(L"ScissorRect: ", command->scissorRect);
					const Rect& r = command->scissorRect;
					::glScissor(r.x, currentRenderTargetSize.y - r.h - r.y, r.w, r.h);
					
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
				case GLRender2DInstruction::PixelShader:
				{
					const auto* command = static_cast<const GLRender2DCommand<GLRender2DInstruction::PixelShader>*>(static_cast<const void*>(commandPointer));
					
					//Log(L"PixelShader: id = ", command->psID);
					m_pipeline.setPS(shader->getPSProgram(command->psID));
					shader->setPSSamplerUniform(command->psID);
					
					break;
				}
				case GLRender2DInstruction::PSTexture:
				{
					const auto* command = static_cast<const GLRender2DCommand<GLRender2DInstruction::PSTexture>*>(static_cast<const void*>(commandPointer));
					
					//Log(L"PSTexture: slot = ", command->slot, L", id = ", command->textureID);
					Siv3DEngine::GetTexture()->setPS(command->slot, command->textureID);
					
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
	
	void CRenderer2D_GL::setRasterizerState(const RasterizerState& state)
	{
		m_commandManager.pushRasterizerState(state);
	}
	
	RasterizerState CRenderer2D_GL::getRasterizerState() const
	{
		return m_commandManager.getCurrentRasterizerState();
	}
	
	void CRenderer2D_GL::setSamplerState(const ShaderStage stage, const uint32 slot, const SamplerState& state)
	{
		m_commandManager.pushSamplerState(slot, state);
	}
	
	const std::array<SamplerState, SamplerState::MaxSamplerCount>& CRenderer2D_GL::getSamplerStates(const ShaderStage stage) const
	{
		return m_commandManager.getSamplerStates();
	}

	void CRenderer2D_GL::setScissorRect(const Rect& rect)
	{
		m_commandManager.pushScissorRect(rect);
	}

	Rect CRenderer2D_GL::getScissorRect() const
	{
		return m_commandManager.getCurrentScissorRect();
	}
	
	void CRenderer2D_GL::setViewport(const Optional<Rect>& viewport)
	{
		m_commandManager.pushViewport(viewport);
	}
	
	Optional<Rect> CRenderer2D_GL::getViewport() const
	{
		return m_commandManager.getCurrentViewport();
	}
	
	void CRenderer2D_GL::addLine(const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2])
	{
		constexpr IndexType vertexSize = 4, indexSize = 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
		{
			return;
		}
		
		const float thicknessHalf = thickness * 0.5f;
		const Float2 line = (end - begin).setLength(thicknessHalf);
		const Float2 vNormal(-line.y, line.x);
		const Float2 lineHalf(line * thicknessHalf);
		
		pVertex[0].pos = (begin + vNormal - lineHalf);
		pVertex[0].color = colors[0];
		
		pVertex[1].pos = (begin - vNormal - lineHalf);
		pVertex[1].color = colors[0];
		
		pVertex[2].pos = (end + vNormal + lineHalf);
		pVertex[2].color = colors[1];
		
		pVertex[3].pos = (end - vNormal + lineHalf);
		pVertex[3].color = colors[1];
		
		for (IndexType i = 0; i < indexSize; ++i)
		{
			pIndex[i] = indexOffset + detail::rectIndexTable[i];
		}
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
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
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
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
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
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
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
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
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
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
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
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
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
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
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
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
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
	}
	
	void CRenderer2D_GL::addCirclePie(const Float2& center, float r, float startAngle, float angle, const Float4& color)
	{
		if (angle == 0.0f)
		{
			return;
		}
		
		angle = Clamp(angle, -Math::TwoPiF, Math::TwoPiF);
		
		const IndexType quality = detail::CalculateCirclePieQuality(r, angle);
		const IndexType vertexSize = quality + 1, indexSize = (quality - 1) * 3;
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
		const float radDelta = Math::TwoPiF / (quality - 1);
		const float start = -(startAngle + angle) + Math::HalfPiF;
		const float angleScale = angle / Math::TwoPiF;
		
		for (IndexType i = 1; i <= quality; ++i)
		{
			const float rad = start + (radDelta * (i - 1.0f)) * angleScale;
			pVertex[i].pos.set(centerX + r * std::cosf(rad), centerY - r * std::sinf(rad));
		}
		
		for (size_t i = 0; i < vertexSize; ++i)
		{
			(pVertex++)->color = color;
		}
		
		for (IndexType i = 0; i < quality - 1; ++i)
		{
			pIndex[i * 3 + 0] = indexOffset + (i + 0) + 1;
			pIndex[i * 3 + 1] = indexOffset;
			pIndex[i * 3 + 2] = indexOffset + (i + 1) + 1;
		}
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
	}
	
	void CRenderer2D_GL::addCircleArc(const Float2& center, float r, float startAngle, float angle, float thickness, const Float4& color)
	{
		if (angle == 0.0f)
		{
			return;
		}
		
		angle = Clamp(angle, -Math::TwoPiF, Math::TwoPiF);
		
		const float rt = r + thickness;
		const IndexType quality = detail::CalculateCircleFrameQuality(rt);
		const IndexType vertexSize = quality * 2, indexSize = (quality - 1) * 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
		{
			return;
		}
		
		const float centerX = center.x;
		const float centerY = center.y;
		const float radDelta = Math::TwoPiF / (quality - 1);
		const float start = -(startAngle + angle) + Math::HalfPiF;
		const float angleScale = angle / Math::TwoPiF;
		
		for (IndexType i = 0; i < quality; ++i)
		{
			const float rad = start + (radDelta * i) * angleScale;
			const float c = std::cosf(rad);
			const float s = std::sinf(rad);
			
			pVertex->pos.set(centerX + rt * c, centerY - rt * s);
			pVertex->color = color;
			++pVertex;
			
			pVertex->pos.set(centerX + r * c, centerY - r * s);
			pVertex->color = color;
			++pVertex;
		}
		
		for (IndexType i = 0; i < quality - 1; ++i)
		{
			for (IndexType k = 0; k < 6; ++k)
			{
				pIndex[i * 6 + k] = indexOffset + (i * 2 + detail::rectIndexTable[k]);
			}
		}
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
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

		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
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

		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
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
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
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
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
	}
	
	void CRenderer2D_GL::addLineString(const Vec2* pts, uint32 size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, bool isClosed)
	{
		if (!pts || size < 2)
		{
			return;
		}
		
		// 大昔に書いたコードなので整理したい
		
		const float th2 = 0.01f;
		
		Array<Float2> buf;
		{
			buf.push_back(pts[0]);
			
			for (uint16 i = 1; i < size - 1; ++i)
			{
				const Float2 back = pts[i - 1];
				const Float2 current = pts[i];
				
				if (back.distanceFromSq(current) < th2)
				{
					continue;
				}
				
				buf.push_back(current);
			}
			
			const Float2 back = pts[size - 2];
			const Float2 current = pts[size - 1];
			
			if (back.distanceFromSq(current) >= th2)
			{
				buf.push_back(current);
			}
			
			if (isClosed && buf.size() >= 2 && buf.back().distanceFromSq(buf.front()) <= th2)
			{
				buf.pop_back();
			}
			
			if (buf.size() < 2)
			{
				return;
			}
		}
		
		const float threshold = 0.55f;
		
		Array<Float2> buf2;
		
		buf2.push_back(buf.front());
		
		for (size_t i = 1; i < buf.size() - 1 + isClosed; ++i)
		{
			const Float2 back = buf[i - 1];
			const Float2 current = buf[i];
			const Float2 next = buf[(i + 1) % buf.size()];
			
			const Float2 v1 = (back - current).normalized();
			const Float2 v2 = (next - current).normalized();
			
			buf2.push_back(current);
			
			if (!inner && v1.dot(v2) > threshold)
			{
				const Float2 line = current - back;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
				const Float2 line2 = next - current;
				
				if (tangent.dot(line2) >= (-tangent).dot(line2))
				{
					buf2.push_back(current + tangent.normalized()*th2);
				}
				else if (tangent.dot(line2) <= (-tangent).dot(line2))
				{
					buf2.push_back(current + (-tangent).normalized()*th2);
				}
				else
				{
					buf2.push_back(current + normal*0.001f);
				}
			}
		}
		
		if (isClosed)
		{
			const Float2 back = buf[buf.size() - 1];
			const Float2 current = buf[0];
			const Float2 next = buf[1];
			
			const Float2 v1 = (back - current).normalized();
			const Float2 v2 = (next - current).normalized();
			
			if (!inner && v1.dot(v2) > threshold)
			{
				const Float2 line = current - back;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
				const Float2 line2 = next - current;
				
				if (tangent.dot(line2) >= (-tangent).dot(line2))
				{
					buf2.push_back(current - tangent.normalized() * th2);
				}
				else if (tangent.dot(line2) <= (-tangent).dot(line2))
				{
					buf2.push_back(current - (-tangent).normalized() * th2);
				}
				else
				{
					buf2.push_back(current - normal * 0.001f);
				}
			}
		}
		else
		{
			buf2.push_back(buf.back());
		}
		
		size = static_cast<IndexType>(buf2.size());
		const IndexType vertexSize = size * 2, indexSize = 6 * (size - 1) + (isClosed * 6);
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
		{
			return;
		}
		
		const float thicknessHalf = thickness * 0.5f;
		
		if (isClosed)
		{
			const Float2 p0 = buf2[buf2.size() - 1];
			const Float2 p1 = buf2[0];
			const Float2 p2 = buf2[1];
			const Float2 line = p1 - p0;
			const Float2 normal = Float2{ -line.y, line.x }.normalized();
			const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
			const Float2 miter = Float2{ -tangent.y, tangent.x };
			const float length = thicknessHalf / miter.dot(normal);
			const Float2 result0 = p1 + miter * length;
			const Float2 result1 = p1 - miter * length;
			
			pVertex[0].pos.set(result0);
			pVertex[1].pos.set(result1);
		}
		else
		{
			const Float2 p0 = buf2[0];
			const Float2 p1 = buf2[1];
			const Float2 line = p1 - p0;
			const Float2 normal = Float2{ -line.y, line.x }.normalized();
			const Float2 a = p0 + thicknessHalf * normal;
			const Float2 b = p0 - thicknessHalf * normal;
			
			pVertex[0].pos.set(a);
			pVertex[1].pos.set(b);
		}
		
		for (unsigned short i = 0; i < size - 2; ++i)
		{
			const Float2 p0 = buf2[i];
			const Float2 p1 = buf2[i + 1];
			const Float2 p2 = buf2[i + 2];
			const Float2 line = p1 - p0;
			const Float2 normal = Float2{ -line.y, line.x }.normalized();
			const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
			const Float2 miter = Float2{ -tangent.y, tangent.x };
			const float length = thicknessHalf / miter.dot(normal);
			const Float2 result0 = p1 + miter * length;
			const Float2 result1 = p1 - miter * length;
			
			pVertex[i * 2 + 2].pos.set(result0);
			pVertex[i * 2 + 3].pos.set(result1);
		}
		
		if (isClosed)
		{
			const Float2 p0 = buf2[size - 2];
			const Float2 p1 = buf2[size - 1];
			const Float2 p2 = buf2[0];
			const Float2 line = p1 - p0;
			const Float2 normal = Float2{ -line.y, line.x }.normalized();
			const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
			const Float2 miter = Float2{ -tangent.y, tangent.x };
			const float length = thicknessHalf / miter.dot(normal);
			const Float2 result0 = p1 + miter * length;
			const Float2 result1 = p1 - miter * length;
			
			pVertex[size * 2 - 2].pos.set(result0);
			pVertex[size * 2 - 1].pos.set(result1);
		}
		else
		{
			const Float2 p0 = buf2[size - 2];
			const Float2 p1 = buf2[size - 1];
			const Float2 line = p1 - p0;
			const Float2 normal = Float2{ -line.y, line.x }.normalized();
			const Float2 c = p1 + thicknessHalf * normal;
			const Float2 d = p1 - thicknessHalf * normal;
			
			pVertex[size * 2 - 2].pos.set(c);
			pVertex[size * 2 - 1].pos.set(d);
		}
		
		if (offset)
		{
			const Float2 v = offset.value();
			
			for (IndexType i = 0; i < vertexSize; ++i)
			{
				pVertex[i].pos.moveBy(v);
			}
		}
		
		for (size_t i = 0; i < vertexSize; ++i)
		{
			(pVertex++)->color = color;
		}
		
		for (IndexType k = 0; k < size - 1 + isClosed; ++k)
		{
			for (IndexType i = 0; i < 6; ++i)
			{
				pIndex[k * 6 + i] = (indexOffset + (detail::rectIndexTable[i] + k * 2) % vertexSize);
			}
		}
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
	}
	
	void CRenderer2D_GL::addShape2D(const Array<Float2>& vertices, const Array<uint32>& indices, const Float4& color)
	{
		if (vertices.isEmpty())
		{
			return;
		}
		
		const IndexType vertexSize = static_cast<IndexType>(vertices.size()), indexSize = static_cast<IndexType>(indices.size());
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
		{
			return;
		}
		
		{
			const Float2* pSrc = vertices.data();
			const Float2* pSrcEnd = pSrc + vertices.size();
			
			while (pSrc != pSrcEnd)
			{
				pVertex->pos = *pSrc++;
				pVertex->color = color;
				++pVertex;
			}
		}
		
		static_assert(sizeof(IndexType) == sizeof(uint32));
		{
			::memcpy(pIndex, indices.data(), indices.size_bytes());
		}
		
		for (size_t i = 0; i < indexSize; ++i)
		{
			*(pIndex++) += indexOffset;
		}
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
	}
	
	void CRenderer2D_GL::addShape2DFrame(const Float2* pts, uint32 size, float thickness, const Float4& color)
	{
		if (size < 2)
		{
			return;
		}
		
		// 大昔に書いたコードなので整理したい
		
		const float th2 = 0.01f;
		
		Array<Float2> buf;
		{
			buf.push_back(pts[0]);
			
			for (uint16 i = 1; i < size - 1; ++i)
			{
				const Float2 back = pts[i - 1];
				const Float2 current = pts[i];
				
				if (back.distanceFromSq(current) < th2)
				{
					continue;
				}
				
				buf.push_back(current);
			}
			
			const Float2 back = pts[size - 2];
			const Float2 current = pts[size - 1];
			
			if (back.distanceFromSq(current) >= th2)
			{
				buf.push_back(current);
			}
			
			if (buf.size() >= 2 && buf.back().distanceFromSq(buf.front()) <= th2)
			{
				buf.pop_back();
			}
			
			if (buf.size() < 2)
			{
				return;
			}
		}
		
		const float threshold = 0.55f;
		
		Array<Float2> buf2;
		
		buf2.push_back(buf.front());
		
		for (size_t i = 1; i < buf.size(); ++i)
		{
			const Float2 back = buf[i - 1];
			const Float2 current = buf[i];
			const Float2 next = buf[(i + 1) % buf.size()];
			
			const Float2 v1 = (back - current).normalized();
			const Float2 v2 = (next - current).normalized();
			
			buf2.push_back(current);
			
			if (v1.dot(v2) > threshold)
			{
				const Float2 line = current - back;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
				const Float2 line2 = next - current;
				
				if (tangent.dot(line2) >= (-tangent).dot(line2))
				{
					buf2.push_back(current + tangent.normalized()*th2);
				}
				else if (tangent.dot(line2) <= (-tangent).dot(line2))
				{
					buf2.push_back(current + (-tangent).normalized()*th2);
				}
				else
				{
					buf2.push_back(current + normal*0.001f);
				}
			}
		}
		
		{
			const Float2 back = buf[buf.size() - 1];
			const Float2 current = buf[0];
			const Float2 next = buf[1];
			
			const Float2 v1 = (back - current).normalized();
			const Float2 v2 = (next - current).normalized();
			
			if (v1.dot(v2) > threshold)
			{
				const Float2 line = current - back;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
				const Float2 line2 = next - current;
				
				if (tangent.dot(line2) >= (-tangent).dot(line2))
				{
					buf2.push_back(current - tangent.normalized() * th2);
				}
				else if (tangent.dot(line2) <= (-tangent).dot(line2))
				{
					buf2.push_back(current - (-tangent).normalized() * th2);
				}
				else
				{
					buf2.push_back(current - normal * 0.001f);
				}
			}
		}
		
		size = static_cast<IndexType>(buf2.size());
		const IndexType vertexSize = size * 2, indexSize = 6 * (size - 1) + 6;
		Vertex2D* pVertex;
		IndexType* pIndex;
		IndexType indexOffset;
		
		if (!m_spriteBatch.getBuffer(vertexSize, indexSize, &pVertex, &pIndex, &indexOffset, m_commandManager))
		{
			return;
		}
		
		const float thicknessHalf = thickness * 0.5f;
		
		{
			const Float2 p0 = buf2[buf2.size() - 1];
			const Float2 p1 = buf2[0];
			const Float2 p2 = buf2[1];
			const Float2 line = p1 - p0;
			const Float2 normal = Float2{ -line.y, line.x }.normalized();
			const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
			const Float2 miter = Float2{ -tangent.y, tangent.x };
			const float length = thicknessHalf / miter.dot(normal);
			const Float2 result0 = p1 + miter * length;
			const Float2 result1 = p1 - miter * length;
			
			pVertex[0].pos.set(result0);
			pVertex[1].pos.set(result1);
		}
		
		for (unsigned short i = 0; i < size - 2; ++i)
		{
			const Float2 p0 = buf2[i];
			const Float2 p1 = buf2[i + 1];
			const Float2 p2 = buf2[i + 2];
			const Float2 line = p1 - p0;
			const Float2 normal = Float2{ -line.y, line.x }.normalized();
			const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
			const Float2 miter = Float2{ -tangent.y, tangent.x };
			const float length = thicknessHalf / miter.dot(normal);
			const Float2 result0 = p1 + miter * length;
			const Float2 result1 = p1 - miter * length;
			
			pVertex[i * 2 + 2].pos.set(result0);
			pVertex[i * 2 + 3].pos.set(result1);
		}
		
		{
			const Float2 p0 = buf2[size - 2];
			const Float2 p1 = buf2[size - 1];
			const Float2 p2 = buf2[0];
			const Float2 line = p1 - p0;
			const Float2 normal = Float2{ -line.y, line.x }.normalized();
			const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
			const Float2 miter = Float2{ -tangent.y, tangent.x };
			const float length = thicknessHalf / miter.dot(normal);
			const Float2 result0 = p1 + miter * length;
			const Float2 result1 = p1 - miter * length;
			
			pVertex[size * 2 - 2].pos.set(result0);
			pVertex[size * 2 - 1].pos.set(result1);
		}
		
		for (size_t i = 0; i < vertexSize; ++i)
		{
			(pVertex++)->color = color;
		}
		
		for (IndexType k = 0; k < size; ++k)
		{
			for (IndexType i = 0; i < 6; ++i)
			{
				pIndex[k * 6 + i] = (indexOffset + (detail::rectIndexTable[i] + k * 2) % vertexSize);
			}
		}
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Shape);
	}
	
	void CRenderer2D_GL::addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color)
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
		pVertex[0].tex.set(uv.left, uv.top);
		pVertex[0].color = color;
		
		pVertex[1].pos.set(rect.right, rect.top);
		pVertex[1].tex.set(uv.right, uv.top);
		pVertex[1].color = color;
		
		pVertex[2].pos.set(rect.left, rect.bottom);
		pVertex[2].tex.set(uv.left, uv.bottom);
		pVertex[2].color = color;
		
		pVertex[3].pos.set(rect.right, rect.bottom);
		pVertex[3].tex.set(uv.right, uv.bottom);
		pVertex[3].color = color;
		
		for (IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = indexOffset + detail::rectIndexTable[i];
		}
		
		m_commandManager.pushPSTexture(0, texture);
		
		m_commandManager.pushDraw(indexSize, GLRender2DPixelShaderType::Sprite);
	}
}

# endif
