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
# include "Siv3D/String.hpp"

namespace s3d
{
	String& String::assign(const String& text)
	{
		m_string.assign(text.m_string);

		return *this;
	}

	String& String::assign(const string_type& text)
	{
		m_string.assign(text);

		return *this;
	}

	String& String::assign(const value_type* str)
	{
		m_string.assign(str);

		return *this;
	}

	String& String::assign(const size_t count, const value_type ch)
	{
		m_string.assign(count, ch);

		return *this;
	}

	String& String::assign(String&& text) noexcept
	{
		m_string.assign(std::move(text.m_string));

		return *this;
	}

	String& String::assign(string_type&& text) noexcept
	{
		m_string.assign(std::move(text));

		return *this;
	}

	String& String::assign(std::initializer_list<value_type> ilist)
	{
		m_string.assign(ilist);

		return *this;
	}

	String& String::assign(const StringView view)
	{
		m_string.assign(view.begin(), view.end());

		return *this;
	}

	String& String::append(const String& text)
	{
		m_string.append(text.m_string);

		return *this;
	}

	String& String::append(const string_type& text)
	{
		m_string.append(text);

		return *this;
	}

	String& String::append(const value_type* text)
	{
		m_string.append(text);

		return *this;
	}

	String& String::append(const value_type* text, const size_t count)
	{
		m_string.append(text, count);

		return *this;
	}

	String& String::append(std::initializer_list<value_type> ilist)
	{
		m_string.append(ilist);

		return *this;
	}

	String& String::append(const size_t count, const value_type ch)
	{
		m_string.append(count, ch);

		return *this;
	}

	String& String::append(const StringView view)
	{
		m_string.append(view.begin(), view.end());

		return *this;
	}

	String& String::insert(const size_t offset, const String& str)
	{
		m_string.insert(offset, str.m_string);

		return *this;
	}

	String& String::insert(const size_t offset, std::initializer_list<value_type> ilist)
	{
		m_string.insert(offset, ilist);

		return *this;
	}

	String& String::insert(const size_t offset, const value_type* str)
	{
		m_string.insert(offset, str);

		return *this;
	}

	String& String::insert(const size_t offset, const size_t count, const value_type ch)
	{
		m_string.insert(offset, count, ch);

		return *this;
	}

	String::iterator String::insert(const_iterator where, const value_type ch)
	{
		return m_string.insert(where, ch);
	}

	void String::insert(const_iterator where, const size_t count, const value_type ch)
	{
		m_string.insert(where, count, ch);
	}

	String& String::erase(const size_t offset, const size_t count)
	{
		m_string.erase(offset, count);

		return *this;
	}

	String::iterator String::erase(const_iterator where)
	{
		return m_string.erase(where);
	}

	String::iterator String::erase(const_iterator first, const_iterator last)
	{
		return m_string.erase(first, last);
	}

	void String::clear() noexcept
	{
		m_string.clear();
	}

	void String::shrink_to_fit()
	{ 
		m_string.shrink_to_fit();
	}

	void String::release()
	{
		clear();
		
		shrink_to_fit();
	}

	void String::resize(const size_t newSize)
	{
		m_string.resize(newSize);
	}

	void String::resize(const size_t newSize, const value_type ch)
	{
		m_string.resize(newSize, ch);
	}

	void String::reserve(const size_t newCapacity)
	{
		m_string.reserve(newCapacity);
	}

	String String::substr(const size_t offset, const size_t count) const
	{
		return m_string.substr(offset, count);
	}

	size_t String::indexOf(const String& text, const size_t offset) const noexcept
	{
		return m_string.find(text.data(), offset, text.length());
	}

	size_t String::indexOf(const value_type* text, const size_t offset) const
	{
		return m_string.find(text, offset, traits_type::length(text));
	}

	size_t String::indexOf(const value_type ch, const size_t offset) const
	{
		return m_string.find(ch, offset);
	}

	size_t String::indexOfNot(const value_type ch, const size_t offset) const
	{
		return m_string.find_first_not_of(ch, offset);
	}

	size_t String::lastIndexOf(const String& text, const size_t offset) const
	{
		return m_string.rfind(text.data(), offset, text.length());
	}

	size_t String::lastIndexOf(const value_type* text, const size_t offset) const
	{
		return m_string.rfind(text, offset, traits_type::length(text));
	}

	size_t String::lastIndexOf(const value_type ch, const size_t offset) const
	{
		return m_string.rfind(ch, offset);
	}

	size_t String::lastIndexNotOf(const value_type ch, const size_t offset) const
	{
		return m_string.find_last_not_of(ch, offset);
	}

	size_t String::indexOfAny(const String& anyof, const size_t offset) const
	{
		return m_string.find_first_of(anyof.data(), offset, anyof.length());
	}

	size_t String::indexOfAny(const value_type* anyof, const size_t offset) const
	{
		return m_string.find_first_of(anyof, offset, traits_type::length(anyof));
	}

	size_t String::lastIndexOfAny(const String& anyof, const size_t offset) const
	{
		return m_string.find_last_of(anyof.data(), offset, anyof.length());
	}

	size_t String::lastIndexOfAny(const value_type* anyof, const size_t offset) const
	{
		return m_string.find_last_of(anyof, offset, traits_type::length(anyof));
	}

	size_t String::indexNotOfAny(const String& anyof, const size_t offset) const
	{
		return m_string.find_first_not_of(anyof.data(), offset, anyof.length());
	}

	size_t String::indexNotOfAny(const value_type* anyof, const size_t offset) const
	{
		return m_string.find_first_not_of(anyof, offset, traits_type::length(anyof));
	}

	size_t String::lastIndexNotOfAny(const String& anyof, const size_t offset) const
	{
		return m_string.find_last_not_of(anyof.data(), offset, anyof.length());
	}

	size_t String::lastIndexNotOfAny(const value_type* anyof, const size_t offset) const
	{
		return m_string.find_last_not_of(anyof, offset, traits_type::length(anyof));
	}

	int32 String::case_insensitive_compare(const StringView view) const noexcept
	{
		auto first1 = begin(), last1 = end();
		auto first2 = view.begin(), last2 = view.end();

		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			const int32 c = CaseInsensitiveCompare(*first1, *first2);

			if (c != 0)
			{
				return c;
			}
		}

		if ((first1 == last1) && (first2 != last2))
		{
			return -1;
		}
		else if ((first1 != last1) && (first2 == last2))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	bool String::case_insensitive_equals(const StringView view) const noexcept
	{
		if (length() != view.length())
		{
			return false;
		}

		auto first1 = begin(), last1 = end();
		auto first2 = view.begin(), last2 = view.end();

		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			const int32 c = CaseInsensitiveCompare(*first1, *first2);

			if (c != 0)
			{
				return false;
			}
		}

		return true;
	}
}
