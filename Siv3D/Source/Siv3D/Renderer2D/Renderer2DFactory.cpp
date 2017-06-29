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

# include "D3D11/CRenderer2D_D3D11.hpp"
# include "GL/CRenderer2D_GL.hpp"

namespace s3d
{
	ISiv3DRenderer2D* ISiv3DRenderer2D::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return new CRenderer2D_D3D11;

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)
	
		return new CRenderer2D_GL;

	# endif
	}
}
