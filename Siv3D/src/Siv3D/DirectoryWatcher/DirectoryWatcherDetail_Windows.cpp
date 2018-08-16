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
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Logger.hpp>
# include "DirectoryWatcherDetail_Windows.hpp"

namespace s3d
{
	DirectoryWatcher::DirectoryWatcherDetail::DirectoryWatcherDetail(const FilePath& directory)
	{
		m_thread = std::thread(DirectoryWatcherDetail::Update, this, directory);
	}

	DirectoryWatcher::DirectoryWatcherDetail::~DirectoryWatcherDetail()
	{
		if (m_directoryHandle == INVALID_HANDLE_VALUE)
		{
			return;
		}

		m_abort = true;
		m_thread.join();

		::CancelIoEx(m_directoryHandle, &m_overlapped);

		HANDLE tempDirectoryHandle = std::exchange(m_directoryHandle, INVALID_HANDLE_VALUE);
		::WaitForSingleObjectEx(tempDirectoryHandle, 1000, true);
		::CloseHandle(tempDirectoryHandle);

		LOG_DEBUG(U"ℹ️ DirectoryWatcher: End monitoring `{}`"_fmt(m_directory));
	}

	Array<std::pair<FilePath, FileAction>> DirectoryWatcher::DirectoryWatcherDetail::retrieveChanges()
	{
		std::lock_guard lock(m_changesMutex);

		Array<std::pair<FilePath, FileAction>> results;

		results.swap(m_changes);

		return results;
	}

	void DirectoryWatcher::DirectoryWatcherDetail::Update(DirectoryWatcherDetail* watcher, const FilePath& directory)
	{
		if (!watcher->init(directory))
		{
			return;
		}

		while (!watcher->m_abort)
		{
			watcher->update();

			::Sleep(20);
		}
	}

	void CALLBACK DirectoryWatcher::DirectoryWatcherDetail::OnChangeNotification(const DWORD dwErrorCode, const DWORD dwNumberOfBytesTransfered, const LPOVERLAPPED lpOverlapped)
	{
		DirectoryWatcherDetail* directoryWatcher = static_cast<DirectoryWatcherDetail*>(lpOverlapped->hEvent);

		directoryWatcher->processChange(static_cast<uint32>(dwErrorCode), static_cast<size_t>(dwNumberOfBytesTransfered));
	}

	bool DirectoryWatcher::DirectoryWatcherDetail::init(const FilePath& directory)
	{
		if (directory.isEmpty() || !FileSystem::IsDirectory(directory))
		{
			LOG_FAIL(U"❌ DirectoryWatcher: `` is not a directory"_fmt(directory));

			return false;
		}

		m_directory = FileSystem::FullPath(directory);
		m_overlapped.hEvent = this;

		m_buffer.resize(BufferSize);
		m_backBuffer.resize(BufferSize);

		m_directoryHandle = ::CreateFileW(
			m_directory.toWstr().c_str(),
			FILE_LIST_DIRECTORY,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			nullptr,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
			nullptr
		);

		if (m_directoryHandle == INVALID_HANDLE_VALUE)
		{
			LOG_FAIL(U"❌ DirectoryWatcher: Failed to create a directory handle `{}`"_fmt(m_directory));

			return false;
		}

		LOG_DEBUG(U"ℹ️ DirectoryWatcher: A directory handle `{}` created"_fmt(m_directory));

		const bool result = !!::ReadDirectoryChangesW(
			m_directoryHandle,
			m_buffer.data(),
			static_cast<DWORD>(m_buffer.size()),
			true,
			NotificationFilter,
			nullptr,
			&m_overlapped,
			&DirectoryWatcherDetail::OnChangeNotification);

		if (!result)
		{
			LOG_FAIL(U"❌ DirectoryWatcher: ReadDirectoryChangesW() failed. `{}`"_fmt(m_directory));

			::CloseHandle(m_directoryHandle);
			m_directoryHandle = INVALID_HANDLE_VALUE;

			return false;
		}

		LOG_DEBUG(U"ℹ️ DirectoryWatcher: Started monitoring `{}`"_fmt(m_directory));

		return true;
	}

	void DirectoryWatcher::DirectoryWatcherDetail::update()
	{
		::SleepEx(0, true);
	}

	void DirectoryWatcher::DirectoryWatcherDetail::processChange(const uint32 errorCode, const size_t numBytes)
	{
		if (errorCode == ERROR_OPERATION_ABORTED || numBytes == 0)
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
			true,
			NotificationFilter,
			nullptr,
			&m_overlapped,
			&DirectoryWatcherDetail::OnChangeNotification);

		if (!result)
		{
			LOG_FAIL(U"❌ DirectoryWatcher: ReadDirectoryChangesW() failed. `{}`"_fmt(m_directory));

			::CloseHandle(m_directoryHandle);
			m_directoryHandle = INVALID_HANDLE_VALUE;

			return;
		}

		if (!isValid)
		{
			return;
		}

		std::lock_guard lock(m_changesMutex);

		for (const uint8* pInfo = m_backBuffer.data();;)
		{
			const FILE_NOTIFY_INFORMATION* notifyInfo = reinterpret_cast<const FILE_NOTIFY_INFORMATION*>(pInfo);
			const std::wstring_view view(notifyInfo->FileName, notifyInfo->FileNameLength / sizeof(WCHAR));
			const String filePath = Unicode::FromWString(view).replace(L'\\', L'/');
			const FilePath path = (m_directory + filePath);

			FileAction action = FileAction::Unknown;

			switch (notifyInfo->Action)
			{
			case FILE_ACTION_ADDED:
			case FILE_ACTION_RENAMED_NEW_NAME:
				action = FileAction::Added;
				break;
			case FILE_ACTION_MODIFIED:
				action = FileAction::Modified;
				break;
			case FILE_ACTION_REMOVED:
			case FILE_ACTION_RENAMED_OLD_NAME:
				action = FileAction::Removed;
				break;
			}

			m_changes.emplace_back(std::move(path), action);

			if (notifyInfo->NextEntryOffset == 0)
			{
				break;
			}

			pInfo += notifyInfo->NextEntryOffset;
		}
	}
}

# endif
