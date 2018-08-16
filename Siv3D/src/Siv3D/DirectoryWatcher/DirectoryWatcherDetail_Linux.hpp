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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include <Siv3D/DirectoryWatcher.hpp>

namespace s3d
{
	class DirectoryWatcher::DirectoryWatcherDetail
	{
	private:

	public:

		explicit DirectoryWatcherDetail(const FilePath& directory);

		~DirectoryWatcherDetail();

		Array<std::pair<FilePath, FileAction>> retrieveChanges();
	};
}

# endif
