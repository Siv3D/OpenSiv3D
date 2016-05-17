//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cassert>
# include "Fwd.hpp"
# include "String.hpp"

namespace s3d
{
	class StringView
	{
	public:

		using value_type				= wchar;
		using traits_type				= std::char_traits<wchar>;
		using pointer					= const wchar*;
		using const_pointer				= const wchar*;
		using reference					= const wchar&;
		using const_reference			= const wchar&;
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

		constexpr StringView() noexcept
			: m_ptr(nullptr)
			, m_length(0) {}

		constexpr StringView(const StringView&) noexcept = default;

		StringView& operator=(const StringView&) noexcept = default;

		template<class Allocator>
		StringView(const std::basic_string<value_type, traits_type, Allocator>& str) noexcept
			: m_ptr(str.data())
			, m_length(str.size()) {}

		StringView(const String& str) noexcept
			: m_ptr(str.data())
			, m_length(str.size()) {}

		constexpr StringView(const value_type* str, size_type length)
			: m_ptr(str)
			, m_length(length) {}

        StringView(const value_type* str)
            : m_ptr(str)
            , m_length(traits_type::length(str)) {}

        constexpr StringView(std::nullptr_t) noexcept {}

		constexpr StringView(std::nullptr_t, size_type) noexcept {}

		constexpr const_iterator begin() const noexcept { return cbegin(); }

		constexpr const_iterator end() const noexcept { return cend(); }

		constexpr const_iterator cbegin() const noexcept { return m_ptr; }

		constexpr const_iterator cend() const noexcept { return m_ptr + m_length; }

		const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(cend()); }

		const_reverse_iterator rend() const noexcept { return const_reverse_iterator(cbegin()); }

		const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		constexpr size_type size() const noexcept { return m_length; }

		constexpr size_type size_bytes() const noexcept { return m_length * sizeof(value_type); }

		constexpr size_type length() const noexcept { return m_length; }

		constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		constexpr bool empty() const noexcept { return m_length == 0; }

		constexpr bool isEmpty() const noexcept { return m_length == 0; }

		constexpr const_reference operator[] (size_type index) const { return m_ptr[index]; }

		constexpr const_reference at(size_type index) const
		{
			return index >= size()
				? (throw std::out_of_range("StringView::at() index out of range"), m_ptr[0])
				: m_ptr[index];
		}

		constexpr const_reference front() const
		{
			return assert(!empty() && "StringView::front() string is empty"), m_ptr[0];
		}

		constexpr const_reference back() const
		{
			return assert(!empty() && "string_view::back() string is empty"), m_ptr[m_length - 1];
		}

		constexpr const_pointer data() const noexcept { return m_ptr; }

		S3D_CONSTEXPR_CPP14 void clear() noexcept
		{
			m_ptr = nullptr;
			m_length = 0;
		}

		S3D_CONSTEXPR_CPP14 void remove_prefix(size_type n) noexcept
		{
			assert(n <= size() && "StringView::remove_prefix() can't remove more than size()");
			m_ptr	 += n;
			m_length -= n;
		}

		S3D_CONSTEXPR_CPP14 void remove_suffix(size_type n) noexcept
		{
			assert(n <= size() && "StringView::remove_suffix() can't remove more than size()");
			m_length -= n;
		}

		S3D_CONSTEXPR_CPP14 void swap(StringView& other) noexcept
		{
            const value_type* ptr = m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = ptr;
            
            const size_type length = m_length;
            m_length = other.m_length;
            other.m_length = length;
		}

		template <class Allocator>
		explicit operator std::basic_string<value_type, traits_type, Allocator>() const
		{
			return std::basic_string<value_type, traits_type, Allocator>(begin(), end());
		}

		explicit operator String() const
		{
			return String(begin(), end());
		}

		size_type copy(value_type* str, size_type n, size_type pos = 0) const
		{
			if (pos > size())
			{
				throw std::out_of_range("StringView::copy()");
			}

			const size_type len = std::min(n, m_length - pos);

			for (auto it = m_ptr + pos, end = it + len; it != end;)
			{
				*str++ = *it++;
			}

			return len;
		}

