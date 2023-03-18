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

# include <Siv3D/Renderer/WebGPU/CRenderer_WebGPU.hpp>

# include "WebGPUUniformState.hpp"

namespace s3d
{
	namespace detail
	{
        static size_t calculateHash(const s3d::Array<wgpu::BindGroupEntry>& values)
        {
            size_t hashed = 0;

            for (const auto& value : values)
            {
                if (const auto& buffer = value.buffer; buffer != nullptr)
                {
                    s3d::Hash::Combine(hashed, std::hash<decltype(buffer.Get())>{}(buffer.Get()));
                }
                else if (const auto& sampler = value.sampler; sampler != nullptr)
				{
                	s3d::Hash::Combine(hashed, std::hash<decltype(sampler.Get())>{}(sampler.Get()));
				}
				else if (const auto& texture = value.textureView; texture != nullptr)
				{
                	s3d::Hash::Combine(hashed, std::hash<decltype(texture.Get())>{}(texture.Get()));
				}
            }

            return hashed;
        }
    }

    WebGPUUniformState::WebGPUUniformState() {}

    void WebGPUUniformState::init(const wgpu::Device& device)
    {
		m_device = device;
    }

    void WebGPUUniformState::bindUniformBindGroup(const wgpu::RenderPassEncoder& pass, uint32 groupId, const wgpu::RenderPipeline& pipeline, const s3d::Array<wgpu::BindGroupEntry>& binding)
    {
        auto uniformHash = detail::calculateHash(binding);
		{
			if (m_bindGroups.find(uniformHash) == m_bindGroups.end())
			{
                auto cloned = binding;

				for (auto& c : cloned)
				{
					c.offset = 0;
				}

				wgpu::BindGroupDescriptor constantsDescVS
				{
					.layout = pipeline.GetBindGroupLayout(groupId),
					.entries = cloned.data(),
					.entryCount = cloned.size()
				};

				auto constantsUniform = m_device.CreateBindGroup(&constantsDescVS);
				m_bindGroups.emplace(uniformHash, constantsUniform);
			}
		}

        {
            Array<uint32> bufferOffsets = {};

            for (const auto& entry : binding.sorted_by(
                [](const wgpu::BindGroupEntry& lhs, const wgpu::BindGroupEntry& rhs) {
                    return lhs.binding < rhs.binding;
                }))
            {
                if (entry.buffer != nullptr)
                {
                    bufferOffsets << static_cast<uint32>(entry.offset);
                }
            }

            pass.SetBindGroup(groupId, m_bindGroups.find(uniformHash)->second, bufferOffsets.size(), bufferOffsets.data());
		}
    }
}
