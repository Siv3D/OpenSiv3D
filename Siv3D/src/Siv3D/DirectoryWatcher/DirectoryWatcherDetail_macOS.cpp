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
# if defined(SIV3D_TARGET_MACOS)

# include <Siv3D/FileSystem.hpp>
# include "DirectoryWatcherDetail_macOS.hpp"

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
	
	DirectoryWatcher::DirectoryWatcherDetail::DirectoryWatcherDetail(const FilePath& directory)
	{
		CFStringRef FullPathMac = CFStringCreateWithBytes(kCFAllocatorDefault, (const uint8*)directory.c_str(), directory.size_bytes(), kCFStringEncodingUTF32LE, false);
		CFArrayRef PathsToWatch = CFArrayCreate(NULL, (const void**)&FullPathMac, 1, NULL);
		
		FSEventStreamContext context;
		context.version = 0;
		context.info = this;
		context.retain = NULL;
		context.release = NULL;
		context.copyDescription = NULL;
		
		m_eventStream = FSEventStreamCreate(NULL,
											&OnChange,
											&context,
											PathsToWatch,
											kFSEventStreamEventIdSinceNow,
											LatencySec,
											kFSEventStreamCreateFlagUseCFTypes | kFSEventStreamCreateFlagNoDefer | kFSEventStreamCreateFlagFileEvents
											);
		
		CFRelease(PathsToWatch);
		CFRelease(FullPathMac);
		
		if (!m_eventStream)
		{
			return;
		}
		
		FSEventStreamScheduleWithRunLoop(m_eventStream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
		FSEventStreamStart(m_eventStream);
		
		m_running = true;
	}

	DirectoryWatcher::DirectoryWatcherDetail::~DirectoryWatcherDetail()
	{
		m_abort = true;
		
		if (m_running)
		{
			FSEventStreamStop(m_eventStream);
			FSEventStreamUnscheduleFromRunLoop(m_eventStream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
			FSEventStreamInvalidate(m_eventStream);
			FSEventStreamRelease(m_eventStream);
			
			m_running = false;
		}
	}

	Array<std::pair<FilePath, FileAction>> DirectoryWatcher::DirectoryWatcherDetail::retrieveChanges()
	{
		std::lock_guard lock(m_changesMutex);
		
		Array<std::pair<FilePath, FileAction>> results;
		
		results.swap(m_changes);
		
		return results;
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
		
		std::lock_guard lock(m_changesMutex);
		
		for (size_t i = 0; i < eventCount; ++i)
		{
			const FSEventStreamEventFlags flag = flags[i];
			
			if(!(flag & kFSEventStreamEventFlagItemIsFile)
			   && !(flag & kFSEventStreamEventFlagItemIsDir))
			{
				continue;
			}
			
			const bool renamed = (flag & kFSEventStreamEventFlagItemRenamed);
			const bool modified = (flag & kFSEventStreamEventFlagItemModified);
			const bool added = (flag & kFSEventStreamEventFlagItemCreated);
			const bool removed = (flag & kFSEventStreamEventFlagItemRemoved);
			bool checkExistance = false;
			
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
			
			const FilePath path(buffer);
			
			if (checkExistance && !FileSystem::Exists(path))
			{
				action = FileAction::Removed;
			}
			
			m_changes.emplace_back(path, action);
		}
	}
}

# endif
