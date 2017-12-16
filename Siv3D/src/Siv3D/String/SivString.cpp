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

# include <Siv3D/String.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/DefaultRNG.hpp>

namespace s3d
{
	namespace detail
	{
		inline constexpr bool IsTrimmable(const uint32 ch)
		{
			return (ch <= 0x20u) || ((ch - 0x7Fu) <= (0x9Fu - 0x7Fu));
		};
	}

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

	String& String::append(const value_type ch)
	{
		m_string.push_back(ch);

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

	String& String::capitalize() noexcept
	{
		for (auto& v : m_string)
		{
			if (IsAlpha(v))
			{
				if (IsLower(v))
				{
					v -= 32;
				}

				break;
			}
		}

		return *this;
	}

	String String::capitalized() const &
	{
		return String(*this).capitalize();
	}

	String String::capitalized() &&
	{
		capitalize();

		return std::move(*this);
	}

	size_t String::count(const value_type ch) const noexcept
	{
		size_t count = 0;

		for (const auto v : m_string)
		{
			if (v == ch)
			{
				++count;
			}
		}

		return count;
	}

	size_t String::count(const StringView view) const
	{
		size_t count = 0;

		for (auto it = begin();; ++it, ++count)
		{
			it = std::search(it, end(), view.begin(), view.end());

			if (it == end())
			{
				return count;
			}
		}
	}

	String String::drop(const size_t n) const
	{
		if (n >= m_string.size())
		{
			return String();
		}

		return String(m_string.begin() + n, m_string.end());
	}

	bool String::ends_with(const value_type ch) const noexcept
	{
		return !m_string.empty() && (m_string[m_string.size() - 1] == ch);
	}

	bool String::ends_with(const StringView view) const
	{
		return (size() >= view.size()) && std::equal(view.begin(), view.end(), end() - view.size());
	}

	String String::expand_tabs(const size_t tabSize) const
	{
		const size_t new_size = m_string.length() + (count(value_type('\t')) * tabSize);

		String result(new_size, value_type('\0'));

		value_type* dst = &result[0];

		for (const auto v : m_string)
		{
			if (v == value_type('\t'))
			{
				for (size_t i = 0; i < tabSize; ++i)
				{
					*dst++ = value_type(' ');
				}
			}
			else
			{
				*dst++ = v;
			}
		}

		return result;
	}

	String::value_type String::fetch(const size_t index, const value_type defaultValue) const noexcept
	{
		if (index >= size())
		{
			return defaultValue;
		}

		return m_string[index];
	}

	String& String::fill(const value_type value)
	{
		std::fill(m_string.begin(), m_string.end(), value);

		return *this;
	}

	bool String::includes(const value_type ch) const
	{
		return indexOf(ch) != String::npos;
	}

	bool String::includes(const value_type* str) const
	{
		return indexOf(str) != String::npos;
	}

	bool String::includes(const String& str) const
	{
		return indexOf(str) != String::npos;
	}

	String& String::keep_if(std::function<bool(value_type)> f)
	{
		m_string.erase(std::remove_if(m_string.begin(), m_string.end(), std::not_fn(f)), m_string.end());

		return *this;
	}

	String String::layout(const size_t width) const
	{
		String result;

		result.reserve(m_string.length());

		size_t count = 0;

		for (const auto v : m_string)
		{
			if (v == value_type('\n'))
			{
				result.push_back(value_type('\n'));

				count = 0;
			}
			else if (v != value_type('\r'))
			{
				if (width <= count)
				{
					result.push_back(value_type('\n'));

					count = 0;
				}

				result.push_back(v);

				++count;
			}
		}

		return result;
	}

	String& String::lowercase() noexcept
	{
		for (auto& v : m_string)
		{
			if (IsUpper(v))
			{
				v += 32;
			}
		}

		return *this;
	}

	String String::lowercased() const &
	{
		return String(*this).lowercase();
	}

	String String::lowercased() &&
	{
		lowercase();

		return std::move(*this);
	}

	String& String::lpad(const size_t length, const value_type fillChar)
	{
		if (length <= m_string.length())
		{
			return *this;
		}

		m_string.insert(m_string.begin(), length - m_string.length(), fillChar);

		return *this;
	}

	String String::lpadded(const size_t length, const value_type fillChar) const &
	{
		if (length <= m_string.length())
		{
			return *this;
		}

		String new_string;

		new_string.reserve(length);

		new_string.assign(length - m_string.length(), fillChar);

		new_string.append(m_string);

		return new_string;
	}

	String String::lpadded(const size_t length, const value_type fillChar) &&
	{
		lpad(length, fillChar);

		return std::move(*this);
	}

	String& String::ltrim()
	{
		m_string.erase(m_string.begin(), std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable));

		return *this;
	}

