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

# import <Cocoa/Cocoa.h>

bool macOS_LaunchBrowser(const char* url)
{
	NSString* str = [NSString stringWithCString:url encoding:NSUTF8StringEncoding];
	NSURL* ns_url = [NSURL URLWithString:str];

	const bool result = [[NSWorkspace sharedWorkspace]
				   openURLs:@[ns_url]
				   withAppBundleIdentifier:nil
				   options:NSWorkspaceLaunchDefault
				   additionalEventParamDescriptor:nil
				   launchIdentifiers:nil];

	return result;
}
