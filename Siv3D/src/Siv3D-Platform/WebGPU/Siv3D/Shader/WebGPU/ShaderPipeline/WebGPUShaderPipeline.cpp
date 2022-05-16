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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ShaderStage.hpp>
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/Shader/WebGPU/CShader_WebGPU.hpp>
# include "WebGPUShaderPipeline.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr wgpu::BlendFactor BlendFactorTable[20] =
		{
			wgpu::BlendFactor::Zero, // Invalid Value
			wgpu::BlendFactor::Zero,
			wgpu::BlendFactor::One,
			wgpu::BlendFactor::Src,
			wgpu::BlendFactor::OneMinusSrc,

			wgpu::BlendFactor::SrcAlpha,
			wgpu::BlendFactor::OneMinusSrcAlpha,
			wgpu::BlendFactor::DstAlpha,
			wgpu::BlendFactor::OneMinusDstAlpha,
			wgpu::BlendFactor::Dst,

			wgpu::BlendFactor::OneMinusDst,
			wgpu::BlendFactor::SrcAlphaSaturated,
			wgpu::BlendFactor::Zero, // None
			wgpu::BlendFactor::Zero, // None
			wgpu::BlendFactor::Zero, // Invalid Value

			wgpu::BlendFactor::Zero, // Invalid Value
			wgpu::BlendFactor::Constant,
			wgpu::BlendFactor::OneMinusConstant,
			wgpu::BlendFactor::Zero, // Invalid Value
			wgpu::BlendFactor::Zero, // Invalid Value
		};

		static constexpr wgpu::BlendFactor BlendFactorTableWithoutAlpha[20] =
		{
			wgpu::BlendFactor::Zero, // Invalid Value
			wgpu::BlendFactor::Zero,
			wgpu::BlendFactor::One,
			wgpu::BlendFactor::Src,
			wgpu::BlendFactor::OneMinusSrc,

			wgpu::BlendFactor::One,
			wgpu::BlendFactor::Zero,
			wgpu::BlendFactor::One,
			wgpu::BlendFactor::Zero,
			wgpu::BlendFactor::Dst,

			wgpu::BlendFactor::OneMinusDst,
			wgpu::BlendFactor::SrcAlphaSaturated,
			wgpu::BlendFactor::Zero, // None
			wgpu::BlendFactor::Zero, // None
			wgpu::BlendFactor::Zero, // Invalid Value

			wgpu::BlendFactor::Zero, // Invalid Value
			wgpu::BlendFactor::Constant,
			wgpu::BlendFactor::OneMinusConstant,
			wgpu::BlendFactor::Zero, // Invalid Value
			wgpu::BlendFactor::Zero, // Invalid Value
		};
		
		static constexpr wgpu::CompareFunction CompareFunctionTable[9] = 
		{
			wgpu::CompareFunction::Undefined,
			wgpu::CompareFunction::Never,
			wgpu::CompareFunction::Less,
			wgpu::CompareFunction::Equal,
			wgpu::CompareFunction::LessEqual,
			wgpu::CompareFunction::Greater,
			wgpu::CompareFunction::NotEqual,
			wgpu::CompareFunction::GreaterEqual,
			wgpu::CompareFunction::Always
		};
	}

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

        pShader = static_cast<CShader_WebGPU*>(SIV3D_ENGINE(Shader));

        m_standard2DVertexAttributes =
        {
            .attributes = 
			{
                {
                    .format = wgpu::VertexFormat::Float32x2,
                    .offset = 0,
                    .shaderLocation = 0
                },
                {
                    .format = wgpu::VertexFormat::Float32x2,
                    .offset = 8,
                    .shaderLocation = 1
                },
                {
                    .format = wgpu::VertexFormat::Float32x4,
                    .offset = 16,
                    .shaderLocation = 2
                }
            },

            .stride = 32
        };

		m_standard3DVertexAttributes =
        {
            .attributes = 
			{
                {
                    .format = wgpu::VertexFormat::Float32x3,
                    .offset = 0,
                    .shaderLocation = 0
                },
                {
                    .format = wgpu::VertexFormat::Float32x3,
                    .offset = 12,
                    .shaderLocation = 1
                },
                {
                    .format = wgpu::VertexFormat::Float32x2,
                    .offset = 24,
                    .shaderLocation = 2
                }
            },

            .stride = 32
        };

		m_standard3DLineVertexAttributes =
		{
			.attributes =
			{
				{
                    .format = wgpu::VertexFormat::Float32x4,
                    .offset = 0,
                    .shaderLocation = 0
                },
				{
                    .format = wgpu::VertexFormat::Float32x4,
                    .offset = 16,
                    .shaderLocation = 1
                }
			},

			.stride = 32
		};

		initializeSamplerBindingGroup(device);
    }

	void WebGPUShaderPipeline::initializeSamplerBindingGroup(const wgpu::Device& device)
	{
		for (auto shaderStage : { wgpu::ShaderStage::Fragment, wgpu::ShaderStage::Vertex })
		{
			Array<wgpu::BindGroupLayoutEntry> bindingLayout{};

			// for (uint32 i = 0; i < SamplerState::MaxSamplerCount; i++)

			const uint32 maxSamplerCount = shaderStage == wgpu::ShaderStage::Vertex ? 2 : 4;
			for (uint32 i = 0; i < maxSamplerCount; i++)
			{
				bindingLayout << wgpu::BindGroupLayoutEntry
				{
					.binding = 2 * i,
					.visibility = shaderStage,
					.sampler = wgpu::SamplerBindingLayout 
					{
						.type = wgpu::SamplerBindingType::Filtering
					}
				};
			
				bindingLayout << wgpu::BindGroupLayoutEntry
				{
					.binding = 2 * i + 1,
					.visibility = shaderStage,
					.texture = wgpu::TextureBindingLayout 
					{
						.sampleType = wgpu::TextureSampleType::Float,
						.viewDimension = wgpu::TextureViewDimension::e2D
					}
				};
			}

			wgpu::BindGroupLayoutDescriptor layoutDesc
			{
				.entries = bindingLayout.data(),
				.entryCount = bindingLayout.size(),
			};

			auto uniformLayout = device.CreateBindGroupLayout(&layoutDesc);
			m_standardSamplerBindingGroup << uniformLayout;
		}
	}

    wgpu::RenderPipeline WebGPUShaderPipeline::getPipeline(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState, DepthStencilState depthStencilState, const WebGPUVertexAttribute& attribute, wgpu::PrimitiveTopology topology, bool overridePipelineLayout)
    {
        const KeyType key { vertexShader, pixelShader, rasterizerState, blendState, renderTargetState, depthStencilState, std::hash<s3d::WebGPUVertexAttribute>()(attribute) };

        auto it = m_pipelines.find(key);
		
		if (it != m_pipelines.end())
		{
			return it->second;
		}

        wgpu::RenderPipelineDescriptor desc;

        wgpu::VertexBufferLayout vertexLayout
        {
            .arrayStride = attribute.stride,
            .attributeCount = attribute.attributes.size(),
            .attributes = attribute.attributes.data()
        };

        desc.vertex =
		{
			.module = pShader->getShaderModuleVS(vertexShader),
			.entryPoint = "main",
            .bufferCount = vertexLayout.attributeCount > 0 ? 1u : 0u,
            .buffers = &vertexLayout
		};

		wgpu::BlendState wgpuBlendState;

		if (blendState.enable)
		{
			if (renderTargetState.hasAlpha)
			{
				wgpuBlendState = wgpu::BlendState
				{
					.color =
					{
						.operation = ToEnum<wgpu::BlendOperation>(FromEnum(blendState.op) - 1),
						.srcFactor = detail::BlendFactorTable[FromEnum(blendState.src)],
						.dstFactor = detail::BlendFactorTable[FromEnum(blendState.dst)],
					},
					.alpha =
					{
						.operation = ToEnum<wgpu::BlendOperation>(FromEnum(blendState.opAlpha) - 1),
						.srcFactor = detail::BlendFactorTable[FromEnum(blendState.srcAlpha)],
						.dstFactor = detail::BlendFactorTable[FromEnum(blendState.dstAlpha)],
					}
				};
			}
			else
			{
				wgpuBlendState = wgpu::BlendState
				{
					.color =
					{
						.operation = ToEnum<wgpu::BlendOperation>(FromEnum(blendState.op) - 1),
						.srcFactor = detail::BlendFactorTableWithoutAlpha[FromEnum(blendState.src)],
						.dstFactor = detail::BlendFactorTableWithoutAlpha[FromEnum(blendState.dst)],
					}
				};
			}
		}

		wgpu::ColorTargetState colorTargetState
		{
			.format = ToEnum<wgpu::TextureFormat>(renderTargetState.renderTargetFormat),
			.blend = &wgpuBlendState
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
			.frontFace = wgpu::FrontFace::CW,
			.topology = topology
        };

		wgpu::DepthStencilState wgpuDepthStencilState
		{
			.format = wgpu::TextureFormat::Depth32Float,
			.depthWriteEnabled = depthStencilState.depthWriteEnable,
			.depthCompare = detail::CompareFunctionTable[FromEnum(depthStencilState.depthFunc)]
		};

		if (renderTargetState.hasDepth)
		{
			desc.depthStencil = &wgpuDepthStencilState;
		}

		desc.multisample =
		{
			.count = renderTargetState.sampleCount
		};

		if (overridePipelineLayout)
		{
			Array<wgpu::BindGroupLayout> bindGroup;

			bindGroup << pShader->getBindingGroupVS(vertexShader);
			bindGroup << pShader->getBindingGroupPS(pixelShader);

			bindGroup.append(m_standardSamplerBindingGroup);

			wgpu::PipelineLayoutDescriptor pipelineLayoutDesc
			{
				.bindGroupLayouts = bindGroup.data(),
				.bindGroupLayoutCount = bindGroup.size()
			};

			desc.layout = m_device.CreatePipelineLayout(&pipelineLayoutDesc);
		}
		
        auto pipeline = m_device.CreateRenderPipeline(&desc);
        return m_pipelines.emplace(key, pipeline).first->second;
    }

	wgpu::RenderPipeline WebGPUShaderPipeline::getPipelineWithStandard2DVertexLayout(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState)
    {
        return getPipeline(vertexShader, pixelShader, rasterizerState, blendState, renderTargetState, DepthStencilState::Default2D, m_standard2DVertexAttributes, wgpu::PrimitiveTopology::TriangleList, true);
    }

	wgpu::RenderPipeline WebGPUShaderPipeline::getPipelineWithStandard3DVertexLayout(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState, DepthStencilState depthStencilState)
    {
        return getPipeline(vertexShader, pixelShader, rasterizerState, blendState, renderTargetState, depthStencilState, m_standard3DVertexAttributes, wgpu::PrimitiveTopology::TriangleList, true);
    }

	wgpu::RenderPipeline WebGPUShaderPipeline::getPipelineWithStandard3DLineVertexLayout(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState, DepthStencilState depthStencilState)
    {
        return getPipeline(vertexShader, pixelShader, rasterizerState, blendState, renderTargetState, depthStencilState, m_standard3DLineVertexAttributes, wgpu::PrimitiveTopology::LineList, true);
    }
}