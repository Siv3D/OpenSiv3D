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
# include <thread>
# include <atomic>
# include <Siv3D/DirectoryWatcher.hpp>
# include <Siv3D/Windows.hpp>

namespace s3d
{
	class DirectoryWatcher::DirectoryWatcherDetail
	{
	private:

		static constexpr size_t MaxNotifyInformation = 16384;

		static constexpr size_t BufferSize = sizeof(FILE_NOTIFY_INFORMATION) * MaxNotifyInformation;

		static constexpr uint32 NotificationFilter = FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION;


		FilePath m_directory;

		OVERLAPPED m_overlapped;

		Array<uint8> m_buffer;

		Array<uint8> m_backBuffer;

		HANDLE m_directoryHandle = INVALID_HANDLE_VALUE;

		std::mutex m_changesMutex;

		Array<std::pair<FilePath, FileAction>> m_changes;


		std::thread m_thread;

		std::atomic<bool> m_abort = false;


		static void Update(DirectoryWatcherDetail* watcher);

		static void CALLBACK OnChangeNotification(const DWORD dwErrorCode, const DWORD dwNumberOfBytesTransfered, const LPOVERLAPPED lpOverlapped);

		bool init();

		void update();

		void processChange(const uint32 errorCode, const size_t numBytes);

	public:

		explicit DirectoryWatcherDetail(const FilePath& directory);

		~DirectoryWatcherDetail();

		Array<std::pair<FilePath, FileAction>> retrieveChanges();

		const FilePath& directory() const;
	};
}
