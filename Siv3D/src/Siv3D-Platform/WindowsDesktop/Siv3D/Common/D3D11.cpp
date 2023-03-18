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

# include "D3D11.hpp"

namespace s3d
{
	namespace D3D11
	{
		void ResetPSShaderResources(ID3D11DeviceContext* context)
		{
			constexpr ID3D11ShaderResourceView* nullAttach[16] = { nullptr };
			context->PSSetShaderResources(0, 16, nullAttach);
		}
	}
}
