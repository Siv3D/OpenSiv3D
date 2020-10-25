//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/D3D11.hpp>

namespace s3d
{
	class D3D11DepthStencilState
	{
	private:

		ID3D11Device* m_device			= nullptr;

		ID3D11DeviceContext* m_context	= nullptr;

		ComPtr<ID3D11DepthStencilState> m_state;

	public:

		D3D11DepthStencilState(ID3D11Device* device, ID3D11DeviceContext* context);
	};
}
