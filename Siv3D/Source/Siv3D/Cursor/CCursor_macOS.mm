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
# include <Siv3D/Cursor.hpp>
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
		
		void CursorSetStyle_macOS(const CursorStyle style)
		{
			static id hiddenCursor;
			
			switch (style)
			{
			case CursorStyle::Arrow:
				[[NSCursor arrowCursor] set];
				break;
			case CursorStyle::IBeam:
				[[NSCursor IBeamCursor] set];
				break;
			case CursorStyle::Cross:
				[[NSCursor crosshairCursor] set];
				break;
			case CursorStyle::Hand:
				[[NSCursor pointingHandCursor] set];
				break;
			case CursorStyle::NotAllowed:
				[[NSCursor operationNotAllowedCursor] set];
				break;
			case CursorStyle::ResizeUpDown:
				[[NSCursor resizeUpDownCursor] set];
				break;
			case CursorStyle::ResizeLeftRight:
				[[NSCursor resizeLeftRightCursor] set];
				break;
			case CursorStyle::Hidden:
				if (hiddenCursor == nil)
				{
					NSImage* data = [[NSImage alloc] initWithSize:NSMakeSize(16, 16)];
					hiddenCursor = [[NSCursor alloc] initWithImage:data
														   hotSpot:NSZeroPoint];
					[data release];
				}
				[(NSCursor*) hiddenCursor set];
				break;
			}
		}
	}
}
