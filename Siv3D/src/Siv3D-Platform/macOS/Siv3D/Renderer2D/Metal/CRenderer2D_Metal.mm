//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CRenderer2D_Metal.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/Metal/CRenderer_Metal.hpp>
# include <Siv3D/Shader/Metal/CShader_Metal.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/ShaderCommon.hpp>

/*
#	define LOG_COMMAND(...) LOG_TRACE(__VA_ARGS__)
/*/
#	define LOG_COMMAND(...) ((void)0)
//*/

namespace s3d
{
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
		
		pRenderer = dynamic_cast<CRenderer_Metal*>(SIV3D_ENGINE(Renderer));
		pShader = dynamic_cast<CShader_Metal*>(SIV3D_ENGINE(Shader));
		m_device = pRenderer->getDevice();
		m_commandQueue = pRenderer->getCommandQueue();
		m_swapchain = pRenderer->getSwapchain();

		// 標準 VS をロード
		{
			m_standardVS = std::make_unique<MetalStandardVS2D>();
			m_standardVS->sprite = MSL(U"VS_Sprite");
			m_standardVS->fullscreen_triangle = MSL(U"VS_FullscreenTriangle");
			if (!m_standardVS->ok())
			{
				throw EngineError(U"CRenderer2D_Metal::m_standardVS initialization failed");
			}
		}

		// 標準 PS をロード
		{
			m_standardPS = std::make_unique<MetalStandardPS2D>();
			m_standardPS->shape = MSL(U"PS_Shape");
			m_standardPS->fullscreen_triangle = MSL(U"PS_FullscreenTriangle");
			if (!m_standardPS->ok())
			{
				throw EngineError(U"CRenderer2D_Metal::m_standardPS initialization failed");
			}
		}
		
		MTLVertexDescriptor* vertexDescriptor = [MTLVertexDescriptor new];
		{
			vertexDescriptor.attributes[0].format = MTLVertexFormatFloat2;
			vertexDescriptor.attributes[0].offset = 0;
			vertexDescriptor.attributes[0].bufferIndex = 0;
			vertexDescriptor.attributes[1].format = MTLVertexFormatFloat2;
			vertexDescriptor.attributes[1].offset = 8;
			vertexDescriptor.attributes[1].bufferIndex = 0;
			vertexDescriptor.attributes[2].format = MTLVertexFormatFloat4;
			vertexDescriptor.attributes[2].offset = 16;
			vertexDescriptor.attributes[2].bufferIndex = 0;
			vertexDescriptor.layouts[0].stride = 32;
		}
		
		//
		// RenderPipelineState の作成
		//
		{
			MTLRenderPipelineDescriptor* rpd = [MTLRenderPipelineDescriptor new];
			{
				rpd.vertexFunction = pShader->getFunctionVS(m_standardVS->sprite.id());
				rpd.fragmentFunction = pShader->getFunctionPS(m_standardPS->shape.id());
				rpd.colorAttachments[0].pixelFormat = MTLPixelFormatRGBA8Unorm;
				rpd.vertexDescriptor = vertexDescriptor;
				rpd.sampleCount = pRenderer->getSampleCount();
			}
			m_sceneRenderPipelineState = [m_device newRenderPipelineStateWithDescriptor:rpd error:NULL];
			assert(m_sceneRenderPipelineState);
			
			{
				rpd.vertexFunction = pShader->getFunctionVS(m_standardVS->fullscreen_triangle.id());
				rpd.fragmentFunction = pShader->getFunctionPS(m_standardPS->fullscreen_triangle.id());
				rpd.colorAttachments[0].pixelFormat = m_swapchain.pixelFormat;
				rpd.vertexDescriptor = nil;
				rpd.sampleCount = 1;
			}
			m_fullscreenTriangleRenderPipelineState = [m_device newRenderPipelineStateWithDescriptor:rpd error:NULL];
			assert(m_fullscreenTriangleRenderPipelineState);
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
	}

	void CRenderer2D_Metal::addLine(const Float2& begin, const Float2& end, const float thickness, const Float4(&colors)[2])
	{
		if (const auto indexCount = Vertex2DBuilder::BuildDefaultLine(m_bufferCreator, begin, end, thickness, colors))
		{
			//if (!m_currentCustomPS)
			//{
			//	m_commands.pushStandardPS(m_standardPS->shapeID);
			//}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_Metal::addRect(const FloatRect& rect, const Float4& color)
	{
		if (const uint16 indexCount = Vertex2DBuilder::BuildRect(m_bufferCreator, rect, color))
		{
			//if (!m_currentCustomPS)
			//{
			//	m_commandManager.pushStandardPS(m_standardPS->shapeID);
			//}

			m_commandManager.pushDraw(indexCount);
		}
	}

	void CRenderer2D_Metal::flush(id<MTLCommandBuffer> commandBuffer)
	{
		ScopeGuard cleanUp = [this]()
		{
			m_commandManager.reset();
		};
		
		m_commandManager.flush();
		
		m_batches.end();
		
		const Size currentRenderTargetSize = pRenderer->getSceneBufferSize();
		Mat3x2 transform = Mat3x2::Identity();
		Mat3x2 screenMat = Mat3x2::Screen(currentRenderTargetSize);
		const Mat3x2 matrix = transform * screenMat;
		
		const ColorF& backgroundColor = pRenderer->getBackgroundColor();
		
		m_vsConstants2D->transform[0] = Float4(matrix._11, -matrix._12, matrix._31, matrix._32);
		m_vsConstants2D->transform[1] = Float4(matrix._21, matrix._22, 0.0f, 1.0f);
		m_vsConstants2D->colorMul = Float4(1, 1, 1, 1);
		
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
					//MetalBatchInfo batchInfo;
					[sceneCommandEncoder setRenderPipelineState:m_sceneRenderPipelineState];
					[sceneCommandEncoder setVertexBytes:m_vsConstants2D.data()
								   length:m_vsConstants2D.size()
								  atIndex:1];
					[sceneCommandEncoder setFragmentBytes:m_psConstants2D.data()
								   length:m_psConstants2D.size()
								  atIndex:1];
					
					MetalBatchInfo batchInfo;
					size_t viBatchIndex = 0;
					
					LOG_COMMAND(U"-2D-");
					
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
											   atIndex:0];

								LOG_COMMAND(U"UpdateBuffers[{}] BatchInfo(indexCount = {}, startIndexLocation = {}, baseVertexLocation = {})"_fmt(
									command.index, batchInfo.indexCount, batchInfo.startIndexLocation, batchInfo.baseVertexLocation));
								break;
							}
						case MetalRenderer2DCommandType::Draw:
							{
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
					[fullscreenTriangleCommandEncoder setRenderPipelineState:m_fullscreenTriangleRenderPipelineState];
					[fullscreenTriangleCommandEncoder setFragmentTexture:sceneTexture atIndex:0];
					[fullscreenTriangleCommandEncoder setViewport:viewport];
					pRenderer->getSamplerState().setPS(fullscreenTriangleCommandEncoder, 0, samplerState);
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
