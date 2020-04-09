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
# include <WritableMemoryMapping/WritableMemoryMappingDetail.hpp>

namespace s3d
{
	namespace detail
	{
		size_t GetGranularity();
	}

	int64 WritableMemoryMapping::WritableMemoryMappingDetail::getFileSize() const
	{
		struct stat s;
		
		if (::fstat(m_fileHandle, &s) == -1)
		{
			return 0;
		}
		
		return s.st_size;
	}

	WritableMemoryMapping::WritableMemoryMappingDetail::WritableMemoryMappingDetail()
	{

	}

	WritableMemoryMapping::WritableMemoryMappingDetail::~WritableMemoryMappingDetail()
	{
		close();
	}

	bool WritableMemoryMapping::WritableMemoryMappingDetail::open(const FilePath& path, const MMFOpenMode_if_Exists ifExists, const MMFOpenMode_if_NotFound ifNotFound)
	{
		if (path.isEmpty())
		{
			return false;
		}

		if (isOpen())
		{
			close();
		}

		int openMode = O_RDWR;
		
		switch (ifExists)
		{
			case MMFOpenMode_if_Exists::JustOpen:
			case MMFOpenMode_if_Exists::MapAll:
				openMode |= (ifNotFound == MMFOpenMode_if_NotFound::Create) ? O_CREAT : 0;
				break;
			case MMFOpenMode_if_Exists::Truncate:
				openMode |= (ifNotFound == MMFOpenMode_if_NotFound::Create) ? (O_TRUNC | O_CREAT) : O_TRUNC;
				break;
			default:
				if (ifNotFound == MMFOpenMode_if_NotFound::Create)
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

		m_fileSize = getFileSize();

		m_fullPath = FileSystem::FullPath(path);

		if (ifExists == MMFOpenMode_if_Exists::MapAll && m_fileSize)
		{
			map(0, 0);
		}

		return true;
	}

	void WritableMemoryMapping::WritableMemoryMappingDetail::close()
	{
		unmap();

		::close(m_fileHandle);
		m_fileHandle = -1;

		m_fileSize = 0;

		m_fullPath.clear();
	}

	bool WritableMemoryMapping::WritableMemoryMappingDetail::isOpen() const
	{
		return m_fileHandle != -1;
	}

	void WritableMemoryMapping::WritableMemoryMappingDetail::map(size_t offset, size_t requestSize)
	{
		unmap();

		if (offset > m_fileSize)
		{
			return;
		}

		const size_t mappingSize = requestSize ? requestSize : static_cast<size_t>(m_fileSize - offset);

		const size_t internalOffset = offset / detail::GetGranularity() * detail::GetGranularity();

		if ((offset + mappingSize) > m_fileSize)
		{
			if (-1 == ftruncate(m_fileHandle, offset + mappingSize))
			{
				return;
			}
			
			m_fileSize = offset + mappingSize;
		}
		
		Byte* const pData = static_cast<Byte*>(
											   ::mmap(0, offset - internalOffset + mappingSize, (PROT_READ | PROT_WRITE), MAP_SHARED, m_fileHandle, internalOffset));
		
		if (pData == MAP_FAILED)
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

	void WritableMemoryMapping::WritableMemoryMappingDetail::unmap()
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

	bool WritableMemoryMapping::WritableMemoryMappingDetail::flush()
	{
		if (m_mapView)
		{
			Byte* const pData = m_mapView - (m_mapOffset - m_mapOffset / detail::GetGranularity() * detail::GetGranularity());
			const size_t flushSize = m_mappedSize + (m_mapView - pData);

			if (::msync(pData, flushSize, MS_SYNC) != 0)
			{
				return false;
			}
		}

		return true;
	}

	size_t WritableMemoryMapping::WritableMemoryMappingDetail::offset() const
	{
		return m_mapOffset;
	}
		
	size_t WritableMemoryMapping::WritableMemoryMappingDetail::mappedSize() const
	{
		return m_mappedSize;
	}

	int64 WritableMemoryMapping::WritableMemoryMappingDetail::fileSize() const
	{
		return m_fileSize;
	}

	Byte* WritableMemoryMapping::WritableMemoryMappingDetail::data() const
	{
		return m_mapView;
	}

	const FilePath& WritableMemoryMapping::WritableMemoryMappingDetail::path() const
	{
		return m_fullPath;
	}
}
