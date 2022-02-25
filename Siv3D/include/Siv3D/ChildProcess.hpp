//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
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
		ChildProcess(FilePathView path, StringView command = U"", Pipe pipe = Pipe::None_);

		~ChildProcess();

		[[nodiscard]]
		explicit operator bool() const;

		[[nodiscard]]
		bool isValid() const;

		/// @brief 子プロセスが実行中であるかを返します。
		/// @return 実行中である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isRunning();

		/// @brief 子プロセスが終了するまで待機します。
		void wait();

		/// @brief 子プロセスを強制終了します。
		void terminate();

		/// @brief 子プロセスの終了コードを取得します。
		/// @return 子プロセスの終了コード。取得に失敗した場合 none
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
