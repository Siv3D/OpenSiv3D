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

# include <Siv3D/FileSystem.hpp>
# include "MemoryMappedFileDetail.hpp"

namespace s3d
{
	namespace detail
	{
		size_t GetGranularity();
	}

	int64 MemoryMappedFile::MemoryMappedFileDetail::getFileSize() const
	{
		LARGE_INTEGER size;

		::GetFileSizeEx(m_fileHandle, &size);

		return size.QuadPart;
	}

	MemoryMappedFile::MemoryMappedFileDetail::MemoryMappedFileDetail()
	{

	}

	MemoryMappedFile::MemoryMappedFileDetail::~MemoryMappedFileDetail()
	{
		close();
	}

	bool MemoryMappedFile::MemoryMappedFileDetail::open(const FilePathView path, const MMFOpenMode_if_Exists ifExists, const MMFOpenMode_if_NotFound ifNotFound)
	{
		if (path.isEmpty())
		{
			return false;
		}

		if (isOpen())
		{
			close();
		}

		int32 openMode;

		switch (ifExists)
		{
		case MMFOpenMode_if_Exists::JustOpen:
		case MMFOpenMode_if_Exists::MapAll:
			openMode = (ifNotFound == MMFOpenMode_if_NotFound::Create) ? OPEN_ALWAYS : OPEN_EXISTING;
			break;
		case MMFOpenMode_if_Exists::Truncate:
			openMode = (ifNotFound == MMFOpenMode_if_NotFound::Create) ? CREATE_ALWAYS : TRUNCATE_EXISTING;
			break;
		default:
			if (ifNotFound == MMFOpenMode_if_NotFound::Create)
			{
				openMode = CREATE_NEW;
			}
			else
			{
				return false;
			}
		}

		m_fileHandle = ::CreateFileW(
			path.toWstr().c_str(), (GENERIC_READ | GENERIC_WRITE), (FILE_SHARE_READ | FILE_SHARE_WRITE),
			nullptr, openMode, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (m_fileHandle == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		m_fileSize = getFileSize();

		m_fullPath = FileSystem::FullPath(path);

		if (ifExists == MMFOpenMode_if_Exists::MapAll && m_fileSize)
		{
			map(0, 0);
		}

		return true;
	}

	void MemoryMappedFile::MemoryMappedFileDetail::close()
	{
		unmap();

		::CloseHandle(m_fileHandle);
		m_fileHandle = INVALID_HANDLE_VALUE;

		m_fileSize = 0;

		m_fullPath.clear();
	}

	bool MemoryMappedFile::MemoryMappedFileDetail::isOpen() const
	{
		return m_fileHandle != INVALID_HANDLE_VALUE;
	}

	void MemoryMappedFile::MemoryMappedFileDetail::map(size_t offset, size_t requestSize)
	{
		unmap();

		if (offset > m_fileSize)
		{
			return;
		}

		const size_t mappingSize = requestSize ? requestSize : static_cast<size_t>(m_fileSize - offset);

		const size_t internalOffset = offset / detail::GetGranularity() * detail::GetGranularity();

		m_mapHandle = ::CreateFileMappingW(
			m_fileHandle, 0, PAGE_READWRITE,
			static_cast<uint64>(offset + mappingSize) >> 32, (offset + mappingSize) & 0xffFFffFF, nullptr);

		if (m_mapHandle == NULL)
		{
			return;
		}

		Byte* const pData = static_cast<Byte*>(::MapViewOfFile(
			m_mapHandle, FILE_MAP_WRITE, static_cast<uint64>(internalOffset) >> 32,
			internalOffset & 0xffFFffFF, offset - internalOffset + mappingSize));

		if (pData == nullptr)
		{
			return;
		}

		if (offset + mappingSize > m_fileSize)
		{
			m_fileSize = offset + mappingSize;
		}

		m_mappedSize = mappingSize;

		m_mapOffset = offset;

		m_mapView = pData + (offset - internalOffset);
	}

	void MemoryMappedFile::MemoryMappedFileDetail::unmap()
	{
		if (m_mapView == nullptr)
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

	bool MemoryMappedFile::MemoryMappedFileDetail::flush()
	{
		if (m_mapView)
		{
			Byte* const pData = m_mapView - (m_mapOffset - m_mapOffset / detail::GetGranularity() * detail::GetGranularity());
			const size_t flushSize = m_mappedSize + (m_mapView - pData);

			return ::FlushViewOfFile(pData, flushSize) != 0 && ::FlushFileBuffers(m_fileHandle) != 0;
		}

		return ::FlushFileBuffers(m_fileHandle) != 0;
	}

	size_t MemoryMappedFile::MemoryMappedFileDetail::offset() const
	{
		return m_mapOffset;
	}

	size_t MemoryMappedFile::MemoryMappedFileDetail::mappedSize() const
	{
		return m_mappedSize;
	}

	int64 MemoryMappedFile::MemoryMappedFileDetail::fileSize() const
	{
		return m_fileSize;
	}

	Byte* MemoryMappedFile::MemoryMappedFileDetail::data() const
	{
		return m_mapView;
	}

	const FilePath& MemoryMappedFile::MemoryMappedFileDetail::path() const
	{
		return m_fullPath;
	}
}
