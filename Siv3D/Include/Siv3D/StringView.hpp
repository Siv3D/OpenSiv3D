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
# include "Fwd.hpp"
# include "Hash.hpp"

namespace s3d
{
	template <class CharType>
	class BasicStringView
	{
	public:

		using traits_type				= std::char_traits<CharType>;
		using value_type				= CharType;
		using pointer					= const CharType*;
		using const_pointer				= const CharType*;
		using reference					= const CharType&;
		using const_reference			= const CharType&;
		using const_iterator			= const_pointer;
		using iterator					= const_iterator;
		using const_reverse_iterator	= std::reverse_iterator<const_iterator>;
		using reverse_iterator			= const_reverse_iterator;
		using size_type					= size_t;
		using difference_type			= ptrdiff_t;

		static constexpr const size_type npos = size_type(-1);

	private:

		const value_type* m_ptr = nullptr;

		size_type m_length = 0;

	public:

		constexpr BasicStringView() noexcept
			: m_ptr(nullptr)
			, m_length(0) {}

		constexpr BasicStringView(const BasicStringView&) noexcept = default;

		template<class Allocator>
		BasicStringView(const std::basic_string<value_type, traits_type, Allocator>& str) noexcept
			: m_ptr(str.data())
			, m_length(str.size()) {}

		constexpr BasicStringView(const value_type* str, size_type count)
			: m_ptr(str)
			, m_length(count) {}

		BasicStringView(const value_type* str)
			: m_ptr(str)
			, m_length(traits_type::length(str)) {}

		BasicStringView& operator =(const BasicStringView&) noexcept = default;

		constexpr const_iterator begin() const noexcept { return cbegin(); }

		constexpr const_iterator end() const noexcept { return cend(); }

		constexpr const_iterator cbegin() const noexcept { return m_ptr; }

		constexpr const_iterator cend() const noexcept { return m_ptr + m_length; }

		constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(cend()); }

		constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(cbegin()); }

		constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		constexpr const_reference operator[](const size_type index) const { return m_ptr[index]; }

		constexpr const_reference at(const size_type index) const
		{
			return index >= size()
				? (throw std::out_of_range("BasicStringView::at() index out of range"), m_ptr[0])
				: m_ptr[index];
		}

		constexpr const_reference front() const
		{
			return assert(!empty() && "BasicStringView::front() string is empty"), m_ptr[0];
		}

		constexpr const_reference back() const
		{
			return assert(!empty() && "string_view::back() string is empty"), m_ptr[m_length - 1];
		}

		constexpr const_pointer data() const noexcept { return m_ptr; }

		constexpr size_type size() const noexcept { return m_length; }

		constexpr size_type size_bytes() const noexcept { return m_length * sizeof(value_type); }

		constexpr size_type length() const noexcept { return m_length; }

		constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		constexpr bool empty() const noexcept { return m_length == 0; }

		constexpr bool isEmpty() const noexcept { return m_length == 0; }

		/// <summary>
		/// 文字列に要素が含まれているかを示します。
		/// </summary>
		explicit constexpr operator bool() const noexcept
		{
			return m_length != 0;
		}

		constexpr void remove_prefix(const size_type n) noexcept
		{
			assert(n <= size() && "BasicStringView::remove_prefix() can't remove more than size()");
			m_ptr += n;
			m_length -= n;
		}

		constexpr void remove_suffix(const size_type n) noexcept
		{
			assert(n <= size() && "BasicStringView::remove_suffix() can't remove more than size()");
			m_length -= n;
		}

		constexpr void swap(BasicStringView& other) noexcept
		{
			const value_type* ptr = m_ptr;
			m_ptr = other.m_ptr;
			other.m_ptr = ptr;

			const size_type length = m_length;
			m_length = other.m_length;
			other.m_length = length;
		}

		constexpr void clear() noexcept
		{
			m_ptr = nullptr;
			m_length = 0;
		}

		std::basic_string<CharType> to_string() const
		{
			return std::basic_string<CharType>(begin(), end());
		}

		explicit operator std::basic_string<CharType>() const
		{
			return std::basic_string<CharType>(begin(), end());
		}

		size_type copy(const value_type* str, const size_type n, const size_type pos = 0) const
		{
			if (pos > size())
			{
				throw std::out_of_range("BasicStringView::copy()");
			}

			const size_type len = std::min(n, m_length - pos);

			for (auto it = m_ptr + pos, end = it + len; it != end;)
			{
				*str++ = *it++;
			}

			return len;
		}

		constexpr BasicStringView substr(const size_type pos = 0, const size_type n = npos) const
		{
			return pos > size()
				? throw std::out_of_range("BasicStringView::substr()")
				: BasicStringView(data() + pos, std::min(n, size() - pos));
		}

		constexpr int32 compare(const BasicStringView sv) const noexcept
		{
			int32 result = traits_type::compare(data(), sv.data(), std::min(size(), sv.size()));
			
			if (result == 0)
			{
				result = size() == sv.size() ? 0 : (size() < sv.size() ? -1 : 1);
			}

			return result;
		}

		constexpr int32 compare(const size_type pos1, const size_type n1, const BasicStringView sv) const noexcept
		{
			return substr(pos1, n1).compare(sv);
		}

		constexpr int32 compare(const size_type pos1, const size_type n1, const BasicStringView sv, const size_type pos2, const size_type n2) const noexcept
		{
			return substr(pos1, n1).compare(sv.substr(pos2, n2));
		}

		constexpr  int32 compare(const value_type* str) const noexcept
		{
			return compare(BasicStringView(str));
		}

		constexpr int32 compare(const size_type pos1, const size_type n1, const value_type* str) const noexcept
		{
			return substr(pos1, n1).compare(BasicStringView(str));
		}

		constexpr int32 compare(const size_type pos1, const size_type n1, const value_type* str, const size_type n2) const noexcept
		{
			return substr(pos1, n1).compare(BasicStringView(str, n2));
		}

		constexpr bool starts_with(const CharType ch) const
		{
			return !empty() && front() == ch;
		}

		constexpr bool starts_with(const BasicStringView str) const
		{
			return m_length >= str.m_length && traits_type::compare(m_ptr, str.m_ptr, str.m_length) == 0;
		}

		constexpr bool ends_with(const CharType ch) const
		{
			return !empty() && back() == ch;
		}

		constexpr bool ends_with(const BasicStringView str) const
		{
			return m_length >= str.m_length && traits_type::compare(m_ptr + m_length - str.m_length, str.m_ptr, str.m_length) == 0;
		}

		constexpr size_type indexOf(const BasicStringView str, const size_type pos = 0) const noexcept
		{
			return indexOf(str.m_ptr, pos, str.m_length);
		}

		constexpr size_type indexOf(const CharType ch, const size_type pos = 0) const noexcept
		{
			size_type result = npos;

			if (pos < m_length)
			{
				const size_type n = m_length - pos;
				const CharType* p = traits_type::find(m_ptr + pos, n, ch);
				
				if (p)
				{
					result = p - m_ptr;
				}
			}

			return result;
		}

		constexpr size_type indexOf(const CharType* s, size_type pos, const size_type count) const noexcept
		{
			if (count == 0)
			{
				return pos <= m_length ? pos : npos;
			}

			if (count <= m_length)
			{
				for (; pos <= m_length - count; ++pos)
				{
					if (traits_type::eq(m_ptr[pos], s[0]) && traits_type::compare(m_ptr + pos + 1, s + 1, count - 1) == 0)
					{
						return pos;
					}
				}
			}

			return npos;
		}

		constexpr size_type indexOf(const CharType* s, const size_type pos = 0) const noexcept
		{
			return indexOf(s, pos, traits_type::length(s));
		}

		constexpr size_type lastIndexOf(const BasicStringView str, const size_type pos = npos) const noexcept
		{
			return lastIndexOf(str.m_ptr, pos, str.m_length);
		}

		constexpr size_type lastIndexOf(const CharType ch, const size_type pos = npos) const noexcept
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
					if (traits_type::eq(m_ptr[size], ch))
					{
						return size;
					}
				}
			}

			return npos;
		}
		
		constexpr size_type lastIndexOf(const CharType* s, size_type pos, const size_type count) const noexcept
		{
			if (count <= m_length)
			{
				pos = std::min(size_type(m_length - count), pos);

				do
				{
					if (traits_type::compare(m_ptr + pos, s, count) == 0)
					{
						return pos;
					}

				} while (pos-- > 0);
			}

			return npos;
		}

		constexpr size_type lastIndexOf(const CharType* s, const size_type pos = npos) const noexcept
		{
			return lastIndexOf(s, pos, traits_type::length(s));
		}

		// indexOfAny

		// lastIndexOfAny

		// indexNotOfAny

		// lastIndexNotOfAny
	};

	template <class CharType>
	inline constexpr bool operator ==(const BasicStringView<CharType> x, const BasicStringView<CharType> y) noexcept
	{
		return x.compare(y) == 0;
	}

	template <class CharType>
	inline constexpr bool operator !=(const BasicStringView<CharType> x, const BasicStringView<CharType> y) noexcept
	{
		return !(x == y);
	}

	template <class CharType>
	inline constexpr bool operator <(const BasicStringView<CharType> x, const BasicStringView<CharType> y) noexcept
	{
		return x.compare(y) < 0;
	}

	template <class CharType>
	inline constexpr bool operator <=(const BasicStringView<CharType> x, const BasicStringView<CharType> y) noexcept
	{
		return x.compare(y) <= 0;
	}

	template <class CharType>
	inline constexpr bool operator >(const BasicStringView<CharType> x, const BasicStringView<CharType> y) noexcept
	{
		return x.compare(y) > 0;
	}

	template <class CharType>
	inline constexpr bool operator >=(const BasicStringView<CharType> x, const BasicStringView<CharType> y) noexcept
	{
		return x.compare(y) >= 0;
	}

	inline std::ostream& operator <<(std::ostream& os, const BasicStringView<char>& str)
	{
		return os.write(str.data(), str.length());
	}

	inline std::wostream& operator <<(std::wostream& os, const BasicStringView<wchar>& str)
	{
		return os.write(str.data(), str.length());
	}

	using CStringView		= BasicStringView<char>;
	using UTF8StringView	= BasicStringView<char>;
	using StringView		= BasicStringView<wchar>;
}

namespace std
{
	template <class CharType>
	struct hash<s3d::BasicStringView<CharType>>
	{
		size_t operator()(const s3d::BasicStringView<CharType>& keyVal) const
		{
			return s3d::Hash::FNV1a(keyVal.data(), keyVal.length() * sizeof(CharType));
		}
	};
}
