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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ShaderStage.hpp>
# include "WebGPUVertexShader.hpp"

namespace s3d
{
	WebGPUVertexShader::WebGPUVertexShader(Null)
	{
		m_initialized = true;
	}

	WebGPUVertexShader::~WebGPUVertexShader()
	{
		if (m_vertexShader)
		{
			m_vertexShader.Release();
			m_vertexShader = nullptr;
		}
	}

	WebGPUVertexShader::WebGPUVertexShader(const wgpu::Device& device, const StringView source, const Array<ConstantBufferBinding>& bindings)
	{
		// 頂点シェーダプログラムを作成

        // シェーダのコンパイル
		{
			const std::string sourceUTF8 = source.toUTF8();
			const char* pSource = sourceUTF8.c_str();

			wgpu::ShaderModuleWGSLDescriptor wgslDesc;
			{
				wgslDesc.source = pSource;
			};

			wgpu::ShaderModuleDescriptor desc
			{
				.nextInChain = &wgslDesc
			};

			m_vertexShader = device.CreateShaderModule(&desc);

			// ログメッセージ
			if (not m_vertexShader)
			{
				LOG_FAIL(U"❌ Vertex shader compilation failed");
			}	
		}

		{
			Array<wgpu::BindGroupLayoutEntry> bindingLayout{};

			for (const auto& binding : bindings)
			{
				bindingLayout << wgpu::BindGroupLayoutEntry
				{
					.binding = binding.index,
					.visibility = wgpu::ShaderStage::Vertex,
					.buffer =
					{
						.type = wgpu::BufferBindingType::Uniform,
						.hasDynamicOffset = true
					}
				};
			}

			wgpu::BindGroupLayoutDescriptor layoutDesc
			{
				.entries = bindingLayout.data(),
				.entryCount = bindingLayout.size(),
			};

			m_uniformBindingLayout = device.CreateBindGroupLayout(&layoutDesc);
		}
		
		m_initialized = static_cast<bool>(m_vertexShader);
	}

	bool WebGPUVertexShader::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const Blob& WebGPUVertexShader::getBinary() const noexcept
	{
		return m_binary;
	}

	wgpu::ShaderModule WebGPUVertexShader::getShaderModule() const
	{
		return m_vertexShader;
	}

	wgpu::BindGroupLayout WebGPUVertexShader::getBindingGroup() const
	{
		return m_uniformBindingLayout;
	}
}
