//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <array>
# include <Siv3D/Common.hpp>
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/HashTable.hpp>
# import <Metal/Metal.h>

namespace s3d
{
	class MetalSamplerState
	{
	private:

		static constexpr SamplerState NullState{ TextureAddressMode::Repeat,
			TextureAddressMode::Repeat,
			TextureAddressMode::Repeat,
			TextureFilter::Linear,
			TextureFilter::Linear,
			TextureFilter::Linear,
			0,
			-1,
			Float4(FLT_MIN, FLT_MIN, FLT_MIN, FLT_MIN) };

		using StateList = HashTable<SamplerState, id<MTLSamplerState>>;
		
		id<MTLDevice> m_device = nil;

		StateList m_states;

		//std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentVSStates;

		//std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentPSStates;

		StateList::iterator create(const SamplerState& state);

	public:

		explicit MetalSamplerState(id<MTLDevice> device);

		//void setVS(uint32 slot, const SamplerState& state);

		void setPS(id<MTLRenderCommandEncoder> renderCommandEncoder, uint32 slot, const SamplerState& state);
	};
}
