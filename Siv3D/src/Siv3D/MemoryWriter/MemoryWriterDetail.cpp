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

# include "MemoryWriterDetail.hpp"

namespace s3d
{
	MemoryWriter::MemoryWriterDetail::MemoryWriterDetail()
	{

	}

	MemoryWriter::MemoryWriterDetail::~MemoryWriterDetail()
	{

	}

	void MemoryWriter::MemoryWriterDetail::release()
	{
		m_data.release();

		m_pos = 0;
	}

	void MemoryWriter::MemoryWriterDetail::clear()
	{
		m_data.clear();

		m_pos = 0;
	}

	int64 MemoryWriter::MemoryWriterDetail::size() const
	{
		return m_data.size();
	}

	int64 MemoryWriter::MemoryWriterDetail::write(const void* const src, const size_t size)
	{
		assert(src || size == 0);

		if (m_pos < 0)
		{
			return 0;
		}

		if (size == 0)
		{
			return 0;
		}

		const size_t newSize = static_cast<size_t>(m_pos) + size;

		if (m_pos != static_cast<int64>(m_data.size()))
		{
			m_data.resize(newSize);

			std::memcpy(&m_data[static_cast<size_t>(m_pos)], src, size);
		}
		else
		{
			const Byte* begin = static_cast<const Byte*>(src);

			m_data.insert(m_data.end(), begin, begin + size);
		}

		m_pos += size;

		return size;
	}

	const Byte* MemoryWriter::MemoryWriterDetail::data()
	{
		return m_data.data();
	}

	int64 MemoryWriter::MemoryWriterDetail::setPos(const int64 pos)
	{
		return m_pos = pos;
	}

	int64 MemoryWriter::MemoryWriterDetail::getPos() const
	{
		return m_pos;
	}

	ByteArray MemoryWriter::MemoryWriterDetail::retrieve()
	{
		ByteArray data(std::move(m_data));

		m_pos = 0;

		return data;
	}
}
