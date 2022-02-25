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
# include "FileAction.hpp"
# include "Array.hpp"
# include "String.hpp"

namespace s3d
{
	/// @brief ファイルの操作とファイルパス
	struct FileChange
	{
		/// @brief ファイルパス
		FilePath path;

		/// @brief ファイルの操作
		FileAction action;
	};

	/// @brief ディレクトリの監視
	class DirectoryWatcher
	{
	public:

		SIV3D_NODISCARD_CXX20
		DirectoryWatcher();

		SIV3D_NODISCARD_CXX20
		explicit DirectoryWatcher(const FilePath& directory);

		~DirectoryWatcher();

		[[nodiscard]]
		bool isOpen() const;

		[[nodiscard]]
		explicit operator bool() const;

		Array<FileChange> retrieveChanges() const;

		bool retrieveChanges(Array<FileChange>& fileChanges) const;

		void clearChanges();

		[[nodiscard]]
		FilePath directory() const;

	private:

		class DirectoryWatcherDetail;

		std::shared_ptr<DirectoryWatcherDetail> pImpl;
	};
}
