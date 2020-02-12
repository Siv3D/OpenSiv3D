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

# include <Siv3D/FileSystem.hpp>
# include <MemoryMapping/MemoryMappingDetail.hpp>

namespace s3d
{
	namespace detail
	{
		static size_t GetGranularity_impl()
		{
			SYSTEM_INFO systemInfo;
			::GetSystemInfo(&systemInfo);
			return systemInfo.dwAllocationGranularity;
		}

		size_t GetGranularity()
		{
			static const size_t granularity = detail::GetGranularity_impl();
			return granularity;
		}
	}

	int64 MemoryMapping::MemoryMappingDetail::getFileSize() const
	{
		LARGE_INTEGER size;
			
		::GetFileSizeEx(m_fileHandle, &size);
			
		return size.QuadPart;
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

		if (isOpen())
		{
			close();
		}

		m_fileHandle = ::CreateFileW(
			Unicode::ToWString(path).c_str(), GENERIC_READ, (FILE_SHARE_READ | FILE_SHARE_WRITE),
			nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (m_fileHandle == INVALID_HANDLE_VALUE)
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

		::CloseHandle(m_fileHandle);
		m_fileHandle = INVALID_HANDLE_VALUE;

		m_fileSize = 0;

		m_fullPath.clear();
	}

	bool MemoryMapping::MemoryMappingDetail::isOpen() const
	{
		return m_fileHandle != INVALID_HANDLE_VALUE;
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

		const size_t internalOffset = offset / detail::GetGranularity() * detail::GetGranularity();

		m_mapHandle = ::CreateFileMappingW(
			m_fileHandle, 0, PAGE_READONLY,
			static_cast<uint64>(offset + mappingSize) >> 32, (offset + mappingSize) & 0xffFFffFF, nullptr);

		if (m_mapHandle == 0)
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

		::UnmapViewOfFile(pData);
			
		::CloseHandle(m_mapHandle);
			
		m_mapHandle = INVALID_HANDLE_VALUE;

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
