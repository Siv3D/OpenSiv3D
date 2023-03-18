//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

namespace s3d
{
	enum class LogType : uint8
	{
		Error,		// Release

		Fail,		// Release

		Warning,	// Release

		App,		// Release

		Info,		// Release

		Trace,		// Debug

		Verbose,	// Verbose
	};
}
