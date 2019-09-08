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
# include <Siv3D/Process.hpp>
# include <boost/process/child.hpp>
# include <boost/process/pipe.hpp>

namespace s3d
{
	class ChildProcess::ChildProcessDetail
	{
	private:

		boost::process::opstream m_ops;

		boost::process::ipstream m_ips;

		boost::process::child m_child;


	public:

		ChildProcessDetail();

		ChildProcessDetail(const FilePath& path, const String& command, Pipe pipe);

		~ChildProcessDetail();

		bool isValid() const;

		bool isRunning();

		void wait();

		void terminate();

		Optional<int32> getExitCode();

		std::istream& istream();

		std::ostream& ostream();
	};
}
