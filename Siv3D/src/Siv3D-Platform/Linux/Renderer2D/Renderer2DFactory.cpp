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

# include <Renderer2D/GL/CRenderer2D_GL.hpp>

namespace s3d
{
	ISiv3DRenderer2D* ISiv3DRenderer2D::Create()
	{
		return new CRenderer2D_GL;
	}
}
