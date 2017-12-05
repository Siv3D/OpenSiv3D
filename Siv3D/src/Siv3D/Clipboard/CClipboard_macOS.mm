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
				
				if (NSString* str = [content firstObject])
				{
					text = CharacterSet::Widen([str UTF8String]);
				}
			}
		}
		
		
		bool ClipboardGetText_macOS(String& text)
		{
			text.clear();
			
			NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
			NSDictionary* options		= [NSDictionary dictionary];
			NSArray* stringClassArray	= [NSArray arrayWithObject:[NSString class]];

			if ([pasteboard canReadObjectForClasses:stringClassArray options:options])
			{
				NSArray* content = [pasteboard readObjectsForClasses:stringClassArray options:options];
				
				if (NSString* str = [content firstObject])
				{
					text = CharacterSet::Widen([str UTF8String]);
				}
			}
			
			return !text.isEmpty();
		}
		
		bool ClipboardGetImage_macOS(Image& image)
		{
			image.clear();

			NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
			NSDictionary* options		= [NSDictionary dictionary];
			NSArray* imageClassArray	= [NSArray arrayWithObject:[NSImage class]];

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
			
			return !image.isEmpty();
		}
		
		bool ClipboardGetFilePaths_macOS(Array<FilePath>& filePaths)
		{
			filePaths.clear();
			
			NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
			NSDictionary* options		= [NSDictionary dictionary];
			NSArray* urlClassArray		= [NSArray arrayWithObject:[NSURL class]];
			
			if ([pasteboard canReadObjectForClasses:urlClassArray options:options])
			{
				NSArray* content = [pasteboard readObjectsForClasses:urlClassArray options:options];
				
				for (NSURL* url in content)
				{
					filePaths.push_back(CharacterSet::Widen([url.absoluteString UTF8String]));
				}
			}
			
			return !filePaths.isEmpty();
		}
		
		
		void ClipboardSetText_macOS(const String& text)
		{
			NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
			NSArray* stringClassArray	= [NSArray arrayWithObjects:NSStringPboardType, nil];
			
			[pasteboard declareTypes:stringClassArray owner:nil];
			[pasteboard setString:[NSString stringWithUTF8String:text.narrow().c_str()]
							 forType:NSStringPboardType];
		}
		
		void ClipboardSetImage_macOS(const Image& _image)
		{
			Image image(_image);
			
			image.swapRB();
			
			CGImageRef cgImage;
			{
				CFDataRef data = CFDataCreateWithBytesNoCopy(kCFAllocatorDefault,
															 image.dataAsUint8(), image.size_bytes(), kCFAllocatorNull);
			
				CGDataProviderRef dataProvider = CGDataProviderCreateWithCFData(data);
			
				cgImage = CGImageCreate(image.width(), image.height(), 8, 32, image.stride(),
										CGColorSpaceCreateWithName(kCGColorSpaceSRGB),
										kCGImageAlphaFirst | kCGBitmapByteOrder32Host,
										dataProvider, nullptr, false, kCGRenderingIntentDefault);
			}
			
			NSBitmapImageRep* rep = [[[NSBitmapImageRep alloc] initWithCGImage:cgImage] autorelease];
			NSImage* img = [[NSImage alloc] init];
			[img addRepresentation: rep];
			
			NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
			[pasteboard declareTypes: [NSArray arrayWithObject: NSTIFFPboardType] owner:nil];
			[pasteboard setData:[img TIFFRepresentation] forType:NSTIFFPboardType];
			
			[img release];
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
