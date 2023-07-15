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

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include "ChildProcessDetail.hpp"

namespace s3d
{
	ChildProcess::ChildProcessDetail::ChildProcessDetail() {}

	ChildProcess::ChildProcessDetail::ChildProcessDetail(const FilePathView path, const StringView command, const Pipe pipe)
	{
		LOG_FAIL(U"ChildProcess is not supported");
	}

	ChildProcess::ChildProcessDetail::~ChildProcessDetail() {}

	bool ChildProcess::ChildProcessDetail::isValid() const
	{
		return false;
	}

	bool ChildProcess::ChildProcessDetail::isRunning()
	{
		return false;
	}

	void ChildProcess::ChildProcessDetail::wait()
	{
	}

	void ChildProcess::ChildProcessDetail::terminate()
	{
	}

	Optional<int32> ChildProcess::ChildProcessDetail::getExitCode()
	{
		return none;
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
