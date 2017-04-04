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
# include <Siv3D/Image.hpp>
# import  <Cocoa/Cocoa.h>

namespace s3d
{
	namespace detail
	{
		String ClipboardGetText_macOS()
		{
			NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
			NSArray* classArray			= [NSArray arrayWithObject:[NSString class]];
			NSDictionary* options		= [NSDictionary dictionary];
			
			if ([pasteboard canReadObjectForClasses:classArray options:options])
			{
				NSArray* content = [pasteboard readObjectsForClasses:classArray options:options];
				
				if(NSString* text = [content firstObject])
				{
					return CharacterSet::Widen([text UTF8String]);
				}
			}
			
			return String();
		}
		
		Image ClipboardGetImage_macOS()
		{
			NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
			NSArray* classArray			= [NSArray arrayWithObject:[NSImage class]];
			NSDictionary* options		= [NSDictionary dictionary];

			if ([pasteboard canReadObjectForClasses:classArray options:options])
			{
				if (NSBitmapImageRep* rep = [NSBitmapImageRep imageRepWithPasteboard:pasteboard])
				{
					const int32 width = [rep size].width;
					const int32 height = [rep size].height;
					Image image(width, height);
					
					const uint8* pSrc = [rep bitmapData];
					Color* pDst = image.data();
					
					::memcpy(pDst, pSrc, image.size_bytes());

					return image;
				}
			}
			
			return Image();
		}
		
		Array<FilePath> ClipboardGetFilePaths_macOS()
		{
			NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
			NSArray* classArray			= [NSArray arrayWithObject:[NSURL class]];
			NSDictionary* options		= [NSDictionary dictionaryWithObject:
										   [NSNumber numberWithBool:YES] forKey:NSPasteboardURLReadingFileURLsOnlyKey];
			NSArray* fileURLs			= [pasteboard readObjectsForClasses:classArray options:options];
			
			if ([fileURLs count] > 0)
			{
				return Array<FilePath>([fileURLs count]);
			}
			
			return Array<FilePath>();
		}
		
		void ClipboardClear_macOS()
		{
			NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
			[pasteboard clearContents];
		}
		
		long ClipboardGetChangeCount_macOS()
		{
			NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
			return [pasteboard changeCount];
		}
	}
}
