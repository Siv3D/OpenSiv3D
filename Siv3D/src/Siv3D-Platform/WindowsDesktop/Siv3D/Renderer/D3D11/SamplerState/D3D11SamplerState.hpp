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
# include <array>
# include <Siv3D/Common.hpp>
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include "../Device/D3D11Device.hpp"

namespace s3d
{
	class D3D11SamplerState
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

		using StateList = HashTable<SamplerState, ComPtr<ID3D11SamplerState>>;

		ID3D11Device* m_device			= nullptr;

		ID3D11DeviceContext* m_context	= nullptr;

		StateList m_states;

		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentVSStates;

		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentPSStates;

		StateList::iterator create(const SamplerState& state);

	public:

		D3D11SamplerState(const D3D11Device& device);

		void setVS(uint32 slot, const SamplerState& state);

		void setPS(uint32 slot, const SamplerState& state);
	};
}
