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
		D3D11_RASTERIZER_DESC desc{};
		desc.FillMode				= D3D11_FILL_SOLID;
		desc.CullMode				= D3D11_CULL_NONE;
		desc.FrontCounterClockwise	= false;
		desc.DepthBias				= 0;
		desc.DepthBiasClamp			= 0.0f;
		desc.SlopeScaledDepthBias	= 0.0f;
		desc.DepthClipEnable		= true;
		desc.ScissorEnable			= false;
		desc.MultisampleEnable		= false;
		desc.AntialiasedLineEnable	= false;

		if (FAILED(m_device->CreateRasterizerState(&desc, &m_state)))
		{
			return;
		}

		m_context->RSSetState(m_state.Get());
	}
}

# endif
