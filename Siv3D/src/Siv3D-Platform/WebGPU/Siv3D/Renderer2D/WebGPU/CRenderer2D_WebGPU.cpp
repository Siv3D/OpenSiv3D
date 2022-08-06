//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CRenderer2D_WebGPU.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/WebGPU/CRenderer_WebGPU.hpp>
# include <Siv3D/Shader/WebGPU/CShader_WebGPU.hpp>
# include <Siv3D/ConstantBuffer/WebGPU/ConstantBufferDetail_WebGPU.hpp>
# include <Siv3D/Texture/WebGPU/WebGPURenderTargetState.hpp>

/*/
#	define LOG_COMMAND(...) LOG_TRACE(__VA_ARGS__)
/*/
#	define LOG_COMMAND(...) ((void)0)
//*/

namespace s3d
{
	CRenderer2D_WebGPU::CRenderer2D_WebGPU()
	{
		m_batches.resize(2);
	}

	CRenderer2D_WebGPU::~CRenderer2D_WebGPU()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_WebGPU::~CRenderer2D_WebGPU()");

		//////////////////////////////////////////////////
		//
		//	full screen triangle
		//
		//////////////////////////////////////////////////
	}

	void CRenderer2D_WebGPU::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_WebGPU::init()");

		pRenderer	= static_cast<CRenderer_WebGPU*>(SIV3D_ENGINE(Renderer));
		pShader		= static_cast<CShader_WebGPU*>(SIV3D_ENGINE(Shader));
		pTexture	= static_cast<CTexture_WebGPU*>(SIV3D_ENGINE(Texture));

		m_device = pRenderer->getDevice();

		// 標準 VS をロード
		{
			LOG_INFO(U"📦 Loading vertex shaders for CRenderer2D_WebGPU:");
			m_standardVS = std::make_unique<WebGPUStandardVS2D>();
			m_standardVS->sprite				= WGSL{ Resource(U"engine/shader/wgsl/sprite.vert.wgsl"), { { U"VSConstants2D", 0 } } };
			m_standardVS->fullscreen_triangle	= WGSL{ Resource(U"engine/shader/wgsl/fullscreen_triangle.vert.wgsl"), {} };
			if (not m_standardVS->setup())
			{
				throw EngineError(U"CRenderer2D_WebGPU::m_standardVS initialization failed");
			}
		}

		// 標準 PS をロード
		{
			LOG_INFO(U"📦 Loading pixel shaders for CRenderer2D_WebGPU:");
			m_standardPS = std::make_unique<WebGPUStandardPS2D>();
			m_standardPS->shape					= WGSL{ Resource(U"engine/shader/wgsl/shape.frag.wgsl"), { { U"PSConstants2D", 0 } } };
			m_standardPS->square_dot			= WGSL{ Resource(U"engine/shader/wgsl/square_dot.frag.wgsl"), { { U"PSConstants2D", 0 } } };
			m_standardPS->round_dot				= WGSL{ Resource(U"engine/shader/wgsl/round_dot.frag.wgsl"), { { U"PSConstants2D", 0 } } };
			m_standardPS->texture				= WGSL{ Resource(U"engine/shader/wgsl/texture.frag.wgsl"), { { U"PSConstants2D", 0 } } };
			m_standardPS->fullscreen_triangle	= WGSL{ Resource(U"engine/shader/wgsl/fullscreen_triangle.frag.wgsl"), {} };
			if (not m_standardPS->setup())
			{
				throw EngineError(U"CRenderer2D_WebGPU::m_standardPS initialization failed");
			}
		}

		// Batch 管理を初期化
		{
			for (auto &batch : m_batches)
			{
				if (not batch.init(*m_device))
				{
					throw EngineError(U"WebGPUVertex2DBatch::init() failed");
				}
			}
		}

		// バッファ作成関数を作成
		m_bufferCreator = [this](Vertex2D::IndexType vertexSize, Vertex2D::IndexType indexSize)
		{
			return m_batches[m_drawCount % 2].requestBuffer(vertexSize, indexSize, m_commandManager);
		};

		// シャドウ画像を作成
		{
			const Image boxShadowImage{ Resource(U"engine/texture/box-shadow/256.png") };

			const Array<Image> boxShadowImageMips =
			{
				Image{ Resource(U"engine/texture/box-shadow/128.png") },
				Image{ Resource(U"engine/texture/box-shadow/64.png") },
				Image{ Resource(U"engine/texture/box-shadow/32.png") },
				Image{ Resource(U"engine/texture/box-shadow/16.png") },
				Image{ Resource(U"engine/texture/box-shadow/8.png") },
			};

			m_boxShadowTexture = std::make_unique<Texture>(boxShadowImage, boxShadowImageMips);

			if (m_boxShadowTexture->isEmpty())
			{
				throw EngineError(U"Failed to create a box-shadow texture");
			}
		}

		{
			Image emptyImage{ Size(1, 1), Palette::Yellow };
			m_emptyTexture = std::make_unique<Texture>(emptyImage);
		}
	}

	void CRenderer2D_WebGPU::update()
	{
		m_stat = {};
	}

	const Renderer2DStat& CRenderer2D_WebGPU::getStat() const
	{
		return m_stat;
	}

	void CRenderer2D_WebGPU::addLine(const LineStyle& style, const Float2& begin, const Float2& end, const float thickness, const Float4(&colors)[2])
	{
		if (const auto indexCount = Vertex2DBuilder::BuildLine(style, m_bufferCreator, begin, end, thickness, colors, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				if (style.hasSquareDot())
				{
					m_commandManager.pushStandardPS(m_standardPS->square_dotID);
				}
				else if (style.hasRoundDot())
				{
					m_commandManager.pushStandardPS(m_standardPS->round_dotID);
				}
				else
				{
					m_commandManager.pushStandardPS(m_standardPS->shapeID);
				}
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addTriangle(const Float2(&points)[3], const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildTriangle(m_bufferCreator, points, color))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addTriangle(const Float2(&points)[3], const Float4(&colors)[3])
	{
		if (const auto indexCount = Vertex2DBuilder::BuildTriangle(m_bufferCreator, points, colors))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addRect(const FloatRect& rect, const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildRect(m_bufferCreator, rect, color))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addRect(const FloatRect& rect, const Float4(&colors)[4])
	{
		if (const auto indexCount = Vertex2DBuilder::BuildRect(m_bufferCreator, rect, colors))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addRectFrame(const FloatRect& rect, const float thickness, const Float4& innerColor, const Float4& outerColor)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildRectFrame(m_bufferCreator, rect, thickness, innerColor, outerColor))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addCircle(const Float2& center, const float r, const Float4& innerColor, const Float4& outerColor)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildCircle(m_bufferCreator, center, r, innerColor, outerColor, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addCircleFrame(const Float2& center, const float rInner, const float thickness, const Float4& innerColor, const Float4& outerColor)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildCircleFrame(m_bufferCreator, center, rInner, thickness, innerColor, outerColor, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addCirclePie(const Float2& center, const float r, const float startAngle, const float angle, const Float4& innerColor, const Float4& outerColor)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildCirclePie(m_bufferCreator, center, r, startAngle, angle, innerColor, outerColor, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addCircleArc(const LineStyle& style, const Float2& center, const float rInner, const float startAngle, const float angle, const float thickness, const Float4& innerColor, const Float4& outerColor)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildCircleArc(m_bufferCreator, style, center, rInner, startAngle, angle, thickness, innerColor, outerColor, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addEllipse(const Float2& center, const float a, const float b, const Float4& innerColor, const Float4& outerColor)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildEllipse(m_bufferCreator, center, a, b, innerColor, outerColor, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addEllipseFrame(const Float2& center, const float aInner, const float bInner, const float thickness, const Float4& innerColor, const Float4& outerColor)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildEllipseFrame(m_bufferCreator, center, aInner, bInner, thickness, innerColor, outerColor, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addQuad(const FloatQuad& quad, const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildQuad(m_bufferCreator, quad, color))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addQuad(const FloatQuad& quad, const Float4(&colors)[4])
	{
		if (const auto indexCount = Vertex2DBuilder::BuildQuad(m_bufferCreator, quad, colors))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addRoundRect(const FloatRect& rect, const float w, const float h, const float r, const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildRoundRect(m_bufferCreator, m_buffer, rect, w, h, r, color, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}
	
	void CRenderer2D_WebGPU::addRoundRectFrame(const RoundRect& outer, const RoundRect& inner, const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildRoundRectFrame(m_bufferCreator, m_buffer, outer, inner, color, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addLineString(const LineStyle& style, const Vec2* points, const size_t size, const Optional<Float2>& offset, const float thickness, const bool inner, const Float4& color, const CloseRing closeRing)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildLineString(m_bufferCreator, m_buffer, style, points, size, offset, thickness, inner, color, closeRing, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addLineString(const Vec2* points, const ColorF* colors, size_t size, const Optional<Float2>& offset, const float thickness, const bool inner, const CloseRing closeRing)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildDefaultLineString(m_bufferCreator, points, colors, size, offset, thickness, inner, closeRing, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addPolygon(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Optional<Float2>& offset, const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildPolygon(m_bufferCreator, vertices, indices, offset, color))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addPolygon(const Vertex2D* vertices, const size_t vertexCount, const TriangleIndex* indices, const size_t num_triangles)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildPolygon(m_bufferCreator, vertices, vertexCount, indices, num_triangles))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addPolygonTransformed(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, float s, float c, const Float2& offset, const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildPolygonTransformed(m_bufferCreator, vertices, indices, s, c, offset, color))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addPolygonFrame(const Float2* points, const size_t size, const float thickness, const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildPolygonFrame(m_bufferCreator, m_buffer, points, size, thickness, color, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->shapeID);
			}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addNullVertices(const uint32 count)
	{
		if (not m_currentCustomPS)
		{
			m_commandManager.pushStandardPS(m_standardPS->shapeID);
		}

		m_commandManager.pushNullVertices(count);
	}

	void CRenderer2D_WebGPU::addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildTextureRegion(m_bufferCreator, rect, uv, color))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->textureID);
			}

			m_commandManager.pushPSTexture(0, texture);
			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4])
	{
		if (const auto indexCount = Vertex2DBuilder::BuildTextureRegion(m_bufferCreator, rect, uv, colors))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->textureID);
			}

			m_commandManager.pushPSTexture(0, texture);
			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addTexturedCircle(const Texture& texture, const Circle& circle, const FloatRect& uv, const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildTexturedCircle(m_bufferCreator, circle, uv, color, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->textureID);
			}

			m_commandManager.pushPSTexture(0, texture);
			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildTexturedQuad(m_bufferCreator, quad, uv, color))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->textureID);
			}

			m_commandManager.pushPSTexture(0, texture);
			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addTexturedRoundRect(const Texture& texture, const FloatRect& rect, const float w, const float h, const float r, const FloatRect& uvRect, const Float4& color)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildTexturedRoundRect(m_bufferCreator, m_buffer, rect, w, h, r, uvRect, color, getMaxScaling()))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->textureID);
			}

			m_commandManager.pushPSTexture(0, texture);
			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addTexturedVertices(const Texture& texture, const Vertex2D* vertices, const size_t vertexCount, const TriangleIndex* indices, const size_t num_triangles)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildTexturedVertices(m_bufferCreator, vertices, vertexCount, indices, num_triangles))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->textureID);
			}

			m_commandManager.pushPSTexture(0, texture);
			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_WebGPU::addTexturedParticles(const Texture& texture, const Array<Particle2D>& particles,
		ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc,
		ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc)
	{
		if (const auto indexCount = Vertex2DBuilder::BuildTexturedParticles(m_bufferCreator, particles, sizeOverLifeTimeFunc, colorOverLifeTimeFunc))
		{
			if (not m_currentCustomVS)
			{
				m_commandManager.pushStandardVS(m_standardVS->spriteID);
			}

			if (not m_currentCustomPS)
			{
				m_commandManager.pushStandardPS(m_standardPS->textureID);
			}

			m_commandManager.pushPSTexture(0, texture);
			m_commandManager.pushDraw(indexCount);
		}
	}	

	Float4 CRenderer2D_WebGPU::getColorMul() const
	{
		return m_commandManager.getCurrentColorMul();
	}

	Float4 CRenderer2D_WebGPU::getColorAdd() const
	{
		return m_commandManager.getCurrentColorAdd();
	}

	void CRenderer2D_WebGPU::setColorMul(const Float4& color)
	{
		m_commandManager.pushColorMul(color);
	}

	void CRenderer2D_WebGPU::setColorAdd(const Float4& color)
	{
		m_commandManager.pushColorAdd(color);
	}

	BlendState CRenderer2D_WebGPU::getBlendState() const
	{
		return m_commandManager.getCurrentBlendState();
	}

	RasterizerState CRenderer2D_WebGPU::getRasterizerState() const
	{
		return m_commandManager.getCurrentRasterizerState();
	}

	SamplerState CRenderer2D_WebGPU::getSamplerState(const ShaderStage shaderStage, const uint32 slot) const
	{
		if (shaderStage == ShaderStage::Vertex)
		{
			return m_commandManager.getVSCurrentSamplerState(slot);
		}
		else
		{
			return m_commandManager.getPSCurrentSamplerState(slot);
		}
	}

	void CRenderer2D_WebGPU::setBlendState(const BlendState& state)
	{
		m_commandManager.pushBlendState(state);
	}

	void CRenderer2D_WebGPU::setRasterizerState(const RasterizerState& state)
	{
		m_commandManager.pushRasterizerState(state);
	}

	void CRenderer2D_WebGPU::setSamplerState(const ShaderStage shaderStage, const uint32 slot, const SamplerState& state)
	{
		if (shaderStage == ShaderStage::Vertex)
		{
			m_commandManager.pushVSSamplerState(state, slot);
		}
		else
		{
			m_commandManager.pushPSSamplerState(state, slot);
		}
	}

	void CRenderer2D_WebGPU::setScissorRect(const Rect& rect)
	{
		m_commandManager.pushScissorRect(rect);
	}

	Rect CRenderer2D_WebGPU::getScissorRect() const
	{
		return m_commandManager.getCurrentScissorRect();
	}

	void CRenderer2D_WebGPU::setViewport(const Optional<Rect>& viewport)
	{
		m_commandManager.pushViewport(viewport);
	}

	Optional<Rect> CRenderer2D_WebGPU::getViewport() const
	{
		return m_commandManager.getCurrentViewport();
	}

	void CRenderer2D_WebGPU::setSDFParameters(const std::array<Float4, 3>& params)
	{
		m_commandManager.pushSDFParameters(params);
	}

	void CRenderer2D_WebGPU::setInternalPSConstants(const Float4& value)
	{
		m_commandManager.pushInternalPSConstants(value);
	}

	Optional<VertexShader> CRenderer2D_WebGPU::getCustomVS() const
	{
		return m_currentCustomVS;
	}

	Optional<PixelShader> CRenderer2D_WebGPU::getCustomPS() const
	{
		return m_currentCustomPS;
	}

	void CRenderer2D_WebGPU::setCustomVS(const Optional<VertexShader>& vs)
	{
		if (vs && (not vs->isEmpty()))
		{
			m_currentCustomVS = *vs;
			m_commandManager.pushCustomVS(*vs);
		}
		else
		{
			m_currentCustomVS.reset();
		}
	}

	void CRenderer2D_WebGPU::setCustomPS(const Optional<PixelShader>& ps)
	{
		if (ps && (not ps->isEmpty()))
		{
			m_currentCustomPS = *ps;
			m_commandManager.pushCustomPS(*ps);
		}
		else
		{
			m_currentCustomPS.reset();
		}
	}

	const Mat3x2& CRenderer2D_WebGPU::getLocalTransform() const
	{
		return m_commandManager.getCurrentLocalTransform();
	}

	const Mat3x2& CRenderer2D_WebGPU::getCameraTransform() const
	{
		return m_commandManager.getCurrentCameraTransform();
	}

	void CRenderer2D_WebGPU::setLocalTransform(const Mat3x2& matrix)
	{
		m_commandManager.pushLocalTransform(matrix);
	}

	void CRenderer2D_WebGPU::setCameraTransform(const Mat3x2& matrix)
	{
		m_commandManager.pushCameraTransform(matrix);
	}

	float CRenderer2D_WebGPU::getMaxScaling() const noexcept
	{
		return m_commandManager.getCurrentMaxScaling();
	}

	void CRenderer2D_WebGPU::setVSTexture(const uint32 slot, const Optional<Texture>& texture)
	{
		if (texture)
		{
			m_commandManager.pushVSTexture(slot, *texture);
		}
		else
		{
			m_commandManager.pushVSTextureUnbind(slot);
		}
	}

	void CRenderer2D_WebGPU::setPSTexture(const uint32 slot, const Optional<Texture>& texture)
	{
		if (texture)
		{
			m_commandManager.pushPSTexture(slot, *texture);
		}
		else
		{
			m_commandManager.pushPSTextureUnbind(slot);
		}
	}

	void CRenderer2D_WebGPU::setRenderTarget(const Optional<RenderTexture>& rt)
	{
		if (rt)
		{
			bool hasChanged = false;
			const Texture::IDType textureID = rt->id();

			// バインドされていたら解除
			{
				{
					const auto& currentPSTextures = m_commandManager.getCurrentPSTextures();

					for (uint32 slot = 0; slot < currentPSTextures.size(); ++slot)
					{
						if (currentPSTextures[slot] == textureID)
						{
							m_commandManager.pushPSTextureUnbind(slot);
							hasChanged = true;
						}
					}
				}

				{
					const auto& currentVSTextures = m_commandManager.getCurrentVSTextures();

					for (uint32 slot = 0; slot < currentVSTextures.size(); ++slot)
					{
						if (currentVSTextures[slot] == textureID)
						{
							m_commandManager.pushVSTextureUnbind(slot);
							hasChanged = true;
						}
					}
				}
			}

			if (hasChanged)
			{
				m_commandManager.flush();
			}
		}

		m_commandManager.pushRT(rt);
	}

	Optional<RenderTexture> CRenderer2D_WebGPU::getRenderTarget() const
	{
		return m_commandManager.getCurrentRT();
	}

	void CRenderer2D_WebGPU::setConstantBuffer(const ShaderStage stage, const uint32 slot, const ConstantBufferBase& buffer, const float* data, const uint32 num_vectors)
	{
		m_commandManager.pushConstantBuffer(stage, slot, buffer, data, num_vectors);
	}

	const Texture& CRenderer2D_WebGPU::getBoxShadowTexture() const noexcept
	{
		return *m_boxShadowTexture;
	}

	void CRenderer2D_WebGPU::flush()
	{
		auto encoder = *pRenderer->getCommandEncoder();
		flush(encoder);
	}

	void CRenderer2D_WebGPU::flush(const wgpu::CommandEncoder& encoder)
	{
		WebGPUVertex2DBatch& batch = m_batches[m_drawCount % 2];

		ScopeGuard cleanUp = [this, &batch]()
		{
			batch.reset();
			m_commandManager.reset();
			m_currentCustomVS.reset();
			m_currentCustomPS.reset();
		};

		m_commandManager.flush();

		m_vsConstants2D->colorMul = Float4(1, 1, 1, 1);

		BlendState currentBlendState = BlendState::Default2D;
		RasterizerState currentRasterizerState = RasterizerState::Default2D;

		auto currentRenderingPass = pRenderer->getBackBuffer().begin(encoder);
		auto currentRenderTargetState = pRenderer->getBackBuffer().getRenderTargetState();

		Size currentRenderTargetSize = SIV3D_ENGINE(Renderer)->getSceneBufferSize();
		Rect currentViewportRect{ 0, 0, currentRenderTargetSize.x, currentRenderTargetSize.y };

		Mat3x2 transform = Mat3x2::Identity();
		Mat3x2 screenMat = Mat3x2::Screen(currentRenderTargetSize);

		BatchInfo2D batchInfo;

		LOG_COMMAND(U"----");

		for (const auto& command : m_commandManager.getCommands())
		{
			switch (command.type)
			{
			case WebGPURenderer2DCommandType::Null:
				{
					LOG_COMMAND(U"Null");
					break;
				}
			case WebGPURenderer2DCommandType::SetBuffers:
				{
					//
					LOG_COMMAND(U"SetBuffers[{}]"_fmt(command.index));
					break;
				}
			case WebGPURenderer2DCommandType::UpdateBuffers:
				{
					batchInfo = batch.updateBuffers(*m_device, command.index);

					LOG_COMMAND(U"UpdateBuffers[{}] BatchInfo(indexCount = {}, startIndexLocation = {}, baseVertexLocation = {})"_fmt(
						command.index, batchInfo.indexCount, batchInfo.startIndexLocation, batchInfo.baseVertexLocation));
					break;
				}
			case WebGPURenderer2DCommandType::Draw:
				{
					m_vsConstants2D._update_if_dirty();
					m_psConstants2D._update_if_dirty();

					pShader->setConstantBufferVS(0, m_vsConstants2D.base());
					pShader->setConstantBufferPS(0, m_psConstants2D.base());

					auto pipeline = pShader->usePipelineWithStandard2DVertexLayout(currentRenderingPass, currentRasterizerState, currentBlendState, currentRenderTargetState);
					pRenderer->getSamplerState().bind(m_device, pipeline, currentRenderingPass);

					batch.setBuffers(currentRenderingPass);			

					const WebGPUDrawCommand& draw = m_commandManager.getDraw(command.index);
					const uint32 indexCount = draw.indexCount;
					const uint32 startIndexLocation = batchInfo.startIndexLocation;
					const uint32 baseVertexLocation = batchInfo.baseVertexLocation;

					currentRenderingPass.DrawIndexed(indexCount, 1, startIndexLocation, baseVertexLocation);

					batchInfo.startIndexLocation += indexCount;

					++m_stat.drawCalls;
					m_stat.triangleCount += (indexCount / 3);

					LOG_COMMAND(U"Draw[{}] indexCount = {}, startIndexLocation = {}, baseVertexLocation = {}"_fmt(command.index, indexCount, startIndexLocation, baseVertexLocation));
					break;
				}
			case WebGPURenderer2DCommandType::DrawNull:
				{
					m_vsConstants2D._update_if_dirty();
					m_psConstants2D._update_if_dirty();

					pShader->setConstantBufferVS(0, m_vsConstants2D.base());
					pShader->setConstantBufferPS(0, m_psConstants2D.base());

					auto pipeline = pShader->usePipeline(currentRenderingPass, currentRasterizerState, currentBlendState, currentRenderTargetState, DepthStencilState::Default2D, {});

					const uint32 draw = m_commandManager.getNullDraw(command.index);

					// draw null vertex buffer
					{
						currentRenderingPass.Draw(draw);

						++m_stat.drawCalls;
						m_stat.triangleCount += (draw / 3);

						// batch.setBuffers(pass);
					}

					LOG_COMMAND(U"DrawNull[{}] count = {}"_fmt(command.index, draw));
					break;
				}
			case WebGPURenderer2DCommandType::ColorMul:
				{
					m_vsConstants2D->colorMul = m_commandManager.getColorMul(command.index);
					LOG_COMMAND(U"ColorMul[{}] {}"_fmt(command.index, m_vsConstants2D->colorMul));
					break;
				}
			case WebGPURenderer2DCommandType::ColorAdd:
				{
					m_psConstants2D->colorAdd = m_commandManager.getColorAdd(command.index);
					LOG_COMMAND(U"ColorAdd[{}] {}"_fmt(command.index, m_psConstants2D->colorAdd));
					break;
				}
			case WebGPURenderer2DCommandType::BlendState:
				{
					const auto& blendState = m_commandManager.getBlendState(command.index);
					currentBlendState = blendState;
					LOG_COMMAND(U"BlendState[{}]"_fmt(command.index));
					break;
				}
			case WebGPURenderer2DCommandType::RasterizerState:
				{
					const auto& rasterizerState = m_commandManager.getRasterizerState(command.index);
					currentRasterizerState = rasterizerState;
					LOG_COMMAND(U"RasterizerState[{}]"_fmt(command.index));
					break;
				}
			case WebGPURenderer2DCommandType::VSSamplerState0:
			case WebGPURenderer2DCommandType::VSSamplerState1:
			case WebGPURenderer2DCommandType::VSSamplerState2:
			case WebGPURenderer2DCommandType::VSSamplerState3:
			case WebGPURenderer2DCommandType::VSSamplerState4:
			case WebGPURenderer2DCommandType::VSSamplerState5:
			case WebGPURenderer2DCommandType::VSSamplerState6:
			case WebGPURenderer2DCommandType::VSSamplerState7:
				{
					const uint32 slot = FromEnum(command.type) - FromEnum(WebGPURenderer2DCommandType::VSSamplerState0);
					const auto& samplerState = m_commandManager.getVSSamplerState(slot, command.index);
					pRenderer->getSamplerState().setVSSampler(m_device, slot, samplerState);
					LOG_COMMAND(U"VSSamplerState{}[{}] "_fmt(slot, command.index));
					break;
				}
			case WebGPURenderer2DCommandType::PSSamplerState0:
			case WebGPURenderer2DCommandType::PSSamplerState1:
			case WebGPURenderer2DCommandType::PSSamplerState2:
			case WebGPURenderer2DCommandType::PSSamplerState3:
			case WebGPURenderer2DCommandType::PSSamplerState4:
			case WebGPURenderer2DCommandType::PSSamplerState5:
			case WebGPURenderer2DCommandType::PSSamplerState6:
			case WebGPURenderer2DCommandType::PSSamplerState7:
				{
					const uint32 slot = FromEnum(command.type) - FromEnum(WebGPURenderer2DCommandType::PSSamplerState0);
					const auto& samplerState = m_commandManager.getPSSamplerState(slot, command.index);
					pRenderer->getSamplerState().setPSSampler(m_device, slot, samplerState);
					LOG_COMMAND(U"PSSamplerState{}[{}] "_fmt(slot, command.index));
					break;
				}
			case WebGPURenderer2DCommandType::ScissorRect:
				{
					const auto& scissorRect = m_commandManager.getScissorRect(command.index);

					if (scissorRect.hasArea())
					{
						currentRenderingPass.SetScissorRect(scissorRect.x, scissorRect.y, scissorRect.w, scissorRect.h);
					}

					LOG_COMMAND(U"ScissorRect[{}] {}"_fmt(command.index, scissorRect));
					break;
				}
			case WebGPURenderer2DCommandType::Viewport:
				{
					const auto& viewport = m_commandManager.getViewport(command.index);
					Rect rect;

					if (viewport)
					{
						rect = *viewport;
					}
					else
					{
						rect.x = 0;
						rect.y = 0;
						rect.w = currentRenderTargetSize.x;
						rect.h = currentRenderTargetSize.y;
					}

					rect.w = Min(rect.w, currentRenderTargetSize.x);
					rect.h = Min(rect.h, currentRenderTargetSize.y);

					currentViewportRect = rect;
					currentRenderingPass.SetViewport(rect.x, rect.y, rect.w, rect.h, 0.0f, 1.0f);

					screenMat = Mat3x2::Screen(rect.w, rect.h);
					const Mat3x2 matrix = (transform * screenMat);
					m_vsConstants2D->transform[0].set(matrix._11, matrix._12, matrix._31, matrix._32);
					m_vsConstants2D->transform[1].set(matrix._21, matrix._22, 0.0f, 1.0f);

					LOG_COMMAND(U"Viewport[{}] (x = {}, y = {}, w = {}, h = {})"_fmt(command.index,
						rect.x, rect.y, rect.w, rect.h));
					break;
				}
			case WebGPURenderer2DCommandType::SDFParams:
				{
					const auto& sdfParams = m_commandManager.getSDFParameters(command.index);
					m_psConstants2D->sdfParam		= sdfParams[0];
					m_psConstants2D->sdfOuterColor	= sdfParams[1];
					m_psConstants2D->sdfShadowColor	= sdfParams[2];
					LOG_COMMAND(U"SDFParams[{}] "_fmt(command.index) + Format(sdfParams));
					break;
				}
			case WebGPURenderer2DCommandType::InternalPSConstants:
				{
					const auto& internalPSConstants = m_commandManager.getInternalPSConstants(command.index);
					m_psConstants2D->internal = internalPSConstants;
					LOG_COMMAND(U"SDFParams[{}] "_fmt(command.index) + Format(internalPSConstants));
					break;
				}
			case WebGPURenderer2DCommandType::SetRT:
				{
					const auto& rt = m_commandManager.getRT(command.index);
					
					currentRenderingPass.End();

					if (rt) // [カスタム RenderTexture]
					{
						currentRenderingPass = pTexture->begin(rt->id(), encoder);
						currentRenderTargetState = pTexture->getRenderTargetState(rt->id());
						currentRenderTargetSize = pTexture->getSize(rt->id());

						LOG_COMMAND(U"SetRT[{}] (texture {})"_fmt(command.index, rt->id().value()));
					}
					else // [シーン]
					{
						currentRenderingPass = pRenderer->getBackBuffer().begin(encoder);
						currentRenderTargetState = pRenderer->getBackBuffer().getRenderTargetState();
						currentRenderTargetSize = pRenderer->getBackBuffer().getSceneBufferSize();

						LOG_COMMAND(U"SetRT[{}] (default scene)"_fmt(command.index));
					}

					Rect rect{ currentViewportRect };

					rect.w = Min(rect.w, currentRenderTargetSize.x);
					rect.h = Min(rect.h, currentRenderTargetSize.y);

					currentRenderingPass.SetViewport(0.0f, 0.0f, currentRenderTargetSize.x, currentRenderTargetSize.y, 0.0f, 1.0f);
					break;
				}
			case WebGPURenderer2DCommandType::SetVS:
				{
					const auto& vsID = m_commandManager.getVS(command.index);

					pShader->resetConstantBufferVS();

					if (vsID == VertexShader::IDType::InvalidValue())
					{
						;// [Siv3D ToDo] set null
						LOG_COMMAND(U"SetVS[{}]: null"_fmt(command.index));
					}
					else
					{
						pShader->setVS(vsID);
						LOG_COMMAND(U"SetVS[{}]: {}"_fmt(command.index, vsID.value()));
					}

					break;
				}
			case WebGPURenderer2DCommandType::SetPS:
				{
					const auto& psID = m_commandManager.getPS(command.index);

					pShader->resetConstantBufferPS();

					if (psID == PixelShader::IDType::InvalidValue())
					{
						;// [Siv3D ToDo] set null
						LOG_COMMAND(U"SetPS[{}]: null"_fmt(command.index));
					}
					else
					{
						pShader->setPS(psID);
						LOG_COMMAND(U"SetPS[{}]: {}"_fmt(command.index, psID.value()));
					}

					break;
				}
			case WebGPURenderer2DCommandType::Transform:
				{
					transform = m_commandManager.getCombinedTransform(command.index);
					const Mat3x2 matrix = (transform * screenMat);
					m_vsConstants2D->transform[0].set(matrix._11, matrix._12, matrix._31, matrix._32);
					m_vsConstants2D->transform[1].set(matrix._21, matrix._22, 0.0f, 1.0f);

					LOG_COMMAND(U"Transform[{}] {}"_fmt(command.index, matrix));
					break;
				}
			case WebGPURenderer2DCommandType::SetConstantBuffer:
				{
					auto& cb = m_commandManager.getConstantBuffer(command.index);
					const __m128* p = m_commandManager.getConstantBufferPtr(cb.offset);
					
					if (cb.num_vectors)
					{	
						cb.cbBase._internal_update(p, (cb.num_vectors * 16));

						if (cb.stage == ShaderStage::Vertex)
						{
							pShader->setConstantBufferVS(cb.slot, cb.cbBase);
						}
						else
						{
							pShader->setConstantBufferPS(cb.slot, cb.cbBase);
						}	
					}
					
					LOG_COMMAND(U"SetConstantBuffer[{}] (stage = {}, slot = {}, offset = {}, num_vectors = {})"_fmt(
						command.index, FromEnum(cb.stage), cb.slot, cb.offset, cb.num_vectors));
					break;
				}
			case WebGPURenderer2DCommandType::VSTexture0:
			case WebGPURenderer2DCommandType::VSTexture1:
			case WebGPURenderer2DCommandType::VSTexture2:
			case WebGPURenderer2DCommandType::VSTexture3:
			case WebGPURenderer2DCommandType::VSTexture4:
			case WebGPURenderer2DCommandType::VSTexture5:
			case WebGPURenderer2DCommandType::VSTexture6:
			case WebGPURenderer2DCommandType::VSTexture7:
				{
					const uint32 slot = (FromEnum(command.type) - FromEnum(WebGPURenderer2DCommandType::VSTexture0));
					const auto& textureID = m_commandManager.getVSTexture(slot, command.index);

					if (textureID.isInvalid())
					{
						pRenderer->getSamplerState().setVSTexture(slot, pTexture->getTextureView(m_emptyTexture->id()));
						LOG_COMMAND(U"VSTexture{}[{}]: null"_fmt(slot, command.index));
					}
					else
					{
						pRenderer->getSamplerState().setVSTexture(slot, pTexture->getTextureView(textureID));
						LOG_COMMAND(U"VSTexture{}[{}]: {}"_fmt(slot, command.index, textureID.value()));
					}

					break;
				}
			case WebGPURenderer2DCommandType::PSTexture0:
			case WebGPURenderer2DCommandType::PSTexture1:
			case WebGPURenderer2DCommandType::PSTexture2:
			case WebGPURenderer2DCommandType::PSTexture3:
			case WebGPURenderer2DCommandType::PSTexture4:
			case WebGPURenderer2DCommandType::PSTexture5:
			case WebGPURenderer2DCommandType::PSTexture6:
			case WebGPURenderer2DCommandType::PSTexture7:
				{
					const uint32 slot = (FromEnum(command.type) - FromEnum(WebGPURenderer2DCommandType::PSTexture0));
					const auto& textureID = m_commandManager.getPSTexture(slot, command.index);

					if (textureID.isInvalid())
					{
						pRenderer->getSamplerState().setPSTexture(slot, pTexture->getTextureView(m_emptyTexture->id()));
						LOG_COMMAND(U"VSTexture{}[{}]: null"_fmt(slot, command.index));
					}
					else
					{
						pRenderer->getSamplerState().setPSTexture(slot, pTexture->getTextureView(textureID));
						LOG_COMMAND(U"VSTexture{}[{}]: {}"_fmt(slot, command.index, textureID.value()));
					}

					break;
				}
			}
		}

		currentRenderingPass.End();

		++m_drawCount;
	}

	void CRenderer2D_WebGPU::drawFullScreenTriangle(const wgpu::RenderPassEncoder& pass, const TextureFilter textureFilter)
	{
		// view port
		{
			auto [s, viewRect] = pRenderer->getLetterboxComposition();

			pass.SetViewport(
				viewRect.x,
				viewRect.y,
				viewRect.w,
				viewRect.h,
				0.0f,
				1.0f
			);
		}

		// render states
		{
			pShader->resetConstantBufferVS();
			pShader->resetConstantBufferPS();

			pShader->setVS(m_standardVS->fullscreen_triangle.id());
			pShader->setPS(m_standardPS->fullscreen_triangle.id());		
		}

		// draw fullscreen-triangle
		{
			WebGPURenderTargetState renderTargetState
			{
				.renderTargetFormat = FromEnum(wgpu::TextureFormat::BGRA8Unorm),
				.hasDepth = false,
				.sampleCount = 1
			};

			pShader->usePipeline(pass, RasterizerState::Default2D, BlendState::Default2D, renderTargetState, DepthStencilState::Default2D, {});
			{
				pass.Draw(3);

				++m_stat.drawCalls;
				m_stat.triangleCount += 1;
			}
		}
	}
}
