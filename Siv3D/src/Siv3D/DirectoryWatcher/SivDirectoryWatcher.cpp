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

# include <Siv3D/DirectoryWatcher.hpp>

# if defined(SIV3D_TARGET_WINDOWS)

	# include "DirectoryWatcherDetail_Windows.hpp"

# elif defined(SIV3D_TARGET_MACOS)

	# include "DirectoryWatcherDetail_macOS.hpp"

# else // defined(SIV3D_TARGET_LINUX)

	# include "DirectoryWatcherDetail_Linux.hpp"

# endif

namespace s3d
{
	DirectoryWatcher::DirectoryWatcher()
	{

	}

	DirectoryWatcher::DirectoryWatcher(const FilePath& directory)
		: m_detail(std::make_shared<DirectoryWatcherDetail>(directory))
	{

	}

	DirectoryWatcher::~DirectoryWatcher()
	{

	}

	Array<std::pair<FilePath, FileAction>> DirectoryWatcher::retrieveChanges() const
	{
		if (!m_detail)
		{
			return{};
		}

		return m_detail->retrieveChanges();
	}

	FilePath DirectoryWatcher::directory() const
	{
		if (!m_detail)
		{
			return{};
		}

		return m_detail->directory();
	}
}
