//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/FileSystem.hpp>
# include "CWritableMemoryMapping.hpp"

namespace s3d
{
	namespace detail
	{
		size_t GetGranularity();
	}

	int64 WritableMemoryMapping::CWritableMemoryMapping::getFileSize() const
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

	WritableMemoryMapping::CWritableMemoryMapping::CWritableMemoryMapping()
	{

	}

	WritableMemoryMapping::CWritableMemoryMapping::~CWritableMemoryMapping()
	{
		close();
	}

	bool WritableMemoryMapping::CWritableMemoryMapping::open(const FilePath& path, const MMFOpenMode_IfExists ifExists, const MMFOpenMode_IfNotFound ifNotFound)
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

		int32 openMode;

		switch (ifExists)
		{
		case MMFOpenMode_IfExists::JustOpen:
		case MMFOpenMode_IfExists::MapAll:
			openMode = (ifNotFound == MMFOpenMode_IfNotFound::Create) ? OPEN_ALWAYS : OPEN_EXISTING;
			break;
		case MMFOpenMode_IfExists::Truncate:
			openMode = (ifNotFound == MMFOpenMode_IfNotFound::Create) ? CREATE_ALWAYS : TRUNCATE_EXISTING;
			break;
		default:
			if (ifNotFound == MMFOpenMode_IfNotFound::Create)
			{
				openMode = CREATE_NEW;
			}
			else
			{
				return false;
			}
		}

		m_fileHandle = ::CreateFileW(
			path.c_str(), (GENERIC_READ | GENERIC_WRITE), (FILE_SHARE_READ | FILE_SHARE_WRITE),
			nullptr, openMode, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (m_fileHandle == INVALID_HANDLE_VALUE)
		{
			return false;
		}

	# else

		int openMode = O_RDWR;

		switch (ifExists)
		{
		case MMFOpenMode_IfExists::JustOpen:
		case MMFOpenMode_IfExists::MapAll:
			openMode |= (ifNotFound == MMFOpenMode_IfNotFound::Create) ? O_CREAT : 0;
			break;
		case MMFOpenMode_IfExists::Truncate:
			openMode |= (ifNotFound == MMFOpenMode_IfNotFound::Create) ? (O_TRUNC | O_CREAT) : O_TRUNC;
			break;
		default:
			if (ifNotFound == MMFOpenMode_IfNotFound::Create)
			{
				openMode |= O_EXCL | O_CREAT;
			}
			else
			{
				return false;
			}
		}

		m_fileHandle = ::open(path.narrow().c_str(), openMode, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));

		if (m_fileHandle == -1)
		{
			return false;
		}

	# endif

		m_fileSize = getFileSize();

		m_fullPath = FileSystem::FullPath(path);

		if (ifExists == MMFOpenMode_IfExists::MapAll && m_fileSize)
		{
			map(0, 0);
		}

		return true;
	}

	void WritableMemoryMapping::CWritableMemoryMapping::close()
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

	bool WritableMemoryMapping::CWritableMemoryMapping::isOpened() const
	{
	# if defined (SIV3D_TARGET_WINDOWS)

		return m_fileHandle != INVALID_HANDLE_VALUE;

	# else

		return m_fileHandle != -1;

	# endif
	}

	void WritableMemoryMapping::CWritableMemoryMapping::map(size_t offset, size_t requestSize)
	{
		unmap();

		if (offset > m_fileSize)
		{
			return;
		}

		const size_t mappingSize = requestSize ? requestSize : static_cast<size_t>(m_fileSize - offset);

		const size_t internalOffset = offset / detail::GetGranularity() * detail::GetGranularity();

	# if defined (SIV3D_TARGET_WINDOWS)

		m_mapHandle = ::CreateFileMappingW(
			m_fileHandle, 0, PAGE_READWRITE,
			static_cast<uint64>(offset + mappingSize) >> 32, (offset + mappingSize) & 0xffFFffFF, nullptr);

		if (m_mapHandle == INVALID_HANDLE_VALUE)
		{
			return;
		}

		uint8* const pData = static_cast<uint8*>(::MapViewOfFile(
			m_mapHandle, FILE_MAP_WRITE, static_cast<uint64>(internalOffset) >> 32,
			internalOffset & 0xffFFffFF, offset - internalOffset + mappingSize));

		if (!pData)
		{
			return;
		}

	# else

		if ((offset + mappingSize) > m_fileSize)
		{
			if (-1 == ftruncate(m_fileHandle, offset + mappingSize))
			{
				return;
			}
					
			m_fileSize = offset + mappingSize;
		}

		uint8* const pData = static_cast<uint8*>(
			::mmap(0, offset - internalOffset + mappingSize, (PROT_READ | PROT_WRITE), MAP_SHARED, m_fileHandle, internalOffset));

		if (pData == MAP_FAILED)
		{
			return;
		}

	# endif

		if (offset + mappingSize > m_fileSize)
		{
			m_fileSize = offset + mappingSize;
		}

		m_mappedSize = mappingSize;

		m_mapOffset = offset;

		m_mapView = pData + (offset - internalOffset);
	}

	void WritableMemoryMapping::CWritableMemoryMapping::unmap()
	{
		if (!m_mapView)
		{
			return;
		}

		uint8* const pData = m_mapView - (m_mapOffset - m_mapOffset / detail::GetGranularity() * detail::GetGranularity());

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

	bool WritableMemoryMapping::CWritableMemoryMapping::flush()
	{
		if (m_mapView)
		{
			uint8* const pData = m_mapView - (m_mapOffset - m_mapOffset / detail::GetGranularity() * detail::GetGranularity());
			const size_t flushSize = m_mappedSize + (m_mapView - pData);
			
		# if defined (SIV3D_TARGET_WINDOWS)

			return ::FlushViewOfFile(pData, flushSize) != 0 && ::FlushFileBuffers(m_fileHandle) != 0;

		# else

			if (::msync(pData, flushSize, MS_SYNC) != 0)
			{
				return false;
			}

		# endif
		}

		# if defined (SIV3D_TARGET_WINDOWS)

			return ::FlushFileBuffers(m_fileHandle) != 0;

		# else

			return true;

		# endif
	}

	size_t WritableMemoryMapping::CWritableMemoryMapping::offset() const
	{
		return m_mapOffset;
	}
		
	size_t WritableMemoryMapping::CWritableMemoryMapping::mappedSize() const
	{
		return m_mappedSize;
	}

	int64 WritableMemoryMapping::CWritableMemoryMapping::fileSize() const
	{
		return m_fileSize;
	}

	uint8* WritableMemoryMapping::CWritableMemoryMapping::data() const
	{
		return m_mapView;
	}

	const FilePath& WritableMemoryMapping::CWritableMemoryMapping::path() const
	{
		return m_fullPath;
	}
}
