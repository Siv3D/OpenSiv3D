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
	inline String::String()
		: m_string()
	{

	}

	inline String::String(const String& other)
		: m_string(other.m_string)
	{

	}

	inline String::String(const string_type& s)
		: m_string(s)
	{

	}

	inline String::String(const String& other, const size_type pos)
		: m_string(other.m_string, pos)
	{

	}

	inline String::String(const String& other, const size_type pos, const size_type count)
		: m_string(other.m_string, pos, count)
	{

	}

	inline String::String(const value_type* s)
		: m_string(s)
	{

	}

	inline String::String(const value_type* s, const size_type count)
		: m_string(s, count)
	{

	}

	inline String::String(std::initializer_list<value_type> ilist)
		: m_string(ilist)
	{

	}

	inline String::String(const size_t count, const value_type ch)
		: m_string(count, ch)
	{

	}

	template <class Iterator>
	inline String::String(Iterator first, Iterator last)
		: m_string(first, last)
	{
	
	}

	inline String::String(String&& other) noexcept
		: m_string(std::move(other.m_string))
	{

	}

	inline String::String(string_type&& s) noexcept
		: m_string(std::move(s))
	{

	}

	template <class StringViewIsh, class>
	inline String::String(const StringViewIsh& s)
		: m_string(s.data(), s.size())
	{
	
	}

	inline String::operator StringView() const noexcept
	{
		return StringView(m_string.data(), m_string.size());
	}

	inline String& String::operator =(const String& other)
	{
		return assign(other);
	}

	inline String& String::operator =(const string_type& s)
	{
		return assign(s);
	}

	inline String& String::operator =(String&& other) noexcept
	{
		return assign(std::move(other));
	}

	inline String& String::operator =(string_type&& s) noexcept
	{
		return assign(std::move(s));
	}

	inline String& String::operator =(const value_type* s)
	{
		return assign(s);
	}

	inline String& String::operator =(std::initializer_list<value_type> ilist)
	{
		return assign(ilist);
	}

	template <class StringViewIsh, class>
	inline String& String::operator =(const StringViewIsh& s)
	{
		return assign(s);
	}

	inline String& String::assign(const String& s)
	{
		m_string.assign(s.m_string);

		return *this;
	}

	inline String& String::assign(const string_type& s)
	{
		m_string.assign(s);

		return *this;
	}

	inline String& String::assign(const value_type* s)
	{
		m_string.assign(s);

		return *this;
	}

	inline String& String::assign(const size_t count, const value_type ch)
	{
		m_string.assign(count, ch);

		return *this;
	}

	inline String& String::assign(String&& s) noexcept
	{
		m_string.assign(std::move(s.m_string));

		return *this;
	}

	inline String& String::assign(string_type&& s) noexcept
	{
		m_string.assign(std::move(s));

		return *this;
	}

	inline String& String::assign(std::initializer_list<value_type> ilist)
	{
		m_string.assign(ilist);

		return *this;
	}

	template <class StringViewIsh, class>
	inline String& String::assign(const StringViewIsh& s)
	{
		m_string.assign(s.data(), s.size());

		return *this;
	}

	template <class Iterator>
	inline String& String::assign(Iterator first, Iterator last)
	{
		m_string.assign(first, last);

		return *this;
	}

	inline String::allocator_type String::get_allocator() const noexcept
	{
		return m_string.get_allocator();
	}

	inline String& String::operator <<(const value_type ch)
	{
		return append(ch);
	}

	inline String& String::operator +=(const String& s)
	{
		return append(s);
	}

	inline String& String::operator +=(const string_type& s)
	{
		return append(s);
	}

	inline String& String::operator +=(const value_type ch)
	{
		return append(ch);
	}

	inline String& String::operator +=(const value_type* s)
	{
		return append(s);
	}

	inline String& String::operator +=(std::initializer_list<value_type> ilist)
	{
		return append(ilist);
	}

	template <class StringViewIsh, class>
	inline String& String::operator +=(const StringViewIsh& s)
	{
		return append(s);
	}

	inline String& String::append(const String& s)
	{
		m_string.append(s.m_string);

		return *this;
	}

	inline String& String::append(const string_type& s)
	{
		m_string.append(s);

		return *this;
	}

	inline String& String::append(const value_type ch)
	{
		m_string.push_back(ch);

		return *this;
	}

	inline String& String::append(const value_type* s)
	{
		m_string.append(s);

		return *this;
	}

	inline String& String::append(const value_type* s, const size_t count)
	{
		m_string.append(s, count);

		return *this;
	}

	inline String& String::append(std::initializer_list<value_type> ilist)
	{
		m_string.append(ilist);

		return *this;
	}

	inline String& String::append(const size_t count, const value_type ch)
	{
		m_string.append(count, ch);

		return *this;
	}

	template <class StringViewIsh, class>
	inline String& String::append(const StringViewIsh& s)
	{
		m_string.append(s.data(), s.size());

		return *this;
	}

	template <class Iterator>
	inline String& String::append(Iterator first, Iterator last)
	{
		m_string.append(first, last);

		return *this;
	}

	inline String& String::insert(const size_t offset, const String& s)
	{
		m_string.insert(offset, s.m_string);

		return *this;
	}

	inline String& String::insert(const size_t offset, std::initializer_list<value_type> ilist)
	{
		m_string.insert(offset, ilist);

		return *this;
	}

	inline String& String::insert(const size_t offset, const value_type* s)
	{
		m_string.insert(offset, s);

		return *this;
	}

	template <class StringViewIsh, class>
	inline String& String::insert(const size_t offset, const StringViewIsh& s)
	{
		m_string.insert(offset, s.data(), s.size());

		return *this;
	}

	inline String& String::insert(const size_t offset, const size_t count, const value_type ch)
	{
		m_string.insert(offset, count, ch);

		return *this;
	}

	inline String::iterator String::insert(const_iterator where, const value_type ch)
	{
		return m_string.insert(where, ch);
	}

	inline String::iterator String::insert(const_iterator where, const size_t count, const value_type ch)
	{
		return m_string.insert(where, count, ch);
	}

	template <class Iterator>
	inline String::iterator String::insert(const_iterator where, Iterator first, Iterator last)
	{
		return m_string.insert(where, first, last);
	}

	template <class Iterator>
	inline String& String::insert(const_iterator first1, const_iterator last1, Iterator first2, Iterator last2)
	{
		m_string.insert(first1, last1, first2, last2);

		return *this;
	}

	inline String& String::erase(const size_t offset, const size_t count)
	{
		m_string.erase(offset, count);

		return *this;
	}

	inline String::iterator String::erase(const_iterator where) noexcept
	{
		return m_string.erase(where);
	}

	inline String::iterator String::erase(const_iterator first, const_iterator last) noexcept
	{
		return m_string.erase(first, last);
	}

	inline void String::clear() noexcept
	{
		m_string.clear();
	}

	inline String::iterator String::begin() noexcept
	{
		return m_string.begin();
	}

	inline String::iterator String::end() noexcept
	{
		return m_string.end();
	}

	inline String::const_iterator String::begin() const noexcept
	{
		return m_string.begin();
	}

	inline String::const_iterator String::end() const noexcept
	{
		return m_string.end();
	}

	inline String::const_iterator String::cbegin() const noexcept
	{
		return m_string.cbegin();
	}

	inline String::const_iterator String::cend() const noexcept
	{
		return m_string.cend();
	}

	inline String::reverse_iterator String::rbegin() noexcept
	{
		return m_string.rbegin();
	}

	inline String::reverse_iterator String::rend() noexcept
	{
		return m_string.rend();
	}

	inline String::const_reverse_iterator String::rbegin() const noexcept
	{
		return m_string.rbegin();
	}

	inline String::const_reverse_iterator String::rend() const noexcept
	{
		return m_string.rend();
	}

	inline String::const_reverse_iterator String::crbegin() const noexcept
	{
		return m_string.crbegin();
	}

	inline String::const_reverse_iterator String::crend() const noexcept
	{
		return m_string.crend();
	}

	inline void String::shrink_to_fit()
	{
		m_string.shrink_to_fit();
	}

	inline void String::release()
	{
		clear();

		shrink_to_fit();
	}

	inline String::value_type& String::at(const size_t offset)&
	{
		return m_string.at(offset);
	}

	inline const String::value_type& String::at(const size_t offset) const&
	{
		return m_string.at(offset);
	}

	inline String::value_type String::at(const size_t offset)&&
	{
		return m_string.at(offset);
	}

	inline String::value_type& String::operator[](const size_t offset)& noexcept
	{
		return m_string[offset];
	}

	inline const String::value_type& String::operator[](const size_t offset) const& noexcept
	{
		return m_string[offset];
	}

	inline String::value_type String::operator[](const size_t offset) && noexcept
	{
		return std::move(m_string[offset]);
	}

	inline void String::push_front(const value_type ch)
	{
		insert(begin(), ch);
	}

	inline void String::push_back(const value_type ch)
	{
		m_string.push_back(ch);
	}

	inline void String::pop_front()
	{
		m_string.erase(m_string.begin());
	}

	inline void String::pop_front_N(const size_t n)
	{
		m_string.erase(m_string.begin(), m_string.begin() + Min(n, m_string.size()));
	}

	inline void String::pop_back() noexcept
	{
		m_string.pop_back();
	}

	inline void String::pop_back_N(const size_t n) noexcept
	{
		m_string.erase(m_string.end() - Min(n, m_string.size()), m_string.end());
	}

	inline String::value_type& String::front() noexcept
	{
		return m_string.front();
	}

	inline const String::value_type& String::front() const noexcept
	{
		return m_string.front();
	}

	inline String::value_type& String::back() noexcept
	{
		return m_string.back();
	}

	inline const String::value_type& String::back() const noexcept
	{
		return m_string.back();
	}

	inline const String::value_type* String::c_str() const noexcept
	{
		return m_string.c_str();
	}

	inline const String::value_type* String::data() const noexcept
	{
		return m_string.data();
	}

	inline String::value_type* String::data() noexcept
	{
		return m_string.data();
	}

	inline String::string_type& String::str() noexcept
	{
		return m_string;
	}

	inline const String::string_type& String::str() const noexcept
	{
		return m_string;
	}

	inline size_t String::length() const noexcept
	{
		return m_string.length();
	}

	inline size_t String::size() const noexcept
	{
		return m_string.size();
	}

	inline size_t String::size_bytes() const noexcept
	{
		return (m_string.size() * sizeof(value_type));
	}

	inline bool String::empty() const noexcept
	{
		return m_string.empty();
	}

	inline bool String::isEmpty() const noexcept
	{
		return m_string.empty();
	}

	inline String::operator bool() const noexcept
	{
		return (not m_string.empty());
	}

	inline size_t String::max_size() const noexcept
	{
		return m_string.max_size();
	}

	inline size_t String::capacity() const noexcept
	{
		return m_string.capacity();
	}

	inline void String::resize(const size_t newSize)
	{
		m_string.resize(newSize);
	}

	inline void String::resize(const size_t newSize, const value_type ch)
	{
		m_string.resize(newSize, ch);
	}

	inline void String::reserve(const size_t newCapacity)
	{
		m_string.reserve(newCapacity);
	}

	inline void String::swap(String& other) noexcept
	{
		m_string.swap(other.m_string);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline bool String::all(Fty f) const
	{
		return std::all_of(m_string.begin(), m_string.end(), f);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline bool String::any(Fty f) const
	{
		return std::any_of(m_string.begin(), m_string.end(), f);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline size_t String::count_if(Fty f) const
	{
		return std::count_if(m_string.begin(), m_string.end(), f);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32&>>*>
	inline String& String::each(Fty f)
	{
		for (auto& c : m_string)
		{
			f(c);
		}

		return *this;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32>>*>
	inline const String& String::each(Fty f) const
	{
		for (const auto c : m_string)
		{
			f(c);
		}

		return *this;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, char32&>>*>
	inline String& String::each_index(Fty f)
	{
		size_t i = 0;

		for (auto& c : m_string)
		{
			f(i++, c);
		}

		return *this;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, char32>>*>
	inline const String& String::each_index(Fty f) const
	{
		size_t i = 0;

		for (const auto c : m_string)
		{
			f(i++, c);
		}

		return *this;
	}

	inline String::value_type String::fetch(const size_t index, const value_type defaultValue) const noexcept
	{
		if (index >= size())
		{
			return defaultValue;
		}

		return m_string[index];
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline String String::filter(Fty f) const
	{
		String new_array;

		for (const auto c : m_string)
		{
			if (f(c))
			{
				new_array.push_back(c);
			}
		}

		return new_array;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline bool String::includes_if(Fty f) const
	{
		return any(f);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline String& String::keep_if(Fty f)
	{
		m_string.erase(std::remove_if(m_string.begin(), m_string.end(), std::not_fn(f)), m_string.end());

		return *this;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32>>*>
	auto String::map(Fty f) const
	{
		using T = std::decay_t<std::invoke_result_t<Fty, char32>>;
		Array<T, std::allocator<T>> new_array;

		new_array.reserve(size());

		for (const auto v : m_string)
		{
			new_array.push_back(f(v));
		}

		return new_array;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline bool String::none(Fty f) const
	{
		return std::none_of(m_string.begin(), m_string.end(), f);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline String& String::remove_if(Fty f)
	{
		m_string.erase(std::remove_if(m_string.begin(), m_string.end(), f), m_string.end());

		return *this;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline String String::removed_if(Fty f) const&
	{
		String new_string;

		for (const auto c : m_string)
		{
			if (not f(c))
			{
				new_string.push_back(c);
			}
		}

		return new_string;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline String String::removed_if(Fty f)&&
	{
		remove_if(f);

		return std::move(*this);
	}

	template <class StringViewIsh, class>
	inline String& String::replace(const size_type pos, const size_type count, const StringViewIsh& s)
	{
		m_string.replace(pos, count, s);

		return *this;
	}

	template <class StringViewIsh, class>
	inline String& String::replace(const_iterator first, const_iterator last, const StringViewIsh& s)
	{
		m_string.replace(first, last, s);

		return *this;
	}

	template <class Iterator>
	inline String& String::replace(const_iterator first, const_iterator last, Iterator first2, Iterator last2)
	{
		m_string.replace(first, last, first2, last2);

		return *this;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline String& String::replace_if(Fty f, const value_type newChar)
	{
		for (auto& c : m_string)
		{
			if (f(c))
			{
				c = newChar;
			}
		}

		return *this;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline String String::replaced_if(Fty f, const value_type newChar) const&
	{
		return String(*this).replace_if(f, newChar);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline String String::replaced_if(Fty f, const value_type newChar)&&
	{
		replace_if(f, newChar);

		return std::move(*this);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32&>>*>
	inline String& String::reverse_each(Fty f)
	{
		auto it = m_string.rbegin();
		const auto itEnd = m_string.rend();

		while (it != itEnd)
		{
			f(*it++);
		}

		return *this;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32>>*>
	inline const String& String::reverse_each(Fty f) const
	{
		auto it = m_string.rbegin();
		const auto itEnd = m_string.rend();

		while (it != itEnd)
		{
			f(*it++);
		}

		return *this;
	}

	SIV3D_CONCEPT_URBG_
	inline String& String::shuffle(URBG&& rbg)
	{
		Shuffle(m_string.begin(), m_string.end(), std::forward<URBG>(rbg));

		return *this;
	}

	SIV3D_CONCEPT_URBG_
	inline String String::shuffled(URBG&& rbg) const&
	{
		return String(*this).shuffle(std::forward<URBG>(rbg));
	}

	SIV3D_CONCEPT_URBG_
	inline String String::shuffled(URBG&& rbg)&&
	{
		Shuffle(m_string.begin(), m_string.end(), std::forward<URBG>(rbg));

		return std::move(*this);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32, char32>>*>
	inline String& String::sort_by(Fty f)
	{
		std::sort(m_string.begin(), m_string.end(), f);

		return *this;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32, char32>>*>
	inline String String::sorted_by(Fty f) const&
	{
		return String(*this).sort_by(f);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32, char32>>*>
	inline String String::sorted_by(Fty f)&&
	{
		std::sort(m_string.begin(), m_string.end(), f);

		return std::move(*this);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>*>
	inline String String::take_while(Fty f) const
	{
		return String(m_string.begin(), std::find_if_not(m_string.begin(), m_string.end(), f));
	}

	inline void swap(String& a, String& b) noexcept
	{
		a.swap(b);
	}

	inline namespace Literals
	{
		inline namespace StringLiterals
		{
			inline String operator ""_s(const char32_t* s, const size_t length)
			{
				return String(s, length);
			}
		}
	}
}

template <>
inline void std::swap(s3d::String& a, s3d::String& b) noexcept
{
	a.swap(b);
}
