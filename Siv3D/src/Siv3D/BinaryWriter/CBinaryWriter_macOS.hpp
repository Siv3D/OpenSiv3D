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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	class BinaryWriter::CBinaryWriter
	{
	private:

		constexpr static size_t BufferSize = 64 * 1024;

		FILE* m_pFile = nullptr;

		FilePath m_fullPath;

		Byte* m_pBuffer = nullptr;

		size_t m_currentBufferPos = 0;

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