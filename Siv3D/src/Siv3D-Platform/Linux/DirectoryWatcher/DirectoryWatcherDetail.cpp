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

# include <boost/filesystem.hpp>

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include "DirectoryWatcherDetail.hpp"

namespace fs = boost::filesystem;

namespace s3d
{
	DirectoryWatcher::DirectoryWatcherDetail::DirectoryWatcherDetail(const FilePath& directory)
	{
		if (!FileSystem::IsDirectory(directory))
		{
			LOG_FAIL(U"❌ DirectoryWatcher: `{}` is not a directory"_fmt(directory));
			return;
		}

		m_directory = FileSystem::FullPath(directory);

		m_buffer = std::make_unique<uint8_t[]>(EVENT_BUFFER_LENGTH);
		if (!m_buffer)
		{
			LOG_FAIL(U"❌ DirectoryWatcher: std::make_unique() failed. `{}`"_fmt(directory));
			return;
		}

		m_thread = std::thread(DirectoryWatcherDetail::watch, this);
	}
	
	DirectoryWatcher::DirectoryWatcherDetail::~DirectoryWatcherDetail()
	{
		m_abort = true;

		if(m_thread.joinable())
		{
			m_thread.join();
		}

		dispose();

		LOG_DEBUG(U"ℹ️ DirectoryWatcher: End monitoring `{}`"_fmt(m_directory));
	}
	
	Array<std::pair<FilePath, FileAction>> DirectoryWatcher::DirectoryWatcherDetail::retrieveChanges()
	{
		std::lock_guard lock(m_changesMutex);

		Array<std::pair<FilePath, FileAction>> results;

		results.swap(m_changes);

		return results;
	}
	
	const FilePath& DirectoryWatcher::DirectoryWatcherDetail::directory() const
	{
		return m_directory;
	}

	void DirectoryWatcher::DirectoryWatcherDetail::watch(DirectoryWatcherDetail* watcher)
	{
		if (!watcher->init())
		{
			return;
		}

		while (!watcher->m_abort)
		{
			watcher->update();
		}
	}

	bool DirectoryWatcher::DirectoryWatcherDetail::init()
	{
		m_fd = inotify_init();
		if (m_fd < 0)
		{
			LOG_FAIL(U"❌ DirectoryWatcher: inotify_init() failed. `{}`"_fmt(m_directory));

			return false;
		}

		Array<FilePath> watched_directory_paths;
		watched_directory_paths.push_back(m_directory);

		// サブディレクトリも監視対象に追加する
		boost::system::error_code error_code, no_error;
		fs::recursive_directory_iterator end;
		for (fs::recursive_directory_iterator itr(Unicode::Narrow(m_directory)); itr != end; itr.increment(error_code))
		{
			if (error_code != no_error)
			{
				dispose();
				LOG_FAIL(U"❌ DirectoryWatcher: boost::filesystem::recursive_directory_iterator::increment() failed. `{}`"_fmt(m_directory));

				return false;
			}
			else
			{
				if (fs::is_directory(itr->path()))
				{
					watched_directory_paths.push_back(FileSystem::FullPath(Unicode::Widen(itr->path().c_str())));
				}
			}
		}

		// 各ディレクトリに対する watch discriptor を作成
		for (auto itr = watched_directory_paths.cbegin(); itr != watched_directory_paths.cend(); ++itr)
		{
			int wd = inotify_add_watch(m_fd, Unicode::Narrow(*itr).c_str(), WATCH_MASK);

			if (wd < 0)
			{
				dispose();
				LOG_FAIL(U"❌ DirectoryWatcher: inotify_add_watch() failed. `{}`"_fmt(*itr));

				return false;
			}

			m_watched_directories.insert(bimap_value_t(wd, *itr));
		}

		LOG_DEBUG(U"ℹ️ DirectoryWatcher: Started monitoring `{}`"_fmt(m_directory));

		return true;
	}

