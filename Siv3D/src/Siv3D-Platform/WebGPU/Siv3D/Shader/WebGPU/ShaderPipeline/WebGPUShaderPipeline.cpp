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

        pShader = dynamic_cast<CShader_WebGPU*>(SIV3D_ENGINE(Shader));

        m_standard2DVertexAttributes =
        {
            .attributes = {
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
            .attributes = {
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

		initializeStandard2DPipeline(device);
		initializeStandard3DPipeline(device);
    }

	void WebGPUShaderPipeline::initializeStandard2DPipeline(const wgpu::Device& device)
	{
		Array<wgpu::BindGroupLayout> standard2DBindgroupLayout;

        {
			Array<wgpu::BindGroupLayoutEntry> bindingLayout{};

			bindingLayout << wgpu::BindGroupLayoutEntry
			{
				.binding = 0,
				.visibility = wgpu::ShaderStage::Vertex,
				.buffer = wgpu::BufferBindingLayout
				{
					.type = wgpu::BufferBindingType::Uniform
				}
			};

			bindingLayout << wgpu::BindGroupLayoutEntry
			{
				.binding = 1,
				.visibility = wgpu::ShaderStage::Fragment,
				.buffer = wgpu::BufferBindingLayout
				{
					.type = wgpu::BufferBindingType::Uniform
				}
			};

			wgpu::BindGroupLayoutDescriptor layoutDesc
			{
				.entries = bindingLayout.data(),
				.entryCount = bindingLayout.size(),
			};

			auto uniformLayout = device.CreateBindGroupLayout(&layoutDesc);
			standard2DBindgroupLayout << uniformLayout;
		}

		for (auto shaderStage : { wgpu::ShaderStage::Fragment, wgpu::ShaderStage::Vertex })
		{
			Array<wgpu::BindGroupLayoutEntry> bindingLayout{};

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; i++)
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
			standard2DBindgroupLayout << uniformLayout;
		}

		{
			wgpu::PipelineLayoutDescriptor desc
			{
				.bindGroupLayoutCount = standard2DBindgroupLayout.size(),
				.bindGroupLayouts = standard2DBindgroupLayout.data()
			};

			m_standard2DPipelineLayout = device.CreatePipelineLayout(&desc);
		}
	}

	void WebGPUShaderPipeline::initializeStandard3DPipeline(const wgpu::Device& device)
	{
		Array<wgpu::BindGroupLayout> standard3DBindgroupLayout;

        {
			Array<wgpu::BindGroupLayoutEntry> bindingLayout{};

			bindingLayout << wgpu::BindGroupLayoutEntry
			{
				.binding = 0,
				.visibility = wgpu::ShaderStage::Vertex,
				.buffer = wgpu::BufferBindingLayout
				{
					.type = wgpu::BufferBindingType::Uniform
				}
			};

			bindingLayout << wgpu::BindGroupLayoutEntry
			{
				.binding = 1,
				.visibility = wgpu::ShaderStage::Vertex,
				.buffer = wgpu::BufferBindingLayout
				{
					.type = wgpu::BufferBindingType::Uniform
				}
			};

			bindingLayout << wgpu::BindGroupLayoutEntry
			{
				.binding = 2,
				.visibility = wgpu::ShaderStage::Fragment,
				.buffer = wgpu::BufferBindingLayout
				{
					.type = wgpu::BufferBindingType::Uniform
				}
			};

			bindingLayout << wgpu::BindGroupLayoutEntry
			{
				.binding = 3,
				.visibility = wgpu::ShaderStage::Fragment,
				.buffer = wgpu::BufferBindingLayout
				{
					.type = wgpu::BufferBindingType::Uniform
				}
			};

			bindingLayout << wgpu::BindGroupLayoutEntry
			{
				.binding = 4,
				.visibility = wgpu::ShaderStage::Fragment,
				.buffer = wgpu::BufferBindingLayout
				{
					.type = wgpu::BufferBindingType::Uniform
				}
			};

			wgpu::BindGroupLayoutDescriptor layoutDesc
			{
				.entries = bindingLayout.data(),
				.entryCount = bindingLayout.size(),
			};

			auto uniformLayout = device.CreateBindGroupLayout(&layoutDesc);
			standard3DBindgroupLayout << uniformLayout;
		}

		for (auto shaderStage : { wgpu::ShaderStage::Fragment, wgpu::ShaderStage::Vertex })
		{
			Array<wgpu::BindGroupLayoutEntry> bindingLayout{};

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; i++)
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
			standard3DBindgroupLayout << uniformLayout;
		}

		{
			wgpu::PipelineLayoutDescriptor desc
			{
				.bindGroupLayoutCount = standard3DBindgroupLayout.size(),
				.bindGroupLayouts = standard3DBindgroupLayout.data()
			};

			m_standard3DPipelineLayout = device.CreatePipelineLayout(&desc);
		}
	}

    wgpu::RenderPipeline WebGPUShaderPipeline::getPipeline(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState, DepthStencilState depthStencilState, const WebGPUVertexAttribute& attribute, const wgpu::PipelineLayout* pipelineLayout)
    {
        const KeyType key { vertexShader, pixelShader, rasterizerState, blendState, depthStencilState, std::hash<s3d::WebGPUVertexAttribute>()(attribute) };

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

		wgpu::BlendState wgpuBlendState
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

		wgpu::DepthStencilState wgpuDepthStencilState
		{
			.format = wgpu::TextureFormat::Depth32Float,
			.depthWriteEnabled = depthStencilState.depthWriteEnable,
			.depthCompare = detail::CompareFunctionTable[FromEnum(depthStencilState.depthFunc)]
		};

		wgpu::ColorTargetState colorTargetState
		{
			.format = wgpu::TextureFormat::BGRA8Unorm,
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
			.frontFace = wgpu::FrontFace::CW
        };

		// desc.depthStencil = &wgpuDepthStencilState;

        if (pipelineLayout != nullptr)
        {
            desc.layout = *pipelineLayout;
        }

        auto pipeline = m_device.CreateRenderPipeline2(&desc);

        return m_pipelines.emplace(key, pipeline).first->second;
    }

	wgpu::RenderPipeline WebGPUShaderPipeline::getPipelineWithStandard2DVertexLayout(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState)
    {
        return getPipeline(vertexShader, pixelShader, rasterizerState, blendState, DepthStencilState::Default2D, m_standard2DVertexAttributes, &m_standard2DPipelineLayout);
    }

	wgpu::RenderPipeline WebGPUShaderPipeline::getPipelineWithStandard3DVertexLayout(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState, DepthStencilState depthStencilState)
    {
        return getPipeline(vertexShader, pixelShader, rasterizerState, blendState, depthStencilState, m_standard3DVertexAttributes, &m_standard3DPipelineLayout);
    }
}