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
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Byte.hpp>
# include <Siv3D/NonNull.hpp>

namespace s3d
{
	class BinaryWriter::BinaryWriterDetail
	{
	private:

		constexpr static size_t BufferSize = 8192;

		struct File
		{
			std::FILE* file = nullptr;
		} m_file;

		struct Info
		{
			FilePath fullPath;
			bool isOpen = false;
		} m_info;

		struct Buffer
		{
			std::unique_ptr<Byte[]> data;
			size_t currentWritePos = 0;
		} m_buffer;

		int64 fillBuffer(NonNull<const void*> src, size_t size);

	public:

		BinaryWriterDetail();

		~BinaryWriterDetail();

		bool open(FilePathView path, OpenMode openMode);

		void close();

		bool isOpen() const noexcept;

		void flush();

		void clear();

		int64 size();

		int64 getPos();

		int64 setPos(int64 clampedPos);

		int64 write(NonNull<const void*> src, size_t size);

		const FilePath& path() const noexcept;
	};
}
