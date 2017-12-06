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
# include <cassert>
# include <string>
# include <string_view>
# include <algorithm>
# include <iostream>
# include "Types.hpp"
# include "Hash.hpp"

namespace s3d
{
	class StringView
	{
	public:

		using traits_type				= std::char_traits<char32>;
		using value_type				= char32;
		using pointer					= const char32*;
		using const_pointer				= const char32*;
		using reference					= const char32&;
		using const_reference			= const char32&;
		using const_iterator			= const_pointer;
		using iterator					= const_iterator;
		using const_reverse_iterator	= std::reverse_iterator<const_iterator>;
		using reverse_iterator			= const_reverse_iterator;
		using size_type					= size_t;
		using difference_type			= ptrdiff_t;

		static constexpr size_type npos = size_type{ static_cast<size_type>(-1) };

	private:

		const value_type* m_data = nullptr;

		size_type m_length = 0;

		[[nodiscard]] static constexpr size_type _length(const value_type* pSrc) noexcept
		{
			size_type count = 0;

			while (*pSrc != value_type())
			{
				++count;
				++pSrc;
			}

			return count;
		}

		[[nodiscard]] static constexpr int32 _compare(const value_type* pSrc1, const value_type* pSrc2, size_type count) noexcept
		{
			while (0 < count)
			{
				if (*pSrc1 != *pSrc2)
				{
					return ((*pSrc1 < *pSrc2) ? -1 : +1);
				}

				--count;
				++pSrc1;
				++pSrc2;
			}

			return 0;
		}

		[[nodiscard]] static constexpr const value_type* _find(const value_type* pSrc, size_type count, const value_type ch) noexcept
		{
			while (0 < count)
			{
				if (*pSrc == ch)
				{
					return pSrc;
				}

				--count;
				++pSrc;
			}

			return nullptr;
		}

	public:

		constexpr StringView() noexcept
			: m_data(nullptr)
			, m_length(0) {}

		constexpr StringView(const StringView&) noexcept = default;

		StringView(const std::u32string& text) noexcept
			: m_data(text.data())
			, m_length(text.size()) {}

		constexpr StringView(std::u32string_view sv) noexcept
			: m_data(sv.data())
			, m_length(sv.size()) {}

		constexpr StringView(const value_type* text, const size_type count)
			: m_data(text)
			, m_length(count) {}

		constexpr StringView(const value_type* text)
			: m_data(text)
			, m_length(_length(text)) {}

		constexpr StringView& operator =(const StringView&) noexcept = default;

		[[nodiscard]] constexpr const_iterator begin() const noexcept { return cbegin(); }

		[[nodiscard]] constexpr const_iterator end() const noexcept { return cend(); }

		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return m_data; }

