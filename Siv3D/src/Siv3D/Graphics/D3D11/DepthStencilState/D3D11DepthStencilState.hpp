//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Windows.hpp>
# include <wrl.h>
# include <d3d11.h>

using namespace Microsoft::WRL;

namespace s3d
{
	class D3D11DepthStencilState
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		ComPtr<ID3D11DepthStencilState> m_state;

	public:

		D3D11DepthStencilState(ID3D11Device* device, ID3D11DeviceContext* context);
	};
}

# endif
