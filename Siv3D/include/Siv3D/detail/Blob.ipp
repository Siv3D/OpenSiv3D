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
	inline Blob::Blob(const size_t sizeBytes)
		: m_data(sizeBytes) {}

	inline Blob::Blob(const Arg::reserve_<size_t> resrveSizeBytes)
		: m_data(resrveSizeBytes) {}

	inline Blob::Blob(const FilePathView path)
	{
		createFromFile(path);
	}

	inline Blob::Blob(IReader& reader)
		: m_data(reader.size())
	{
		reader.read(m_data.data(), m_data.size());
	}

	inline Blob::Blob(const void* src, const size_t sizeBytes)
		: m_data(static_cast<const Byte*>(src), (static_cast<const Byte*>(src) + sizeBytes)) {}

	inline Blob::Blob(const Array<Byte>& data)
		: m_data(data) {}

	inline Blob::Blob(Array<Byte>&& data)
		: m_data(std::move(data)) {}

	inline Blob& Blob::operator =(const Array<Byte>& other)
	{
		m_data = other;

		return *this;
	}

	inline Blob& Blob::operator =(Array<Byte>&& other) noexcept
	{
		m_data = std::move(other);

		return *this;
	}

	inline Blob& Blob::operator =(const Blob& other)
	{
		m_data = other.m_data;

		return *this;
	}

	inline Blob& Blob::operator =(Blob&& other) noexcept
	{
		m_data = std::move(other.m_data);

		return *this;
	}

	inline void Blob::create(const Blob& other)
	{
		m_data = other.m_data;
	}

	inline void Blob::create(Blob&& other)
	{
		m_data = std::move(other.m_data);
	}

	inline void Blob::create(const void* src, const size_t sizeBytes)
	{
		m_data.assign(static_cast<const Byte*>(src), (static_cast<const Byte*>(src) + sizeBytes));
	}

	inline void Blob::create(const Array<Byte>& data)
	{
		m_data = data;
	}

	inline void Blob::create(Array<Byte>&& data)
	{
		m_data = std::move(data);
	}

	inline const Byte& Blob::operator[](const size_t index) const
	{
		return m_data[index];
	}

	inline Byte& Blob::operator[](const size_t index)
	{
		return m_data[index];
	}

	inline const Byte* Blob::data() const noexcept
	{
		return m_data.data();
	}

	inline Byte* Blob::data() noexcept
	{
		return m_data.data();
	}

	inline const Array<Byte>& Blob::asArray() const noexcept
	{
		return m_data;
	}

	inline bool Blob::empty() const noexcept
	{
		return m_data.empty();
	}

	inline bool Blob::isEmpty() const noexcept
	{
		return m_data.empty();
	}

	inline Blob::operator bool() const noexcept
	{
		return (not m_data.empty());
	}

	inline size_t Blob::size() const noexcept
	{
		return m_data.size();
	}

	inline size_t Blob::size_bytes() const noexcept
	{
		return m_data.size_bytes();
	}

	inline size_t Blob::capacity() const noexcept
	{
		return m_data.capacity();
	}

	inline void Blob::reserve(const size_t sizeBytes)
	{
		m_data.reserve(sizeBytes);
	}

	inline void Blob::resize(const size_t sizeBytes)
	{
		m_data.resize(sizeBytes, Byte{ 0 });
	}

	inline void Blob::shrink_to_fit()
	{
		m_data.shrink_to_fit();
	}

	inline void Blob::clear()
	{
		m_data.clear();
	}

	inline void Blob::release()
	{
		m_data.release();
	}

	inline Blob::iterator Blob::begin() noexcept
	{
		return m_data.begin();
	}

	inline Blob::iterator Blob::end() noexcept
	{
		return m_data.end();
	}

	inline Blob::const_iterator Blob::begin() const noexcept
	{
		return m_data.begin();
	}

	inline Blob::const_iterator Blob::end() const noexcept
	{
		return m_data.end();
	}

	inline Blob::const_iterator Blob::cbegin() const noexcept
	{
		return m_data.cbegin();
	}

	inline Blob::const_iterator Blob::cend() const noexcept
	{
		return m_data.cend();
	}

	inline Blob::reverse_iterator Blob::rbegin() noexcept
	{
		return m_data.rbegin();
	}

	inline Blob::reverse_iterator Blob::rend() noexcept
	{
		return m_data.rend();
	}

	inline Blob::const_reverse_iterator Blob::rbegin() const noexcept
	{
		return m_data.rbegin();
	}

	inline Blob::const_reverse_iterator Blob::rend() const noexcept
	{
		return m_data.rend();
	}

	inline Blob::const_reverse_iterator Blob::crbegin() const noexcept
	{
		return m_data.crbegin();
	}

	inline Blob::const_reverse_iterator Blob::crend() const noexcept
	{
		return m_data.crend();
	}

	inline void Blob::append(const void* src, const size_t sizeBytes)
	{
		m_data.insert(m_data.end(), static_cast<const Byte*>(src), (static_cast<const Byte*>(src) + sizeBytes));
	}
}
