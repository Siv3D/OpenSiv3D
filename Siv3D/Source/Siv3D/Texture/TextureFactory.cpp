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

# include "D3D11/CTexture_D3D11.hpp"
# include "GL/CTexture_GL.hpp"

namespace s3d
{
	ISiv3DTexture* ISiv3DTexture::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return new CTexture_D3D11;

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)
	
		return new CTexture_GL;

	# endif
	}
}

