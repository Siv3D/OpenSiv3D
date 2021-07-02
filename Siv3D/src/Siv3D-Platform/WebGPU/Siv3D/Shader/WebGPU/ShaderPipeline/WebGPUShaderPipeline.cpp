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
# include <Siv3D/Shader/WebGPU/CShader_WebGPU.hpp>
# include "WebGPUShaderPipeline.hpp"

namespace s3d
{
    WebGPUShaderPipeline::WebGPUShaderPipeline()
    {
    }

    WebGPUShaderPipeline::~WebGPUShaderPipeline()
    {
        for (auto [shaderSet, pipeline] : m_pipelines)
		{
			pipeline.Release();
		}
    }

    void WebGPUShaderPipeline::init(const wgpu::Device& device)
    {
        m_device = device;

        pShader = dynamic_cast<CShader_WebGPU*>(SIV3D_ENGINE(Shader));

        m_standardVertexAttributes = WebGPUVertexAttribute
        {
            .attributes = {
                {
                    .format = wgpu::VertexFormat::Float32x2,
                    .offset = 0,
                    .shaderLocation = 0
                },
                {
                    .format = wgpu::VertexFormat::Float32x2,
                    .offset = 4,
                    .shaderLocation = 1
                },
                {
                    .format = wgpu::VertexFormat::Float32x4,
                    .offset = 8,
                    .shaderLocation = 2
                }
            },

            .stride = 32
        };
    }

    wgpu::RenderPipeline WebGPUShaderPipeline::getPipeline(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, const WebGPUVertexAttribute& attribute)
    {
        const KeyType key { vertexShader, pixelShader, rasterizerState, std::hash<s3d::WebGPUVertexAttribute>()(attribute) };

        auto it = m_pipelines.find(key);
		
		if (it != m_pipelines.end())
		{
			return it->second;
		}

        wgpu::RenderPipelineDescriptor2 desc;

        wgpu::VertexBufferLayout vertexLayout
        {
            .arrayStride = attribute.stride,
            .attributeCount = attribute.attributes.size(),
            .attributes = attribute.attributes.data()
        };

        desc.vertex = wgpu::VertexState
		{
			.module = pShader->getShaderModuleVS(vertexShader),
			.entryPoint = "main",
            .bufferCount = 1,
            .buffers = &vertexLayout
		};

		wgpu::ColorTargetState colorTargetState
		{
			.format = wgpu::TextureFormat::BGRA8Unorm
		};

		wgpu::FragmentState fragmentState
		{
			.module = pShader->getShaderModulePS(pixelShader),
			.entryPoint = "main",
			.targetCount = 1,
			.targets = &colorTargetState
		};

		desc.fragment = &fragmentState;

        desc.primitive = wgpu::PrimitiveState
        {
            .cullMode = ToEnum<wgpu::CullMode>(FromEnum(rasterizerState.cullMode) - 1),
        };

        auto pipeline = m_device.CreateRenderPipeline2(&desc);

        return m_pipelines.emplace(key, pipeline).first->second;
    }

	wgpu::RenderPipeline WebGPUShaderPipeline::getPipelineWithStandardVertexLayout(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState)
    {
        return getPipeline(vertexShader, pixelShader, rasterizerState, m_standardVertexAttributes);
    }
}