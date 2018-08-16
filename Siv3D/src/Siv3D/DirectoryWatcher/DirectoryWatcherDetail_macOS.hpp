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
# if defined(SIV3D_TARGET_MACOS)

# include <CoreServices/CoreServices.h>
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
		
		FSEventStreamRef m_eventStream;
		
		std::mutex m_changesMutex;
		
		Array<std::pair<FilePath, FileAction>> m_changes;

		static void OnChange(ConstFSEventStreamRef, void* pWatch, size_t eventCount, void* paths, const FSEventStreamEventFlags flags[], const FSEventStreamEventId[]);
		
		void processChanges(const size_t eventCount, void* paths, const FSEventStreamEventFlags flags[]);
		
	public:

		explicit DirectoryWatcherDetail(const FilePath& directory);

		~DirectoryWatcherDetail();

		Array<std::pair<FilePath, FileAction>> retrieveChanges();

		const FilePath& directory() const;
	};
}

# endif
