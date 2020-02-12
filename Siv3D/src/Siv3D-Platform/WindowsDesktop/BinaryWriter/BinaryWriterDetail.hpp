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
# include <Siv3D/Windows.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	class BinaryWriter::BinaryWriterDetail
	{
	private:

		constexpr static size_t BufferSize = 64 * 1024;

		HANDLE m_handle = INVALID_HANDLE_VALUE;

		FilePath m_fullPath;

		Byte* m_pBuffer = nullptr;

		size_t m_currentBufferPos = 0;

		bool m_opened = false;

		int64 fillBuffer(const void* src, size_t size);

	public:

		BinaryWriterDetail();

		~BinaryWriterDetail();

		bool open(FilePathView path, OpenMode openMode);

		void flush();

		void close();

		bool isOpen() const noexcept;

		void clear();

		int64 size();

		int64 setPos(int64 pos);

		int64 getPos();

		int64 write(const void* src, size_t size);

		const FilePath& path() const;
	};
}
