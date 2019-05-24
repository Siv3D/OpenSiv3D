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

# include <Siv3D/DirectoryWatcher.hpp>
# include <DirectoryWatcher/DirectoryWatcherDetail.hpp>

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

	bool DirectoryWatcher::isOpened() const
	{
		return static_cast<bool>(m_detail);
	}

	DirectoryWatcher::operator bool() const
	{
		return isOpened();
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
