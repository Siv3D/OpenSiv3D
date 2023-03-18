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

# include <Siv3D/2DShapes.hpp>
# include "D3D11RasterizerState.hpp"

namespace s3d
{
	D3D11RasterizerState::D3D11RasterizerState(const D3D11Device& device)
		: m_device{ device.getDevice() }
		, m_context{ device.getContext() } {}

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

	void D3D11RasterizerState::setScissorRect(const Rect& scissorRect)
	{
		D3D11_RECT r{ scissorRect.x, scissorRect.y, scissorRect.x + scissorRect.w, scissorRect.y + scissorRect.h };

		m_context->RSSetScissorRects(1, &r);
	}

	D3D11RasterizerState::StateList::iterator D3D11RasterizerState::create(const RasterizerState& state)
	{
		const D3D11_RASTERIZER_DESC desc =
		{
			.FillMode				= static_cast<D3D11_FILL_MODE>(state.fillMode),
			.CullMode				= static_cast<D3D11_CULL_MODE>(state.cullMode),
			.FrontCounterClockwise	= false,
			.DepthBias				= state.depthBias,
			.DepthBiasClamp			= 0.0f,
			.SlopeScaledDepthBias	= 0.0f,
			.DepthClipEnable		= true,
			.ScissorEnable			= state.scissorEnable,
			.MultisampleEnable		= (state.antialiasedLine3D ? false : true),
			.AntialiasedLineEnable	= (state.antialiasedLine3D ? true : false),
		};

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
