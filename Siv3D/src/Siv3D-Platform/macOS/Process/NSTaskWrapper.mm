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

# include <Foundation/Foundation.h>
# include "NSTaskWrapper.hpp"

namespace s3d
{
	NSTaskWrapper::NSTaskWrapper(const char* path, const char* command, const Pipe pipe)
	{
		NSString* pathNS = [NSString stringWithUTF8String:path];
		NSString* commandNS = [NSString stringWithUTF8String:command];
		
		m_task = [[NSTask alloc] init];
		m_task.launchPath = pathNS;
		
		NSArray *arguments = [NSArray arrayWithObjects:commandNS, nil];
		m_task.arguments = arguments;

		if (pipe == Pipe::StdIn || pipe == Pipe::StdInOut)
		{
			m_ips = [NSPipe pipe];
			m_task.standardInput = m_ips;
		}
		
		if (pipe == Pipe::StdOut || pipe == Pipe::StdInOut)
		{
			m_ops = [NSPipe pipe];
			m_task.standardOutput = m_ops;
		}

		NSError* error = nil;
		m_valid = [m_task launchAndReturnError:&error];
	}
	
	bool NSTaskWrapper::isValid() const
	{
		return m_valid;
	}
	
	bool NSTaskWrapper::isRunning()
	{
		if (!isValid())
		{
			return false;
		}
		
		return [m_task isRunning] == YES;
	}
	
	void NSTaskWrapper::wait()
	{
		if (!isValid())
		{
			return;
		}
		
		[m_task waitUntilExit];
	}
	
	void NSTaskWrapper::terminate()
	{
		if (!isValid())
		{
			return;
		}
		
		[m_task terminate];
	}
	
	Optional<int32> NSTaskWrapper::getExitCode()
	{
		if (!isValid() || [m_task isRunning])
		{
			return none;
		}
		
		return [m_task terminationStatus];
	}
	
	std::istream& NSTaskWrapper::istream()
	{
		return m_is;
	}
	
	std::ostream& NSTaskWrapper::ostream()
	{
		return m_os;
	}
}
