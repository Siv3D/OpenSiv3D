//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Windows.hpp>
# include <d3d11.h>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/BlendState.hpp>

namespace s3d
{
	const BlendState NullBlendState(false, Blend(0));

	class D3D11BlendState
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		using BlendStateList = HashTable<BlendState, ComPtr<ID3D11BlendState>>;

		BlendStateList m_states;

		BlendState m_currentState = NullBlendState;

		BlendStateList::iterator create(const BlendState& state);

	public:

		D3D11BlendState(ID3D11Device* device, ID3D11DeviceContext* context);

		void set(const BlendState& state);
	};
}
