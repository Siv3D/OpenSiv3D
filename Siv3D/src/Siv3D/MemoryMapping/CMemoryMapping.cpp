﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/FileSystem.hpp>
# include "CMemoryMapping.hpp"

namespace s3d
{
	namespace detail
	{
		static size_t GetGranularity_impl()
		{
		# if defined (SIV3D_TARGET_WINDOWS)	

			SYSTEM_INFO systemInfo;
			::GetSystemInfo(&systemInfo);
			return systemInfo.dwAllocationGranularity;

		# else

			return sysconf(_SC_PAGE_SIZE);

		# endif
		}

		size_t GetGranularity()
		{
			static const size_t granularity = detail::GetGranularity_impl();
			return granularity;
		}
	}

	int64 MemoryMapping::CMemoryMapping::getFileSize() const
	{
	# if defined (SIV3D_TARGET_WINDOWS)	

		LARGE_INTEGER size;
			
		::GetFileSizeEx(m_fileHandle, &size);
			
		return size.QuadPart;

	# else

		struct stat s;
			
		if (::fstat(m_fileHandle, &s) == -1)
		{
			return 0;
		}
			
		return s.st_size;

	# endif
	}

	MemoryMapping::CMemoryMapping::CMemoryMapping()
	{

	}

	MemoryMapping::CMemoryMapping::~CMemoryMapping()
	{
		close();
	}

	bool MemoryMapping::CMemoryMapping::open(const FilePath& path, bool mapAll)
	{
		if (path.isEmpty())
		{
			return false;
		}

		if (isOpened())
		{
			close();
		}

	# if defined (SIV3D_TARGET_WINDOWS)

		m_fileHandle = ::CreateFileW(
			path.toWstr().c_str(), GENERIC_READ, (FILE_SHARE_READ | FILE_SHARE_WRITE),
			nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (m_fileHandle == INVALID_HANDLE_VALUE)
		{
			return false;
		}

	# else

		m_fileHandle = ::open(path.narrow().c_str(), O_RDONLY);
		
		if (m_fileHandle == -1)
		{
			return false;
		}

	# endif

		m_fileSize = getFileSize();

		m_fullPath = FileSystem::FullPath(path);
		
		if (mapAll)
		{
			map(0, 0);
		}

		return true;
	}

	void MemoryMapping::CMemoryMapping::close()
	{
		unmap();

	# if defined (SIV3D_TARGET_WINDOWS)

		::CloseHandle(m_fileHandle);
		m_fileHandle = INVALID_HANDLE_VALUE;

	# else

		::close(m_fileHandle);
		m_fileHandle = -1;

	# endif
			
		m_fileSize = 0;

		m_fullPath.clear();
	}

	bool MemoryMapping::CMemoryMapping::isOpened() const
	{
	# if defined (SIV3D_TARGET_WINDOWS)

		return m_fileHandle != INVALID_HANDLE_VALUE;

	# else

		return m_fileHandle != -1;

	# endif
	}

	void MemoryMapping::CMemoryMapping::map(size_t offset, size_t requestSize)
	{
		unmap();

		if (offset >= m_fileSize)
		{
			return;
		}

		const size_t mappingSize = static_cast<size_t>(
			requestSize && ((offset + requestSize) < m_fileSize) ? requestSize : (m_fileSize - offset));

		if (mappingSize <= 0)
		{
			return;
		}

		const size_t internalOffset = offset / detail::GetGranularity() * detail::GetGranularity();

	# if defined (SIV3D_TARGET_WINDOWS)

		m_mapHandle = ::CreateFileMappingW(
			m_fileHandle, 0, PAGE_READONLY,
			static_cast<uint64>(offset + mappingSize) >> 32, (offset + mappingSize) & 0xffFFffFF, nullptr);

		if (m_mapHandle == INVALID_HANDLE_VALUE)
		{
			return;
		}

		Byte* const pData = static_cast<Byte*>(::MapViewOfFile(
			m_mapHandle, FILE_MAP_READ, static_cast<uint64>(internalOffset) >> 32,
			internalOffset & 0xffFFffFF, offset - internalOffset + mappingSize));
			
		if (!pData)
		{
			return;
		}

	# else

		Byte* const pData = static_cast<Byte*>(
			::mmap(0, offset - internalOffset + mappingSize, PROT_READ, MAP_SHARED, m_fileHandle, internalOffset));

		if (pData == MAP_FAILED)
		{
			return;
		}

	# endif
		
		m_mappedSize = mappingSize;
			
		m_mapOffset = offset;

		m_mapView = pData + (offset - internalOffset);
	}

	void MemoryMapping::CMemoryMapping::unmap()
	{
		if (!m_mapView)
		{
			return;
		}

		Byte* const pData = m_mapView - (m_mapOffset - m_mapOffset / detail::GetGranularity() * detail::GetGranularity());

	# if defined (SIV3D_TARGET_WINDOWS)

		::UnmapViewOfFile(pData);
			
		::CloseHandle(m_mapHandle);
			
		m_mapHandle = INVALID_HANDLE_VALUE;

	# else

		::munmap(static_cast<void*>(pData), m_mappedSize + (m_mapView - pData));

	# endif
	
		m_mapOffset = 0;
		m_mappedSize = 0;
		m_mapView = nullptr;
	}

	size_t MemoryMapping::CMemoryMapping::offset() const
	{
		return m_mapOffset;
	}
		
	size_t MemoryMapping::CMemoryMapping::mappedSize() const
	{
		return m_mappedSize;
	}

	int64 MemoryMapping::CMemoryMapping::fileSize() const
	{
		return m_fileSize;
	}

	const Byte* MemoryMapping::CMemoryMapping::data() const
	{
		return m_mapView;
	}

	const FilePath& MemoryMapping::CMemoryMapping::path() const
	{
		return m_fullPath;
	}
}
