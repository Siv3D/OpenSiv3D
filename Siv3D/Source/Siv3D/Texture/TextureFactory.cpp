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

# include "D3D11/CTextureD3D11.hpp"
# include "GL/CTextureGL.hpp"

namespace s3d
{
	ISiv3DTexture* ISiv3DTexture::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return new CTextureD3D11;

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)
	
		return new CTextureGL;

	# endif
	}
}

