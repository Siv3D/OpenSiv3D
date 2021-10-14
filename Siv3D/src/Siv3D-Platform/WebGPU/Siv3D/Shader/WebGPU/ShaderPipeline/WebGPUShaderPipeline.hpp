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

# pragma once
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/RasterizerState.hpp>
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

		using KeyType = std::tuple<VertexShader::IDType, PixelShader::IDType, RasterizerState, BlendState, WebGPUVertexAttributeHash>;
		
		HashTable<KeyType, wgpu::RenderPipeline> m_pipelines;

		WebGPUVertexAttribute m_standardVertexAttributes;

		Array<wgpu::BindGroupLayout> m_standardBindgroupLayout;

		wgpu::PipelineLayout m_standardPipelineLayout;

		wgpu::Device m_device = nullptr;

		CShader_WebGPU* pShader = nullptr;

	public:
		
		WebGPUShaderPipeline();

		~WebGPUShaderPipeline();

		void init(const wgpu::Device& device);

		wgpu::RenderPipeline getPipeline(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState, const WebGPUVertexAttribute& attribute, const wgpu::PipelineLayout* pipelineLayout = nullptr);

		wgpu::RenderPipeline getPipelineWithStandardVertexLayout(VertexShader::IDType vertexShader, PixelShader::IDType pixelShader, RasterizerState rasterizerState, BlendState blendState);
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