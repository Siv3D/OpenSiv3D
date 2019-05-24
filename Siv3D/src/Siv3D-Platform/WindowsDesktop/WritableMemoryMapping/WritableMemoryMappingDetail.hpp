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

# pragma once
# include <Siv3D/String.hpp>
# include <Siv3D/WritableMemoryMapping.hpp>
# include <Siv3D/Windows.hpp>

namespace s3d
{
	class WritableMemoryMapping::WritableMemoryMappingDetail
	{
	private:

		HANDLE m_fileHandle = INVALID_HANDLE_VALUE;

		HANDLE m_mapHandle = INVALID_HANDLE_VALUE;

		uint64 m_fileSize = 0;

		size_t m_mappedSize = 0;

		size_t m_mapOffset = 0;

		Byte* m_mapView = nullptr;

		FilePath m_fullPath;

		int64 getFileSize() const;

	public:

		WritableMemoryMappingDetail();

		~WritableMemoryMappingDetail();

		bool open(const FilePath& path, const MMFOpenMode_if_Exists ifExists, const MMFOpenMode_if_NotFound ifNotFound);

		void close();

		bool isOpened() const;

		void map(size_t offset, size_t requestSize);

		void unmap();

		bool flush();

		size_t offset() const;

		size_t mappedSize() const;

		int64 fileSize() const;

		Byte* data() const;

		const FilePath& path() const;
	};
}
