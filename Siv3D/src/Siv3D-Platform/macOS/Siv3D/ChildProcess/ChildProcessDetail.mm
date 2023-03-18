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

# include "ChildProcessDetail.hpp"
# include "NSTaskWrapper.hpp"

namespace s3d
{
	ChildProcess::ChildProcessDetail::ChildProcessDetail()
		: m_detail(std::make_unique<NSTaskWrapper>()) {}

	ChildProcess::ChildProcessDetail::ChildProcessDetail(const FilePathView path, const StringView command, const Pipe pipe)
		: m_detail{ std::make_unique<NSTaskWrapper>(path.toUTF8().c_str(), command.toUTF8().c_str(), pipe) } {}

	ChildProcess::ChildProcessDetail::~ChildProcessDetail()
	{

	}

	bool ChildProcess::ChildProcessDetail::isValid() const
	{
		return m_detail->isValid();
	}

	bool ChildProcess::ChildProcessDetail::isRunning()
	{
		return m_detail->isRunning();
	}

	void ChildProcess::ChildProcessDetail::wait()
	{
		m_detail->wait();
	}

	void ChildProcess::ChildProcessDetail::terminate()
	{
		m_detail->terminate();
	}

	Optional<int32> ChildProcess::ChildProcessDetail::getExitCode()
	{
		return m_detail->getExitCode();
	}

	std::istream& ChildProcess::ChildProcessDetail::istream()
	{
		return m_detail->istream();
	}

	std::ostream& ChildProcess::ChildProcessDetail::ostream()
	{
		return m_detail->ostream();
	}
}
