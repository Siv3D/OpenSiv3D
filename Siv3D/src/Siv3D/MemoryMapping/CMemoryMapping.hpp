//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/String.hpp>
# include <Siv3D/MemoryMapping.hpp>

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
	class MemoryMapping::CMemoryMapping
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

		Byte* m_mapView = nullptr;

		FilePath m_fullPath;

		int64 getFileSize() const;

	public:

		CMemoryMapping();

		~CMemoryMapping();

		bool open(const FilePath& path, bool mapAll);

		void close();

		bool isOpened() const;

		void map(size_t offset, size_t requestSize);

		void unmap();

		size_t offset() const;

		size_t mappedSize() const;

		int64 fileSize() const;

		const Byte* data() const;

		const FilePath& path() const;
	};
}
