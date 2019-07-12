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
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	class BinaryWriter::BinaryWriterDetail
	{
	private:

		constexpr static size_t BufferSize = 64 * 1024;
		
		FILE* m_pFile = nullptr;
		
		FilePath m_fullPath;
		
		Byte* m_pBuffer = nullptr;
		
		size_t m_currentBufferPos = 0;
		
		int64 fillBuffer(const void* src, size_t size);

	public:

		BinaryWriterDetail();

		~BinaryWriterDetail();

		bool open(FilePathView path, OpenMode openMode);

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
