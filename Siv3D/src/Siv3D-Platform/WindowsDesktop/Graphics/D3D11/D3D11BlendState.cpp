//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "D3D11BlendState.hpp"

namespace s3d
{
	D3D11BlendState::D3D11BlendState(ID3D11Device* const device, ID3D11DeviceContext* const context)
		: m_device(device)
		, m_context(context)
	{

	}

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

	D3D11BlendState::BlendStateList::iterator D3D11BlendState::create(const BlendState& state)
	{
		D3D11_BLEND_DESC desc{};
		desc.AlphaToCoverageEnable					= state.alphaToCoverageEnable;
		desc.IndependentBlendEnable					= false;
		desc.RenderTarget[0].BlendEnable			= state.enable;
		desc.RenderTarget[0].SrcBlend				= static_cast<D3D11_BLEND>(state.src);
		desc.RenderTarget[0].DestBlend				= static_cast<D3D11_BLEND>(state.dst);
		desc.RenderTarget[0].BlendOp				= static_cast<D3D11_BLEND_OP>(state.op);
		desc.RenderTarget[0].RenderTargetWriteMask	= (state.writeA << 3) | (state.writeB << 2) | (state.writeG << 1) | uint32(state.writeR);
		desc.RenderTarget[0].SrcBlendAlpha			= static_cast<D3D11_BLEND>(state.srcAlpha);
		desc.RenderTarget[0].DestBlendAlpha			= static_cast<D3D11_BLEND>(state.dstAlpha);
		desc.RenderTarget[0].BlendOpAlpha			= static_cast<D3D11_BLEND_OP>(state.opAlpha);

		ComPtr<ID3D11BlendState> blendState;

		if (FAILED(m_device->CreateBlendState(&desc, &blendState)))
		{
			return m_states.end();
		}

		return m_states.emplace(state, std::move(blendState)).first;
	}
}
