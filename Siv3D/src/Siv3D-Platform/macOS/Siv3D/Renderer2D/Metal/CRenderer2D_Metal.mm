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

# include "CRenderer2D_Metal.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/Metal/CRenderer_Metal.hpp>
# include <Siv3D/Shader/Metal/CShader_Metal.hpp>
# include <Siv3D/ConstantBuffer/Metal/ConstantBufferDetail_Metal.hpp>

/*
#	define LOG_COMMAND(...) LOG_TRACE(__VA_ARGS__)
/*/
#	define LOG_COMMAND(...) ((void)0)
//*/

namespace s3d
{
	namespace detail
	{
		constexpr MTLTriangleFillMode FillModeTable[4] =
		{
			MTLTriangleFillMode(0),
			MTLTriangleFillMode(0),
			MTLTriangleFillModeLines,
			MTLTriangleFillModeFill,
		};

		constexpr MTLCullMode CullModeTable[4] =
		{
			MTLCullMode(0),
			MTLCullModeNone,
			MTLCullModeFront,
			MTLCullModeBack,
		};
	}

	CRenderer2D_Metal::CRenderer2D_Metal()
	{
	
	}

	CRenderer2D_Metal::~CRenderer2D_Metal()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_Metal::~CRenderer2D_Metal()");
	}

	void CRenderer2D_Metal::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_Metal::init()");
		
		pRenderer = static_cast<CRenderer_Metal*>(SIV3D_ENGINE(Renderer));
		pShader = static_cast<CShader_Metal*>(SIV3D_ENGINE(Shader));
		m_device = pRenderer->getDevice();
		m_commandQueue = pRenderer->getCommandQueue();
		m_swapchain = pRenderer->getSwapchain();

		// 標準 VS をロード
		{
			m_standardVS = std::make_unique<MetalStandardVS2D>();
			m_standardVS->sprite = MSL{ U"VS_Sprite" };
			m_standardVS->fullscreen_triangle = MSL{ U"VS_FullscreenTriangle" };
			if (not m_standardVS->setup())
			{
				throw EngineError(U"CRenderer2D_Metal::m_standardVS initialization failed");
			}
		}

		// 標準 PS をロード
		{
			m_standardPS = std::make_unique<MetalStandardPS2D>();
			m_standardPS->shape = MSL{ U"PS_Shape" };
			m_standardPS->square_dot = MSL{ U"PS_SquareDot" };
			m_standardPS->round_dot = MSL{ U"PS_RoundDot" };
			m_standardPS->fullscreen_triangle = MSL{ U"PS_FullscreenTriangle" };
			if (not m_standardPS->setup())
			{
				throw EngineError(U"CRenderer2D_Metal::m_standardPS initialization failed");
			}
		}
				
		//
		// RenderPipelineState の作成
		//
		{
			m_renderPipelineManager.init(pShader, m_device, *m_standardVS, *m_standardPS, m_swapchain.pixelFormat, pRenderer->getSampleCount());
		}
		
		m_renderPassDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
		
		// Batch 管理を初期化
		{
			if (not m_batches.init(m_device))
			{
				throw EngineError(U"MetalVertex2DBatch::init() failed");
			}
		}

		// バッファ作成関数を作成
		m_bufferCreator = [this](Vertex2D::IndexType vertexSize, Vertex2D::IndexType indexSize)
		{
			return m_batches.requestBuffer(vertexSize, indexSize, m_commandManager);
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

			//if (m_boxShadowTexture->isEmpty())
			//{
			//	throw EngineError(U"Failed to create a box-shadow texture");
			//}
		}
	}

	void CRenderer2D_Metal::update()
	{
		m_stat = {};
	}

	const Renderer2DStat& CRenderer2D_Metal::getStat() const
	{
		return m_stat;
	}

	void CRenderer2D_Metal::addLine(const LineStyle& style, const Float2& begin, const Float2& end, const float thickness, const Float4(&colors)[2])
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

	void CRenderer2D_Metal::addTriangle(const Float2(&points)[3], const Float4& color)
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

	void CRenderer2D_Metal::addTriangle(const Float2(&points)[3], const Float4(&colors)[3])
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

	void CRenderer2D_Metal::addRect(const FloatRect& rect, const Float4& color)
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

	void CRenderer2D_Metal::addRect(const FloatRect& rect, const Float4(&colors)[4])
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

	void CRenderer2D_Metal::addRectFrame(const FloatRect& rect, const float thickness, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_Metal::addCircle(const Float2& center, const float r, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_Metal::addCircleFrame(const Float2& center, const float rInner, const float thickness, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_Metal::addCirclePie(const Float2& center, const float r, const float startAngle, const float angle, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_Metal::addCircleArc(const LineStyle& style, const Float2& center, const float rInner, const float startAngle, const float angle, const float thickness, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_Metal::addEllipse(const Float2& center, const float a, const float b, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_Metal::addEllipseFrame(const Float2& center, const float aInner, const float bInner, const float thickness, const Float4& innerColor, const Float4& outerColor)
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

	void CRenderer2D_Metal::addQuad(const FloatQuad& quad, const Float4& color)
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

	void CRenderer2D_Metal::addQuad(const FloatQuad& quad, const Float4(&colors)[4])
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

	void CRenderer2D_Metal::addRoundRect(const FloatRect& rect, const float w, const float h, const float r, const Float4& color)
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

	void CRenderer2D_Metal::addRoundRectFrame(const RoundRect& outer, const RoundRect& inner, const Float4& color)
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

	void CRenderer2D_Metal::addLineString(const LineStyle& style, const Vec2* points, const size_t size, const Optional<Float2>& offset, const float thickness, const bool inner, const Float4& color, const CloseRing closeRing)
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

	void CRenderer2D_Metal::addLineString(const Vec2* points, const ColorF* colors, size_t size, const Optional<Float2>& offset, const float thickness, const bool inner, const CloseRing closeRing)
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

	void CRenderer2D_Metal::addPolygon(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Optional<Float2>& offset, const Float4& color)
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

	void CRenderer2D_Metal::addPolygon(const Vertex2D* vertices, const size_t vertexCount, const TriangleIndex* indices, const size_t num_triangles)
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

	void CRenderer2D_Metal::addPolygonTransformed(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, float s, float c, const Float2& offset, const Float4& color)
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

	void CRenderer2D_Metal::addPolygonFrame(const Float2* points, const size_t size, const float thickness, const Float4& color)
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

	void CRenderer2D_Metal::addNullVertices(const uint32 count)
	{
		if (not m_currentCustomPS)
		{
			m_commandManager.pushStandardPS(m_standardPS->shapeID);
		}

		m_commandManager.pushNullVertices(count);
	}

	void CRenderer2D_Metal::addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color)
	{

	}

	void CRenderer2D_Metal::addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4])
	{

	}

	void CRenderer2D_Metal::addTexturedCircle(const Texture& texture, const Circle& circle, const FloatRect& uv, const Float4& color)
	{

	}

	void CRenderer2D_Metal::addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color)
	{

	}

	void CRenderer2D_Metal::addTexturedRoundRect(const Texture& texture, const FloatRect& rect, const float w, const float h, const float r, const FloatRect& uvRect, const Float4& color)
	{

	}

	void CRenderer2D_Metal::addTexturedVertices(const Texture& texture, const Vertex2D* vertices, const size_t vertexCount, const TriangleIndex* indices, const size_t num_triangles)
	{

	}

	void CRenderer2D_Metal::addTexturedParticles(const Texture& texture, const Array<Particle2D>& particles,
		ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc,
		ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc)
	{

	}


	Float4 CRenderer2D_Metal::getColorMul() const
	{
		return m_commandManager.getCurrentColorMul();
	}

	Float4 CRenderer2D_Metal::getColorAdd() const
	{
		return m_commandManager.getCurrentColorAdd();
	}

	void CRenderer2D_Metal::setColorMul(const Float4& color)
	{
		m_commandManager.pushColorMul(color);
	}

	void CRenderer2D_Metal::setColorAdd(const Float4& color)
	{
		m_commandManager.pushColorAdd(color);
	}

	BlendState CRenderer2D_Metal::getBlendState() const
	{
		return m_commandManager.getCurrentBlendState();
	}

	RasterizerState CRenderer2D_Metal::getRasterizerState() const
	{
		return m_commandManager.getCurrentRasterizerState();
	}

	SamplerState CRenderer2D_Metal::getSamplerState(const ShaderStage shaderStage, const uint32 slot) const
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

	void CRenderer2D_Metal::setBlendState(const BlendState& state)
	{
		m_commandManager.pushBlendState(state);
	}

	void CRenderer2D_Metal::setRasterizerState(const RasterizerState& state)
	{
		m_commandManager.pushRasterizerState(state);
	}

	void CRenderer2D_Metal::setSamplerState(const ShaderStage shaderStage, const uint32 slot, const SamplerState& state)
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

	void CRenderer2D_Metal::setScissorRect(const Rect&)
	{
		// [Siv3D ToDo]
	}

	Rect CRenderer2D_Metal::getScissorRect() const
	{
		// [Siv3D ToDo]
		return Rect::Empty();
	}

	void CRenderer2D_Metal::setViewport(const Optional<Rect>&)
	{
		// [Siv3D ToDo]
	}

	Optional<Rect> CRenderer2D_Metal::getViewport() const
	{
		// [Siv3D ToDo]
		return none;
	}

	void CRenderer2D_Metal::setSDFParameters(const std::array<Float4, 3>&)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_Metal::setInternalPSConstants(const Float4& value)
	{
		// [Siv3D ToDo]
	}

	Optional<VertexShader> CRenderer2D_Metal::getCustomVS() const
	{
		return m_currentCustomVS;
	}

	Optional<PixelShader> CRenderer2D_Metal::getCustomPS() const
	{
		return m_currentCustomPS;
	}

	void CRenderer2D_Metal::setCustomVS(const Optional<VertexShader>& vs)
	{
		if (vs && (not vs->isEmpty()))
		{
			m_currentCustomVS = vs.value();
			m_commandManager.pushCustomVS(vs.value());
		}
		else
		{
			m_currentCustomVS.reset();
		}
	}

	void CRenderer2D_Metal::setCustomPS(const Optional<PixelShader>& ps)
	{
		if (ps && (not ps->isEmpty()))
		{
			m_currentCustomPS = ps.value();
			m_commandManager.pushCustomPS(ps.value());
		}
		else
		{
			m_currentCustomPS.reset();
		}
	}

	const Mat3x2& CRenderer2D_Metal::getLocalTransform() const
	{
		return m_commandManager.getCurrentLocalTransform();
	}

	const Mat3x2& CRenderer2D_Metal::getCameraTransform() const
	{
		return m_commandManager.getCurrentCameraTransform();
	}

	void CRenderer2D_Metal::setLocalTransform(const Mat3x2& matrix)
	{
		m_commandManager.pushLocalTransform(matrix);
	}

	void CRenderer2D_Metal::setCameraTransform(const Mat3x2& matrix)
	{
		m_commandManager.pushCameraTransform(matrix);
	}

	float CRenderer2D_Metal::getMaxScaling() const noexcept
	{
		return m_commandManager.getCurrentMaxScaling();
	}

	void CRenderer2D_Metal::setVSTexture(const uint32 slot, const Optional<Texture>& texture)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_Metal::setPSTexture(const uint32 slot, const Optional<Texture>& texture)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_Metal::setRenderTarget(const Optional<RenderTexture>& rt)
	{
		// [Siv3D ToDo]
	}

	Optional<RenderTexture> CRenderer2D_Metal::getRenderTarget() const
	{
		// [Siv3D ToDo]
		return(none);
	}

	void CRenderer2D_Metal::setConstantBuffer(const ShaderStage stage, const uint32 slot, const ConstantBufferBase& buffer, const float* data, const uint32 num_vectors)
	{
		m_commandManager.pushConstantBuffer(stage, slot, buffer, data, num_vectors);
	}

	const Texture& CRenderer2D_Metal::getBoxShadowTexture() const noexcept
	{
		return *m_boxShadowTexture;
	}

	void CRenderer2D_Metal::flush()
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_Metal::flush(id<MTLCommandBuffer> commandBuffer)
	{
		ScopeGuard cleanUp = [this]()
		{
			m_commandManager.reset();
			m_currentCustomVS.reset();
			m_currentCustomPS.reset();
		};
		
		m_commandManager.flush();
		
		m_batches.end();
		
		const Size currentRenderTargetSize = pRenderer->getSceneBufferSize();
		Mat3x2 transform = Mat3x2::Identity();
		Mat3x2 screenMat = Mat3x2::Screen(currentRenderTargetSize);

		const ColorF& backgroundColor = pRenderer->getBackgroundColor();
		
		@autoreleasepool {

			if (1 == pRenderer->getSampleCount())
			{
				id<MTLTexture> sceneTexture = pRenderer->getSceneTexture();
				m_renderPassDescriptor.colorAttachments[0].texture = sceneTexture;
				m_renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1);
				m_renderPassDescriptor.colorAttachments[0].loadAction  = MTLLoadActionClear;
				m_renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
			}
			else
			{
				id<MTLTexture> sceneTexture = pRenderer->getSceneTexture();
				id<MTLTexture> resolvedTexture = pRenderer->getResolvedTexture();
				m_renderPassDescriptor.colorAttachments[0].texture = sceneTexture;
				m_renderPassDescriptor.colorAttachments[0].resolveTexture = resolvedTexture;
				m_renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1);
				m_renderPassDescriptor.colorAttachments[0].loadAction  = MTLLoadActionClear;
				m_renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionMultisampleResolve;
			}
		
			{
				id<MTLRenderCommandEncoder> sceneCommandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:m_renderPassDescriptor];
				{
					std::pair<VertexShader::IDType, PixelShader::IDType> currentSetShaders{ VertexShader::IDType::InvalidValue(), PixelShader::IDType::InvalidValue() };
					std::pair<VertexShader::IDType, PixelShader::IDType> currentShaders = currentSetShaders;
					BlendState currentSetBlendState{ false, Blend{ 0 }};
					BlendState currentBlendState = currentSetBlendState;
					RasterizerState currentSetRasterizerState{ FillMode::Solid, CullMode::Off, false, false, 0 };
					
					BatchInfo2D batchInfo;
					size_t viBatchIndex = 0;
					
					LOG_COMMAND(U"----");
					
					for (const auto& command : m_commandManager.getCommands())
					{
						switch (command.type)
						{
						case MetalRenderer2DCommandType::Null:
							{
								LOG_COMMAND(U"Null");
								break;
							}
						case MetalRenderer2DCommandType::SetBuffers:
							{
								// do nothing

								LOG_COMMAND(U"SetBuffers[{}]"_fmt(command.index));
								break;
							}
						case MetalRenderer2DCommandType::UpdateBuffers:
							{
								viBatchIndex = command.index;
								batchInfo = m_batches.updateBuffers(viBatchIndex);
								
								[sceneCommandEncoder setVertexBuffer:m_batches.getCurrentVertexBuffer(viBatchIndex)
												offset:0
											   atIndex:16];

								LOG_COMMAND(U"UpdateBuffers[{}] BatchInfo(indexCount = {}, startIndexLocation = {}, baseVertexLocation = {})"_fmt(
									command.index, batchInfo.indexCount, batchInfo.startIndexLocation, batchInfo.baseVertexLocation));
								break;
							}
						case MetalRenderer2DCommandType::Draw:
							{
								if (currentSetShaders != currentShaders)
								{
									if ((currentShaders.first != VertexShader::IDType::InvalidValue())
										&& (currentShaders.second != PixelShader::IDType::InvalidValue()))
									{
										[sceneCommandEncoder setRenderPipelineState:
										 m_renderPipelineManager.get(currentShaders.first, currentShaders.second, MTLPixelFormatRGBA8Unorm, pRenderer->getSampleCount(), currentBlendState)];
									}
									
									currentSetBlendState = currentBlendState;
									currentSetShaders = currentShaders;
								}
								
								if (m_vsConstants2D._update_if_dirty())
								{
									[sceneCommandEncoder setVertexBytes:m_vsConstants2D.data()
																 length:m_vsConstants2D.size()
																atIndex:0];
								}
								
								if (m_psConstants2D._update_if_dirty())
								{
									[sceneCommandEncoder setFragmentBytes:m_psConstants2D.data()
																   length:m_psConstants2D.size()
																  atIndex:0];
								}
								
								const MetalDrawCommand& draw = m_commandManager.getDraw(command.index);
								const uint32 indexCount = draw.indexCount;
								const uint32 startIndexLocation = batchInfo.startIndexLocation;

								[sceneCommandEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
													indexCount:indexCount
													 indexType:MTLIndexTypeUInt16
												   indexBuffer:m_batches.getCurrentIndexBuffer(viBatchIndex)
											 indexBufferOffset:(sizeof(Vertex2D::IndexType) * startIndexLocation)];
								batchInfo.startIndexLocation += indexCount;

								LOG_COMMAND(U"Draw[{}] indexCount = {}, startIndexLocation = {}"_fmt(command.index, indexCount, startIndexLocation));
								break;
							}
						case MetalRenderer2DCommandType::DrawNull:
							{
								if (currentSetShaders != currentShaders)
								{
									if ((currentShaders.first != VertexShader::IDType::InvalidValue())
										&& (currentShaders.second != PixelShader::IDType::InvalidValue()))
									{
										[sceneCommandEncoder setRenderPipelineState:
										 m_renderPipelineManager.get(currentShaders.first, currentShaders.second, MTLPixelFormatRGBA8Unorm, pRenderer->getSampleCount(), currentBlendState)];
									}
									
									currentSetBlendState = currentBlendState;
									currentSetShaders = currentShaders;
								}
								
								if (m_vsConstants2D._update_if_dirty())
								{
									[sceneCommandEncoder setVertexBytes:m_vsConstants2D.data()
																 length:m_vsConstants2D.size()
																atIndex:0];
								}
								
								if (m_psConstants2D._update_if_dirty())
								{
									[sceneCommandEncoder setFragmentBytes:m_psConstants2D.data()
																   length:m_psConstants2D.size()
																  atIndex:0];
								}

								const uint32 draw = m_commandManager.getNullDraw(command.index);

								// draw null vertex buffer
								{
									[sceneCommandEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:draw];
								}

								LOG_COMMAND(U"DrawNull[{}] count = {}"_fmt(command.index, draw));
								break;
							}
						case MetalRenderer2DCommandType::ColorMul:
							{
								m_vsConstants2D->colorMul = m_commandManager.getColorMul(command.index);
								LOG_COMMAND(U"ColorMul[{}] {}"_fmt(command.index, m_vsConstants2D->colorMul));
								break;
							}
						case MetalRenderer2DCommandType::ColorAdd:
							{
								m_psConstants2D->colorAdd = m_commandManager.getColorAdd(command.index);
								LOG_COMMAND(U"ColorAdd[{}] {}"_fmt(command.index, m_psConstants2D->colorAdd));
								break;
							}
						case MetalRenderer2DCommandType::BlendState:
							{
								const auto& blendState = m_commandManager.getBlendState(command.index);
								currentBlendState = blendState;
								LOG_COMMAND(U"BlendState[{}]"_fmt(command.index));
								break;
							}
						case MetalRenderer2DCommandType::RasterizerState:
							{
								const auto& rasterizerState = m_commandManager.getRasterizerState(command.index);

								if (currentSetRasterizerState != rasterizerState)
								{
									if (rasterizerState.fillMode != currentSetRasterizerState.fillMode)
									{
										[sceneCommandEncoder setTriangleFillMode:detail::FillModeTable[static_cast<uint32>(rasterizerState.fillMode)]];
									}
									
									if (rasterizerState.cullMode != currentSetRasterizerState.cullMode)
									{
										[sceneCommandEncoder setCullMode:detail::CullModeTable[static_cast<uint32>(rasterizerState.cullMode)]];
									}
									
									currentSetRasterizerState = rasterizerState;
								}
								
								LOG_COMMAND(U"RasterizerState[{}]"_fmt(command.index));
								break;
							}
						case MetalRenderer2DCommandType::VSSamplerState0:
						case MetalRenderer2DCommandType::VSSamplerState1:
						case MetalRenderer2DCommandType::VSSamplerState2:
						case MetalRenderer2DCommandType::VSSamplerState3:
						case MetalRenderer2DCommandType::VSSamplerState4:
						case MetalRenderer2DCommandType::VSSamplerState5:
						case MetalRenderer2DCommandType::VSSamplerState6:
						case MetalRenderer2DCommandType::VSSamplerState7:
							{
								const uint32 slot = FromEnum(command.type) - FromEnum(MetalRenderer2DCommandType::VSSamplerState0);
								const auto& samplerState = m_commandManager.getVSSamplerState(slot, command.index);
								[sceneCommandEncoder setVertexSamplerState:pRenderer->getSamplerState().get(samplerState) atIndex:slot];
								LOG_COMMAND(U"VSSamplerState{}[{}] "_fmt(slot, command.index));
								break;
							}
						case MetalRenderer2DCommandType::PSSamplerState0:
						case MetalRenderer2DCommandType::PSSamplerState1:
						case MetalRenderer2DCommandType::PSSamplerState2:
						case MetalRenderer2DCommandType::PSSamplerState3:
						case MetalRenderer2DCommandType::PSSamplerState4:
						case MetalRenderer2DCommandType::PSSamplerState5:
						case MetalRenderer2DCommandType::PSSamplerState6:
						case MetalRenderer2DCommandType::PSSamplerState7:
							{
								const uint32 slot = FromEnum(command.type) - FromEnum(MetalRenderer2DCommandType::PSSamplerState0);
								const auto& samplerState = m_commandManager.getPSSamplerState(slot, command.index);
								[sceneCommandEncoder setFragmentSamplerState:pRenderer->getSamplerState().get(samplerState) atIndex:slot];
								LOG_COMMAND(U"PSSamplerState{}[{}] "_fmt(slot, command.index));
								break;
							}
						case MetalRenderer2DCommandType::SetVS:
							{
								const auto& vsID = m_commandManager.getVS(command.index);

								if (vsID == VertexShader::IDType::InvalidValue())
								{
									;// [Siv3D ToDo] set null
									LOG_COMMAND(U"SetVS[{}]: null"_fmt(command.index));
								}
								else
								{
									currentShaders.first = vsID;
									LOG_COMMAND(U"SetVS[{}]: {}"_fmt(command.index, vsID.value()));
								}

								break;
							}
						case MetalRenderer2DCommandType::SetPS:
							{
								const auto& psID = m_commandManager.getPS(command.index);

								if (psID == PixelShader::IDType::InvalidValue())
								{
									;// [Siv3D ToDo] set null
									LOG_COMMAND(U"SetPS[{}]: null"_fmt(command.index));
								}
								else
								{
									currentShaders.second = psID;
									LOG_COMMAND(U"SetPS[{}]: {}"_fmt(command.index, psID.value()));
								}

								break;
							}
						case MetalRenderer2DCommandType::Transform:
							{
								transform = m_commandManager.getCombinedTransform(command.index);

								const Mat3x2 matrix = (transform * screenMat);
								m_vsConstants2D->transform[0] = Float4(matrix._11, -matrix._12, matrix._31, matrix._32);
								m_vsConstants2D->transform[1] = Float4(matrix._21, matrix._22, 0.0f, 1.0f);

								LOG_COMMAND(U"Transform[{}] {}"_fmt(command.index, matrix));
								break;
							}
						case MetalRenderer2DCommandType::SetConstantBuffer:
							{
								auto& cb = m_commandManager.getConstantBuffer(command.index);
								const __m128* p = m_commandManager.getConstantBufferPtr(cb.offset);

								if (cb.num_vectors)
								{
									//const ConstantBufferDetail_Metal* cbd = static_cast<const ConstantBufferDetail_Metal*>(cb.cbBase._detail());

									if (cb.stage == ShaderStage::Vertex)
									{
										[sceneCommandEncoder setVertexBytes:p
																	 length:(cb.num_vectors * 16)
																	atIndex:cb.slot];
									}
									else if (cb.stage == ShaderStage::Pixel)
									{
										[sceneCommandEncoder setFragmentBytes:p
																	 length:(cb.num_vectors * 16)
																	atIndex:cb.slot];
									}
								}

								LOG_COMMAND(U"SetConstantBuffer[{}] (stage = {}, slot = {}, offset = {}, num_vectors = {})"_fmt(
									command.index, FromEnum(cb.stage), cb.slot, cb.offset, cb.num_vectors));
								break;
							}
						}
					}
				}
				[sceneCommandEncoder endEncoding];
			}
		}
	}

	void CRenderer2D_Metal::drawFullScreenTriangle(id<MTLCommandBuffer> commandBuffer, const TextureFilter textureFilter)
	{
		const ColorF& letterboxColor = pRenderer->getLetterboxColor();
		const auto [s, viewRect] = pRenderer->getLetterboxComposition();
		const MTLViewport viewport = { viewRect.x, viewRect.y, viewRect.w, viewRect.h, 0.0, 1.0 };
		const SamplerState samplerState = (textureFilter == TextureFilter::Linear) ? SamplerState::ClampLinear : SamplerState::ClampNearest;
		
		@autoreleasepool {
			
			id<MTLTexture> sceneTexture =  (1 == pRenderer->getSampleCount()) ? pRenderer->getSceneTexture() : pRenderer->getResolvedTexture();
			id<CAMetalDrawable> drawable = [m_swapchain nextDrawable];
			assert(drawable);

			m_renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(letterboxColor.r, letterboxColor.g, letterboxColor.b, 1);
			m_renderPassDescriptor.colorAttachments[0].loadAction  = MTLLoadActionClear;
			m_renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
			m_renderPassDescriptor.colorAttachments[0].texture = drawable.texture;
			m_renderPassDescriptor.colorAttachments[0].resolveTexture = nil;
			{
				id<MTLRenderCommandEncoder> fullscreenTriangleCommandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:m_renderPassDescriptor];
				{
					[fullscreenTriangleCommandEncoder setRenderPipelineState:m_renderPipelineManager.get(m_standardVS->fullscreen_triangle.id(), m_standardPS->fullscreen_triangle.id(), m_swapchain.pixelFormat, 1, BlendState::Opaque)];
					[fullscreenTriangleCommandEncoder setFragmentTexture:sceneTexture atIndex:0];
					[fullscreenTriangleCommandEncoder setViewport:viewport];
					[fullscreenTriangleCommandEncoder setFragmentSamplerState:pRenderer->getSamplerState().get(samplerState) atIndex:0];
					[fullscreenTriangleCommandEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3];
				}
				[fullscreenTriangleCommandEncoder endEncoding];
			}
			[commandBuffer presentDrawable:drawable];
			
			__weak dispatch_semaphore_t semaphore = m_batches.getSemaphore();
			[commandBuffer addCompletedHandler:^(id<MTLCommandBuffer>)
			{
				dispatch_semaphore_signal(semaphore);
			}];
			
			[commandBuffer commit];
		}
	}

	void CRenderer2D_Metal::begin()
	{
		m_batches.begin();
	}
}
