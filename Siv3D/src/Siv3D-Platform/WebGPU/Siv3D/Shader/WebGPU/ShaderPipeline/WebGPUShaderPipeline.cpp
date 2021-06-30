//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ShaderStage.hpp>
# include <Siv3D/SamplerState.hpp>
# include "WebGPUShaderPipeline.hpp"

namespace s3d
{
    WebGPUShaderPipeline::~WebGPUShaderPipeline()
    {
        for (auto [shaderSet, pipeline] : m_pipelines)
		{
			pipeline.Release();
		}
    }

    bool WebGPUShaderPipeline::hasCachedShaderPipeline(ShaderType vertexShader, ShaderType pixelShader) const
    {
        // return m_pipelines.contains({ vertexShader, pixelShader });
        return m_pipelines.size() > 0;
    }

    WebGPUShaderPipeline::PipelineState WebGPUShaderPipeline::linkShaders(const wgpu::Device& device, const wgpu::RenderPipelineDescriptor2& desc) 
    {
        ShaderSet shaderSet = { desc.vertex.module, desc.fragment->module };

        bool cacheExists = hasCachedShaderPipeline( desc.vertex.module, desc.fragment->module );

        if (!cacheExists)
        {
            auto newPipeline = device.CreateRenderPipeline2(&desc);
            m_pipelines.emplace(shaderSet, newPipeline);
        } 
       
        PipelineState state;

        state.shaderProgram = m_pipelines[shaderSet];
        state.cacheHit = cacheExists;
        
        return state;
    }
}