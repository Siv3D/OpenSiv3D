﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "D3D11DepthStencilState.hpp"

namespace s3d
{
	D3D11DepthStencilState::D3D11DepthStencilState(ID3D11Device* device, ID3D11DeviceContext* context)
		: m_device(device)
		, m_context(context)
	{
		const D3D11_DEPTH_STENCIL_DESC desc =
		{
			.DepthEnable					= false,
			.DepthWriteMask					= D3D11_DEPTH_WRITE_MASK_ZERO,
			.DepthFunc						= D3D11_COMPARISON_GREATER,
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

		if (FAILED(m_device->CreateDepthStencilState(&desc, &m_state)))
		{
			return;
		}

		m_context->OMSetDepthStencilState(m_state.Get(), 0);
	}
}
