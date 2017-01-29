//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CConsole.hpp"

namespace s3d
{
	ISiv3DConsole* ISiv3DConsole::Create()
	{
		return new CConsole;
	}
}

