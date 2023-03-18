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
# include <Siv3D/SamplerState.hpp>
# include "WebGPUPixelShader.hpp"

namespace s3d
{
	WebGPUPixelShader::WebGPUPixelShader(Null)
	{
		m_initialized = true;
	}

	WebGPUPixelShader::~WebGPUPixelShader()
	{
		if (m_pixelShader)
		{
			m_pixelShader.Release();
			m_pixelShader = nullptr;
		}
	}

	WebGPUPixelShader::WebGPUPixelShader(const wgpu::Device& device, const StringView source, const Array<ConstantBufferBinding>& bindings)
	{
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

			m_pixelShader = device.CreateShaderModule(&desc);

			// ログメッセージ
			if (not m_pixelShader)
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
					.visibility = wgpu::ShaderStage::Fragment,
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
		
		m_initialized = static_cast<bool>(m_pixelShader);
	}

	bool WebGPUPixelShader::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const Blob& WebGPUPixelShader::getBinary() const noexcept
	{
		return m_binary;
	}

	wgpu::ShaderModule WebGPUPixelShader::getShaderModule() const
	{
		return m_pixelShader;
	}

	wgpu::BindGroupLayout WebGPUPixelShader::getBindingGroup() const
	{
		return m_uniformBindingLayout;
	}
}
