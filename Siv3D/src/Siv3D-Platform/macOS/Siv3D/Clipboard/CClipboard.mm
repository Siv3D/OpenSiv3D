//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include "CClipboard.hpp"
# import  <Cocoa/Cocoa.h>

namespace s3d
{
	namespace detail
	{		
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
					text = Unicode::Widen([str UTF8String]);
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
					NSString* s = [url.absoluteString stringByRemovingPercentEncoding];
					String path = Unicode::Widen([s UTF8String]);
					if (path.starts_with(U"file://"))
					{
						path.pop_front_N(7);
					}
					
					filePaths.push_back(path);
				}
			}
			
			return !filePaths.isEmpty();
		}
		
		
		void ClipboardSetText_macOS(const String& text)
		{
			NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
			NSArray* stringClassArray	= [NSArray arrayWithObjects:NSPasteboardTypeString, nil];
			
			[pasteboard declareTypes:stringClassArray owner:nil];
			[pasteboard setString:[NSString stringWithUTF8String:text.narrow().c_str()]
						  forType:NSPasteboardTypeString];
		}
		
		void ClipboardSetImage_macOS(const Image& _image)
		{
			Image image(_image);
			
			image.RGBAtoBGRA();
			
			@autoreleasepool
			{
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
				
				NSBitmapImageRep* rep = [[NSBitmapImageRep alloc] initWithCGImage:cgImage];
				NSImage* img = [[NSImage alloc] init];
				[img addRepresentation: rep];
				
				NSPasteboard* pasteboard	= [NSPasteboard generalPasteboard];
				[pasteboard declareTypes: [NSArray arrayWithObject: NSPasteboardTypeTIFF] owner:nil];
				[pasteboard setData:[img TIFFRepresentation] forType:NSPasteboardTypeTIFF];
			}
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

	CClipboard::CClipboard() {}

	CClipboard::~CClipboard()
	{
		LOG_SCOPED_TRACE(U"CClipboard::~CClipboard()");
	}

	void CClipboard::init()
	{
		LOG_SCOPED_TRACE(U"CClipboard::init()");
		
		m_changeCount = detail::ClipboardGetChangeCount_macOS();
	}

	bool CClipboard::hasChanged()
	{
		const uint64 currentChangeCount = detail::ClipboardGetChangeCount_macOS();
		
		const bool hasChanged = (currentChangeCount != m_changeCount);
		
		m_changeCount = currentChangeCount;
		
		return hasChanged;
	}

	bool CClipboard::getText(String& text)
	{
		return detail::ClipboardGetText_macOS(text);
	}

	bool CClipboard::getImage(Image& image)
	{
		return detail::ClipboardGetImage_macOS(image);
	}

	bool CClipboard::getFilePaths(Array<FilePath>& paths)
	{
		return detail::ClipboardGetFilePaths_macOS(paths);
	}

	void CClipboard::setText(const String& text)
	{
		detail::ClipboardSetText_macOS(text);
		
		m_changeCount = detail::ClipboardGetChangeCount_macOS();
	}

	void CClipboard::setImage(const Image& image)
	{
		detail::ClipboardSetImage_macOS(image);
		
		m_changeCount = detail::ClipboardGetChangeCount_macOS();
	}

	void CClipboard::clear()
	{
		detail::ClipboardClear_macOS();
		
		m_changeCount = detail::ClipboardGetChangeCount_macOS();
	}
}
