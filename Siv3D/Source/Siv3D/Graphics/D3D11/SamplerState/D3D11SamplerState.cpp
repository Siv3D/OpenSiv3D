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
	D3D11SamplerState::D3D11SamplerState(ID3D11Device* const device, ID3D11DeviceContext* const context)
		: m_device(device)
		, m_context(context)
	{
		D3D11_SAMPLER_DESC desc{};
		desc.Filter			= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		desc.AddressU		= D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV		= D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW		= D3D11_TEXTURE_ADDRESS_WRAP;
		desc.MinLOD			= -D3D11_FLOAT32_MAX;
		desc.MaxLOD			= D3D11_FLOAT32_MAX;
		desc.MaxAnisotropy	= 1;
		desc.ComparisonFunc	= D3D11_COMPARISON_NEVER;
		desc.BorderColor[0] = 1.0f;
		desc.BorderColor[1] = 1.0f;
		desc.BorderColor[2] = 1.0f;
		desc.BorderColor[3] = 1.0f;
		
		if (FAILED(m_device->CreateSamplerState(&desc, &m_state)))
		{
			return;
		}

		m_context->PSSetSamplers(0, 1, m_state.GetAddressOf());
	}
}

# endif
