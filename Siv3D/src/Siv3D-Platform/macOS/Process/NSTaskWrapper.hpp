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

# pragma once
# include <sstream>
# include <Siv3D/Process.hpp>
# include <AppKit/AppKit.h>

namespace s3d
{
	class NSTaskWrapper
	{
	private:
		
		NSTask* m_task = nullptr;
		
		NSPipe* m_ips = nullptr;
		
		NSPipe* m_ops = nullptr;
		
		bool m_valid = false;
		
		std::ostringstream m_os;
		
		std::istringstream m_is;
		
	public:
		
		NSTaskWrapper() = default;
		
		NSTaskWrapper(const char* path, const char* command, Pipe pipe);
		
		bool isValid() const;
		
		bool isRunning();
		
		void wait();
		
		void terminate();
		
		Optional<int32> getExitCode();
		
		std::istream& istream();
		
		std::ostream& ostream();
	};
}
