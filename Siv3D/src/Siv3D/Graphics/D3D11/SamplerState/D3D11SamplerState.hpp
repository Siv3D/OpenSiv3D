//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Windows.hpp>
# include <wrl.h>
# include <d3d11.h>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/SamplerState.hpp>
# include <cfloat>

using namespace Microsoft::WRL;

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

	class D3D11SamplerState
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		using SamplerStateList = HashTable<SamplerState, ComPtr<ID3D11SamplerState>>;

		SamplerStateList m_states;

		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentVSStates;

		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentPSStates;

		SamplerStateList::iterator create(const SamplerState& state);

	public:

		D3D11SamplerState(ID3D11Device* device, ID3D11DeviceContext* context);

		void setVS(uint32 slot, const SamplerState& state);

		void setPS(uint32 slot, const SamplerState& state);
	};
}

# endif
