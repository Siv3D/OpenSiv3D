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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Siv3D/String.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	class BinaryWriter::CBinaryWriter
	{
	private:

		constexpr static size_t BufferSize = 64 * 1024;

		::HANDLE m_handle = INVALID_HANDLE_VALUE;

		FilePath m_fullPath;

		uint8* m_pBuffer = nullptr;

		size_t m_currentBufferPos = 0;

		bool m_opened = false;

		int64 fillBuffer(const void* src, size_t size);

	public:

		CBinaryWriter();

		~CBinaryWriter();

		bool open(const FilePath& path, OpenMode openMode);

		void flush();

		void close();

		bool isOpened() const noexcept;

		void clear();

		int64 size();

		int64 setPos(int64 pos);

		int64 getPos();

		int64 write(const void* src, size_t size);

		const FilePath& path() const;
	};
}

# endif
