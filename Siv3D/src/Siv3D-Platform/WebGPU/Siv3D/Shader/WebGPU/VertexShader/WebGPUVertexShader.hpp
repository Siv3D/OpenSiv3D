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
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/Blob.hpp>
# include <Siv3D/ConstantBufferBinding.hpp>

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	class WebGPUVertexShader
	{
	private:

		Blob m_binary;

		wgpu::ShaderModule m_vertexShader = nullptr;

		Array<ConstantBufferBinding> m_constantBufferBindings;

		wgpu::BindGroupLayout m_uniformBindingLayout;

		bool m_initialized = false;

		void setUniformBlockBinding(const StringView name, GLuint index);

		void setUniformBlockBindings(const Array<ConstantBufferBinding>& bindings);

	public:

		struct Null {};

		WebGPUVertexShader() = default;

		explicit WebGPUVertexShader(Null);

		explicit WebGPUVertexShader(const wgpu::Device& device, const StringView source, const Array<ConstantBufferBinding>& bindings);

		~WebGPUVertexShader();

		bool isInitialized() const noexcept;

		const Blob& getBinary() const noexcept;

		wgpu::ShaderModule getShaderModule() const;

		wgpu::BindGroupLayout getBindingGroup() const;
	};
}
