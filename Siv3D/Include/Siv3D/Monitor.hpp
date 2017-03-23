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

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "Rectangle.hpp"

namespace s3d
{
	struct Monitor
	{
		String name;
		String id;
		String displayDeviceName;
		Rect displayRect;
		Rect workArea;
		bool isPrimary;
	};

	namespace System
	{
		// [x] Windows | [x] macOS | [ ] Linux
		Array<Monitor> EnumActiveMonitors();

		// [x] Windows | [ ] macOS | [ ] Linux
		size_t GetCurrentMonitorIndex();
	}
}
