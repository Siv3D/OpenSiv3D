﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline FilePath FileOrResource(const FilePathView path)
	{
		if (GetResourceOption() == ResourceOption::File)
		{
			return FilePath{ path };
		}
		else
		{
			return Resource(path);
		}
	}
}
