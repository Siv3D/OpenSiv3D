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

# include "D3D11BlendState.hpp"

namespace s3d
{
	D3D11BlendState::D3D11BlendState(ID3D11Device* const device, ID3D11DeviceContext* const context)
		: m_device(device)
		, m_context(context)
	{
		D3D11_BLEND_DESC desc{};
		desc.AlphaToCoverageEnable					= false;
		desc.IndependentBlendEnable					= false;
		desc.RenderTarget[0].BlendEnable			= true;
		desc.RenderTarget[0].SrcBlend				= D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend				= D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;
		desc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha			= D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;

		if (FAILED(m_device->CreateBlendState(&desc, &m_state)))
		{
			return;
		}

		static constexpr float blendFactor[4]{ 0.0f, 0.0f, 0.0f, 0.0f };

		m_context->OMSetBlendState(m_state.Get(), blendFactor, 0xffFFffFF);
	}
}