	String String::ltrimmed() const &
	{
		return String(std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable), m_string.end());
	}

	String String::ltrimmed() &&
	{
		ltrim();

		return std::move(*this);
	}

	std::string String::narrow() const
	{
		return Unicode::Narrow(*this);
	}

	String& String::remove(const value_type ch)
	{
		m_string.erase(std::remove(m_string.begin(), m_string.end(), ch), m_string.end());

		return *this;
	}

	String& String::remove(const StringView view)
	{
		return *this = removed(view);
	}

	String String::removed(const value_type ch) const &
	{
		String new_string;

		for (const auto v : m_string)
		{
			if (v != ch)
			{
				new_string.push_back(v);
			}
		}

		return new_string;
	}

	String String::removed(const value_type ch) &&
	{
		remove(ch);

		return std::move(*this);
	}

	String String::removed(const StringView view) const
	{
		String result;

		for (auto it = begin(); it != end();)
		{
			const auto it2 = it;

			result.append(it2, it = std::search(it, end(), view.begin(), view.end()));

			if (it != end())
			{
				it += view.size();
			}
		}

		return result;
	}

	String& String::remove_at(const size_t index)
	{
		if (m_string.size() <= index)
		{
			throw std::out_of_range("String::remove_at() index out of range");
		}

		m_string.erase(m_string.begin() + index);

		return *this;
	}

	String String::removed_at(const size_t index) const &
	{
		if (m_string.size() <= index)
		{
			throw std::out_of_range("String::removed_at() index out of range");
		}

		String new_string;

		new_string.reserve(m_string.length() - 1);

		new_string.assign(m_string.begin(), m_string.begin() + index);

		new_string.append(m_string.begin() + index + 1, m_string.end());

		return new_string;
	}

	String String::removed_at(const size_t index) &&
	{
		remove_at(index);

		return std::move(*this);
	}

	String& String::replace(const value_type oldChar, const value_type newChar)
	{
		for (auto& v : m_string)
		{
			if (v == oldChar)
			{
				v = newChar;
			}
		}

		return *this;
	}

	String& String::replace(const String& oldStr, const String& newStr)
	{
		return *this = replaced(oldStr, newStr);
	}

	String String::replaced(const value_type oldChar, const value_type newChar) const &
	{
		return String(*this).replace(oldChar, newChar);
	}

	String String::replaced(const value_type oldChar, const value_type newChar) &&
	{
		replace(oldChar, newChar);

		return std::move(*this);
	}

	String String::replaced(const String& oldStr, const String& newStr) const
	{
		String new_string;

		if (newStr.length() >= oldStr.length())
		{
			new_string.reserve(m_string.length());
		}

		const auto itEnd = m_string.end();
		auto itCurrent = m_string.begin();
		auto itNext = std::search(itCurrent, itEnd, oldStr.begin(), oldStr.end());

		while (itNext != itEnd)
		{
			new_string.append(itCurrent, itNext);
			new_string.append(newStr);
			itCurrent = itNext + oldStr.length();
			itNext = std::search(itCurrent, itEnd, oldStr.begin(), oldStr.end());
		}

		new_string.append(itCurrent, itNext);

		return new_string;
	}

	String& String::reverse()
	{
		std::reverse(m_string.begin(), m_string.end());

		return *this;
	}

	String String::reversed() const &
	{
		return String(m_string.rbegin(), m_string.rend());
	}

	String String::reversed() &&
	{
		reverse();

		return *this;
	}

	String& String::rotate(std::ptrdiff_t count)
	{
		if (m_string.empty())
		{
			;
		}
		else if (count > 0) // rotation to the left
		{
			if (static_cast<size_t>(count) > m_string.size())
			{
				count %= m_string.size();
			}

			std::rotate(m_string.begin(), m_string.begin() + count, m_string.end());
		}
		else if (count < 0) // rotation to the right
		{
			count = -count;

			if (static_cast<size_t>(count) > m_string.size())
			{
				count %= m_string.size();
			}

			std::rotate(m_string.rbegin(), m_string.rbegin() + count, m_string.rend());
		}

		return *this;
	}

	String String::rotated(const std::ptrdiff_t count) const &
	{
		return String(*this).rotate(count);
	}

	String String::rotated(const std::ptrdiff_t count) &&
	{
		rotate(count);

		return std::move(*this);
	}

	String& String::rpad(const size_t length, const value_type fillChar)
	{
		if (length <= m_string.length())
		{
			return *this;
		}

		m_string.append(length - m_string.length(), fillChar);

		return *this;
	}

	String String::rpadded(const size_t length, const value_type fillChar) const &
	{
		if (length <= m_string.length())
		{
			return *this;
		}

		String new_string;

		new_string.reserve(length);

		new_string.assign(m_string);

		new_string.append(length - m_string.length(), fillChar);

		return new_string;
	}

	String String::rpadded(const size_t length, const value_type fillChar) &&
	{
		rpad(length, fillChar);

		return std::move(*this);
	}

	String& String::rtrim()
	{
		m_string.erase(std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base(), m_string.end());

		return *this;
	}

	String String::rtrimmed() const &
	{
		return String(m_string.begin(), std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base());
	}

	String String::rtrimmed() &&
	{
		rtrim();

		return std::move(*this);
	}

	String& String::shuffle()
	{
		return shuffle(GetDefaultRNG());
	}

	String String::shuffled() const &
	{
		return shuffled(GetDefaultRNG());
	}

	String String::shuffled() &&
	{
		return shuffled(GetDefaultRNG());
	}

	Array<String> String::split(const value_type ch) const
	{
		if (m_string.empty())
		{
			return{};
		}

		Array<String> result(1);

		const value_type* pSrc = m_string.data();
		const value_type* const pSrcEnd = pSrc + m_string.length();
		String* currentLine = &result.back();

		while (pSrc != pSrcEnd)
		{
			if (*pSrc == ch)
			{
				result.emplace_back();
				currentLine = &result.back();
			}
			else
			{
				currentLine->push_back(*pSrc);
			}

			++pSrc;
		}

		return result;
	}

	std::pair<String, String> String::split_at(const size_t pos) const
	{
		return{ substr(0, pos), substr(pos) };
	}

	Array<String> String::split_lines() const
	{
		if (m_string.empty())
		{
			return{};
		}

		Array<String> result(1);

		const value_type* pSrc = m_string.data();
		const value_type* const pSrcEnd = pSrc + m_string.length();
		String* currentLine = &result.back();

		while (pSrc != pSrcEnd)
		{
			if (*pSrc == value_type('\n'))
			{
				result.emplace_back();
				currentLine = &result.back();
			}
			else if (*pSrc != value_type('\r'))
			{
				currentLine->push_back(*pSrc);
			}

			++pSrc;
		}

		return result;
	}

	bool String::starts_with(const value_type ch) const noexcept
	{
		return !m_string.empty() && (m_string[0] == ch);
	}

	bool String::starts_with(const StringView view) const
	{
		return (size() >= view.size()) && std::equal(view.begin(), view.end(), begin());
	}

	String& String::swapcase() noexcept
	{
		for (auto& v : m_string)
		{
			if (IsLower(v))
			{
				v -= 32;
			}
			else if (IsUpper(v))
			{
				v += 32;
			}
		}

		return *this;
	}

	String String::swapcased() const &
	{
		return String(*this).swapcase();
	}

	String String::swapcased() &&
	{
		swapcase();

		return std::move(*this);
	}

	String& String::trim()
	{
		m_string.erase(m_string.begin(), std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable));

		m_string.erase(std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base(), m_string.end());

		return *this;
	}

	String String::trimmed() const &
	{
		return String(std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable), std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base());
	}

	String String::trimmed() &&
	{
		trim();

		return std::move(*this);
	}

	String& String::uppercase() noexcept
	{
		for (auto& v : m_string)
		{
			if (IsLower(v))
			{
				v -= 32;
			}
		}

		return *this;
	}

	String String::uppercased() const &
	{
		return String(*this).uppercase();
	}

	String String::uppercased() &&
	{
		uppercase();

		return std::move(*this);
	}

	std::string String::toUTF8() const
	{
		return Unicode::ToUTF8(*this);
	}

	std::u16string String::toUTF16() const
	{
		return Unicode::ToUTF16(*this);
	}

	const std::u32string& String::toUTF32() const
	{
		return m_string;
	}

	std::wstring String::toWstr() const
	{
		return Unicode::ToWString(*this);
	}

	String& String::sort()
	{
		std::sort(m_string.begin(), m_string.end());

		return *this;
	}

	String String::sorted() const &
	{
		return String(*this).sort();
	}

	String String::sorted() &&
	{
		std::sort(m_string.begin(), m_string.end());

		return std::move(*this);
	}

	String String::take(const size_t n) const
	{
		return String(m_string.begin(), m_string.begin() + std::min(n, m_string.size()));
	}

	String& String::unique()
	{
		sort();

		m_string.erase(std::unique(m_string.begin(), m_string.end()), m_string.end());

		return *this;
	}

	String String::uniqued() const &
	{
		return String(*this).unique();
	}

	String String::uniqued() &&
	{
		sort();

		m_string.erase(std::unique(m_string.begin(), m_string.end()), m_string.end());

		m_string.shrink_to_fit();

		return std::move(*this);
	}

	String String::values_at(std::initializer_list<size_t> indices) const
	{
		String new_array;

		new_array.reserve(indices.size());

		for (auto index : indices)
		{
			if (index >= m_string.size())
			{
				throw std::out_of_range("String::values_at() index out of range");
			}

			new_array.push_back(m_string[index]);
		}

		return new_array;
	}

	String& String::xml_escape()
	{
		return *this = xml_escaped();
	}

	String String::xml_escaped() const
	{
		String new_string;

		new_string.reserve(m_string.length());

		for (const auto v : m_string)
		{
			switch (v)
			{
			case value_type('\"'):
				new_string.append(U"&quot;", 6);
				break;
			case value_type('&'):
				new_string.append(U"&amp;", 5);
				break;
			case value_type('\''):
				new_string.append(U"&apos;", 6);
				break;
			case value_type('<'):
				new_string.append(U"&lt;", 4);
				break;
			case value_type('>'):
				new_string.append(U"&gt;", 4);
				break;
			default:
				new_string.push_back(v);
				break;
			}
		}

		return new_string;
	}

	std::ostream& operator <<(std::ostream& output, const String& value)
	{
		return output << value.narrow();
	}

	std::wostream& operator <<(std::wostream& output, const String& value)
	{
		return output << value.toWstr();
	}

	std::istream& operator >>(std::istream& input, String& value)
	{
		std::string s;

		input >> s;

		value = Unicode::Widen(s);

		return input;
	}

	std::wistream& operator >>(std::wistream& input, String& value)
	{
		std::wstring s;

		input >> s;

		value = Unicode::FromWString(s);

		return input;
	}
}
