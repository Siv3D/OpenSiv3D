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
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "CTexture_GL.hpp"
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	Texture::IDType CTexture_GL::createFromBackBuffer()
	{
		return 0;
	}

	Texture::IDType CTexture_GL::createRT(const Size& size)
	{
		return 0;
	}
	
	void CTexture_GL::release(Texture::IDType handleID)
	{
	
	}
	
	Size CTexture_GL::getSize(Texture::IDType handleID)
	{
		return Size(0, 0);
	}
}

# endif
