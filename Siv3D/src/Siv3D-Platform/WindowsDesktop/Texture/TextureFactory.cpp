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

# include <Texture/D3D11/CTexture_D3D11.hpp>

namespace s3d
{
	ISiv3DTexture* ISiv3DTexture::Create()
	{
		return new CTexture_D3D11;
	}
}
