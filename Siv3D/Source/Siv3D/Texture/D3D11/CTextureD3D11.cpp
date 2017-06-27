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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "CTextureD3D11.hpp"

namespace s3d
{
	bool CTextureD3D11::init(ID3D11Device* const device, IDXGISwapChain* const swapChain)
	{
		m_device = device;

		return true;
	}
}

# endif
