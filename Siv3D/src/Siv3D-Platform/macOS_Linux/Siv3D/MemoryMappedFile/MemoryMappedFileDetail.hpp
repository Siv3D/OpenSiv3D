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
# include <Siv3D/MemoryMappedFile.hpp>

namespace s3d
{
	class MemoryMappedFile::MemoryMappedFileDetail
	{
	public:

		MemoryMappedFileDetail();

		~MemoryMappedFileDetail();

		bool open(FilePathView path, MMFOpenMode_if_Exists ifExists, MMFOpenMode_if_NotFound ifNotFound);

		void close();

		bool isOpen() const;

		void map(size_t offset, size_t requestSize);

		void unmap();

		bool flush();

		size_t offset() const;

		size_t mappedSize() const;

		int64 fileSize() const;

		Byte* data() const;

		const FilePath& path() const;
		
	private:

		int m_fileHandle = -1;

		uint64 m_fileSize = 0;

		size_t m_mappedSize = 0;

		size_t m_mapOffset = 0;

		Byte* m_mapView = nullptr;

		FilePath m_fullPath;

		int64 getFileSize() const;
	};
}
