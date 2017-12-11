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

# include "CByteArray.hpp"

namespace s3d
{
	bool ByteArray::CByteArray::createFromFile(const FilePath& path)
	{
		release();

		if (!m_memoryMapping.open(path))
		{
			return false;
		}

		m_view = m_memoryMapping.data();
		m_size = m_memoryMapping.fileSize();

		return true;
	}

	bool ByteArray::CByteArray::create(const void* src, const size_t size)
	{
		release();

		m_array.assign(static_cast<const Byte*>(src), static_cast<const Byte*>(src) + size);
		
		m_view = m_array.data();
		m_size = m_array.size();

		return true;
	}

	bool ByteArray::CByteArray::create(const Array<Byte>& data)
	{
		release();

		m_array = data;

		m_view = m_array.data();
		m_size = m_array.size();

		return true;
	}

	bool ByteArray::CByteArray::create(Array<Byte>&& data)
	{
		release();

		m_array = std::move(data);

		m_view = m_array.data();
		m_size = m_array.size();

		return true;
	}

	void ByteArray::CByteArray::release()
	{
		m_array.release();
		m_memoryMapping.close();

		m_view = nullptr;
		m_size = 0;
		m_pos = 0;
	}

	bool ByteArray::CByteArray::isOpened() const
	{
		return m_view != nullptr;
	}

	int64 ByteArray::CByteArray::size() const
	{
		return m_size;
	}

	int64 ByteArray::CByteArray::setPos(const int64 pos)
	{
		return m_pos = Clamp(pos, int64(0), m_size);
	}

	int64 ByteArray::CByteArray::getPos() const
	{
		return m_pos;
	}

	const Byte* ByteArray::CByteArray::data() const
	{
		return m_view;
	}

	int64 ByteArray::CByteArray::read(void* const dst, const int64 size)
	{
		return read(dst, m_pos, size);
	}

	int64 ByteArray::CByteArray::read(void* const dst, const int64 pos, const int64 size)
	{
		const int64 readSize = lookahead(dst, pos, size);

		m_pos = (pos + readSize);

		return readSize;
	}

	int64 ByteArray::CByteArray::lookahead(void* const dst, const int64 size) const
	{
		return lookahead(dst, m_pos, size);
	}

	int64 ByteArray::CByteArray::lookahead(void* const dst, const int64 pos, int64 size) const
	{
		if (!m_view || !dst || size <= 0 || pos < 0)
		{
			return 0;
		}

		if ((pos + size) > m_size)
		{
			size = m_size - pos;
		}

		if (size == 0)
		{
			return 0;
		}

		::memcpy(dst, m_view + pos, static_cast<size_t>(size));

		return size;
	}
}