	void DirectoryWatcher::DirectoryWatcherDetail::update()
	{
		fd_set watch_set;
		FD_ZERO(&watch_set);
		FD_SET(m_fd, &watch_set);

		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 10000; // 10ms

		int ret = select(m_fd + 1, &watch_set, NULL, NULL, &timeout);
		if (ret <= 0)
			return;

		if (!FD_ISSET(m_fd, &watch_set))
			return;

		int length = read(m_fd, m_buffer.get(), EVENT_BUFFER_LENGTH);
		if (length < 0)
		{
			LOG_FAIL(U"❌ DirectoryWatcher: read() failed. `{}`"_fmt(m_directory));
			return;
		}

		struct inotify_event* event;
		for (int i = 0; i < length; i += (EVENT_SIZE + event->len))
		{
			event = (struct inotify_event*)&m_buffer[i];

			FilePath current_path, event_path;
			FileAction action;

			if (event->wd == -1 || event->mask & IN_Q_OVERFLOW)
			{
				LOG_FAIL(U"❌ DirectoryWatcher: inotify event buffer overflowed. `{}`"_fmt(m_directory));
			}

			if (event->mask & IN_MODIFY)
			{
				event_path = m_watched_directories.left.at(event->wd) + Unicode::Widen(event->name);
				action = FileAction::Modified;

				LOG_DEBUG(U"ℹ️ DirectoryWatcher: file modified. `{}`"_fmt(event_path));
			}
			else if (event->mask & IN_CREATE || event->mask & IN_MOVED_TO)
			{
				current_path = m_watched_directories.left.at(event->wd);
				event_path = FileSystem::FullPath(current_path + Unicode::Widen(event->name));

				action = FileAction::Added;

				if (event->mask & IN_ISDIR)
				{
					int wd = inotify_add_watch(m_fd, Unicode::Narrow(event_path).c_str(), WATCH_MASK);
					if (wd < 0)
					{
						LOG_FAIL(U"❌ DirectoryWatcher: inotify_add_watch() failed. `{}`"_fmt(event_path));
					}
					else
					{
						m_watched_directories.insert(bimap_value_t(wd, event_path));

						LOG_DEBUG(U"ℹ️ DirectoryWatcher: new directory. `{}`"_fmt(event_path));
					}
				}
				else
				{
					action = FileAction::Added;

					LOG_DEBUG(U"ℹ️ DirectoryWatcher: new file. `{}`"_fmt(event_path));
				}
			}
			else if (event->mask & IN_DELETE || event->mask & IN_MOVED_FROM)
			{
				action = FileAction::Removed;

				if (event->mask & IN_ISDIR)
				{
					// この時点でevent_pathのディレクトリは存在しないのでFilesystem::FullPath()はうまく動かない
					event_path = m_watched_directories.left.at(event->wd) + Unicode::Widen(event->name) + U'/';

					LOG_DEBUG(U"ℹ️ DirectoryWatcher: directory deleted. `{}`"_fmt(event_path));
				}
				else
				{
					event_path = m_watched_directories.left.at(event->wd) + Unicode::Widen(event->name);

					LOG_DEBUG(U"ℹ️ DirectoryWatcher: file deleted. `{}`"_fmt(event_path));
				}
			}
			else if (event->mask & IN_DELETE_SELF)
			{
				inotify_rm_watch(m_fd, event->wd);
				continue; // m_changesに追加しない
			}
			else if (event->mask & IN_IGNORED)
			{
				event_path = m_watched_directories.left.at(event->wd);
				m_watched_directories.left.erase(event->wd);
				if (event_path == m_directory)
				{
					action = FileAction::Removed;

					LOG_DEBUG(U"ℹ️ DirectoryWatcher: Root directory deleted. `{}`"_fmt(m_directory));
				}
				else
					continue; // m_changesに追加しない
			}

			{
				std::lock_guard lock(m_changesMutex);
				m_changes.emplace_back(std::move(event_path), action);
			}
		}
	}

	void DirectoryWatcher::DirectoryWatcherDetail::dispose()
	{
		if (!m_disposed)
		{
			m_disposed = true;

			for (auto itr = m_watched_directories.left.begin(); itr != m_watched_directories.left.end(); ++itr)
			{
				inotify_rm_watch(m_fd, itr->first);
			}
		}
		close(m_fd);
	}
}
