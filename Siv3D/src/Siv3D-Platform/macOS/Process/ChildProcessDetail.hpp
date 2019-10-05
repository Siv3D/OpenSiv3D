//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include <Siv3D/Process.hpp>

namespace s3d
{
	class NSTaskWrapper;

	class ChildProcess::ChildProcessDetail
	{
	private:

		std::unique_ptr<NSTaskWrapper> m_detail;

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
