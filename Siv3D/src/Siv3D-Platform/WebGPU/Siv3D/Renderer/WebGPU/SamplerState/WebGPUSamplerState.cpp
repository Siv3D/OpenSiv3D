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

# include <cfloat>
# include <Siv3D/ShaderStage.hpp>
# include "WebGPUSamplerState.hpp"

namespace s3d
{
	static const SamplerState NullSamplerState(TextureAddressMode::Repeat,
		TextureAddressMode::Repeat,
		TextureAddressMode::Repeat,
		TextureFilter::Linear,
		TextureFilter::Linear,
		TextureFilter::Linear,
		0,
		-1,
		Float4(FLT_MIN, FLT_MIN, FLT_MIN, FLT_MIN));

	WebGPUSamplerState::WebGPUSamplerState()
	{
		m_currentVSStates.fill(NullSamplerState);
		m_currentPSStates.fill(NullSamplerState);
	}

	void WebGPUSamplerState::setVS(wgpu::Device* device, const uint32 slot, const SamplerState& state)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		if (state == m_currentVSStates[slot])
		{
			return;
		}

		auto it = m_states.find(state);

		if (it == m_states.end())
		{
			it = create(device, state);

			if (it == m_states.end())
			{
				return;
			}
		}

		m_currentVSStates[slot] = state;
	}

	void WebGPUSamplerState::setVS(wgpu::Device* device, const uint32 slot, None_t)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		m_currentVSStates[slot] = NullSamplerState;
	}

	void WebGPUSamplerState::setPS(wgpu::Device* device, const uint32 slot, const SamplerState& state)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		if (state == m_currentPSStates[slot])
		{
			return;
		}

		auto it = m_states.find(state);

		if (it == m_states.end())
		{
			it = create(device, state);

			if (it == m_states.end())
			{
				return;
			}
		}

		m_currentPSStates[slot] = state;
	}

	void WebGPUSamplerState::setPS(wgpu::Device* device, const uint32 slot, None_t)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		m_currentPSStates[slot] = NullSamplerState;
	}

	void WebGPUSamplerState::bindSamplers(wgpu::Device* device, const wgpu::RenderPipeline& pipeline, const wgpu::RenderPassEncoder& pass)
	{
		{
			Array<wgpu::BindGroupEntry> vsSamplerBindings{};

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; i++)
			{
				const auto& state = m_currentVSStates[i];

				if (auto it = m_states.find(state); it != m_states.end())
				{
					vsSamplerBindings << wgpu::BindGroupEntry
					{
						.binding = i,
						.sampler = it->second->m_sampler
					};
				}
			}

			wgpu::BindGroupDescriptor constantsDesc
			{
				.layout = pipeline.GetBindGroupLayout(0),
				.entries = vsSamplerBindings.data(),
				.entryCount = vsSamplerBindings.size()
			};

			auto m_constantsUniform = device->CreateBindGroup(&constantsDesc);
			pass.SetBindGroup(2, m_constantsUniform);
		}

		{
			Array<wgpu::BindGroupEntry> psSamplerBindings{};

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; i++)
			{
				const auto& state = m_currentPSStates[i];

				if (auto it = m_states.find(state); it != m_states.end())
				{
					psSamplerBindings << wgpu::BindGroupEntry
					{
						.binding = i,
						.sampler = it->second->m_sampler
					};
				}
			}

			wgpu::BindGroupDescriptor constantsDesc
			{
				.layout = pipeline.GetBindGroupLayout(0),
				.entries = psSamplerBindings.data(),
				.entryCount = psSamplerBindings.size()
			};

			auto m_constantsUniform = device->CreateBindGroup(&constantsDesc);
			pass.SetBindGroup(4, m_constantsUniform);
		}
	}

	WebGPUSamplerState::SamplerStateList::iterator WebGPUSamplerState::create(wgpu::Device* device, const SamplerState& state)
	{
		std::unique_ptr<SamplerState_WebGPU> samplerState = std::make_unique<SamplerState_WebGPU>();

		wgpu::SamplerDescriptor desc 
		{
			.minFilter = ToEnum<wgpu::FilterMode>(FromEnum(state.min)),
			.magFilter = ToEnum<wgpu::FilterMode>(FromEnum(state.mag)),
			.mipmapFilter = ToEnum<wgpu::FilterMode>(FromEnum(state.mip)),
			.addressModeU = ToEnum<wgpu::AddressMode>(FromEnum(state.addressU)),
			.addressModeV = ToEnum<wgpu::AddressMode>(FromEnum(state.addressV)),
			.addressModeW = ToEnum<wgpu::AddressMode>(FromEnum(state.addressW)),
			.maxAnisotropy = state.maxAnisotropy,
			.lodMinClamp = 0.0f,
			.lodMaxClamp = 1000.0f,
		};

		samplerState->m_sampler = device->CreateSampler(&desc);

		if (m_states.size() >= 1024)
		{
			m_states.clear();
		}

		return m_states.emplace(state, std::move(samplerState)).first;
	}
}
