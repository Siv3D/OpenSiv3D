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

# include <mutex>
# include <Siv3D/DirectoryWatcher.hpp>

namespace s3d
{
	class DirectoryWatcher::DirectoryWatcherDetail
	{
	private:

		static constexpr double LatencySec = 0.25;
		
		FilePath m_directory;
		
		bool m_running = false;
		
		bool m_abort = false;
		
		std::mutex m_changesMutex;
		
		Array<std::pair<FilePath, FileAction>> m_changes;
		
	public:

		explicit DirectoryWatcherDetail(const FilePath& directory);

		~DirectoryWatcherDetail();

		Array<std::pair<FilePath, FileAction>> retrieveChanges();

		const FilePath& directory() const;
	};
}
