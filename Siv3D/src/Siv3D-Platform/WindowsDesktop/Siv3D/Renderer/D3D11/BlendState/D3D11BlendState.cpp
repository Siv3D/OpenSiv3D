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

# include "D3D11BlendState.hpp"

namespace s3d
{
	D3D11BlendState::D3D11BlendState(const D3D11Device& device)
		: m_device{ device.getDevice() }
		, m_context{ device.getContext() } {}

	void D3D11BlendState::set(const BlendState& state)
	{
		if (state == m_currentState)
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

		static constexpr float BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		m_context->OMSetBlendState(it->second.Get(), BlendFactor, 0xffFFffFF);

		m_currentState = state;
	}

	D3D11BlendState::StateList::iterator D3D11BlendState::create(const BlendState& state)
	{
		const D3D11_BLEND_DESC desc
		{
			.AlphaToCoverageEnable	= state.alphaToCoverageEnable,
			.IndependentBlendEnable	= false,
			.RenderTarget
			{
				{
					.BlendEnable			= state.enable,
					.SrcBlend				= static_cast<D3D11_BLEND>(state.src),
					.DestBlend				= static_cast<D3D11_BLEND>(state.dst),
					.BlendOp				= static_cast<D3D11_BLEND_OP>(state.op),
					.SrcBlendAlpha			= static_cast<D3D11_BLEND>(state.srcAlpha),
					.DestBlendAlpha			= static_cast<D3D11_BLEND>(state.dstAlpha),
					.BlendOpAlpha			= static_cast<D3D11_BLEND_OP>(state.opAlpha),
					.RenderTargetWriteMask	= ((state.writeA << 3) | (state.writeB << 2) | (state.writeG << 1) | uint32(state.writeR)),
				}
			}
		};

		ComPtr<ID3D11BlendState> blendState;

		if (FAILED(m_device->CreateBlendState(&desc, &blendState)))
		{
			return m_states.end();
		}

		return m_states.emplace(state, std::move(blendState)).first;
	}
}
