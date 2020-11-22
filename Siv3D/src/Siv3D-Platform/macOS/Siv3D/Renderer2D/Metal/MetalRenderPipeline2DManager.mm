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

# include "MetalRenderPipeline2DManager.hpp"
# include <Siv3D/Shader/Metal/CShader_Metal.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
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
		
		add(standardVS.sprite.id(), standardPS.shape.id(), MTLPixelFormatRGBA8Unorm, sampleCount);
		add(standardVS.fullscreen_triangle.id(), standardPS.fullscreen_triangle.id(), swapchainFormat, 1);
	}

	void MetalRenderPipeline2DManager::add(const VertexShader::IDType vsID, const PixelShader::IDType psID, const MTLPixelFormat pixelFormat, const uint32 sampleCount)
	{
		const KeyType key{ vsID, psID, pixelFormat, sampleCount };

		if (m_pipelineStates.contains(key))
		{
			return;
		}
		
		{
			m_renderPipelineDescriptor.vertexFunction = pShader->getFunctionVS(vsID);
			m_renderPipelineDescriptor.fragmentFunction = pShader->getFunctionPS(psID);
			m_renderPipelineDescriptor.colorAttachments[0].pixelFormat = pixelFormat;
			m_renderPipelineDescriptor.vertexDescriptor = detail::HasStandardVertexLayout(m_renderPipelineDescriptor.vertexFunction) ? m_standardVertexDescriptor : nil;
			m_renderPipelineDescriptor.sampleCount = sampleCount;
		}
		
		id<MTLRenderPipelineState> renderPipelineState = [m_device newRenderPipelineStateWithDescriptor:m_renderPipelineDescriptor error:NULL];
		assert(renderPipelineState);
		
		LOG_TRACE(U"new MTLRenderPipelineState created (vsID = {}, psID = {}, pixelFormat = {}, sampleCount = {})"_fmt
				  (vsID.value(), psID.value(), pixelFormat, sampleCount));
		
		m_pipelineStates.emplace(key, renderPipelineState);
	}

	id<MTLRenderPipelineState> MetalRenderPipeline2DManager::get(const VertexShader::IDType vsID, const PixelShader::IDType psID, const MTLPixelFormat pixelFormat, const uint32 sampleCount)
	{
		const KeyType key{ vsID, psID, pixelFormat, sampleCount };
		
		auto it = m_pipelineStates.find(key);
		
		if (it != m_pipelineStates.end())
		{
			return it->second;
		}
		
		{
			m_renderPipelineDescriptor.vertexFunction = pShader->getFunctionVS(vsID);
			m_renderPipelineDescriptor.fragmentFunction = pShader->getFunctionPS(psID);
			m_renderPipelineDescriptor.colorAttachments[0].pixelFormat = pixelFormat;
			m_renderPipelineDescriptor.vertexDescriptor = detail::HasStandardVertexLayout(m_renderPipelineDescriptor.vertexFunction) ? m_standardVertexDescriptor : nil;
			m_renderPipelineDescriptor.sampleCount = sampleCount;
		}
		
		id<MTLRenderPipelineState> renderPipelineState = [m_device newRenderPipelineStateWithDescriptor:m_renderPipelineDescriptor error:NULL];
		assert(renderPipelineState);
		
		LOG_TRACE(U"new MTLRenderPipelineState created (vsID = {}, psID = {}, pixelFormat = {}, sampleCount = {})"_fmt
				  (vsID.value(), psID.value(), pixelFormat, sampleCount));
		
		return m_pipelineStates.emplace(key, renderPipelineState).first->second;
	}
}
