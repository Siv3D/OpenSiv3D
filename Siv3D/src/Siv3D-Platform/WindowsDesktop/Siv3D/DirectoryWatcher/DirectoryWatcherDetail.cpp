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

# include "DirectoryWatcherDetail.hpp"
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		constexpr uint32 NotificationFilter = (FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION);

		[[nodiscard]]
		inline constexpr FileAction ToFileAction(DWORD action) noexcept
		{
			switch (action)
			{
			case FILE_ACTION_ADDED:
			case FILE_ACTION_RENAMED_NEW_NAME:
				return FileAction::Added;
			case FILE_ACTION_MODIFIED:
				return FileAction::Modified;
			case FILE_ACTION_REMOVED:
			case FILE_ACTION_RENAMED_OLD_NAME:
				return FileAction::Removed;
			default:
				return FileAction::Unknown;
			}
		}
	}

	DirectoryWatcher::DirectoryWatcherDetail::DirectoryWatcherDetail(const FilePathView directory)
	{
		if (directory.isEmpty()
			|| (not FileSystem::IsDirectory(directory)))
		{
			LOG_FAIL(U"❌ DirectoryWatcher: `{}` is not a directory"_fmt(directory));
			return;
		}

		m_targetDirectory = FileSystem::FullPath(directory);

		m_thread = std::jthread{ DirectoryWatcherDetail::Update, this };

		while (not m_initCalled)
		{
			::Sleep(1);
		}

		m_isActive = (m_directoryHandle != INVALID_HANDLE_VALUE);
	}

	DirectoryWatcher::DirectoryWatcherDetail::~DirectoryWatcherDetail()
	{
		if (m_thread.joinable())
		{
			m_thread.request_stop();

			m_thread.join();
		}

		if (m_directoryHandle == INVALID_HANDLE_VALUE)
		{
			return;
		}

		::CancelIoEx(m_directoryHandle, &m_overlapped);
		HANDLE tempDirectoryHandle = std::exchange(m_directoryHandle, INVALID_HANDLE_VALUE);
		::WaitForSingleObjectEx(tempDirectoryHandle, 1000, true);
		::CloseHandle(tempDirectoryHandle);

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

	bool DirectoryWatcher::DirectoryWatcherDetail::init()
	{
		m_overlapped.hEvent = this;
		m_buffer.resize(BufferSize);
		m_backBuffer.resize(BufferSize);

		m_directoryHandle = ::CreateFileW(
			m_targetDirectory.toWstr().c_str(),
			FILE_LIST_DIRECTORY,
			(FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE),
			nullptr,
			OPEN_EXISTING,
			(FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED),
			nullptr
		);

		if (m_directoryHandle == INVALID_HANDLE_VALUE)
		{
			LOG_FAIL(U"❌ DirectoryWatcher: Failed to create a directory handle `{}`"_fmt(m_targetDirectory));
			return false;
		}

		LOG_INFO(U"ℹ️ DirectoryWatcher: A directory handle `{}` created"_fmt(m_targetDirectory));

		const bool result = !!::ReadDirectoryChangesW(
			m_directoryHandle,
			m_buffer.data(),
			static_cast<DWORD>(m_buffer.size()),
			WatchSubtree,
			detail::NotificationFilter,
			nullptr,
			&m_overlapped,
			&DirectoryWatcherDetail::OnChangeNotification);

		if (not result)
		{
			LOG_FAIL(U"❌ DirectoryWatcher: ReadDirectoryChangesW() failed. `{}`"_fmt(m_targetDirectory));
			::CloseHandle(m_directoryHandle);
			m_directoryHandle = INVALID_HANDLE_VALUE;
			return false;
		}

		LOG_INFO(U"ℹ️ DirectoryWatcher: Monitoring `{}` is activated"_fmt(m_targetDirectory));

		return true;
	}

	void DirectoryWatcher::DirectoryWatcherDetail::processChange(const DWORD errorCode, const DWORD numBytes)
	{
		if ((errorCode == ERROR_OPERATION_ABORTED)
			|| (numBytes == 0))
		{
			return;
		}

		const bool isValid = (errorCode != ERROR_IO_INCOMPLETE);

		if (isValid)
		{
			m_backBuffer.swap(m_buffer);
		}

		const bool result = !!::ReadDirectoryChangesW(
			m_directoryHandle,
			m_buffer.data(),
			static_cast<DWORD>(m_buffer.size()),
			WatchSubtree,
			detail::NotificationFilter,
			nullptr,
			&m_overlapped,
			&DirectoryWatcherDetail::OnChangeNotification);

		if (not result)
		{
			LOG_FAIL(U"❌ DirectoryWatcher: ReadDirectoryChangesW() failed. `{}`"_fmt(m_targetDirectory));
			::CloseHandle(m_directoryHandle);
			m_directoryHandle = INVALID_HANDLE_VALUE;
			return;
		}

		if (not isValid)
		{
			return;
		}

		std::lock_guard lock{ m_changesMutex };

		for (const uint8* pInfo = m_backBuffer.data();;)
		{
			const FILE_NOTIFY_INFORMATION* notifyInfo = reinterpret_cast<const FILE_NOTIFY_INFORMATION*>(pInfo);
			const std::wstring_view view(notifyInfo->FileName, (notifyInfo->FileNameLength / sizeof(WCHAR)));
			const String localPath = Unicode::FromWstring(view).replace(L'\\', L'/');
			const FileAction action = detail::ToFileAction(notifyInfo->Action);

			m_fileChanges.emplace_back((m_targetDirectory + localPath), action);

			if (notifyInfo->NextEntryOffset == 0)
			{
				break;
			}

			pInfo += notifyInfo->NextEntryOffset;
		}
	}

	void DirectoryWatcher::DirectoryWatcherDetail::Update(std::stop_token stop_token, DirectoryWatcherDetail* watcher)
	{
		if (not watcher->init())
		{
			watcher->m_initCalled = true;
			return;
		}

		watcher->m_initCalled = true;

		while (not stop_token.stop_requested())
		{
			::SleepEx(15, true);
		}
	}

	void CALLBACK DirectoryWatcher::DirectoryWatcherDetail::OnChangeNotification(const DWORD dwErrorCode, const DWORD dwNumberOfBytesTransfered, const LPOVERLAPPED lpOverlapped)
	{
		DirectoryWatcherDetail* directoryWatcher = static_cast<DirectoryWatcherDetail*>(lpOverlapped->hEvent);

		directoryWatcher->processChange(dwErrorCode, dwNumberOfBytesTransfered);
	}
}
