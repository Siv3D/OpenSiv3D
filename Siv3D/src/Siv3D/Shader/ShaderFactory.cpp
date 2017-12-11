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

# include "D3D11/CShader_D3D11.hpp"
# include "GL/CShader_GL.hpp"

namespace s3d
{
	ISiv3DShader* ISiv3DShader::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return new CShader_D3D11;

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)
	
		return new CShader_GL;

	# endif
	}
}

