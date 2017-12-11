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
# import  <Foundation/Foundation.h>

bool macOS_TrashFile(const char* path, const unsigned long pathLength, const bool isDirectory)
{
	NSURL* url = (CFBridgingRelease(CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8*)path, pathLength, isDirectory)));
    
	const bool result = [[NSFileManager defaultManager] trashItemAtURL: url
														resultingItemURL: nil
																	error: nil];

	return result;
}

std::string macOS_SpecialFolder(const int folder)
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
	
	// NSCachesDirectory
	if (folder == 2)
	{
		NSString* bundleID = [[NSBundle mainBundle] bundleIdentifier];
		directory = [directory stringByAppendingString:@"/Siv3DApp/"];
		directory = [directory stringByAppendingString:bundleID];
	}

	return [directory UTF8String];
}

std::string macOS_FullPath(const char* _path, bool isRelative)
{
	NSString* path = [NSString stringWithUTF8String:_path];
	
	if (isRelative)
	{
		NSURL* bundle = [[NSBundle mainBundle] bundleURL];
		NSURL* file = [NSURL URLWithString:path relativeToURL:bundle];
		NSURL* absolutePath = [file absoluteURL];
		return [absolutePath.absoluteString UTF8String];
	}
	else
	{
		NSURL* file = [NSURL URLWithString:path];
		NSURL* absolutePath = [file absoluteURL];
		return [absolutePath.absoluteString UTF8String];
	}
}
