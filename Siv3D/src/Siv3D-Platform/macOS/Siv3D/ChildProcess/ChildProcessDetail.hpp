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
# include <memory>
# include <Siv3D/ChildProcess.hpp>

namespace s3d
{
	class NSTaskWrapper;

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

		std::unique_ptr<NSTaskWrapper> m_detail;
	};
}
