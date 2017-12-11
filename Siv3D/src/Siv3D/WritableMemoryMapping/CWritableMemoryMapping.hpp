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

# pragma once
# include <Siv3D/String.hpp>
# include <Siv3D/WritableMemoryMapping.hpp>

# if defined (SIV3D_TARGET_WINDOWS)

	# ifndef NOMINMAX
	#	define  NOMINMAX
	# endif
	# ifndef STRICT
	#	define  STRICT
	# endif
	# ifndef WIN32_LEAN_AND_MEAN
	#	define  WIN32_LEAN_AND_MEAN
	# endif
	# ifndef _WIN32_WINNT
	#	define  _WIN32_WINNT _WIN32_WINNT_WIN7
	# endif
	# ifndef NTDDI_VERSION
	#	define  NTDDI_VERSION NTDDI_WIN7
	# endif
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

		Byte* m_mapView = nullptr;

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

		Byte* data() const;

		const FilePath& path() const;
	};
}