		constexpr StringView substr(size_type pos = 0, size_type n = npos) const
		{
			return pos > size()
				? throw std::out_of_range("StringView::substr()")
				: StringView(data() + pos, std::min(n, size() - pos));
		}

        int32 compare(StringView sv) const noexcept
		{
			int32 result = traits_type::compare(data(), sv.data(), std::min(size(), sv.size()));
			
			if (result == 0)
			{
				result = size() == sv.size() ? 0 : (size() < sv.size() ? -1 : 1);
			}

			return result;
		}

        int32 compare(size_type pos1, size_type n1, StringView sv) const
		{
			return substr(pos1, n1).compare(sv);
		}

        int32 compare(size_type pos1, size_type n1,	StringView sv, size_type pos2, size_type n2) const
		{
			return substr(pos1, n1).compare(sv.substr(pos2, n2));
		}

        int32 compare(const value_type* str) const
		{
			return compare(StringView(str));
		}

        int32 compare(size_type pos1, size_type n1, const value_type* str) const
		{
			return substr(pos1, n1).compare(StringView(str));
		}

        int32 compare(size_type pos1, size_type n1, const value_type* str, size_type n2) const
		{
			return substr(pos1, n1).compare(StringView(str, n2));
		}

		constexpr bool starts_with(wchar ch) const { return !empty() && front() == ch; }

		bool starts_with(StringView str) const
		{
			return m_length >= str.m_length && traits_type::compare(m_ptr, str.m_ptr, str.m_length) == 0;
		}

		constexpr bool endsWith(wchar ch) const { return !empty() && back() == ch; }

		bool endsWith(StringView str) const
		{
			return m_length >= str.m_length && traits_type::compare(m_ptr + m_length - str.m_length, str.m_ptr, str.m_length) == 0;
		}

		size_type indexOf(StringView str) const
		{
			const_iterator iter = std::search(cbegin(), cend(), str.cbegin(), str.cend());

			return (iter == cend()) ? npos : std::distance(cbegin(), iter);
		}

		size_type indexOf(wchar ch) const noexcept
		{
			const_iterator iter = std::find(cbegin(), cend(), ch);

			return (iter == cend()) ? npos : std::distance(cbegin(), iter);
		}

		size_type lastIndexOf(StringView str) const
		{
			const_reverse_iterator iter = std::search(crbegin(), crend(), str.crbegin(), str.crend());

			return (iter == crend()) ? npos : reverse_distance(crbegin(), iter);
		}

		size_type lastIndexOf(wchar ch) const noexcept
		{
			const_reverse_iterator iter = std::find(crbegin(), crend(), ch);

			return (iter == crend()) ? npos : reverse_distance(crbegin(), iter);
		}

		size_type indexOfAny(wchar ch) const noexcept { return indexOf(ch); }

		size_type lastIndexOfAny(wchar ch) const noexcept { return lastIndexOf(ch); }

		size_type indexOfAny(StringView anyof) const
		{
			const_iterator iter = std::find_first_of(cbegin(), cend(), anyof.cbegin(), anyof.cend());

			return (iter == cend()) ? npos : std::distance(cbegin(), iter);
		}

		size_type lastIndexOfAny(StringView anyof) const
		{
			const_reverse_iterator iter = std::find_first_of(crbegin(), crend(), anyof.cbegin(), anyof.cend());

			return (iter == crend()) ? npos : reverse_distance(crbegin(), iter);
		}

		size_type indexNotOfAny(StringView anyof) const
		{
			const_iterator iter = find_not_of(cbegin(), cend(), anyof);

			return (iter == cend()) ? npos : std::distance(cbegin(), iter);
		}

		size_type indexNotOf(wchar ch) const noexcept
		{
			for (const_iterator iter = cbegin(); iter != cend(); ++iter)
			{
				if (ch != *iter)
				{
					return std::distance(cbegin(), iter);
				}
			}

			return npos;
		}

		size_type lastIndexNotOfAny(StringView anyof) const
		{
			const_reverse_iterator iter = find_not_of(crbegin(), crend(), anyof);

			return (iter == crend()) ? npos : reverse_distance(crbegin(), iter);
		}

