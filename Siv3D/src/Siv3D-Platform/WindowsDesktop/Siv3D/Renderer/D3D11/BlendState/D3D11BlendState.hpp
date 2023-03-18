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
# include <Siv3D/BlendState.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include "../Device/D3D11Device.hpp"

namespace s3d
{
	class D3D11BlendState
	{
	private:

		static constexpr BlendState NullState{ false, Blend{ 0 } };

		using StateList = HashTable<BlendState, ComPtr<ID3D11BlendState>>;

		ID3D11Device* m_device			= nullptr;

		ID3D11DeviceContext* m_context	= nullptr;

		StateList m_states;

		BlendState m_currentState = NullState;

		StateList::iterator create(const BlendState& state);

	public:

		D3D11BlendState(const D3D11Device& device);

		void set(const BlendState& state);
	};
}
