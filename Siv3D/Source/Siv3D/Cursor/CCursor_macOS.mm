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

# include <Siv3D/PointVector.hpp>
# import  <Cocoa/Cocoa.h>

namespace s3d
{
	namespace detail
	{
		Point CursorScreenPos_macOS()
		{
			const int32 screenHeight = [[NSScreen mainScreen] frame].size.height;
			const NSPoint screenPos = [NSEvent mouseLocation];
			return Point(static_cast<int32>(screenPos.x), static_cast<int32>(screenHeight - screenPos.y));
		}
		
		void CursorSetPos_macOS(const int32 x, const int32 y)
		{
			CGPoint globalPos;
			globalPos.x = x;
			globalPos.y = y;
			CGWarpMouseCursorPosition(globalPos);
		}
	}
}
