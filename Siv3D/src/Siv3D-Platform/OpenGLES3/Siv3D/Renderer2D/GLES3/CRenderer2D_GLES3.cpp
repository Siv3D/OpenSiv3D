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

# include "CRenderer2D_GLES3.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/GLES3/CRenderer_GLES3.hpp>
# include <Siv3D/Shader/GLES3/CShader_GLES3.hpp>
# include <Siv3D/ConstantBuffer/GLES3/ConstantBufferDetail_GLES3.hpp>

/*/
#	define LOG_COMMAND(...) LOG_TRACE(__VA_ARGS__)
/*/
#	define LOG_COMMAND(...) ((void)0)
//*/

namespace s3d
{
	CRenderer2D_GLES3::CRenderer2D_GLES3()
	{
		m_batches.resize(2);
	}

	CRenderer2D_GLES3::~CRenderer2D_GLES3()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_GLES3::~CRenderer2D_GLES3()");

		//////////////////////////////////////////////////
		//
		//	full screen triangle
		//
		//////////////////////////////////////////////////

		if (m_sampler)
		{
			::glDeleteSamplers(1, &m_sampler);
			m_sampler = 0;
		}

		if (m_vertexArray)
		{
			::glDeleteVertexArrays(1, &m_vertexArray);
			m_vertexArray = 0;
		}

