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

# import <Cocoa/Cocoa.h>

void macOS_GetScreenCursorPos(double* xpos, double* ypos)
{
	const int screenHeight = [[NSScreen mainScreen] frame].size.height;
	const NSPoint screenPos = [NSEvent mouseLocation];
	
	if (xpos)
		*xpos = screenPos.x;
	if (ypos)
		*ypos = screenHeight - screenPos.y;
}
