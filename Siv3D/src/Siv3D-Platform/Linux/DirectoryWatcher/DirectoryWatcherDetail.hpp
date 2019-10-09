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

# include <string>
# include <mutex>
# include <thread>
# include <memory>

# include <sys/inotify.h>
# include <limits.h>
# include <boost/bimap.hpp>

# include <Siv3D/DirectoryWatcher.hpp>
# include <Siv3D/String.hpp>

namespace s3d
{
	class DirectoryWatcher::DirectoryWatcherDetail
	{
	private:

		FilePath m_directory;
		
		bool m_disposed = false;
		
		bool m_abort = false;
		
		std::mutex m_changesMutex;
		
		Array<std::pair<FilePath, FileAction>> m_changes;
		
		std::thread m_thread;


		int m_fd;

		using bimap_t = boost::bimap<int, FilePath>;
		using bimap_value_t = bimap_t::value_type;
		bimap_t m_watched_directories;

		std::unique_ptr<uint8_t[]> m_buffer;

		constexpr static int EVENT_SIZE = sizeof(struct inotify_event);
		constexpr static int EVENT_BUFFER_LENGTH = 4096 * (EVENT_SIZE + NAME_MAX + 1);
		constexpr static int WATCH_MASK = (IN_CREATE | IN_DELETE | IN_DELETE_SELF | IN_MODIFY | IN_MOVED_FROM | IN_MOVED_TO | IN_ONLYDIR);


		static void watch(DirectoryWatcherDetail* watcher);

		bool init();

		void update();

		void dispose();

	public:

		explicit DirectoryWatcherDetail(const FilePath& directory);

		~DirectoryWatcherDetail();

		Array<std::pair<FilePath, FileAction>> retrieveChanges();

		const FilePath& directory() const;
	};
}
