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

		SamplerStateList::iterator create(wgpu::Device* device, const SamplerState& state);

	public:

		WebGPUSamplerState();

		void setVS(wgpu::Device* device, uint32 slot, const SamplerState& state);

		void setVS(wgpu::Device* device, uint32 slot, None_t);

		void setPS(wgpu::Device* device, uint32 slot, const SamplerState& state);

		void setPS(wgpu::Device* device, uint32 slot, None_t);

		void bindSamplers(wgpu::Device* device, const wgpu::RenderPipeline& pipeline, const wgpu::RenderPassEncoder& pass);
	};
}
