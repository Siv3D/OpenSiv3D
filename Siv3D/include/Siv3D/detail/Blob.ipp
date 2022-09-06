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
}
