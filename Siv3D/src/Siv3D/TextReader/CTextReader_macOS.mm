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

# include <string>
# import  <Foundation/Foundation.h>

std::string ConvertLine(const std::string& line)
{
	NSString* string = [NSString stringWithCString:line.c_str() encoding:[NSString defaultCStringEncoding]];

	return [string UTF8String];
}
