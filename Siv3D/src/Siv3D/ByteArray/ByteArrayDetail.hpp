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
# include <Siv3D/ByteArray.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/MemoryMapping.hpp>

namespace s3d
{
	class ByteArray::ByteArrayDetail
	{
	private:

		MemoryMapping m_memoryMapping;

		Array<Byte> m_array;

		const Byte* m_view = nullptr;

		int64 m_size = 0;

		int64 m_pos = 0;

	public:

		bool createFromFile(FilePathView path);

		bool create(const void* src, size_t size);

		bool create(const Array<Byte>& data);

		bool create(Array<Byte>&& data);

		void release();

		bool isOpened() const;

		int64 size() const;

		int64 setPos(int64 pos);

		int64 getPos() const;

		const Byte* data() const;

		int64 read(void* dst, int64 size);

		int64 read(void* dst, int64 pos, int64 size);

		int64 lookahead(void* dst, int64 size) const;

		int64 lookahead(void* dst, int64 pos, int64 size) const;
	};
}
