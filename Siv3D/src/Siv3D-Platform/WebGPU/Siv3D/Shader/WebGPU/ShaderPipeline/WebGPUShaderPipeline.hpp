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

# pragma once
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/DepthStencilState.hpp>
# include <Siv3D/Texture/WebGPU/WebGPURenderTargetState.hpp>
# include <Siv3D/HashTable.hpp>
# include <tuple>

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	class CShader_WebGPU;

	struct WebGPUVertexAttribute
	{
		Array<wgpu::VertexAttribute> attributes;

		uint32 stride = 0;
	};

	class WebGPUShaderPipeline
	{
	private:

		using WebGPUVertexAttributeHash = size_t;

		using KeyType = std::tuple<VertexShader::IDType, PixelShader::IDType, RasterizerState, BlendState, WebGPURenderTargetState, DepthStencilState, WebGPUVertexAttributeHash>;
		
		HashTable<KeyType, wgpu::RenderPipeline> m_pipelines;

		WebGPUVertexAttribute m_standard2DVertexAttributes;

		WebGPUVertexAttribute m_standard3DVertexAttributes;

		WebGPUVertexAttribute m_standard3DLineVertexAttributes;

		Array<wgpu::BindGroupLayout> m_standardSamplerBindingGroup;

		wgpu::Device m_device = nullptr;

		CShader_WebGPU* pShader = nullptr;

		void initializeSamplerBindingGroup(const wgpu::Device& device);

	public:
		
		WebGPUShaderPipeline();

		~WebGPUShaderPipeline();

		void init(const wgpu::Device& device);

		wgpu::RenderPipeline getPipeline(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState, DepthStencilState depthStencilState, const WebGPUVertexAttribute& attribute, wgpu::PrimitiveTopology topology = wgpu::PrimitiveTopology::TriangleList, bool overridePipelineLayout = false);

		wgpu::RenderPipeline getPipelineWithStandard2DVertexLayout(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState);

		wgpu::RenderPipeline getPipelineWithStandard3DVertexLayout(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState, DepthStencilState depthStencilState);

		wgpu::RenderPipeline getPipelineWithStandard3DLineVertexLayout(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState, DepthStencilState depthStencilState);
	};
}

template <>
struct std::hash<s3d::WebGPUVertexAttribute>
{
	[[nodiscard]]
	size_t operator()(const s3d::WebGPUVertexAttribute& value) const noexcept
	{
		return s3d::Hash::FNV1a(value.attributes.data(), sizeof(wgpu::VertexAttribute) * value.attributes.size());
	}
};