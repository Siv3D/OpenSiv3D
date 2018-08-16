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
# include <memory>
# include "Fwd.hpp"
# include "Array.hpp"

namespace s3d
{
	enum class FileAction
	{
		Unknown,

		Added,

		Removed,

		Modified,
	};

	class DirectoryWatcher
	{
	private:

		class DirectoryWatcherDetail;

		std::shared_ptr<DirectoryWatcherDetail> m_detail;

	public:

		DirectoryWatcher();

		explicit DirectoryWatcher(const FilePath& directory);

		~DirectoryWatcher();

		Array<std::pair<FilePath, FileAction>> retrieveChanges() const;

		FilePath directory() const;
	};
}
