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

# include "DirectoryWatcherDetail_Linux.hpp"

namespace s3d
{
	DirectoryWatcher::DirectoryWatcherDetail::DirectoryWatcherDetail(const FilePath& directory)
	{

	}

	DirectoryWatcher::DirectoryWatcherDetail::~DirectoryWatcherDetail()
	{

	}

	Array<std::pair<FilePath, FileAction>> DirectoryWatcher::DirectoryWatcherDetail::retrieveChanges()
	{
		return{};
	}

	const FilePath& DirectoryWatcher::DirectoryWatcherDetail::directory() const
	{
		return FilePath();
	}
}

# endif
