//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "MetalRenderPipeline2DManager.hpp"
# include <Siv3D/Shader/Metal/CShader_Metal.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr MTLBlendOperation BlendOperationTable[6] =
		{
			MTLBlendOperation(0),
			MTLBlendOperationAdd,
			MTLBlendOperationSubtract,
			MTLBlendOperationReverseSubtract,
			MTLBlendOperationMin,
			MTLBlendOperationMax
		};

		static constexpr MTLBlendFactor BlendFactorTable[20] =
		{
			MTLBlendFactor(0),
			MTLBlendFactorZero,
			MTLBlendFactorOne,
			MTLBlendFactorSourceColor,
			MTLBlendFactorOneMinusSourceColor,
			MTLBlendFactorSourceAlpha,
			MTLBlendFactorOneMinusSourceAlpha,
			MTLBlendFactorDestinationAlpha,
			MTLBlendFactorOneMinusDestinationAlpha,
			MTLBlendFactorDestinationColor,
			MTLBlendFactorOneMinusDestinationColor,
			MTLBlendFactorSourceAlphaSaturated,
			MTLBlendFactor(0),
			MTLBlendFactor(0),
			MTLBlendFactorBlendColor,
			MTLBlendFactorOneMinusBlendColor,
			MTLBlendFactorSource1Color,
			MTLBlendFactorOneMinusSource1Color,
			MTLBlendFactorSource1Alpha,
			MTLBlendFactorOneMinusSource1Alpha,
		};
	
		[[nodiscard]]
		static bool HasStandardVertexLayout(id<MTLFunction> vertexFunction)
		{
			return (vertexFunction.stageInputAttributes.count == 3);
		}
	}

	void MetalRenderPipeline2DManager::init(CShader_Metal* _pShader, id<MTLDevice> device, const MetalStandardVS2D& standardVS, const MetalStandardPS2D& standardPS, const MTLPixelFormat swapchainFormat, const uint32 sampleCount)
	{
		pShader = _pShader;
		
		m_device = device;
		
		m_renderPipelineDescriptor = [MTLRenderPipelineDescriptor new];
		
		m_standardVertexDescriptor = [MTLVertexDescriptor new];
		{
			m_standardVertexDescriptor.attributes[0].format = MTLVertexFormatFloat2;
			m_standardVertexDescriptor.attributes[0].offset = 0;
			m_standardVertexDescriptor.attributes[0].bufferIndex = 0;
			m_standardVertexDescriptor.attributes[1].format = MTLVertexFormatFloat2;
			m_standardVertexDescriptor.attributes[1].offset = 8;
			m_standardVertexDescriptor.attributes[1].bufferIndex = 0;
			m_standardVertexDescriptor.attributes[2].format = MTLVertexFormatFloat4;
			m_standardVertexDescriptor.attributes[2].offset = 16;
			m_standardVertexDescriptor.attributes[2].bufferIndex = 0;
			m_standardVertexDescriptor.layouts[0].stride = 32;
		}
		
		add(standardVS.sprite.id(), standardPS.shape.id(), MTLPixelFormatRGBA8Unorm, sampleCount, BlendState::Default2D);
		add(standardVS.fullscreen_triangle.id(), standardPS.fullscreen_triangle.id(), swapchainFormat, 1, BlendState::Opaque);
	}

	void MetalRenderPipeline2DManager::add(const VertexShader::IDType vsID, const PixelShader::IDType psID, const MTLPixelFormat pixelFormat, const uint32 sampleCount, const BlendState& blendState)
	{
		const KeyType key{ vsID, psID, pixelFormat, sampleCount, blendState };

		if (m_pipelineStates.contains(key))
		{
			return;
		}
		
		{
			m_renderPipelineDescriptor.vertexFunction = pShader->getFunctionVS(vsID);
			m_renderPipelineDescriptor.fragmentFunction = pShader->getFunctionPS(psID);
			m_renderPipelineDescriptor.colorAttachments[0].pixelFormat = pixelFormat;
			
			m_renderPipelineDescriptor.colorAttachments[0].blendingEnabled = static_cast<bool>(blendState.enable);
			m_renderPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = detail::BlendFactorTable[static_cast<uint32>(blendState.src)];
			m_renderPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = detail::BlendFactorTable[static_cast<uint32>(blendState.dst)];
			m_renderPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = detail::BlendFactorTable[static_cast<uint32>(blendState.srcAlpha)];
			m_renderPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = detail::BlendFactorTable[static_cast<uint32>(blendState.dstAlpha)];
			m_renderPipelineDescriptor.colorAttachments[0].rgbBlendOperation = detail::BlendOperationTable[static_cast<uint32>(blendState.op)];
			m_renderPipelineDescriptor.colorAttachments[0].alphaBlendOperation = detail::BlendOperationTable[static_cast<uint32>(blendState.opAlpha)];
			m_renderPipelineDescriptor.colorAttachments[0].writeMask =
				(MTLColorWriteMaskRed * blendState.writeR) | (MTLColorWriteMaskGreen * blendState.writeG)
			  | (MTLColorWriteMaskBlue * blendState.writeB) | (MTLColorWriteMaskAlpha * blendState.writeA);
			
			m_renderPipelineDescriptor.vertexDescriptor = detail::HasStandardVertexLayout(m_renderPipelineDescriptor.vertexFunction) ? m_standardVertexDescriptor : nil;
			m_renderPipelineDescriptor.sampleCount = sampleCount;
		}
		
		id<MTLRenderPipelineState> renderPipelineState = [m_device newRenderPipelineStateWithDescriptor:m_renderPipelineDescriptor error:NULL];
		assert(renderPipelineState);
		
		LOG_TRACE(U"new MTLRenderPipelineState created (vsID = {}, psID = {}, pixelFormat = {}, sampleCount = {}, blendState = {})"_fmt
				  (vsID.value(), psID.value(), FromEnum(pixelFormat), sampleCount, blendState.asValue()));
		
		m_pipelineStates.emplace(key, renderPipelineState);
	}

	id<MTLRenderPipelineState> MetalRenderPipeline2DManager::get(const VertexShader::IDType vsID, const PixelShader::IDType psID, const MTLPixelFormat pixelFormat, const uint32 sampleCount, const BlendState& blendState)
	{
		const KeyType key{ vsID, psID, pixelFormat, sampleCount, blendState };
		
		auto it = m_pipelineStates.find(key);
		
		if (it != m_pipelineStates.end())
		{
			return it->second;
		}
		
		{
			m_renderPipelineDescriptor.vertexFunction = pShader->getFunctionVS(vsID);
			m_renderPipelineDescriptor.fragmentFunction = pShader->getFunctionPS(psID);
			m_renderPipelineDescriptor.colorAttachments[0].pixelFormat = pixelFormat;
			
			m_renderPipelineDescriptor.colorAttachments[0].blendingEnabled = static_cast<bool>(blendState.enable);
			m_renderPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = detail::BlendFactorTable[static_cast<uint32>(blendState.src)];
			m_renderPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = detail::BlendFactorTable[static_cast<uint32>(blendState.dst)];
			m_renderPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = detail::BlendFactorTable[static_cast<uint32>(blendState.srcAlpha)];
			m_renderPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = detail::BlendFactorTable[static_cast<uint32>(blendState.dstAlpha)];
			m_renderPipelineDescriptor.colorAttachments[0].rgbBlendOperation = detail::BlendOperationTable[static_cast<uint32>(blendState.op)];
			m_renderPipelineDescriptor.colorAttachments[0].alphaBlendOperation = detail::BlendOperationTable[static_cast<uint32>(blendState.opAlpha)];
			m_renderPipelineDescriptor.colorAttachments[0].writeMask =
				(MTLColorWriteMaskRed * blendState.writeR) | (MTLColorWriteMaskGreen * blendState.writeG)
			  | (MTLColorWriteMaskBlue * blendState.writeB) | (MTLColorWriteMaskAlpha * blendState.writeA);
			
			m_renderPipelineDescriptor.vertexDescriptor = detail::HasStandardVertexLayout(m_renderPipelineDescriptor.vertexFunction) ? m_standardVertexDescriptor : nil;
			m_renderPipelineDescriptor.sampleCount = sampleCount;
		}
		
		id<MTLRenderPipelineState> renderPipelineState = [m_device newRenderPipelineStateWithDescriptor:m_renderPipelineDescriptor error:NULL];
		assert(renderPipelineState);
		
		LOG_TRACE(U"new MTLRenderPipelineState created (vsID = {}, psID = {}, pixelFormat = {}, sampleCount = {}, blendState = {})"_fmt
				  (vsID.value(), psID.value(), FromEnum(pixelFormat), sampleCount, blendState.asValue()));
		
		return m_pipelineStates.emplace(key, renderPipelineState).first->second;
	}
}
