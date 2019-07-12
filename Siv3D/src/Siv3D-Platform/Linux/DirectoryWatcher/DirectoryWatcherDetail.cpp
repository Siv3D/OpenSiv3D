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

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include "DirectoryWatcherDetail.hpp"

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
		Array<std::pair<FilePath, FileAction>> results;
		return results;
	}
	
	const FilePath& DirectoryWatcher::DirectoryWatcherDetail::directory() const
	{
		return m_directory;
	}
}
