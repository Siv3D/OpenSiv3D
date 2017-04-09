//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "IReader.hpp"
# include "ByteArrayView.hpp"

namespace s3d
{
	class ReaderView : public IReader
	{
	private:

		int64 m_size = 0;

		int64 m_pos = 0;

		const Byte* m_ptr = nullptr;

	public:

		ReaderView() = default;

		constexpr ReaderView(const void* data, size_t size) noexcept
			: m_size(size)
			, m_ptr(static_cast<const Byte*>(data)) {}

		constexpr ReaderView(const void* begin, const void* end) noexcept
			: m_size(static_cast<const Byte*>(end) - static_cast<const Byte*>(begin))
			, m_ptr(static_cast<const Byte*>(begin)) {}

		constexpr ReaderView(ByteArrayView view) noexcept
			: m_size(view.size())
			, m_ptr(view.data()) {}

		bool isOpened() const override
		{
			return m_ptr != nullptr;
		}

		int64 size() const override
		{
			return m_size;
		}

		int64 getPos() const override
		{
			return m_pos;
		}

		bool setPos(int64 pos) override 
		{
			if (!InRange<int64>(pos, 0, m_size))
			{
				return false;
			}

			m_pos = pos;

			return true;
		}

		int64 skip(int64 offset) override
		{
			m_pos = Clamp<int64>(m_pos + offset, 0, m_size);

			return m_pos;
		}

		int64 read(void* buffer, int64 size) override
		{
			assert(buffer != nullptr || size == 0);

			const int64 readSize = Clamp<int64>(size, 0, m_size - m_pos);

			::memcpy(buffer, m_ptr + m_pos, static_cast<size_t>(readSize));

			m_pos += readSize;

			return readSize;
		}

		int64 read(void* buffer, int64 pos, int64 size) override
		{
			assert(buffer != nullptr || size == 0);

			const int64 readSize = Clamp<int64>(size, 0, m_size - pos);

			::memcpy(buffer, m_ptr + pos, static_cast<size_t>(readSize));

			m_pos = pos + readSize;

			return readSize;
		}

		template <class Type, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		bool read(Type& to)
		{
			return read(std::addressof(to), sizeof(Type)) == sizeof(Type);
		}

		bool supportsLookahead() const override
		{
			return true;
		}

		int64 lookahead(void* buffer, int64 size) const override
		{
			assert(buffer != nullptr || size == 0);

			const int64 readSize = Clamp<int64>(size, 0, m_size - m_pos);

			::memcpy(buffer, m_ptr + m_pos, static_cast<size_t>(readSize));

			return readSize;
		}

		int64 lookahead(void* buffer, int64 pos, int64 size) const override
		{
			assert(buffer != nullptr || size == 0);

			const int64 readSize = Clamp<int64>(size, 0, m_size - pos);

			::memcpy(buffer, m_ptr + m_pos, static_cast<size_t>(readSize));

			return readSize;
		}

		template <class Type, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		bool lookahead(Type& to)
		{
			return lookahead(std::addressof(to), sizeof(Type)) == sizeof(Type);
		}
	};
}
