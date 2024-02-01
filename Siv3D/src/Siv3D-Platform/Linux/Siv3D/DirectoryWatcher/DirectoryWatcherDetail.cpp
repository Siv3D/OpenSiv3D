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

# include <filesystem>
# include "DirectoryWatcherDetail.hpp"
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	DirectoryWatcher::DirectoryWatcherDetail::DirectoryWatcherDetail(const FilePathView directory)
	{
		if (directory.isEmpty()
			|| (not FileSystem::IsDirectory(directory)))
		{
			LOG_FAIL(U"❌ DirectoryWatcher: `{}` is not a directory"_fmt(directory));
			return;
		}
		
		m_targetDirectory = FileSystem::FullPath(directory);

		m_buffer.resize(EventBufferSize);

		m_thread = std::thread(DirectoryWatcherDetail::watch, this);

		while (not m_initCalled)
		{
			::usleep(1000);
		}

		m_isActive = (true);
	}

	DirectoryWatcher::DirectoryWatcherDetail::~DirectoryWatcherDetail()
	{
		m_abort = true;

		if (m_thread.joinable())
		{
			m_thread.join();
		}

		dispose();

		LOG_INFO(U"ℹ️ DirectoryWatcher: Monitoring `{}` is deactivated"_fmt(m_targetDirectory));
	}

	bool DirectoryWatcher::DirectoryWatcherDetail::isActive() const
	{
		return m_isActive;
	}

	void DirectoryWatcher::DirectoryWatcherDetail::retrieveChanges(Array<FileChange>& fileChanges)
	{
		std::lock_guard lock{ m_changesMutex };

		fileChanges.assign(m_fileChanges.begin(), m_fileChanges.end());

		m_fileChanges.clear();
	}

	void DirectoryWatcher::DirectoryWatcherDetail::clearChanges()
	{
		std::lock_guard lock{ m_changesMutex };

		m_fileChanges.clear();
	}

	const FilePath& DirectoryWatcher::DirectoryWatcherDetail::directory() const noexcept
	{
		return m_targetDirectory;
	}

	void DirectoryWatcher::DirectoryWatcherDetail::watch(DirectoryWatcherDetail* watcher)
	{
		if (not watcher->init())
		{
			watcher->m_initCalled = true;
			return;
		}

		watcher->m_initCalled = true;

		while (not watcher->m_abort)
		{
			watcher->update();
		}
	}

	bool DirectoryWatcher::DirectoryWatcherDetail::init()
	{
		m_fd = inotify_init();
		if (m_fd < 0)
		{
			LOG_FAIL(U"❌ DirectoryWatcher: inotify_init() failed. `{}`"_fmt(m_targetDirectory));

			return false;
		}

		Array<FilePath> watched_directory_paths;
		watched_directory_paths.push_back(m_targetDirectory);

		// サブディレクトリも監視対象に追加する
		namespace fs = std::filesystem;
		std::error_code error_code;
        const std::error_code no_error;
		fs::recursive_directory_iterator end;
		for (fs::recursive_directory_iterator itr(Unicode::Narrow(m_targetDirectory)); itr != end; itr.increment(error_code))
		{
			if (error_code != no_error)
			{
				dispose();
				LOG_FAIL(U"❌ DirectoryWatcher: filesystem::recursive_directory_iterator::increment() failed. `{}`"_fmt(m_targetDirectory));
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
			int wd = inotify_add_watch(m_fd, Unicode::Narrow(*itr).c_str(), WatchMask);

			if (wd < 0)
			{
				dispose();
				LOG_FAIL(U"❌ DirectoryWatcher: inotify_add_watch() failed. `{}`"_fmt(*itr));
				return false;
			}

			m_watched_directories.insert(bimap_value_t(wd, *itr));
		}

		LOG_INFO(U"ℹ️ DirectoryWatcher: Monitoring `{}` is activated"_fmt(m_targetDirectory));

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

		int length = read(m_fd, m_buffer.data(), EventBufferSize);
		if (length < 0)
		{
			LOG_FAIL(U"❌ DirectoryWatcher: read() failed. `{}`"_fmt(m_targetDirectory));
			return;
		}

		struct inotify_event* event;
		for (int i = 0; i < length; i += (EventSize + event->len))
		{
			event = (struct inotify_event*)&m_buffer[i];

			FilePath current_path, event_path;
			FileAction action = FileAction::Unknown;

			if (event->wd == -1 || event->mask & IN_Q_OVERFLOW)
			{
				LOG_FAIL(U"❌ DirectoryWatcher: inotify event buffer overflowed. `{}`"_fmt(m_targetDirectory));
			}

			if (event->mask & IN_MODIFY)
			{
				event_path = m_watched_directories.left.at(event->wd) + Unicode::Widen(event->name);
				action = FileAction::Modified;

				//LOG_INFO(U"ℹ️ DirectoryWatcher: file modified. `{}`"_fmt(event_path));
			}
			else if (event->mask & IN_CREATE || event->mask & IN_MOVED_TO)
			{
				current_path = m_watched_directories.left.at(event->wd);
				event_path = FileSystem::FullPath(current_path + Unicode::Widen(event->name));

				action = FileAction::Added;

				if (event->mask & IN_ISDIR)
				{
					int wd = inotify_add_watch(m_fd, Unicode::Narrow(event_path).c_str(), WatchMask);
					if (wd < 0)
					{
						LOG_FAIL(U"❌ DirectoryWatcher: inotify_add_watch() failed. `{}`"_fmt(event_path));
					}
					else
					{
						m_watched_directories.insert(bimap_value_t(wd, event_path));

						//LOG_INFO(U"ℹ️ DirectoryWatcher: new directory. `{}`"_fmt(event_path));
					}
				}
				else
				{
					action = FileAction::Added;

					//LOG_INFO(U"ℹ️ DirectoryWatcher: new file. `{}`"_fmt(event_path));
				}
			}
			else if (event->mask & IN_DELETE || event->mask & IN_MOVED_FROM)
			{
				action = FileAction::Removed;

				if (event->mask & IN_ISDIR)
				{
					// この時点でevent_pathのディレクトリは存在しないのでFilesystem::FullPath()はうまく動かない
					event_path = m_watched_directories.left.at(event->wd) + Unicode::Widen(event->name) + U'/';

					//LOG_INFO(U"ℹ️ DirectoryWatcher: directory deleted. `{}`"_fmt(event_path));
				}
				else
				{
					event_path = m_watched_directories.left.at(event->wd) + Unicode::Widen(event->name);

					//LOG_INFO(U"ℹ️ DirectoryWatcher: file deleted. `{}`"_fmt(event_path));
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
				if (event_path == m_targetDirectory)
				{
					action = FileAction::Removed;

					//LOG_INFO(U"ℹ️ DirectoryWatcher: Root directory deleted. `{}`"_fmt(m_targetDirectory));
				}
				else
					continue; // m_changesに追加しない
			}

			{
				std::lock_guard lock{ m_changesMutex };
				m_fileChanges.push_back(FileChange{ std::move(event_path), action });
			}
		}
	}

	void DirectoryWatcher::DirectoryWatcherDetail::dispose()
	{
		if (not m_disposed)
		{
			m_disposed = true;

			for (auto itr = m_watched_directories.left.begin(); itr != m_watched_directories.left.end(); ++itr)
			{
				inotify_rm_watch(m_fd, itr->first);
			}
		}

        if (m_fd != -1)
        {
		    close(m_fd);
        }
	}
}
