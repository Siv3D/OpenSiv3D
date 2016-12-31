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

# pragma once
# include <Siv3D/String.hpp>
# include <Siv3D/WritableMemoryMapping.hpp>

# if defined (SIV3D_TARGET_WINDOWS)

	# include <windows.h>

# else

	# include <unistd.h>
	# include <fcntl.h>
	# include <sys/stat.h>
	# include <sys/mman.h>

# endif

namespace s3d
{
	class WritableMemoryMapping::CWritableMemoryMapping
	{
	private:

	# if defined (SIV3D_TARGET_WINDOWS)

		HANDLE m_fileHandle = INVALID_HANDLE_VALUE;

		HANDLE m_mapHandle = INVALID_HANDLE_VALUE;

	# else

		int m_fileHandle = -1;

	# endif

		uint64 m_fileSize = 0;

		size_t m_mappedSize = 0;

		size_t m_mapOffset = 0;

		uint8* m_mapView = nullptr;

		FilePath m_fullPath;

		int64 getFileSize() const;

	public:

		CWritableMemoryMapping();

		~CWritableMemoryMapping();

		bool open(const FilePath& path, const MMFOpenMode_if_Exists ifExists, const MMFOpenMode_if_NotFound ifNotFound);

		void close();

		bool isOpened() const;

		void map(size_t offset, size_t requestSize);

		void unmap();

		bool flush();

		size_t offset() const;

		size_t mappedSize() const;

		int64 fileSize() const;

		uint8* data() const;

		const FilePath& path() const;
	};
}
