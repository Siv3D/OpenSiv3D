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

# pragma once
# include <sstream>
# include <Siv3D/ChildProcess.hpp>
# include <AppKit/AppKit.h>

namespace s3d
{
	class OPStream : public std::ostream, std::streambuf
	{
	public:
		
		OPStream();
		
		void setWriteHandle(NSFileHandle* writeHandle);
		
		int overflow(int c);

	private:
		
		std::string m_buffer;
		
		NSFileHandle* m_writeHandle = nullptr;
	};
	
	class NSTaskWrapper
	{
	public:
		
		NSTaskWrapper();
		
		NSTaskWrapper(const char* path, const char* command, Pipe pipe);
		
		~NSTaskWrapper();
		
		bool isValid() const;
		
		bool isRunning();
		
		void wait();
		
		void terminate();
		
		Optional<int32> getExitCode();
		
		std::istream& istream();
		
		std::ostream& ostream();
		
	private:
		
		NSTask* m_task = nullptr;
		
		NSPipe* m_ips = nullptr;
		NSFileHandle* m_writeHandle = nullptr;
		
		NSPipe* m_ops = nullptr;
		NSFileHandle* m_readHandle = nullptr;
		
		bool m_valid = false;
		
		std::stringstream m_is;
		
		OPStream m_os;
	};
}
