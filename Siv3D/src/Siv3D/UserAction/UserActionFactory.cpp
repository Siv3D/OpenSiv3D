﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CUserAction.hpp"

namespace s3d
{
	ISiv3DUserAction* ISiv3DUserAction::Create()
	{
		return new CUserAction;
	}
}
