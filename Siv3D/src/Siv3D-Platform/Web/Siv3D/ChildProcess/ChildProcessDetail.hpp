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
# include <Siv3D/ChildProcess.hpp>

# ifdef __clang__
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wdeprecated-copy"
#	pragma clang diagnostic ignored "-Wunused-parameter"
# endif
# include <boost/process/child.hpp>
# include <boost/process/pipe.hpp>
# ifdef __clang__
#	pragma clang diagnostic pop
# endif

namespace s3d
{
	class ChildProcess::ChildProcessDetail
	{
	public:

		ChildProcessDetail();

		ChildProcessDetail(const FilePathView path, const StringView command, Pipe pipe);

		~ChildProcessDetail();

		bool isValid() const;

		bool isRunning();

		void wait();

		void terminate();

		Optional<int32> getExitCode();

		std::istream& istream();

		std::ostream& ostream();

	private:

		boost::process::opstream m_ops;

		boost::process::ipstream m_ips;

		boost::process::child m_child;
	};
}
