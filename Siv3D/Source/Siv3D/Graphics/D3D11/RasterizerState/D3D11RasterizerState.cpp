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

# include "D3D11RasterizerState.hpp"

namespace s3d
{
	D3D11RasterizerState::D3D11RasterizerState(ID3D11Device* const device, ID3D11DeviceContext* const context)
		: m_device(device)
		, m_context(context)
	{

	}

	void D3D11RasterizerState::set(const RasterizerState& state)
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

		m_context->RSSetState(it->second.Get());

		m_currentState = state;
	}

	D3D11RasterizerState::RasterizerStateList::iterator D3D11RasterizerState::create(const RasterizerState& state)
	{
		D3D11_RASTERIZER_DESC desc{};
		desc.FillMode				= static_cast<D3D11_FILL_MODE>(state.fillMode);
		desc.CullMode				= static_cast<D3D11_CULL_MODE>(state.cullMode);
		desc.FrontCounterClockwise	= false;
		desc.DepthBias				= state.depthBias;
		desc.DepthBiasClamp			= 0.0f;
		desc.SlopeScaledDepthBias	= 0.0f;
		desc.DepthClipEnable		= true;
		desc.ScissorEnable			= state.scissorEnable;
		desc.MultisampleEnable		= state.antialiasedLine3D ? false : true;
		desc.AntialiasedLineEnable	= state.antialiasedLine3D ? true : false;

		ComPtr<ID3D11RasterizerState> rasterizerState;

		if (FAILED(m_device->CreateRasterizerState(&desc, &rasterizerState)))
		{
			return m_states.end();
		}

		if (m_states.size() >= 1024)
		{
			m_states.clear();
		}

		return m_states.emplace(state, std::move(rasterizerState)).first;
	}
}

# endif
