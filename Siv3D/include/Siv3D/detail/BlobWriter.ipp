//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline BlobWriter::BlobWriter(const Arg::reserve_<size_t> resrveSizeBytes)
		: m_blob{ resrveSizeBytes } {}

	inline bool BlobWriter::isOpen() const noexcept
	{
		return true;
	}

	inline BlobWriter::operator bool() const noexcept
	{
		return true;
	}

	inline int64 BlobWriter::size() const
	{
		return m_blob.size();
	}

	inline int64 BlobWriter::getPos() const
	{
		return m_writePos;
	}

	inline bool BlobWriter::setPos(const int64 pos)
	{
		m_writePos = pos;

		return true;
	}

	inline int64 BlobWriter::seekToEnd()
	{
		m_writePos = m_blob.size();

		return m_writePos;
	}

	inline int64 BlobWriter::write(const void* src, const int64 sizeBytes)
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
	inline bool BlobWriter::write(const TriviallyCopyable& src)
	{
		return (write(std::addressof(src), sizeof(TriviallyCopyable)) == sizeof(TriviallyCopyable));
	}

	inline Blob BlobWriter::retrieve()
	{
		return std::move(m_blob);
	}

	inline const Blob& BlobWriter::getBlob() const noexcept
	{
		return m_blob;
	}

	inline void BlobWriter::reserve(const size_t sizeBytes)
	{
		m_blob.reserve(sizeBytes);
	}

	inline void BlobWriter::clear()
	{
		m_blob.clear();
	}

	inline void BlobWriter::release()
	{
		m_blob.release();
	}
}
