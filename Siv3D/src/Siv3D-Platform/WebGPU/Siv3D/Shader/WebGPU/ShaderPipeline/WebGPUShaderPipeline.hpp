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

# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/HashTable.hpp>
# include <tuple>

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	class WebGPUShaderPipeline
	{
	public:

		using ShaderType = wgpu::ShaderModule;
		using ShaderPipelineType = wgpu::RenderPipeline;

		struct PipelineState
		{	
			ShaderPipelineType shaderProgram;
			bool cacheHit;
		};

		struct ShaderSet
		{
			ShaderType vertexShader;
			ShaderType pixelShader;

			[[nodiscard]]
			friend bool operator==(ShaderSet lhs, ShaderSet rhs)
			{
				return lhs.vertexShader.Get() == rhs.vertexShader.Get() && lhs.pixelShader.Get() == rhs.pixelShader.Get();
			}

			[[nodiscard]]
			friend bool operator!=(ShaderSet lhs, ShaderSet rhs)
			{
				return !(lhs == rhs);
			}
		};

	private:
		
		HashTable<ShaderSet, ShaderPipelineType> m_pipelines;

		bool hasCachedShaderPipeline(ShaderType vertexShader, ShaderType pixelShader) const;

	public:
		
		~WebGPUShaderPipeline();

		PipelineState linkShaders(const wgpu::Device& device, const wgpu::RenderPipelineDescriptor2& desc);
	};
}

template <>
struct std::hash<s3d::WebGPUShaderPipeline::ShaderSet>
{
	[[nodiscard]]
	size_t operator()(const s3d::WebGPUShaderPipeline::ShaderSet& value) const noexcept
	{
		struct 
		{
			WGPUShaderModule vertexShader;
			WGPUShaderModule fragmentShader;	
		} 
		hashed
		{
			.vertexShader = value.pixelShader.Get(),
			.fragmentShader = value.vertexShader.Get()
		};

		return s3d::Hash::FNV1a(hashed);
	}
};