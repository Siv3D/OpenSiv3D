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

# include <Siv3D/Windows.hpp>
# include <wrl.h>
# include <d3d11.h>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/RasterizerState.hpp>

using namespace Microsoft::WRL;

namespace s3d
{
	const RasterizerState NullRasterizerState(FillMode(0));

	class D3D11RasterizerState
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		using RasterizerStateList = HashTable<RasterizerState, ComPtr<ID3D11RasterizerState>>;

		RasterizerStateList m_states;

		RasterizerState m_currentState = NullRasterizerState;

		RasterizerStateList::iterator create(const RasterizerState& state);

	public:

		D3D11RasterizerState(ID3D11Device* device, ID3D11DeviceContext* context);

		void set(const RasterizerState& state);

		void setScissorRect(const Rect& scissorRect);
	};
}

# endif
