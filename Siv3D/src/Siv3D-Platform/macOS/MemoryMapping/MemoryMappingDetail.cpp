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

# include <Siv3D/FileSystem.hpp>
# include "MemoryMappingDetail.hpp"

namespace s3d
{
	namespace detail
	{
		static size_t GetGranularity_impl()
		{
			return sysconf(_SC_PAGE_SIZE);
		}

		size_t GetGranularity()
		{
			static const size_t granularity = detail::GetGranularity_impl();
			return granularity;
		}
	}

	int64 MemoryMapping::MemoryMappingDetail::getFileSize() const
	{
		struct stat s;
			
		if (::fstat(m_fileHandle, &s) == -1)
		{
			return 0;
		}
			
		return s.st_size;
	}

	MemoryMapping::MemoryMappingDetail::MemoryMappingDetail()
	{

	}

	MemoryMapping::MemoryMappingDetail::~MemoryMappingDetail()
	{
		close();
	}

	bool MemoryMapping::MemoryMappingDetail::open(const FilePathView path, bool mapAll)
	{
		if (path.isEmpty())
		{
			return false;
		}

		if (isOpened())
		{
			close();
		}

		m_fileHandle = ::open(Unicode::Narrow(path).c_str(), O_RDONLY);
		
		if (m_fileHandle == -1)
		{
			return false;
		}

		m_fileSize = getFileSize();

		m_fullPath = FileSystem::FullPath(path);
		
		if (mapAll)
		{
			map(0, 0);
		}

		return true;
	}

	void MemoryMapping::MemoryMappingDetail::close()
	{
		unmap();

		::close(m_fileHandle);
		m_fileHandle = -1;
	
		m_fileSize = 0;

		m_fullPath.clear();
	}

	bool MemoryMapping::MemoryMappingDetail::isOpened() const
	{
		return m_fileHandle != -1;
	}

	void MemoryMapping::MemoryMappingDetail::map(size_t offset, size_t requestSize)
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

		Byte* const pData = static_cast<Byte*>(
			::mmap(0, offset - internalOffset + mappingSize, PROT_READ, MAP_SHARED, m_fileHandle, internalOffset));

		if (pData == MAP_FAILED)
		{
			return;
		}
		
		m_mappedSize = mappingSize;
			
		m_mapOffset = offset;

		m_mapView = pData + (offset - internalOffset);
	}

	void MemoryMapping::MemoryMappingDetail::unmap()
	{
		if (!m_mapView)
		{
			return;
		}

		Byte* const pData = m_mapView - (m_mapOffset - m_mapOffset / detail::GetGranularity() * detail::GetGranularity());

		::munmap(static_cast<void*>(pData), m_mappedSize + (m_mapView - pData));

		m_mapOffset = 0;
		m_mappedSize = 0;
		m_mapView = nullptr;
	}

	size_t MemoryMapping::MemoryMappingDetail::offset() const
	{
		return m_mapOffset;
	}
		
	size_t MemoryMapping::MemoryMappingDetail::mappedSize() const
	{
		return m_mappedSize;
	}

	int64 MemoryMapping::MemoryMappingDetail::fileSize() const
	{
		return m_fileSize;
	}

	const Byte* MemoryMapping::MemoryMappingDetail::data() const
	{
		return m_mapView;
	}

	const FilePath& MemoryMapping::MemoryMappingDetail::path() const
	{
		return m_fullPath;
	}
}
