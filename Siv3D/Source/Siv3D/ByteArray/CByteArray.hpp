//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
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
	class ByteArray::CByteArray
	{
	private:

		MemoryMapping m_memoryMapping;

		Array<uint8> m_array;

		const uint8* m_view = nullptr;

		int64 m_size = 0;

		int64 m_pos = 0;

	public:

		bool create(const FilePath& path);

		bool create(const void* src, size_t size);

		bool create(const Array<uint8>& data);

		bool create(Array<uint8>&& data);

		void release();

		bool isOpened() const;

		int64 size() const;

		int64 setPos(int64 pos);

		int64 getPos() const;

		const uint8* data() const;

		int64 read(void* dst, int64 size);

		int64 read(void* dst, int64 pos, int64 size);

		int64 lookahead(void* dst, int64 size) const;

		int64 lookahead(void* dst, int64 pos, int64 size) const;
	};
}
