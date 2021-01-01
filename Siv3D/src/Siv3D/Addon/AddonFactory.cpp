//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CAddon.hpp"

namespace s3d
{
	ISiv3DAddon* ISiv3DAddon::Create()
	{
		return new CAddon;
	}
}