		[[nodiscard]] constexpr const_iterator cend() const noexcept { return m_data + m_length; }

		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(cend()); }

		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] constexpr const_reference operator[](const size_type index) const { return m_data[index]; }

		[[nodiscard]] constexpr const_reference at(const size_type index) const
		{
			if (index >= m_length)
			{
				throw std::out_of_range("StringView::at() index out of range");
			}

			return m_data[index];
		}

		[[nodiscard]] constexpr const_reference front() const
		{
			assert(!empty() && "cannot call StringView::front() on empty StringView");

			return m_data[0];
		}

		[[nodiscard]] constexpr const_reference back() const
		{
			assert(!empty() && "cannot call StringView::back() on empty StringView");

			return m_data[m_length - 1];
		}

		[[nodiscard]] constexpr const_pointer data() const noexcept { return m_data; }

		[[nodiscard]] constexpr size_type size() const noexcept { return m_length; }

		[[nodiscard]] constexpr size_type size_bytes() const noexcept { return m_length * sizeof(value_type); }

		[[nodiscard]] constexpr size_type length() const noexcept { return m_length; }

		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return m_length == 0; }

		[[nodiscard]] constexpr bool isEmpty() const noexcept { return m_length == 0; }

		[[nodiscard]] explicit constexpr operator bool() const noexcept
		{
			return (m_length != 0);
		}

		constexpr void remove_prefix(const size_type n) noexcept
		{
			assert(n <= m_length);

			m_data += n;
			
			m_length -= n;
		}

		constexpr void remove_suffix(const size_type n) noexcept
		{
			assert(n <= m_length);

			m_length -= n;
		}

		constexpr void swap(StringView& other) noexcept
		{
			const StringView tmp(other);

			other = *this;

			*this = tmp;
		}

		constexpr void clear() noexcept
		{
			m_data = nullptr;

			m_length = 0;
		}

		[[nodiscard]] std::u32string to_string() const
		{
			return std::u32string(begin(), end());
		}

		[[nodiscard]] explicit operator std::u32string() const
		{
			return to_string();
		}

		size_type copy(value_type* dst, const size_type n, const size_type pos = 0) const
		{
			if (pos > m_length)
			{
				throw std::out_of_range("StringView::copy()");
			}

			const size_type len = std::min(n, m_length - pos);

			const value_type* src = m_data + pos;

			::memcpy(dst, src, len * sizeof(value_type));

			return len;
		}

		[[nodiscard]] constexpr StringView substr(const size_type pos = 0, const size_type n = npos) const
		{
			if (pos > m_length)
			{
				throw std::out_of_range("BasicStringView::substr()");
			}

			return StringView(m_data + pos, std::min(n, m_length - pos));
		}

		[[nodiscard]] constexpr int32 compare(const StringView sv) const noexcept
		{
			const int32 result = _compare(data(), sv.data(), std::min(size(), sv.size()));

			if (result != 0)
			{
				return result;
			}

			if (size() == sv.size())
			{
				return 0;
			}

			return (size() < sv.size()) ? -1 : 1;
		}

		[[nodiscard]] constexpr int32 compare(const size_type pos1, const size_type n1, const StringView sv) const noexcept
		{
			return substr(pos1, n1).compare(sv);
		}

		[[nodiscard]] constexpr int32 compare(const size_type pos1, const size_type n1, const StringView sv, const size_type pos2, const size_type n2) const noexcept
		{
			return substr(pos1, n1).compare(sv.substr(pos2, n2));
		}

		[[nodiscard]] constexpr int32 compare(const value_type* str) const noexcept
		{
			return compare(StringView(str));
		}

		[[nodiscard]] constexpr int32 compare(const size_type pos1, const size_type n1, const value_type* str) const noexcept
		{
			return substr(pos1, n1).compare(StringView(str));
		}

		[[nodiscard]] constexpr int32 compare(const size_type pos1, const size_type n1, const value_type* str, const size_type n2) const noexcept
		{
			return substr(pos1, n1).compare(StringView(str, n2));
		}

		[[nodiscard]] constexpr bool starts_with(const value_type ch) const
		{
			return !empty() && front() == ch;
		}

		[[nodiscard]] constexpr bool starts_with(const StringView text) const
		{
			return m_length >= text.m_length && _compare(m_data, text.m_data, text.m_length) == 0;
		}

		[[nodiscard]] bool ends_with(const value_type ch) const
		{
			return !empty() && back() == ch;
		}

		[[nodiscard]] constexpr bool ends_with(const StringView text) const
		{
			return m_length >= text.m_length && _compare(m_data + m_length - text.m_length, text.m_data, text.m_length) == 0;
		}

		[[nodiscard]] constexpr size_type indexOf(const StringView str, const size_type pos = 0) const noexcept
		{
			return indexOf(str.m_data, pos, str.m_length);
		}

		[[nodiscard]] constexpr size_type indexOf(const value_type ch, const size_type pos = 0) const noexcept
		{
			size_type result = npos;

			if (pos < m_length)
			{
				const size_type n = m_length - pos;

				if (const value_type* p = _find(m_data + pos, n, ch))
				{
					result = p - m_data;
				}
			}

			return result;
		}

		[[nodiscard]] constexpr size_type indexOf(const value_type* s, size_type pos, const size_type count) const noexcept
		{
			if (count == 0)
			{
				return pos <= m_length ? pos : npos;
			}

			if (count <= m_length)
			{
				for (; pos <= m_length - count; ++pos)
				{
					if ((m_data[pos] == s[0]) && _compare(m_data + pos + 1, s + 1, count - 1) == 0)
					{
						return pos;
					}
				}
			}

			return npos;
		}

		[[nodiscard]] constexpr size_type indexOf(const value_type* s, const size_type pos = 0) const noexcept
		{
			return indexOf(s, pos, _length(s));
		}

		[[nodiscard]] constexpr size_type lastIndexOf(const StringView str, const size_type pos = npos) const noexcept
		{
			return lastIndexOf(str.m_data, pos, str.m_length);
		}

		[[nodiscard]] constexpr size_type lastIndexOf(const value_type ch, const size_type pos = npos) const noexcept
		{
			size_type size = m_length;

			if (size > 0)
			{
				if (--size > pos)
				{
					size = pos;
				}

				for (++size; size-- > 0; )
				{
					if (m_data[size] == ch)
					{
						return size;
					}
				}
			}

			return npos;
		}

		[[nodiscard]] constexpr size_type lastIndexOf(const value_type* s, size_type pos, const size_type count) const noexcept
		{
			if (count <= m_length)
			{
				pos = std::min(size_type(m_length - count), pos);

				do
				{
					if (_compare(m_data + pos, s, count) == 0)
					{
						return pos;
					}

				} while (pos-- > 0);
			}

			return npos;
		}

		[[nodiscard]] constexpr size_type lastIndexOf(const value_type* s, const size_type pos = npos) const noexcept
		{
			return lastIndexOf(s, pos, _length(s));
		}
	};


