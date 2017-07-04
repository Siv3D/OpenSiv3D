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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "D3D11SamplerState.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr D3D11_FILTER filterTable[8] =
		{
			D3D11_FILTER_MIN_MAG_MIP_POINT,
			D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR,
			D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
			D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR,
			D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT,
			D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
			D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,
			D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		};

		static constexpr D3D11_TEXTURE_ADDRESS_MODE addressModeTable[4] =
		{
			D3D11_TEXTURE_ADDRESS_WRAP,
			D3D11_TEXTURE_ADDRESS_MIRROR,
			D3D11_TEXTURE_ADDRESS_CLAMP,
			D3D11_TEXTURE_ADDRESS_BORDER,
		};
	}

	D3D11SamplerState::D3D11SamplerState(ID3D11Device* const device, ID3D11DeviceContext* const context)
		: m_device(device)
		, m_context(context)
	{
		m_currentVSStates.fill(NullSamplerState);
		m_currentPSStates.fill(NullSamplerState);
	}

	void D3D11SamplerState::setVS(const uint32 slot, const SamplerState& state)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		if (state == m_currentVSStates[slot])
		{
			return;
		}

		auto it = m_states.find(state);

		if (it == m_states.end())
		{
			it = create(state);

			if (it == m_states.end())
			{
				return;
			}
		}

		m_context->VSSetSamplers(slot, 1, it->second.GetAddressOf());

		m_currentVSStates[slot] = state;
	}

	void D3D11SamplerState::setPS(const uint32 slot, const SamplerState& state)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		if (state == m_currentPSStates[slot])
		{
			return;
		}

		auto it = m_states.find(state);

		if (it == m_states.end())
		{
			it = create(state);

			if (it == m_states.end())
			{
				return;
			}
		}

		m_context->PSSetSamplers(slot, 1, it->second.GetAddressOf());

		m_currentPSStates[slot] = state;
	}

	D3D11SamplerState::SamplerStateList::iterator D3D11SamplerState::create(const SamplerState& state)
	{
		const uint32 filterIndex = ((static_cast<int32>(state.min) & 1) << 2)
			| ((static_cast<int32>(state.mag) & 1) << 1) | (static_cast<int32>(state.mip) & 1);

		D3D11_SAMPLER_DESC desc{};
		desc.Filter			= detail::filterTable[filterIndex];
		desc.AddressU		= detail::addressModeTable[static_cast<int32>(state.addressU)];
		desc.AddressV		= detail::addressModeTable[static_cast<int32>(state.addressV)];
		desc.AddressW		= detail::addressModeTable[static_cast<int32>(state.addressW)];
		desc.MipLODBias		= state.lodBias;
		desc.ComparisonFunc	= D3D11_COMPARISON_NEVER;
		desc.MaxAnisotropy	= state.maxAnisotropy;
		desc.BorderColor[0] = state.borderColor.x;
		desc.BorderColor[1] = state.borderColor.y;
		desc.BorderColor[2] = state.borderColor.z;
		desc.BorderColor[3] = state.borderColor.w;
		desc.MinLOD			= -D3D11_FLOAT32_MAX;
		desc.MaxLOD			= D3D11_FLOAT32_MAX;

		if (desc.Filter == D3D11_FILTER_MIN_MAG_MIP_LINEAR && desc.MaxAnisotropy > 1)
		{
			desc.Filter = D3D11_FILTER_ANISOTROPIC;
		}

		ComPtr<ID3D11SamplerState> samplerState;

		if (FAILED(m_device->CreateSamplerState(&desc, &samplerState)))
		{
			return m_states.end();
		}

		if (m_states.size() >= 1024)
		{
			m_states.clear();
		}

		return m_states.emplace(state, std::move(samplerState)).first;
	}
}

# endif
