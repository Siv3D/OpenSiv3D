//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <unordered_map>
# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <wrl.h>
using namespace Microsoft::WRL;
# include <d3d11.h>
# include "../../../../../Inc/Siv3D/RasterizerState.hpp"

namespace s3d
{
	const RasterizerState NullRasterizerState(FillMode(0));

	class D3D11RasterizerState
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		using RasterizerStateList = std::unordered_map < RasterizerState, ComPtr<ID3D11RasterizerState> > ;

		RasterizerStateList m_states;

		RasterizerState m_currentState = NullRasterizerState;

		RasterizerStateList::iterator create(const RasterizerState& state);

	public:

		void init();

		void set(const RasterizerState& state);

		void setScissorRect(const Rect& rect);
	};
}
