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

# ifndef NOMINMAX
#	define  NOMINMAX
# endif
# ifndef STRICT
#	define  STRICT
# endif
# ifndef WIN32_LEAN_AND_MEAN
#	define  WIN32_LEAN_AND_MEAN
# endif
# ifndef _WIN32_WINNT
#	define  _WIN32_WINNT _WIN32_WINNT_WIN7
# endif
# ifndef NTDDI_VERSION
#	define  NTDDI_VERSION NTDDI_WIN7
# endif
# include <Windows.h>
# include <wrl.h>
# include <d3d11.h>
# include <Siv3D/HashMap.hpp>
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

		using RasterizerStateList = HashMap<RasterizerState, ComPtr<ID3D11RasterizerState>>;

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
