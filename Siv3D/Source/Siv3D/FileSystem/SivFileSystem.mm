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

# include <string>
# import <Foundation/Foundation.h>

bool trashFile(const char* path, const unsigned long pathLength, const bool isDirectory)
{
	NSURL* url = (CFBridgingRelease(CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8*)path, pathLength, isDirectory)));
    
	const bool result = [[NSFileManager defaultManager] trashItemAtURL: url
														resultingItemURL: nil
																	error: nil];

	return result;
}

std::string specialFolder(const int folder)
{
	const NSSearchPathDirectory folders[] = {
		NSDesktopDirectory,
		NSDocumentDirectory,
		NSCachesDirectory,
		NSMusicDirectory,
		NSPicturesDirectory,
		NSMoviesDirectory
	};

	NSArray* paths = NSSearchPathForDirectoriesInDomains(folders[folder], NSUserDomainMask, YES);
    
	NSString* directory = [paths objectAtIndex:0];

	return [directory UTF8String];
}
