//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/DirectoryWatcher.hpp>
# include <CoreServices/CoreServices.h>

namespace s3d
{
	class DirectoryWatcher::DirectoryWatcherDetail
	{
	public:

		explicit DirectoryWatcherDetail(FilePathView directory);

		~DirectoryWatcherDetail();

		bool isActive() const;

		void retrieveChanges(Array<FileChange>& fileChanges);

		void clearChanges();

		const FilePath& directory() const noexcept;

	private:

		static constexpr double LatencySec = 0.25;
		
		bool m_isActive = false;
		
		FilePath m_targetDirectory;
		
		FSEventStreamRef m_eventStream;
		
		std::atomic<bool> m_abort = false;
		
		std::mutex m_changesMutex;
		
		Array<FileChange> m_fileChanges;
		
		static void OnChange(ConstFSEventStreamRef, void* pWatch, size_t eventCount, void* paths, const FSEventStreamEventFlags flags[], const FSEventStreamEventId[]);
		
		void processChanges(const size_t eventCount, void* paths, const FSEventStreamEventFlags flags[]);
	};
}
