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
	namespace detail
	{
		static constexpr wgpu::AddressMode AddressModeTable[4]
		{
			wgpu::AddressMode::Repeat,
			wgpu::AddressMode::MirrorRepeat,
			wgpu::AddressMode::ClampToEdge,
			wgpu::AddressMode::ClampToEdge
		};
	}

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

	void WebGPUSamplerState::setVSSampler(wgpu::Device* device, const uint32 slot, const SamplerState& state)
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

	void WebGPUSamplerState::setVSSampler(wgpu::Device* device, const uint32 slot, None_t)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		m_currentVSStates[slot] = NullSamplerState;
	}

	void WebGPUSamplerState::setPSSampler(wgpu::Device* device, const uint32 slot, const SamplerState& state)
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

	void WebGPUSamplerState::setPSSampler(wgpu::Device* device, const uint32 slot, None_t)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		m_currentPSStates[slot] = NullSamplerState;
	}

	void WebGPUSamplerState::setVSTexture(const uint32 slot, wgpu::Texture texture)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		m_currentVSTextures[slot] = texture;
	}

	void WebGPUSamplerState::setVSTexture(const uint32 slot, None_t)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		m_currentVSTextures[slot] = nullptr;
	}

	void WebGPUSamplerState::setPSTexture(const uint32 slot, wgpu::Texture texture)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		m_currentPSTextures[slot] = texture;
	}

	void WebGPUSamplerState::setPSTexture(const uint32 slot, None_t)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		m_currentPSTextures[slot] = nullptr;
	}

	void WebGPUSamplerState::bind(wgpu::Device* device, const wgpu::RenderPipeline& pipeline, const wgpu::RenderPassEncoder& pass)
	{
		{
			Array<wgpu::BindGroupEntry> vsBindings{};

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; i++)
			{
				const auto& state = m_currentVSStates[i];
				const auto texture = m_currentVSTextures[i];

				if (auto it = m_states.find(state); it != m_states.end() && texture)
				{
					vsBindings << wgpu::BindGroupEntry
					{
						.binding = 2 * i,
						.sampler = it->second->m_sampler
					};

					vsBindings << wgpu::BindGroupEntry
					{
						.binding = 2 * i + 1,
						.textureView = texture.CreateView()
					};
				}
			}

			wgpu::BindGroupDescriptor constantsDesc
			{
				.layout = pipeline.GetBindGroupLayout(3),
				.entries = vsBindings.data(),
				.entryCount = vsBindings.size()
			};

			auto m_constantsUniform = device->CreateBindGroup(&constantsDesc);
			pass.SetBindGroup(3, m_constantsUniform);
		}

		{
			Array<wgpu::BindGroupEntry> psBindings{};

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; i++)
			{
				const auto& state = m_currentPSStates[i];
				const auto texture = m_currentPSTextures[i];

				if (auto it = m_states.find(state); it != m_states.end() && texture)
				{
					psBindings << wgpu::BindGroupEntry
					{
						.binding = 2 * i,
						.sampler = it->second->m_sampler
					};

					psBindings << wgpu::BindGroupEntry
					{
						.binding = 2 * i + 1,
						.textureView = texture.CreateView()
					};
				}
			}

			wgpu::BindGroupDescriptor constantsDesc
			{
				.layout = pipeline.GetBindGroupLayout(2),
				.entries = psBindings.data(),
				.entryCount = psBindings.size()
			};

			auto m_constantsUniform = device->CreateBindGroup(&constantsDesc);
			pass.SetBindGroup(2, m_constantsUniform);
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
			.addressModeU = detail::AddressModeTable[FromEnum(state.addressU)],
			.addressModeV = detail::AddressModeTable[FromEnum(state.addressV)],
			.addressModeW = detail::AddressModeTable[FromEnum(state.addressW)],
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
