//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Pipe.hpp"
# include "StringView.hpp"
# include "Optional.hpp"

namespace s3d
{
	/// @brief 子プロセスの作成と管理
	class ChildProcess
	{
	public:

		SIV3D_NODISCARD_CXX20
		ChildProcess();

		SIV3D_NODISCARD_CXX20
		ChildProcess(FilePathView path, Pipe pipe);

		SIV3D_NODISCARD_CXX20
		ChildProcess(FilePathView path, StringView command = U"", Pipe pipe = Pipe::_None);

		~ChildProcess();

		[[nodiscard]]
		explicit operator bool() const;

		[[nodiscard]]
		bool isValid() const;

		[[nodiscard]]
		bool isRunning();

		void wait();

		void terminate();

		[[nodiscard]]
		Optional<int32> getExitCode();

		[[nodiscard]]
		std::istream& istream();

		[[nodiscard]]
		std::ostream& ostream();

	private:

		class ChildProcessDetail;

		std::shared_ptr<ChildProcessDetail> pImpl;
	};
}