		size_type lastIndexNotOf(wchar ch) const noexcept
		{
			for (const_reverse_iterator iter = crbegin(); iter != crend(); ++iter)
			{
				if (ch != *iter)
				{
					return reverse_distance(crbegin(), iter);
				}
			}

			return npos;
		}

		String str() const
		{
			return String(begin(), end());
		}

	private:

		size_type reverse_distance(const_reverse_iterator first, const_reverse_iterator last) const
		{
			return m_length - 1 - std::distance(first, last);
		}

		template <class Iterator>
		Iterator find_not_of(Iterator first, Iterator last, StringView s) const
		{
			for (; first != last; ++first)
			{
				if (!traits_type::find(s.m_ptr, s.m_length, *first))
				{
					return first;
				}
			}

			return last;
		}
	};

	inline bool operator == (StringView x, StringView y)
	{
		if (x.size() != y.size()) return false;
		return x.compare(y) == 0;
	}

	inline bool operator == (StringView x, const String& y)
	{
		return x == StringView(y);
	}

	inline bool operator == (const String& x, StringView y)
	{
		return StringView(x) == y;
	}

	inline bool operator == (StringView x, const wchar* y)
	{
		return x == StringView(y);
	}

	inline bool operator == (const wchar* x, StringView y)
	{
		return StringView(x) == y;
	}

	//  Inequality	
	inline bool operator != (StringView x, StringView y)
	{
		if (x.size() != y.size()) return true;
		return x.compare(y) != 0;
	}

	inline bool operator != (StringView x, const String& y)
	{
		return x != StringView(y);
	}

	inline bool operator != (const String& x, StringView y)
	{
		return StringView(x) != y;
	}

	inline bool operator != (StringView x, const wchar* y)
	{
		return x != StringView(y);
	}

	inline bool operator != (const wchar* x, StringView y)
	{
		return StringView(x) != y;
	}

	//  Less than	
	inline bool operator < (StringView x, StringView y)
	{
		return x.compare(y) < 0;
	}

	inline bool operator < (StringView x, const String& y)
	{
		return x < StringView(y);
	}

	inline bool operator < (const String& x, StringView y)
	{
		return StringView(x) < y;
	}

	inline bool operator < (StringView x, const wchar* y)
	{
		return x < StringView(y);
	}

	inline bool operator < (const wchar* x, StringView y)
	{
		return StringView(x) < y;
	}

	//  Greater than	
	inline bool operator > (StringView x, StringView y)
	{
		return x.compare(y) > 0;
	}

	inline bool operator > (StringView x, const String& y)
	{
		return x > StringView(y);
	}

	inline bool operator > (const String& x, StringView y)
	{
		return StringView(x) > y;
	}

	inline bool operator > (StringView x, const wchar* y)
	{
		return x > StringView(y);
	}

	inline bool operator > (const wchar* x, StringView y)
	{
		return StringView(x) > y;
	}

	//  Less than or equal to	
	inline bool operator <=(StringView x, StringView y)
	{
		return x.compare(y) <= 0;
	}

	inline bool operator <= (StringView x, const String& y)
	{
		return x <= StringView(y);
	}

	inline bool operator <= (const String& x, StringView y)
	{
		return StringView(x) <= y;
	}

	inline bool operator <= (StringView x, const wchar* y)
	{
		return x <= StringView(y);
	}

	inline bool operator <= (const wchar* x, StringView y)
	{
		return StringView(x) <= y;
	}

	//  Greater than or equal to	
	inline bool operator >= (StringView x, StringView y)
	{
		return x.compare(y) >= 0;
	}

	inline bool operator >= (StringView x, const String& y)
	{
		return x >= StringView(y);
	}

	inline bool operator >= (const String& x, StringView y)
	{
		return StringView(x) >= y;
	}

	inline bool operator >= (StringView x, const wchar* y)
	{
		return x >= StringView(y);
	}

	inline bool operator >= (const wchar* x, StringView y)
	{
		return StringView(x) >= y;
	}

	inline std::wostream& operator << (std::wostream& os, const StringView& str)
	{
		return os << std::wstring(str.begin(), str.end());
	}
}

namespace std
{
	template <>
	struct hash<s3d::StringView>
	{
		size_t operator () (const s3d::StringView& keyVal) const
		{
			return hash<s3d::String>()(keyVal.str());
		}
	};
}
