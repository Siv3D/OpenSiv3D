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
# include <Siv3D/Windows/Windows.hpp>

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

		static constexpr size_t MaxNotifyInformation = 10000;

		static constexpr size_t BufferSize = sizeof(FILE_NOTIFY_INFORMATION) * MaxNotifyInformation;

		static constexpr bool WatchSubtree = true;

		FilePath m_targetDirectory;

		std::jthread m_thread;

		std::atomic<bool> m_initCalled = false;

		bool m_isActive = false;

		OVERLAPPED m_overlapped = {};

		Array<uint8> m_buffer;

		Array<uint8> m_backBuffer;

		HANDLE m_directoryHandle = INVALID_HANDLE_VALUE;

		std::mutex m_changesMutex;

		Array<FileChange> m_fileChanges;

		bool init();

		void processChange(DWORD errorCode, DWORD numBytes);

		static void Update(std::stop_token stop_token, DirectoryWatcherDetail* watcher);

		static void CALLBACK OnChangeNotification(const DWORD dwErrorCode, const DWORD dwNumberOfBytesTransfered, const LPOVERLAPPED lpOverlapped);
	};
}
