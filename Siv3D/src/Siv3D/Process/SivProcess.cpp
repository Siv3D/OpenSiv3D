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

# include <Siv3D/Process.hpp>
# include "ChildProcessDetail.hpp"

namespace s3d
{
	ChildProcess::ChildProcess()
		: pImpl(std::make_shared<ChildProcessDetail>())
	{

	}

	ChildProcess::ChildProcess(const FilePath& path, const String& command, const Pipe pipe)
		: pImpl(std::make_shared<ChildProcessDetail>(path, command, pipe))
	{

	}

	ChildProcess::~ChildProcess()
	{

	}

	ChildProcess::operator bool() const
	{
		return isValid();
	}

	bool ChildProcess::isValid() const
	{
		return pImpl->isValid();
	}

	bool ChildProcess::isRunning()
	{
		return pImpl->isRunning();
	}

	void ChildProcess::wait()
	{
		pImpl->wait();
	}

	void ChildProcess::terminate()
	{
		pImpl->terminate();
	}

	Optional<int32> ChildProcess::getExitCode()
	{
		return pImpl->getExitCode();
	}

	std::istream& ChildProcess::istream()
	{
		return pImpl->istream();
	}

	std::ostream& ChildProcess::ostream()
	{
		return pImpl->ostream();
	}

	namespace Process
	{
		ChildProcess Spawn(const FilePath& path, Pipe pipe)
		{
			return ChildProcess(path, String(), pipe);
		}

		ChildProcess Spawn(const FilePath& path, const String& command, const Pipe pipe)
		{
			return ChildProcess(path, command, pipe);
		}
	}
}
