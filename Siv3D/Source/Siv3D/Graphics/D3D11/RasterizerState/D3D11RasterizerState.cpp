//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../../../Siv3DEngine.hpp"
# include "../../IGraphics.hpp"
# include "../Device/D3D11Device.hpp"
# include "D3D11RasterizerState.hpp"
# include "../../../../../Inc/Siv3D/Rectangle.hpp"

namespace s3d
{
	void D3D11RasterizerState::init()
	{
		m_device = Siv3DEngine::GetGraphics()->getDevice()->getDevice();

		m_context = Siv3DEngine::GetGraphics()->getDevice()->getContext();
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

	void D3D11RasterizerState::setScissorRect(const Rect& rect)
	{
		D3D11_RECT r{ rect.x, rect.y, rect.x + rect.w, rect.y + rect.h };

		m_context->RSSetScissorRects(1, &r);
	}

	D3D11RasterizerState::RasterizerStateList::iterator D3D11RasterizerState::create(const RasterizerState& state)
	{
		D3D11_RASTERIZER_DESC desc{};
		desc.FillMode				= static_cast<D3D11_FILL_MODE>(state.fillMode);
		desc.CullMode				= static_cast<D3D11_CULL_MODE>(state.cullMode);
		desc.FrontCounterClockwise	= state.frontCounterClockwise;
		desc.DepthBias				= state.depthBias;
		desc.DepthBiasClamp			= 0.0f;
		desc.SlopeScaledDepthBias	= 0.0f;
		desc.DepthClipEnable		= true;
		desc.ScissorEnable			= state.scissorEnable;
		desc.MultisampleEnable		= state.antialiasedLine3D ? false : true;//multisampling;
		desc.AntialiasedLineEnable	= state.antialiasedLine3D ? true: false;

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
