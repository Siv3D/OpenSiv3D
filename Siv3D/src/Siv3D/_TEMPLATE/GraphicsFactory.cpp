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

# include "CGraphics.hpp"

namespace s3d
{
	ISiv3DGraphics* ISiv3DGraphics::Create()
	{
		return new CGraphics;
	}
}
