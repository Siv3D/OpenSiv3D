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

# include "ChildProcessDetail.hpp"
# include <boost/process/io.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	ChildProcess::ChildProcessDetail::ChildProcessDetail()
	{

	}

	ChildProcess::ChildProcessDetail::ChildProcessDetail(const FilePath& path, const String& command, const Pipe pipe)
	{
		const std::wstring pathW = path.toWstr();
		const std::wstring commandW = command.toWstr();

		switch (pipe)
		{
		case Pipe::None:
			m_child = boost::process::child(pathW, commandW);
			break;
		case Pipe::StdIn:
			m_child = boost::process::child(pathW, commandW, boost::process::std_out > m_ips);
			break;
		case Pipe::StdOut:
			m_child = boost::process::child(pathW, commandW, boost::process::std_in < m_ops);
			break;
		case Pipe::StdInOut:
			m_child = boost::process::child(pathW, commandW, boost::process::std_out > m_ips, boost::process::std_in < m_ops);
			break;
		}
	}

	ChildProcess::ChildProcessDetail::~ChildProcessDetail()
	{
		if (m_child.joinable())
		{
			m_child.detach();
		}
	}

	bool ChildProcess::ChildProcessDetail::isValid() const
	{
		return m_child.valid();
	}

	bool ChildProcess::ChildProcessDetail::isRunning()
	{
		return m_child.running();
	}

	void ChildProcess::ChildProcessDetail::wait()
	{
		m_child.wait();
	}

	void ChildProcess::ChildProcessDetail::terminate()
	{
		m_child.terminate();
	}

	Optional<int32> ChildProcess::ChildProcessDetail::getExitCode()
	{
		if (!m_child.valid() || m_child.running())
		{
			return none;
		}
		else
		{
			return m_child.exit_code();
		}
	}

	std::istream& ChildProcess::ChildProcessDetail::istream()
	{
		return m_ips;
	}

	std::ostream& ChildProcess::ChildProcessDetail::ostream()
	{
		return m_ops;
	}
}
