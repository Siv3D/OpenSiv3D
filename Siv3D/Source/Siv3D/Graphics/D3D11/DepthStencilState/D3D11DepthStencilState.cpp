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

# include "D3D11DepthStencilState.hpp"

namespace s3d
{
	D3D11DepthStencilState::D3D11DepthStencilState(ID3D11Device* const device, ID3D11DeviceContext* const context)
		: m_device(device)
		, m_context(context)
	{
		D3D11_DEPTH_STENCIL_DESC desc{};
		desc.DepthEnable					= false;
		desc.DepthWriteMask					= D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc						= D3D11_COMPARISON_GREATER;
		desc.StencilEnable					= false;
		desc.StencilReadMask				= 0xFF;
		desc.StencilWriteMask				= 0xFF;
		desc.FrontFace.StencilFailOp		= D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilDepthFailOp	= D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilPassOp		= D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;
		desc.BackFace.StencilFailOp			= D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilDepthFailOp	= D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilPassOp			= D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;

		if (FAILED(m_device->CreateDepthStencilState(&desc, &m_state)))
		{
			return;
		}

		m_context->OMSetDepthStencilState(m_state.Get(), 0);
	}
}

# endif
