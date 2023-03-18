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
# include <Siv3D/Windows/Windows.hpp>
# include <d3d11.h>
# include <d3d11_1.h>
# include <dxgi1_5.h>
# include <d3dcompiler.h>

# define SIV3D_USE_DIRECT3D11_3
//# define SIV3D_USE_DIRECT3D11_4

namespace s3d
{
	namespace D3D11
	{
		void ResetPSShaderResources(ID3D11DeviceContext* context);
	}
}
