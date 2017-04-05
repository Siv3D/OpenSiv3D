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
		void ClipboardGetItem_macOS(String& text, Image& image, Array<FilePath>& filePaths)
		{
			text.clear();
			image.clear();
			filePaths.clear();
			
			NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
			NSDictionary* options		= [NSDictionary dictionary];
			
			NSArray* stringClassArray	= [NSArray arrayWithObject:[NSString class]];
			NSArray* imageClassArray	= [NSArray arrayWithObject:[NSImage class]];
			NSArray* urlClassArray		= [NSArray arrayWithObject:[NSURL class]];
			
			if ([pasteboard canReadObjectForClasses:imageClassArray options:options])
			{
				NSArray* content = [pasteboard readObjectsForClasses:imageClassArray options:options];
				
				if ([content count] > 0)
				{
					NSImage* img = [content objectAtIndex:0];
					NSBitmapImageRep* rep = [NSBitmapImageRep imageRepWithData:[img TIFFRepresentation]];
				
					image.resize([rep pixelsWide], [rep pixelsHigh]);
					::memcpy(image.data(), [rep bitmapData], image.size_bytes());
				}
			}
			else if ([pasteboard canReadObjectForClasses:urlClassArray options:options])
			{
				NSArray* content = [pasteboard readObjectsForClasses:urlClassArray options:options];
				
				for (NSURL* url in content)
				{
					filePaths.push_back(CharacterSet::Widen([url.absoluteString UTF8String]));
				}
			}
			else if ([pasteboard canReadObjectForClasses:stringClassArray options:options])
			{
				NSArray* content = [pasteboard readObjectsForClasses:stringClassArray options:options];
				
				if(NSString* str = [content firstObject])
				{
					text = CharacterSet::Widen([str UTF8String]);
				}
			}
		}
		
		void ClipboardSetText_macOS(const String& text)
		{
			
		}
		
		void ClipboardSetImage_macOS(const Image& image)
		{
			
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
