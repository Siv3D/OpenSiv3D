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

# include <cstring>
# include <Siv3D/MemoryViewReader.hpp>
# include <Siv3D/Utility.hpp>

namespace s3d
{
	MemoryViewReader::MemoryViewReader(const void* data, const size_t size_bytes) noexcept
		: m_size{ static_cast<int64>(size_bytes) }
		, m_ptr{ static_cast<const Byte*>(data) } {}

	bool MemoryViewReader::supportsLookahead() const noexcept
	{
		return true;
	}

	bool MemoryViewReader::isOpen() const noexcept
	{
		return (m_ptr != nullptr);
	}

	int64 MemoryViewReader::size() const
	{
		return m_size;
	}

	int64 MemoryViewReader::getPos() const
	{
		return m_pos;
	}

	bool MemoryViewReader::setPos(const int64 pos)
	{
		if (not InRange<int64>(pos, 0, m_size))
		{
			return false;
		}

		m_pos = pos;

		return true;
	}

	int64 MemoryViewReader::skip(const int64 offset)
	{
		m_pos = Clamp<int64>((m_pos + offset), 0, m_size);

		return m_pos;
	}

	int64 MemoryViewReader::read(void* dst, const int64 size)
	{
		if (not dst)
		{
			return 0;
		}

		const int64 readSize = Clamp<int64>(size, 0, m_size - m_pos);

		std::memcpy(dst, (m_ptr + m_pos), static_cast<size_t>(readSize));

		m_pos += readSize;

		return readSize;
	}

	int64 MemoryViewReader::read(void* dst, const int64 pos, const int64 size)
	{
		if (not dst)
		{
			return 0;
		}

		const int64 readSize = Clamp<int64>(size, 0, m_size - pos);

		std::memcpy(dst, (m_ptr + pos), static_cast<size_t>(readSize));

		m_pos = pos + readSize;

		return readSize;
	}

	int64 MemoryViewReader::lookahead(void* dst, const int64 size) const
	{
		if (not dst)
		{
			return 0;
		}

		const int64 readSize = Clamp<int64>(size, 0, m_size - m_pos);

		std::memcpy(dst, (m_ptr + m_pos), static_cast<size_t>(readSize));

		return readSize;
	}

	int64 MemoryViewReader::lookahead(void* dst, const int64 pos, const int64 size) const
	{
		if (not dst)
		{
			return 0;
		}

		const int64 readSize = Clamp<int64>(size, 0, m_size - pos);

		std::memcpy(dst, (m_ptr + m_pos), static_cast<size_t>(readSize));

		return readSize;
	}
}
