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

# include "D3D11DepthStencilState.hpp"

namespace s3d
{
	D3D11DepthStencilState::D3D11DepthStencilState(const D3D11Device& device)
		: m_device{ device.getDevice() }
		, m_context{ device.getContext() } {}

	void D3D11DepthStencilState::set(const DepthStencilState& state)
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

		m_context->OMSetDepthStencilState(it->second.Get(), 0);

		m_currentState = state;
	}

	D3D11DepthStencilState::StateList::iterator D3D11DepthStencilState::create(const DepthStencilState& state)
	{
		const D3D11_DEPTH_STENCIL_DESC desc =
		{
			.DepthEnable					= state.depthEnable,
			.DepthWriteMask					= D3D11_DEPTH_WRITE_MASK(state.depthWriteEnable),
			.DepthFunc						= D3D11_COMPARISON_FUNC(state.depthFunc),
			.StencilEnable					= false,
			.StencilReadMask				= 0xFF,
			.StencilWriteMask				= 0xFF,
			.FrontFace	=
				{
					.StencilFailOp		= D3D11_STENCIL_OP_KEEP,
					.StencilDepthFailOp	= D3D11_STENCIL_OP_KEEP,
					.StencilPassOp		= D3D11_STENCIL_OP_KEEP,
					.StencilFunc		= D3D11_COMPARISON_ALWAYS,
				},
			.BackFace	=
				{
					.StencilFailOp		= D3D11_STENCIL_OP_KEEP,
					.StencilDepthFailOp	= D3D11_STENCIL_OP_KEEP,
					.StencilPassOp		= D3D11_STENCIL_OP_KEEP,
					.StencilFunc		= D3D11_COMPARISON_ALWAYS,
				}
		};

		ComPtr<ID3D11DepthStencilState> depthStencilState;

		if (FAILED(m_device->CreateDepthStencilState(&desc, &depthStencilState)))
		{
			return m_states.end();
		}

		if (m_states.size() >= 1024)
		{
			m_states.clear();
		}

		return m_states.emplace(state, std::move(depthStencilState)).first;
	}
}
