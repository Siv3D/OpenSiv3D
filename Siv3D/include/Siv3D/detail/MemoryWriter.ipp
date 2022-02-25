//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline MemoryWriter::MemoryWriter(const Arg::reserve_<size_t> resrveSizeBytes)
		: m_blob{ resrveSizeBytes } {}

	inline bool MemoryWriter::isOpen() const noexcept
	{
		return true;
	}

	inline MemoryWriter::operator bool() const noexcept
	{
		return true;
	}

	inline int64 MemoryWriter::size() const
	{
		return m_blob.size();
	}

	inline int64 MemoryWriter::getPos() const
	{
		return m_writePos;
	}

	inline bool MemoryWriter::setPos(const int64 pos)
	{
		m_writePos = pos;

		return true;
	}

	inline int64 MemoryWriter::seekToEnd()
	{
		m_writePos = m_blob.size();

		return m_writePos;
	}

	inline int64 MemoryWriter::write(const void* src, const int64 sizeBytes)
	{
		assert(src || (sizeBytes == 0));

		if (m_writePos < 0)
		{
			return 0;
		}

		if (sizeBytes == 0)
		{
			return 0;
		}

		const size_t newSize = (static_cast<size_t>(m_writePos) + sizeBytes);

		if (m_writePos != static_cast<int64>(m_blob.size()))
		{
			m_blob.resize(newSize);

			std::memcpy(&m_blob[static_cast<size_t>(m_writePos)], src, sizeBytes);
		}
		else
		{
			m_blob.append(src, sizeBytes);
		}

		m_writePos += sizeBytes;

		return sizeBytes;
	}

	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	inline bool MemoryWriter::write(const TriviallyCopyable& src)
	{
		return (write(std::addressof(src), sizeof(TriviallyCopyable)) == sizeof(TriviallyCopyable));
	}

	inline Blob MemoryWriter::retrieve()
	{
		return std::move(m_blob);
	}

	inline const Blob& MemoryWriter::getBlob() const noexcept
	{
		return m_blob;
	}

	inline void MemoryWriter::reserve(const size_t sizeBytes)
	{
		m_blob.reserve(sizeBytes);
	}

	inline void MemoryWriter::clear()
	{
		m_blob.clear();
	}

	inline void MemoryWriter::release()
	{
		m_blob.release();
	}
}
