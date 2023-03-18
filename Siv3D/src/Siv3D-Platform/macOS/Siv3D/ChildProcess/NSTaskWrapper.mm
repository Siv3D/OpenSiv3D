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

# include <Foundation/Foundation.h>
# include "NSTaskWrapper.hpp"

namespace s3d
{
	OPStream::OPStream()
		: std::ostream(this)
	{
		
	}
	
	void OPStream::setWriteHandle(NSFileHandle* writeHandle)
	{
		m_writeHandle = writeHandle;
	}
	
	int OPStream::overflow(int c)
	{
		if (!m_writeHandle)
		{
			m_buffer.clear();
			return 0;
		}
		
		const char ch = static_cast<char>(c);
		m_buffer.push_back(ch);

		if (ch == '\n')
		{
			NSData* data = [NSData dataWithBytesNoCopy:(void*)m_buffer.c_str() length:m_buffer.size()];
			
			[m_writeHandle writeData:data];

			m_buffer.clear();
		}

		return 0;
	}
	
	NSTaskWrapper::NSTaskWrapper()
	{
		
	}
	
	NSTaskWrapper::NSTaskWrapper(const char* path, const char* command, const Pipe pipe)
	{
		NSString* pathNS = [NSString stringWithUTF8String:path];
		NSString* commandNS = [NSString stringWithUTF8String:command];
		
		m_task = [[NSTask alloc] init];
		m_task.launchPath = pathNS;
		
		NSArray *arguments = [NSArray arrayWithObjects:commandNS, nil];
		m_task.arguments = arguments;

		if (pipe == Pipe::StdOut || pipe == Pipe::StdInOut)
		{
			m_ips = [NSPipe pipe];
			m_task.standardInput = m_ips;
			m_writeHandle = m_ips.fileHandleForWriting;
			m_os.setWriteHandle(m_writeHandle);
		}
		
		if (pipe == Pipe::StdIn || pipe == Pipe::StdInOut)
		{
			m_ops = [NSPipe pipe];
			m_task.standardOutput = m_ops;
			m_readHandle = m_ops.fileHandleForReading;
		}

		NSError* error = nil;
		m_valid = [m_task launchAndReturnError:&error];
		
	}
	
	NSTaskWrapper::~NSTaskWrapper()
	{
		if (m_writeHandle)
		{
			[m_writeHandle closeFile];
		}
		
		if (m_readHandle)
		{
			[m_readHandle closeFile];
		}
		
		if (m_task)
		{
			[m_task release];
		}
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
		if (!isValid() || !m_readHandle)
		{
			return m_is;
		}
		
		NSData* data = [m_readHandle availableData];
		NSString* output = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		std::string s = [output UTF8String];
		[output release];
		
		m_is << s;

		return m_is;
	}
	
	std::ostream& NSTaskWrapper::ostream()
	{
		return m_os;
	}
}
