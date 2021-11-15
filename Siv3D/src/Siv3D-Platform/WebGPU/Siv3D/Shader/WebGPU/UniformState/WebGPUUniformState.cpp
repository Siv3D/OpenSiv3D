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
                s3d::Hash::Combine(hashed, std::hash<decltype(value.buffer.Get())>{}(value.buffer.Get()));
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

            for (const auto& entry : binding)
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
