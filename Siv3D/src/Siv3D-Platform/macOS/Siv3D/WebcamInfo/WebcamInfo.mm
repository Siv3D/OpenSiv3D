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

# include <Siv3D/WebcamInfo.hpp>
# include <Siv3D/Unicode.hpp>
# import <AVFoundation/AVFoundation.h>

namespace s3d
{
	struct macOS_WebcamInfo
	{
		unsigned cameraIndex;
		
		std::string name;
		
		std::string uniqueName;
	};

	std::vector<macOS_WebcamInfo> macOS_EnumerateWebcam()
	{
		@autoreleasepool
		{
			NSArray* devices = [[AVCaptureDevice devicesWithMediaType: AVMediaTypeVideo]
								arrayByAddingObjectsFromArray:[AVCaptureDevice devicesWithMediaType:AVMediaTypeMuxed]];
			
			std::vector<macOS_WebcamInfo> results;
			
			for (unsigned index = 0; index < devices.count; ++index)
			{
				AVCaptureDevice* captureDevice = devices[index];
				
				if (!captureDevice)
				{
					continue;
				}
				
				macOS_WebcamInfo info;
				info.cameraIndex = index;
				info.name = [[captureDevice localizedName] UTF8String];
				info.uniqueName = [[captureDevice uniqueID] UTF8String];
				
				results.push_back(info);
			}
			
			return results;
		}
	}

	namespace System
	{
		Array<WebcamInfo> EnumerateWebcams()
		{
			Array<WebcamInfo> results;
			
			for (const auto& info : macOS_EnumerateWebcam())
			{
				WebcamInfo result;
				result.cameraIndex = info.cameraIndex;
				result.name  = Unicode::FromUTF8(info.name);
				result.uniqueName = Unicode::FromUTF8(info.uniqueName);
				results << result;
			}
			
			return results;
		}
	}
}
