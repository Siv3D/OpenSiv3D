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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/DepthStencilState.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include "../Device/D3D11Device.hpp"

namespace s3d
{
	class D3D11DepthStencilState
	{
	private:

		static constexpr DepthStencilState NullState{ false, false, DepthFunc{ 0 } };

		using StateList = HashTable<DepthStencilState, ComPtr<ID3D11DepthStencilState>>;

		ID3D11Device* m_device			= nullptr;

		ID3D11DeviceContext* m_context	= nullptr;
		
		StateList m_states;

		DepthStencilState m_currentState = NullState;

		StateList::iterator create(const DepthStencilState& state);

	public:

		D3D11DepthStencilState(const D3D11Device& device);

		void set(const DepthStencilState& state);
	};
}