//////////////////////////////////////////////////
//
//	Literals
//
//////////////////////////////////////////////////

	inline namespace literals
	{
		inline namespace stringview_literals
		{
			[[nodiscard]] constexpr StringView operator ""_sv(const char32_t* text, const size_t length) noexcept
			{
				return StringView(text, length);
			}
		}
	}


//////////////////////////////////////////////////
//
//	Comparison Functions
//
//////////////////////////////////////////////////

	[[nodiscard]] inline constexpr bool operator ==(const StringView x, const StringView y) noexcept
	{
		return x.compare(y) == 0;
	}

	[[nodiscard]] inline constexpr bool operator !=(const StringView x, const StringView y) noexcept
	{
		return !(x == y);
	}

	[[nodiscard]] inline constexpr bool operator <(const StringView x, const StringView y) noexcept
	{
		return x.compare(y) < 0;
	}

	[[nodiscard]] inline constexpr bool operator <=(const StringView x, const StringView y) noexcept
	{
		return x.compare(y) <= 0;
	}

	[[nodiscard]] inline constexpr bool operator >(const StringView x, const StringView y) noexcept
	{
		return x.compare(y) > 0;
	}

	[[nodiscard]] inline constexpr bool operator >=(const StringView x, const StringView y) noexcept
	{
		return x.compare(y) >= 0;
	}
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const StringView& value);

	std::ostream& operator <<(std::ostream& output, const StringView& value);

	std::wostream& operator <<(std::wostream& output, const StringView& value);
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <>
	struct hash<s3d::StringView>
	{
		[[nodiscard]] size_t operator()(const s3d::StringView& value) const noexcept
		{
			return s3d::Hash::FNV1a(s3d::ByteArrayView(value.data(), value.size_bytes()));
		}
	};
}

//////////////////////////////////////////////////
//
//	Swap
//
//////////////////////////////////////////////////

namespace std
{
	template <class Type>
	inline void swap(s3d::StringView& a, s3d::StringView& b) noexcept
	{
		a.swap(b);
	}
}
