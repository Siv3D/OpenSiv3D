﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <climits>
# include <Siv3D/DirectoryWatcher.hpp>
# include <sys/inotify.h>
# include <sys/select.h>
# include <boost/bimap.hpp>
# include <boost/container/allocator.hpp>

# include <Siv3D/PseudoThread/PseudoThread.hpp>

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

		constexpr static size_t EventSize = sizeof(inotify_event);
		constexpr static size_t EventBufferSize = ((EventSize + NAME_MAX + 1) * 4096);
		constexpr static size_t WatchMask = (IN_CREATE | IN_DELETE | IN_DELETE_SELF | IN_MODIFY | IN_MOVED_FROM | IN_MOVED_TO | IN_ONLYDIR);

		FilePath m_targetDirectory;

		Array<uint8_t> m_buffer;

		PseudoThread m_thread;

		std::atomic<bool> m_initCalled = false;

		bool m_isActive = false;

		bool m_disposed = false;

		int m_fd = -1;

		using bimap_t = boost::bimap<int, FilePath, boost::container::allocator<int>>;
		using bimap_value_t = bimap_t::value_type;
		bimap_t m_watched_directories;

		std::atomic<bool> m_abort = false;

		std::mutex m_changesMutex;
		
		Array<FileChange> m_fileChanges;	

		static bool watch(DirectoryWatcherDetail* const watcher);

		bool init();

		void update();

		void dispose();
	};
}
