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

# include <Siv3D/ChildProcess.hpp>
# include <Siv3D/ChildProcess/ChildProcessDetail.hpp>

namespace s3d
{
	ChildProcess::ChildProcess()
		: pImpl{ std::make_shared<ChildProcessDetail>() } {}

	ChildProcess::ChildProcess(const FilePathView path, const Pipe pipe)
		: ChildProcess{ path, U"", pipe } {}

	ChildProcess::ChildProcess(const FilePathView path, const StringView command, const Pipe pipe)
		: pImpl{ std::make_shared<ChildProcessDetail>(path, command, pipe) } {}

	ChildProcess::~ChildProcess()
	{
		// do nothing
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
}
