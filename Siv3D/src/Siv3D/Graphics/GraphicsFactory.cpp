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

# include "D3D11/CGraphics_D3D11.hpp"

namespace s3d
{
	ISiv3DGraphics* ISiv3DGraphics::Create()
	{
		return new CGraphics_D3D11;
	}
}

# elif defined(SIV3D_TARGET_MACOS)

# include "GL/CGraphics_GL.hpp"

namespace s3d
{
	ISiv3DGraphics* ISiv3DGraphics::Create()
	{
		return new CGraphics_GL;
	}
}

# elif defined(SIV3D_TARGET_LINUX)

# include "GL/CGraphics_GL.hpp"

namespace s3d
{
	ISiv3DGraphics* ISiv3DGraphics::Create()
	{
		return new CGraphics_GL;
	}
}

# endif
