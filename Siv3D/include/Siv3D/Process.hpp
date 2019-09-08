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
# include "Fwd.hpp"
# include "String.hpp"
# include "Optional.hpp"
# include <memory>

namespace s3d
{
	enum class Pipe
	{
		None,

		StdIn,

		StdOut,

		StdInOut,
	};

	class ChildProcess
	{
	private:

		class ChildProcessDetail;

		std::shared_ptr<ChildProcessDetail> pImpl;

	public:

		ChildProcess();

		ChildProcess(const FilePath& path, const String& command = U"", Pipe pipe = Pipe::None);

		~ChildProcess();

		[[nodiscard]] explicit operator bool() const;

		[[nodiscard]] bool isValid() const;

		[[nodiscard]] bool isRunning();

		void wait();

		void terminate();

		[[nodiscard]] Optional<int32> getExitCode();

		[[nodiscard]] std::istream& istream();

		[[nodiscard]] std::ostream& ostream();
	};

	namespace Process
	{
		ChildProcess Spawn(const FilePath& path, Pipe pipe);

		ChildProcess Spawn(const FilePath& path, const String& command = U"", Pipe pipe = Pipe::None);
	}
}