		CheckOpenGLError();
	}

	void CRenderer2D_GLES3::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_GLES3::init()");

		pRenderer	= static_cast<CRenderer_GLES3*>(SIV3D_ENGINE(Renderer));
		pShader		= static_cast<CShader_GLES3*>(SIV3D_ENGINE(Shader));
		pTexture	= static_cast<CTexture_GLES3*>(SIV3D_ENGINE(Texture));

		// 標準 VS をロード
		{
			LOG_INFO(U"📦 Loading vertex shaders for CRenderer2D_GLES3:");
			m_standardVS = std::make_unique<GLES3StandardVS2D>();
			m_standardVS->sprite				= ESSL{ Resource(U"engine/shader/essl/sprite.vert"), { { U"VSConstants2D", 0 } } };
			m_standardVS->fullscreen_triangle	= ESSL{ Resource(U"engine/shader/essl/fullscreen_triangle.vert"), {} };
			if (not m_standardVS->setup())
			{
				throw EngineError(U"CRenderer2D_GLES3::m_standardVS initialization failed");
			}
		}

		// 標準 PS をロード
		{
			LOG_INFO(U"📦 Loading pixel shaders for CRenderer2D_GLES3:");
			m_standardPS = std::make_unique<GLES3StandardPS2D>();
			m_standardPS->shape					= ESSL{ Resource(U"engine/shader/essl/shape.frag"), { { U"PSConstants2D", 0 } } };
			m_standardPS->square_dot			= ESSL{ Resource(U"engine/shader/essl/square_dot.frag"), { { U"PSConstants2D", 0 } } };
			m_standardPS->round_dot				= ESSL{ Resource(U"engine/shader/essl/round_dot.frag"), { { U"PSConstants2D", 0 } } };
			m_standardPS->texture				= ESSL{ Resource(U"engine/shader/essl/texture.frag"), { { U"PSConstants2D", 0 } } };
			m_standardPS->fullscreen_triangle	= ESSL{ Resource(U"engine/shader/essl/fullscreen_triangle.frag"), {} };
			if (not m_standardPS->setup())
			{
				throw EngineError(U"CRenderer2D_GLES3::m_standardPS initialization failed");
			}
		}

		// Batch 管理を初期化
		{
			for (auto &batch : m_batches)
			{
				if (not batch.init())
				{
					throw EngineError(U"GLES3Vertex2DBatch::init() failed");
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

		// full screen triangle
		{
			::glGenVertexArrays(1, &m_vertexArray);
			::glBindVertexArray(m_vertexArray);

			::glGenSamplers(1, &m_sampler);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		CheckOpenGLError();
	}

	void CRenderer2D_GLES3::update()
	{
		m_stat = {};
	}

	const Renderer2DStat& CRenderer2D_GLES3::getStat() const
	{
		return m_stat;
	}

	void CRenderer2D_GLES3::addLine(const LineStyle& style, const Float2& begin, const Float2& end, const float thickness, const Float4(&colors)[2])
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

	void CRenderer2D_GLES3::addTriangle(const Float2(&points)[3], const Float4& color)
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

	void CRenderer2D_GLES3::addTriangle(const Float2(&points)[3], const Float4(&colors)[3])
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

	void CRenderer2D_GLES3::addRect(const FloatRect& rect, const Float4& color)
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

	void CRenderer2D_GLES3::addRect(const FloatRect& rect, const Float4(&colors)[4])
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

	void CRenderer2D_GLES3::addRectFrame(const FloatRect& rect, const float thickness, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_GLES3::addCircle(const Float2& center, const float r, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_GLES3::addCircleFrame(const Float2& center, const float rInner, const float thickness, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_GLES3::addCirclePie(const Float2& center, const float r, const float startAngle, const float angle, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_GLES3::addCircleArc(const LineStyle& style, const Float2& center, const float rInner, const float startAngle, const float angle, const float thickness, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_GLES3::addEllipse(const Float2& center, const float a, const float b, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_GLES3::addEllipseFrame(const Float2& center, const float aInner, const float bInner, const float thickness, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_GLES3::addQuad(const FloatQuad& quad, const Float4& color)
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

	void CRenderer2D_GLES3::addQuad(const FloatQuad& quad, const Float4(&colors)[4])
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

	void CRenderer2D_GLES3::addRoundRect(const FloatRect& rect, const float w, const float h, const float r, const Float4& color)
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

	void CRenderer2D_GLES3::addRoundRectFrame(const RoundRect& outer, const RoundRect& inner, const Float4& color)
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

	void CRenderer2D_GLES3::addLineString(const LineStyle& style, const Vec2* points, const size_t size, const Optional<Float2>& offset, const float thickness, const bool inner, const Float4& color, const CloseRing closeRing)
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

	void CRenderer2D_GLES3::addLineString(const Vec2* points, const ColorF* colors, size_t size, const Optional<Float2>& offset, const float thickness, const bool inner, const CloseRing closeRing)
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

	void CRenderer2D_GLES3::addPolygon(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Optional<Float2>& offset, const Float4& color)
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

	void CRenderer2D_GLES3::addPolygon(const Vertex2D* vertices, const size_t vertexCount, const TriangleIndex* indices, const size_t num_triangles)
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

	void CRenderer2D_GLES3::addPolygonTransformed(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, float s, float c, const Float2& offset, const Float4& color)
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

	void CRenderer2D_GLES3::addPolygonFrame(const Float2* points, const size_t size, const float thickness, const Float4& color)
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

	void CRenderer2D_GLES3::addNullVertices(const uint32 count)
	{
		if (not m_currentCustomPS)
		{
			m_commandManager.pushStandardPS(m_standardPS->shapeID);
		}

		m_commandManager.pushNullVertices(count);
	}

	void CRenderer2D_GLES3::addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color)
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

	void CRenderer2D_GLES3::addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4])
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

	void CRenderer2D_GLES3::addTexturedCircle(const Texture& texture, const Circle& circle, const FloatRect& uv, const Float4& color)
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

	void CRenderer2D_GLES3::addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color)
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

	void CRenderer2D_GLES3::addTexturedRoundRect(const Texture& texture, const FloatRect& rect, const float w, const float h, const float r, const FloatRect& uvRect, const Float4& color)
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

	void CRenderer2D_GLES3::addTexturedVertices(const Texture& texture, const Vertex2D* vertices, const size_t vertexCount, const TriangleIndex* indices, const size_t num_triangles)
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

	void CRenderer2D_GLES3::addTexturedParticles(const Texture& texture, const Array<Particle2D>& particles,
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

	Float4 CRenderer2D_GLES3::getColorMul() const
	{
		return m_commandManager.getCurrentColorMul();
	}

	Float4 CRenderer2D_GLES3::getColorAdd() const
	{
		return m_commandManager.getCurrentColorAdd();
	}

	void CRenderer2D_GLES3::setColorMul(const Float4& color)
	{
		m_commandManager.pushColorMul(color);
	}

	void CRenderer2D_GLES3::setColorAdd(const Float4& color)
	{
		m_commandManager.pushColorAdd(color);
	}

	BlendState CRenderer2D_GLES3::getBlendState() const
	{
		return m_commandManager.getCurrentBlendState();
	}

	RasterizerState CRenderer2D_GLES3::getRasterizerState() const
	{
		return m_commandManager.getCurrentRasterizerState();
	}

	SamplerState CRenderer2D_GLES3::getSamplerState(const ShaderStage shaderStage, const uint32 slot) const
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

	void CRenderer2D_GLES3::setBlendState(const BlendState& state)
	{
		m_commandManager.pushBlendState(state);
	}

	void CRenderer2D_GLES3::setRasterizerState(const RasterizerState& state)
	{
		m_commandManager.pushRasterizerState(state);
	}

	void CRenderer2D_GLES3::setSamplerState(const ShaderStage shaderStage, const uint32 slot, const SamplerState& state)
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

	void CRenderer2D_GLES3::setScissorRect(const Rect& rect)
	{
		m_commandManager.pushScissorRect(rect);
	}

	Rect CRenderer2D_GLES3::getScissorRect() const
	{
		return m_commandManager.getCurrentScissorRect();
	}

	void CRenderer2D_GLES3::setViewport(const Optional<Rect>& viewport)
	{
		m_commandManager.pushViewport(viewport);
	}

	Optional<Rect> CRenderer2D_GLES3::getViewport() const
	{
		return m_commandManager.getCurrentViewport();
	}

	void CRenderer2D_GLES3::setSDFParameters(const std::array<Float4, 3>& params)
	{
		m_commandManager.pushSDFParameters(params);
	}

	void CRenderer2D_GLES3::setInternalPSConstants(const Float4& value)
	{
		m_commandManager.pushInternalPSConstants(value);
	}

	Optional<VertexShader> CRenderer2D_GLES3::getCustomVS() const
	{
		return m_currentCustomVS;
	}

	Optional<PixelShader> CRenderer2D_GLES3::getCustomPS() const
	{
		return m_currentCustomPS;
	}

	void CRenderer2D_GLES3::setCustomVS(const Optional<VertexShader>& vs)
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

	void CRenderer2D_GLES3::setCustomPS(const Optional<PixelShader>& ps)
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

	const Mat3x2& CRenderer2D_GLES3::getLocalTransform() const
	{
		return m_commandManager.getCurrentLocalTransform();
	}

	const Mat3x2& CRenderer2D_GLES3::getCameraTransform() const
	{
		return m_commandManager.getCurrentCameraTransform();
	}

	void CRenderer2D_GLES3::setLocalTransform(const Mat3x2& matrix)
	{
		m_commandManager.pushLocalTransform(matrix);
	}

	void CRenderer2D_GLES3::setCameraTransform(const Mat3x2& matrix)
	{
		m_commandManager.pushCameraTransform(matrix);
	}

	float CRenderer2D_GLES3::getMaxScaling() const noexcept
	{
		return m_commandManager.getCurrentMaxScaling();
	}

	void CRenderer2D_GLES3::setVSTexture(const uint32 slot, const Optional<Texture>& texture)
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

	void CRenderer2D_GLES3::setPSTexture(const uint32 slot, const Optional<Texture>& texture)
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

	void CRenderer2D_GLES3::setRenderTarget(const Optional<RenderTexture>& rt)
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

	Optional<RenderTexture> CRenderer2D_GLES3::getRenderTarget() const
	{
		return m_commandManager.getCurrentRT();
	}

	void CRenderer2D_GLES3::setConstantBuffer(const ShaderStage stage, const uint32 slot, const ConstantBufferBase& buffer, const float* data, const uint32 num_vectors)
	{
		m_commandManager.pushConstantBuffer(stage, slot, buffer, data, num_vectors);
	}

	const Texture& CRenderer2D_GLES3::getBoxShadowTexture() const noexcept
	{
		return *m_boxShadowTexture;
	}

	void CRenderer2D_GLES3::flush()
	{
		GLES3Vertex2DBatch& batch = m_batches[m_drawCount % 2];

		ScopeGuard cleanUp = [this, &batch]()
		{
			batch.reset();
			m_commandManager.reset();
			m_currentCustomVS.reset();
			m_currentCustomPS.reset();
		};

		m_commandManager.flush();

		pShader->setVS(VertexShader::IDType::NullAsset());
		pShader->setPS(PixelShader::IDType::NullAsset());

		const Size currentRenderTargetSize = SIV3D_ENGINE(Renderer)->getSceneBufferSize();
		::glViewport(0, 0, currentRenderTargetSize.x, currentRenderTargetSize.y);

		Mat3x2 transform = Mat3x2::Identity();
		Mat3x2 screenMat = Mat3x2::Screen(currentRenderTargetSize);

		m_vsConstants2D->colorMul = Float4(1, 1, 1, 1);

		pShader->setConstantBufferVS(0, m_vsConstants2D.base());
		pShader->setConstantBufferPS(0, m_psConstants2D.base());
		pRenderer->getDepthStencilState().set(DepthStencilState::Default2D);
		pRenderer->getBackBuffer().bindSceneToContext();

		BatchInfo2D batchInfo;

		LOG_COMMAND(U"----");

		for (const auto& command : m_commandManager.getCommands())
		{
			switch (command.type)
			{
			case GLES3Renderer2DCommandType::Null:
				{
					LOG_COMMAND(U"Null");
					break;
				}
			case GLES3Renderer2DCommandType::SetBuffers:
				{
					// do nothing

					LOG_COMMAND(U"SetBuffers[{}]"_fmt(command.index));
					break;
				}
			case GLES3Renderer2DCommandType::UpdateBuffers:
				{
					batchInfo = batch.updateBuffers(command.index);

					LOG_COMMAND(U"UpdateBuffers[{}] BatchInfo(indexCount = {}, startIndexLocation = {}, baseVertexLocation = {})"_fmt(
						command.index, batchInfo.indexCount, batchInfo.startIndexLocation, batchInfo.baseVertexLocation));
					break;
				}
			case GLES3Renderer2DCommandType::Draw:
				{
					m_vsConstants2D._update_if_dirty();
					m_psConstants2D._update_if_dirty();

					const GLES3DrawCommand& draw = m_commandManager.getDraw(command.index);
					const uint32 indexCount = draw.indexCount;
					const uint32 startIndexLocation = batchInfo.startIndexLocation;
					// const uint32 baseVertexLocation = batchInfo.baseVertexLocation;
					constexpr Vertex2D::IndexType* pBase = 0;

					::glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, (pBase + startIndexLocation));
					batchInfo.startIndexLocation += indexCount;

					++m_stat.drawCalls;
					m_stat.triangleCount += (indexCount / 3);

					LOG_COMMAND(U"Draw[{}] indexCount = {}, startIndexLocation = {}"_fmt(command.index, indexCount, startIndexLocation));
					break;
				}
			case GLES3Renderer2DCommandType::DrawNull:
				{
					m_vsConstants2D._update_if_dirty();
					m_psConstants2D._update_if_dirty();

					const uint32 draw = m_commandManager.getNullDraw(command.index);

					// draw null vertex buffer
					{
						::glBindVertexArray(m_vertexArray);
						{
							::glBindBuffer(GL_ARRAY_BUFFER, 0);
							::glDrawArrays(GL_TRIANGLES, 0, draw);

							++m_stat.drawCalls;
							m_stat.triangleCount += (draw / 3);
						}
						::glBindVertexArray(0);

						batch.setBuffers();
					}

					LOG_COMMAND(U"DrawNull[{}] count = {}"_fmt(command.index, draw));
					break;
				}
			case GLES3Renderer2DCommandType::ColorMul:
				{
					m_vsConstants2D->colorMul = m_commandManager.getColorMul(command.index);
					LOG_COMMAND(U"ColorMul[{}] {}"_fmt(command.index, m_vsConstants2D->colorMul));
					break;
				}
			case GLES3Renderer2DCommandType::ColorAdd:
				{
					m_psConstants2D->colorAdd = m_commandManager.getColorAdd(command.index);
					LOG_COMMAND(U"ColorAdd[{}] {}"_fmt(command.index, m_psConstants2D->colorAdd));
					break;
				}
			case GLES3Renderer2DCommandType::BlendState:
				{
					const auto& blendState = m_commandManager.getBlendState(command.index);
					pRenderer->getBlendState().set(blendState);
					LOG_COMMAND(U"BlendState[{}]"_fmt(command.index));
					break;
				}
			case GLES3Renderer2DCommandType::RasterizerState:
				{
					const auto& rasterizerState = m_commandManager.getRasterizerState(command.index);
					pRenderer->getRasterizerState().set(rasterizerState);
					LOG_COMMAND(U"RasterizerState[{}]"_fmt(command.index));
					break;
				}
			case GLES3Renderer2DCommandType::VSSamplerState0:
			case GLES3Renderer2DCommandType::VSSamplerState1:
			case GLES3Renderer2DCommandType::VSSamplerState2:
			case GLES3Renderer2DCommandType::VSSamplerState3:
			case GLES3Renderer2DCommandType::VSSamplerState4:
			case GLES3Renderer2DCommandType::VSSamplerState5:
			case GLES3Renderer2DCommandType::VSSamplerState6:
			case GLES3Renderer2DCommandType::VSSamplerState7:
				{
					const uint32 slot = FromEnum(command.type) - FromEnum(GLES3Renderer2DCommandType::VSSamplerState0);
					const auto& samplerState = m_commandManager.getVSSamplerState(slot, command.index);
					pRenderer->getSamplerState().setVS(slot, samplerState);
					LOG_COMMAND(U"VSSamplerState{}[{}] "_fmt(slot, command.index));
					break;
				}
			case GLES3Renderer2DCommandType::PSSamplerState0:
			case GLES3Renderer2DCommandType::PSSamplerState1:
			case GLES3Renderer2DCommandType::PSSamplerState2:
			case GLES3Renderer2DCommandType::PSSamplerState3:
			case GLES3Renderer2DCommandType::PSSamplerState4:
			case GLES3Renderer2DCommandType::PSSamplerState5:
			case GLES3Renderer2DCommandType::PSSamplerState6:
			case GLES3Renderer2DCommandType::PSSamplerState7:
				{
					const uint32 slot = FromEnum(command.type) - FromEnum(GLES3Renderer2DCommandType::PSSamplerState0);
					const auto& samplerState = m_commandManager.getPSSamplerState(slot, command.index);
					pRenderer->getSamplerState().setPS(slot, samplerState);
					LOG_COMMAND(U"PSSamplerState{}[{}] "_fmt(slot, command.index));
					break;
				}
			case GLES3Renderer2DCommandType::ScissorRect:
				{
					const auto& scissorRect = m_commandManager.getScissorRect(command.index);
					::glScissor(scissorRect.x, scissorRect.y, scissorRect.w, scissorRect.h);
					LOG_COMMAND(U"ScissorRect[{}] {}"_fmt(command.index, scissorRect));
					break;
				}
			case GLES3Renderer2DCommandType::Viewport:
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

					::glViewport(rect.x, rect.y, rect.w, rect.h);

					screenMat = Mat3x2::Screen(rect.w, rect.h);
					const Mat3x2 matrix = (transform * screenMat);
					m_vsConstants2D->transform[0].set(matrix._11, -matrix._12, matrix._31, -matrix._32);
					m_vsConstants2D->transform[1].set(matrix._21, -matrix._22, 0.0f, 1.0f);

					LOG_COMMAND(U"Viewport[{}] (x = {}, y = {}, w = {}, h = {})"_fmt(command.index,
						rect.x, rect.y, rect.w, rect.h));
					break;
				}
			case GLES3Renderer2DCommandType::SDFParams:
				{
					const auto& sdfParams = m_commandManager.getSDFParameters(command.index);
					m_psConstants2D->sdfParam		= sdfParams[0];
					m_psConstants2D->sdfOuterColor	= sdfParams[1];
					m_psConstants2D->sdfShadowColor	= sdfParams[2];
					LOG_COMMAND(U"SDFParams[{}] "_fmt(command.index) + Format(sdfParams));
					break;
				}
			case GLES3Renderer2DCommandType::InternalPSConstants:
				{
					const auto& internalPSConstants = m_commandManager.getInternalPSConstants(command.index);
					m_psConstants2D->internal = internalPSConstants;
					LOG_COMMAND(U"SDFParams[{}] "_fmt(command.index) + Format(internalPSConstants));
					break;
				}
			case GLES3Renderer2DCommandType::SetRT:
				{
					const auto& rt = m_commandManager.getRT(command.index);
					
					if (rt) // [カスタム RenderTexture]
					{
						const GLuint frameBuffer = pTexture->getFrameBuffer(rt->id());
						const bool isSRGB = pTexture->getFormat(rt->id()).isSRGB();
						pRenderer->getBackBuffer().bindToScene(frameBuffer);

						// if (isSRGB)
						// {
						// 	::glEnable(GL_FRAMEBUFFER_SRGB);
						// }
						// else
						// {
						// 	::glEnable(GL_FRAMEBUFFER_SRGB);
						// }

						LOG_COMMAND(U"SetRT[{}] (texture {})"_fmt(command.index, rt->id().value()));
					}
					else // [シーン]
					{
						pRenderer->getBackBuffer().bindSceneToContext();
						
						// ::glDisable(GL_FRAMEBUFFER_SRGB);

						LOG_COMMAND(U"SetRT[{}] (default scene)"_fmt(command.index));
					}

					break;
				}
			case GLES3Renderer2DCommandType::SetVS:
				{
					const auto& vsID = m_commandManager.getVS(command.index);

					if (vsID == VertexShader::IDType::InvalidValue())
					{
						;// [Siv3D ToDo] set null
						LOG_COMMAND(U"SetVS[{}]: null"_fmt(command.index));
					}
					else
					{
						pShader->setVS(vsID);
						pShader->usePipeline();
						LOG_COMMAND(U"SetVS[{}]: {}"_fmt(command.index, vsID.value()));
					}

					break;
				}
			case GLES3Renderer2DCommandType::SetPS:
				{
					const auto& psID = m_commandManager.getPS(command.index);

					if (psID == PixelShader::IDType::InvalidValue())
					{
						;// [Siv3D ToDo] set null
						LOG_COMMAND(U"SetPS[{}]: null"_fmt(command.index));
					}
					else
					{
						pShader->setPS(psID);
						pShader->usePipeline();
						LOG_COMMAND(U"SetPS[{}]: {}"_fmt(command.index, psID.value()));
					}

					break;
				}
			case GLES3Renderer2DCommandType::Transform:
				{
					transform = m_commandManager.getCombinedTransform(command.index);
					const Mat3x2 matrix = (transform * screenMat);
					m_vsConstants2D->transform[0].set(matrix._11, -matrix._12, matrix._31, -matrix._32);
					m_vsConstants2D->transform[1].set(matrix._21, -matrix._22, 0.0f, 1.0f);

					LOG_COMMAND(U"Transform[{}] {}"_fmt(command.index, matrix));
					break;
				}
			case GLES3Renderer2DCommandType::SetConstantBuffer:
				{
					auto& cb = m_commandManager.getConstantBuffer(command.index);
					const __m128* p = m_commandManager.getConstantBufferPtr(cb.offset);
					
					if (cb.num_vectors)
					{
						const ConstantBufferDetail_GLES3* cbd = static_cast<const ConstantBufferDetail_GLES3*>(cb.cbBase._detail());
						const uint32 uniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(cb.stage, cb.slot);
						::glBindBufferBase(GL_UNIFORM_BUFFER, uniformBlockBinding, cbd->getHandle());
						cb.cbBase._internal_update(p, (cb.num_vectors * 16));
					}
					
					LOG_COMMAND(U"SetConstantBuffer[{}] (stage = {}, slot = {}, offset = {}, num_vectors = {})"_fmt(
						command.index, FromEnum(cb.stage), cb.slot, cb.offset, cb.num_vectors));
					break;
				}
			case GLES3Renderer2DCommandType::VSTexture0:
			case GLES3Renderer2DCommandType::VSTexture1:
			case GLES3Renderer2DCommandType::VSTexture2:
			case GLES3Renderer2DCommandType::VSTexture3:
			case GLES3Renderer2DCommandType::VSTexture4:
			case GLES3Renderer2DCommandType::VSTexture5:
			case GLES3Renderer2DCommandType::VSTexture6:
			case GLES3Renderer2DCommandType::VSTexture7:
				{
					const uint32 slot = (FromEnum(command.type) - FromEnum(GLES3Renderer2DCommandType::VSTexture0));
					const auto& textureID = m_commandManager.getVSTexture(slot, command.index);

					if (textureID.isInvalid())
					{
						::glActiveTexture(GL_TEXTURE0 + Shader::Internal::MakeSamplerSlot(ShaderStage::Vertex, slot));
						::glBindTexture(GL_TEXTURE_2D, 0);
						LOG_COMMAND(U"VSTexture{}[{}]: null"_fmt(slot, command.index));
					}
					else
					{
						::glActiveTexture(GL_TEXTURE0 + Shader::Internal::MakeSamplerSlot(ShaderStage::Vertex, slot));
						::glBindTexture(GL_TEXTURE_2D, pTexture->getTexture(textureID));
						LOG_COMMAND(U"VSTexture{}[{}]: {}"_fmt(slot, command.index, textureID.value()));
					}

					break;
				}
			case GLES3Renderer2DCommandType::PSTexture0:
			case GLES3Renderer2DCommandType::PSTexture1:
			case GLES3Renderer2DCommandType::PSTexture2:
			case GLES3Renderer2DCommandType::PSTexture3:
			case GLES3Renderer2DCommandType::PSTexture4:
			case GLES3Renderer2DCommandType::PSTexture5:
			case GLES3Renderer2DCommandType::PSTexture6:
			case GLES3Renderer2DCommandType::PSTexture7:
				{
					const uint32 slot = (FromEnum(command.type) - FromEnum(GLES3Renderer2DCommandType::PSTexture0));
					const auto& textureID = m_commandManager.getPSTexture(slot, command.index);

					if (textureID.isInvalid())
					{
						::glActiveTexture(GL_TEXTURE0 + Shader::Internal::MakeSamplerSlot(ShaderStage::Pixel, slot));
						::glBindTexture(GL_TEXTURE_2D, 0);
						LOG_COMMAND(U"PSTexture{}[{}]: null"_fmt(slot, command.index));
					}
					else
					{
						::glActiveTexture(GL_TEXTURE0 + Shader::Internal::MakeSamplerSlot(ShaderStage::Pixel, slot));
						::glBindTexture(GL_TEXTURE_2D, pTexture->getTexture(textureID));
						LOG_COMMAND(U"PSTexture{}[{}]: {}"_fmt(slot, command.index, textureID.value()));
					}

					break;
				}
			}
		}

		::glBindVertexArray(0);

		CheckOpenGLError();

		++m_drawCount;
	}

	void CRenderer2D_GLES3::drawFullScreenTriangle(const TextureFilter textureFilter)
	{
		// view port
		{
			::glBindFramebuffer(GL_FRAMEBUFFER, 0);
			auto [s, viewRect] = pRenderer->getLetterboxComposition();
			::glViewport(
				static_cast<int32>(viewRect.x),
				static_cast<int32>(viewRect.y),
				static_cast<int32>(viewRect.w),
				static_cast<int32>(viewRect.h));
		}

		// render states
		{
			const bool linearFilter = (textureFilter == TextureFilter::Linear);
			::glBindSampler(0, m_sampler);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST);
		
			pRenderer->getBlendState().set(BlendState::Opaque);
			pRenderer->getRasterizerState().set(RasterizerState::Default2D);
			pShader->setVS(m_standardVS->fullscreen_triangle.id());
			pShader->setPS(m_standardPS->fullscreen_triangle.id());
		}

		// draw fullscreen-triangle
		{
			pShader->usePipeline();
			{
				::glBindVertexArray(m_vertexArray);
				{
					::glBindBuffer(GL_ARRAY_BUFFER, 0);
					::glDrawArrays(GL_TRIANGLES, 0, 3);

					++m_stat.drawCalls;
					m_stat.triangleCount += 1;
				}
				::glBindVertexArray(0);
			}
		}

		CheckOpenGLError();
	}
}
