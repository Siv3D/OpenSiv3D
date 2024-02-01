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
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		static void Convert(CFStringRef str, char32_t* dst)
		{
			const size_t Length = CFStringGetLength(str);
			CFRange Range = CFRangeMake(0, Length);
			CFIndex usedBufLen;
			CFStringGetBytes(str, Range, kCFStringEncodingUTF32LE, '?', false, (uint8*)dst, 2048, &usedBufLen);
			dst[usedBufLen / sizeof(char32_t)] = 0;
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
		CFStringRef fullPath = CFStringCreateWithBytes(kCFAllocatorDefault,
													   reinterpret_cast<const uint8*>(m_targetDirectory.c_str()),
													   m_targetDirectory.size_bytes(), kCFStringEncodingUTF32LE, false);
		CFArrayRef pathToWatch = CFArrayCreate(NULL, (const void**)&fullPath, 1, NULL);
		
		FSEventStreamContext context = {
			.version			= 0,
			.info				= this,
			.retain				= NULL,
			.release			= NULL,
			.copyDescription	= NULL
		};
		
		m_eventStream = FSEventStreamCreate(NULL,
											&OnChange,
											&context,
											pathToWatch,
											kFSEventStreamEventIdSinceNow,
											LatencySec,
											(kFSEventStreamCreateFlagUseCFTypes | kFSEventStreamCreateFlagNoDefer | kFSEventStreamCreateFlagFileEvents)
											);
		
		CFRelease(pathToWatch);
		CFRelease(fullPath);
		
		if (not m_eventStream)
		{
			return;
		}
		
		FSEventStreamScheduleWithRunLoop(m_eventStream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
		FSEventStreamStart(m_eventStream);
		
		m_isActive = true;
		LOG_INFO(U"ℹ️ DirectoryWatcher: Monitoring `{}` is activated"_fmt(m_targetDirectory));
	}

	DirectoryWatcher::DirectoryWatcherDetail::~DirectoryWatcherDetail()
	{
		m_abort = true;
		
		if (not m_isActive)
		{
			return;
		}
		
		FSEventStreamStop(m_eventStream);
		FSEventStreamUnscheduleFromRunLoop(m_eventStream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
		FSEventStreamInvalidate(m_eventStream);
		FSEventStreamRelease(m_eventStream);
		
		m_isActive = false;
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

	void DirectoryWatcher::DirectoryWatcherDetail::OnChange(ConstFSEventStreamRef, void* pWatch, size_t eventCount, void* paths, const FSEventStreamEventFlags flags[], const FSEventStreamEventId[])
	{
		DirectoryWatcherDetail* watch = static_cast<DirectoryWatcherDetail*>(pWatch);
		
		watch->processChanges(eventCount, paths, flags);
	}

	void DirectoryWatcher::DirectoryWatcherDetail::processChanges(const size_t eventCount, void* paths, const FSEventStreamEventFlags flags[])
	{
		if (m_abort)
		{
			return;
		}
		
		char32_t buffer[2048];
		CFArrayRef eventPathArray = (CFArrayRef)paths;
		
		std::lock_guard lock{ m_changesMutex };
		
		for (size_t i = 0; i < eventCount; ++i)
		{
			const FSEventStreamEventFlags flag = flags[i];
			
			if(!(flag & kFSEventStreamEventFlagItemIsFile)
			   && !(flag & kFSEventStreamEventFlagItemIsDir))
			{
				continue;
			}
			
			const bool renamed	= (flag & kFSEventStreamEventFlagItemRenamed);
			const bool modified	= (flag & kFSEventStreamEventFlagItemModified);
			const bool added	= (flag & kFSEventStreamEventFlagItemCreated);
			const bool removed	= (flag & kFSEventStreamEventFlagItemRemoved);
			bool checkExistance	= false;
			
			FileAction action = FileAction::Unknown;
			
			if (modified)
			{
				action = FileAction::Modified;
				checkExistance = true;
			}
			else if (renamed)
			{
				action = FileAction::Added;
				checkExistance = true;
			}
			else if (added)
			{
				action = FileAction::Added;
				
				if (removed)
				{
					checkExistance = true;
				}
			}
			else if (removed)
			{
				action = FileAction::Removed;
			}
			else
			{
				continue;
			}
			
			detail::Convert((CFStringRef)CFArrayGetValueAtIndex(eventPathArray, i), buffer);
			
			FilePath path(buffer);
			
			if (checkExistance && !FileSystem::Exists(path))
			{
				action = FileAction::Removed;
			}
			
			m_fileChanges.push_back(FileChange{ std::move(path), action });
		}
	}
}
