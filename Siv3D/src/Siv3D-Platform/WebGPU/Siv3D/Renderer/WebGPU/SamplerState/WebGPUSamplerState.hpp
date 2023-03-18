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
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Optional.hpp>
# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	class WebGPUSamplerState
	{
	private:

		struct SamplerState_WebGPU
		{
			SamplerState_WebGPU()
			{
			}

			~SamplerState_WebGPU()
			{
				if (m_sampler)
				{
					m_sampler.Release();
				}
			}

			wgpu::Sampler m_sampler = nullptr;
		};

		using SamplerStateList = HashTable<SamplerState, std::unique_ptr<SamplerState_WebGPU>>;

		SamplerStateList m_states;

		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentVSStates;

		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentPSStates;

		std::array<wgpu::TextureView, SamplerState::MaxSamplerCount> m_currentVSTextures;

		std::array<wgpu::TextureView, SamplerState::MaxSamplerCount> m_currentPSTextures;

		HashTable<size_t, wgpu::BindGroup> m_bindGroups;

		SamplerStateList::iterator create(wgpu::Device* device, const SamplerState& state);

	public:

		WebGPUSamplerState();

		void setVSSampler(wgpu::Device* device, uint32 slot, const SamplerState& state);

		void setVSSampler(wgpu::Device* device, uint32 slot, None_t);

		void setPSSampler(wgpu::Device* device, uint32 slot, const SamplerState& state);

		void setPSSampler(wgpu::Device* device, uint32 slot, None_t);

		void setVSTexture(uint32 slot, wgpu::TextureView texture);

		void setVSTexture(uint32 slot, None_t);

		void setPSTexture(uint32 slot, wgpu::TextureView texture);

		void setPSTexture(uint32 slot, None_t);

		void bind(wgpu::Device* device, const wgpu::RenderPipeline& pipeline, const wgpu::RenderPassEncoder& pass);
	};
}
