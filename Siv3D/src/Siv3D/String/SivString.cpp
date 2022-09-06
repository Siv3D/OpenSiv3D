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

# include <Siv3D/String.hpp>
# include <Siv3D/Char.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Array.hpp>

namespace s3d
{
	namespace detail
	{
		inline constexpr bool IsTrimmable(char32 ch) noexcept
		{
			return (ch <= 0x20) || ((ch - 0x7F) <= (0x9F - 0x7F));
		};
	}

	bool String::starts_with(const value_type ch) const noexcept
	{
		return (not m_string.empty() && (m_string.front() == ch));
	}

	bool String::starts_with(const StringView s) const
	{
		if (size() < s.size())
		{
			return false;
		}

		return std::equal(s.begin(), s.end(), begin());
	}

	bool String::ends_with(const value_type ch) const noexcept
	{
		return (not m_string.empty() && (m_string.back() == ch));
	}

	bool String::ends_with(const StringView s) const
	{
		if (size() < s.size())
		{
			return false;
		}

		return std::equal(s.begin(), s.end(), end() - s.size());
	}

	String String::substr(const size_t offset, const size_t count) const
	{
		return m_string.substr(offset, count);
	}

	StringView String::substrView(const size_t offset, const size_t count) const&
	{
		if (offset > size())
		{
			throw std::out_of_range("String::substrView(): index out of range");
		}

		return StringView(data() + offset, Min(count, size() - offset));
	}

	std::string String::narrow() const
	{
		return Unicode::Narrow(m_string);
	}

	std::wstring String::toWstr() const
	{
		return Unicode::ToWstring(m_string);
	}

	std::string String::toUTF8() const
	{
		return Unicode::ToUTF8(m_string);
	}

	std::u16string String::toUTF16() const
	{
		return Unicode::ToUTF16(m_string);
	}

	const std::u32string& String::toUTF32() const noexcept
	{
		return m_string;
	}

	uint64 String::hash() const noexcept
	{
		return Hash::FNV1a(data(), size_bytes());
	}

	size_t String::indexOf(const StringView s, const size_t offset) const noexcept
	{
		return m_string.find(s.data(), offset, s.length());
	}

	size_t String::indexOf(const value_type ch, const size_t offset) const noexcept
	{
		return m_string.find(ch, offset);
	}

	size_t String::indexOfNot(const value_type ch, const size_t offset) const noexcept
	{
		return m_string.find_first_not_of(ch, offset);
	}

	size_t String::lastIndexOf(const StringView s, const size_t offset) const noexcept
	{
		return m_string.rfind(s.data(), offset, s.length());
	}

	size_t String::lastIndexOf(const value_type ch, const size_t offset) const noexcept
	{
		return m_string.rfind(ch, offset);
	}

	size_t String::lastIndexNotOf(const value_type ch, const size_t offset) const noexcept
	{
		return m_string.find_last_not_of(ch, offset);
	}

	size_t String::indexOfAny(const StringView anyof, const size_t offset) const noexcept
	{
		return m_string.find_first_of(anyof.data(), offset, anyof.length());
	}

	size_t String::lastIndexOfAny(const StringView anyof, const size_t offset) const noexcept
	{
		return m_string.find_last_of(anyof.data(), offset, anyof.length());
	}

	size_t String::indexNotOfAny(const StringView anyof, const size_t offset) const
	{
		return m_string.find_first_not_of(anyof.data(), offset, anyof.length());
	}

	size_t String::lastIndexNotOfAny(const StringView anyof, const size_t offset) const
	{
		return m_string.find_last_not_of(anyof.data(), offset, anyof.length());
	}

	int32 String::compare(const String& s) const noexcept
	{
		return m_string.compare(s.m_string);
	}

	int32 String::compare(const StringView s) const noexcept
	{
		return m_string.compare(std::u32string_view(s.data(), s.size()));
	}

	int32 String::compare(const value_type* s) const noexcept
	{
		return m_string.compare(s);
	}

	int32 String::case_insensitive_compare(const StringView s) const noexcept
	{
		auto first1 = begin(), last1 = end();
		auto first2 = s.begin(), last2 = s.end();

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

	bool String::case_insensitive_equals(const StringView s) const noexcept
	{
		if (length() != s.length())
		{
			return false;
		}

		auto first1 = begin(), last1 = end();
		auto first2 = s.begin(), last2 = s.end();

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
		for (auto& c : m_string)
		{
			if (IsAlpha(c))
			{
				c = ToUpper(c);
				break;
			}
		}

		return *this;
	}

	String String::capitalized() const&
	{
		return String(*this).capitalize();
	}

	String String::capitalized()&&
	{
		capitalize();

		return std::move(*this);
	}

	size_t String::count(const value_type ch) const noexcept
	{
		return std::count(m_string.begin(), m_string.end(), ch);
	}

	size_t String::count(const StringView s) const
	{
		size_t count = 0;

		for (auto it = begin();; ++it, ++count)
		{
			it = std::search(it, end(), s.begin(), s.end());

			if (it == end())
			{
				return count;
			}
		}
	}

	String String::expandTabs(const size_t tabSize) const
	{
		const size_t tabCount = count(value_type('\t'));
		const size_t new_size = m_string.length() + (tabCount * (tabSize - 1));

		String result(new_size, value_type('\0'));

		value_type* dst = &result[0];

		for (const auto c : m_string)
		{
			if (c == value_type('\t'))
			{
				for (size_t i = 0; i < tabSize; ++i)
				{
					*dst++ = value_type(' ');
				}
			}
			else
			{
				*dst++ = c;
			}
		}

		return result;
	}

	String& String::fill(const value_type value)
	{
		std::fill(m_string.begin(), m_string.end(), value);

		return *this;
	}

	bool String::includes(const value_type ch) const
	{
		return (indexOf(ch) != String::npos);
	}

	bool String::includes(const StringView s) const
	{
		return (indexOf(s) != String::npos);
	}

	String String::layout(const size_t width) const
	{
		String result;

		result.reserve(m_string.length());

		size_t count = 0;

		for (const auto c : m_string)
		{
			if (c == value_type('\n'))
			{
				result.push_back(value_type('\n'));

				count = 0;
			}
			else if (c != value_type('\r'))
			{
				if (width <= count)
				{
					result.push_back(value_type('\n'));

					count = 0;
				}

				result.push_back(c);

				++count;
			}
		}

		return result;
	}

	String& String::lowercase() noexcept
	{
		for (auto& c : m_string)
		{
			c = ToLower(c);
		}

		return *this;
	}

	String String::lowercased() const&
	{
		return String(*this).lowercase();
	}

	String String::lowercased()&&
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

	String String::lpadded(const size_t length, const value_type fillChar)&&
	{
		lpad(length, fillChar);

		return std::move(*this);
	}

	String& String::ltrim()
	{
		m_string.erase(m_string.begin(), std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable));

		return *this;
	}

	String String::ltrimmed() const&
	{
		return String(std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable), m_string.end());
	}

	String String::ltrimmed()&&
	{
		ltrim();

		return std::move(*this);
	}

	String& String::remove(const value_type ch)
	{
		m_string.erase(std::remove(m_string.begin(), m_string.end(), ch), m_string.end());

		return *this;
	}

	String& String::remove(const StringView s)
	{
		return *this = removed(s);
	}

	String String::removed(const value_type ch) const&
	{
		String new_string;

		for (const auto c : m_string)
		{
			if (c != ch)
			{
				new_string.push_back(c);
			}
		}

		return new_string;
	}

	String String::removed(const value_type ch)&&
	{
		remove(ch);

		return std::move(*this);
	}

	String String::removed(const StringView s) const
	{
		String result;

		for (auto it = begin(); it != end();)
		{
			const auto it2 = it;

			result.append(it2, it = std::search(it, end(), s.begin(), s.end()));

			if (it != end())
			{
				it += s.size();
			}
		}

		return result;
	}

	String& String::remove_at(const size_t index)
	{
		if (m_string.size() <= index)
		{
			throw std::out_of_range("String::remove_at(): index out of range");
		}

		m_string.erase(m_string.begin() + index);

		return *this;
	}

	String String::removed_at(const size_t index) const&
	{
		if (m_string.size() <= index)
		{
			throw std::out_of_range("String::removed_at(): index out of range");
		}

		String new_string;

		new_string.reserve(m_string.length() - 1);

		new_string.assign(m_string.begin(), m_string.begin() + index);

		new_string.append(m_string.begin() + index + 1, m_string.end());

		return new_string;
	}

	String String::removed_at(const size_t index)&&
	{
		remove_at(index);

		return std::move(*this);
	}

	String& String::replace(const value_type oldChar, const value_type newChar)
	{
		for (auto& c : m_string)
		{
			if (c == oldChar)
			{
				c = newChar;
			}
		}

		return *this;
	}

	String& String::replace(const StringView oldStr, const StringView newStr)
	{
		return *this = replaced(oldStr, newStr);
	}

	String& String::replace(const size_type pos, const size_type count, const String& s)
	{
		m_string.replace(pos, count, s.m_string);

		return *this;
	}

	String& String::replace(const size_type pos, const size_type count, const value_type* s)
	{
		m_string.replace(pos, count, s);

		return *this;
	}

	String& String::replace(const_iterator first, const_iterator last, const String& s)
	{
		m_string.replace(first, last, s.m_string);

		return *this;
	}

	String& String::replace(const_iterator first, const_iterator last, const value_type* s)
	{
		m_string.replace(first, last, s);

		return *this;
	}

	String String::replaced(const value_type oldChar, const value_type newChar) const&
	{
		return String(*this).replace(oldChar, newChar);
	}

	String String::replaced(const value_type oldChar, const value_type newChar)&&
	{
		replace(oldChar, newChar);

		return std::move(*this);
	}

	String String::replaced(const StringView oldStr, const StringView newStr) const
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

	String String::reversed() const&
	{
		return String(m_string.rbegin(), m_string.rend());
	}

	String String::reversed()&&
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

	String String::rotated(const std::ptrdiff_t count) const&
	{
		return String(*this).rotate(count);
	}

	String String::rotated(const std::ptrdiff_t count)&&
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

	String String::rpadded(const size_t length, const value_type fillChar) const&
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

	String String::rpadded(const size_t length, const value_type fillChar)&&
	{
		rpad(length, fillChar);

		return std::move(*this);
	}

	String& String::rtrim()
	{
		m_string.erase(std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base(), m_string.end());

		return *this;
	}

	String String::rtrimmed() const&
	{
		return String(m_string.begin(), std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base());
	}

	String String::rtrimmed()&&
	{
		rtrim();

		return std::move(*this);
	}

	String& String::shuffle()
	{
		return shuffle(GetDefaultRNG());
	}

	String String::shuffled() const&
	{
		return shuffled(GetDefaultRNG());
	}

	String String::shuffled()&&
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

	String String::stable_uniqued() const
	{
		String result;

		detail::StableUniqueHelper<value_type> pred;

		std::copy_if(m_string.begin(), m_string.end(), std::back_inserter(result), std::ref(pred));

		return result;
	}

	String& String::swapcase() noexcept
	{
		for (auto& v : m_string)
		{
			if (IsLower(v))
			{
				v -= ('a' - 'A');
			}
			else if (IsUpper(v))
			{
				v += ('a' - 'A');
			}
		}

		return *this;
	}

	String String::swapcased() const&
	{
		return String(*this).swapcase();
	}

	String String::swapcased()&&
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

	String String::trimmed() const&
	{
		return String(std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable), std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base());
	}

	String String::trimmed()&&
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
				v -= ('a' - 'A');
			}
		}

		return *this;
	}

	String String::uppercased() const&
	{
		return String(*this).uppercase();
	}

	String String::uppercased()&&
	{
		uppercase();

		return std::move(*this);
	}

	String& String::rsort() noexcept
	{
		std::sort(begin(), end(), std::greater<>());

		return *this;
	}

	String String::rsorted() const&
	{
		return String(*this).rsort();
	}

	String String::rsorted()&&
	{
		rsort();

		return std::move(*this);
	}

	String& String::sort() noexcept
	{
		std::sort(m_string.begin(), m_string.end());

		return *this;
	}

	String String::sorted() const&
	{
		return String(*this).sort();
	}

	String String::sorted()&&
	{
		std::sort(m_string.begin(), m_string.end());

		return std::move(*this);
	}

	String String::take(const size_t n) const
	{
		return String(m_string.begin(), m_string.begin() + Min(n, m_string.size()));
	}

	String& String::stable_unique()
	{
		// [Siv3D ToDo: 最適化]
		return *this = stable_uniqued();
	}

	String& String::sort_and_unique()
	{
		sort();

		m_string.erase(std::unique(m_string.begin(), m_string.end()), m_string.end());

		return *this;
	}

	String String::sorted_and_uniqued() const&
	{
		return String(*this).sort_and_unique();
	}

	String String::sorted_and_uniqued()&&
	{
		sort();

		m_string.erase(std::unique(m_string.begin(), m_string.end()), m_string.end());

		m_string.shrink_to_fit();

		return std::move(*this);
	}

	String& String::unique_consecutive()
	{
		m_string.erase(std::unique(m_string.begin(), m_string.end()), m_string.end());

		return *this;
	}

	String String::uniqued_consecutive() const&
	{
		String result;

		std::unique_copy(m_string.begin(), m_string.end(), std::back_inserter(result));

		return result;
	}

	String String::uniqued_consecutive()&&
	{
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

		for (const auto c : m_string)
		{
			switch (c)
			{
			case value_type('\"'):
				new_string.append(U"&quot;"_sv);
				break;
			case value_type('&'):
				new_string.append(U"&amp;"_sv);
				break;
			case value_type('\''):
				new_string.append(U"&apos;"_sv);
				break;
			case value_type('<'):
				new_string.append(U"&lt;"_sv);
				break;
			case value_type('>'):
				new_string.append(U"&gt;"_sv);
				break;
			default:
				new_string.push_back(c);
				break;
			}
		}

		return new_string;
	}

	bool operator ==(const String& lhs, const String::value_type* rhs)
	{
		return (lhs.str() == rhs);
	}

#if __cpp_impl_three_way_comparison

	std::strong_ordering operator <=>(const String& lhs, const String::value_type* rhs)
	{
		return (lhs.str() <=> rhs);
	}

#else

	bool operator ==(const String& lhs, const String& rhs) noexcept
	{
		return (lhs.m_string == rhs.m_string);
	}

	bool operator ==(const String::value_type* lhs, const String& rhs)
	{
		return (lhs == rhs.str());
	}

	bool operator !=(const String& lhs, const String& rhs) noexcept
	{
		return (lhs.m_string != rhs.m_string);
	}

	bool operator !=(const String::value_type* lhs, const String& rhs)
	{
		return (lhs != rhs.str());
	}

	bool operator !=(const String& lhs, const String::value_type* rhs)
	{
		return (lhs.str() != rhs);
	}

	bool operator <(const String& lhs, const String& rhs) noexcept
	{
		return (lhs.m_string < rhs.m_string);
	}

	bool operator <(const String::value_type* lhs, const String& rhs)
	{
		return (lhs < rhs.str());
	}

	bool operator <(const String& lhs, const String::value_type* rhs)
	{
		return (lhs.str() < rhs);
	}

	bool operator >(const String& lhs, const String& rhs) noexcept
	{
		return (lhs.m_string > rhs.m_string);
	}

	bool operator >(const String::value_type* lhs, const String& rhs)
	{
		return (lhs > rhs.str());
	}

	bool operator >(const String& lhs, const String::value_type* rhs)
	{
		return (lhs.str() > rhs);
	}

	bool operator <=(const String& lhs, const String& rhs) noexcept
	{
		return (lhs.m_string <= rhs.m_string);
	}

	bool operator <=(const String::value_type* lhs, const String& rhs)
	{
		return (lhs <= rhs.str());
	}

	bool operator <=(const String& lhs, const String::value_type* rhs)
	{
		return (lhs.str() <= rhs);
	}

	bool operator >=(const String& lhs, const String& rhs) noexcept
	{
		return (lhs.m_string >= rhs.m_string);
	}

	bool operator >=(const String::value_type* lhs, const String& rhs)
	{
		return (lhs >= rhs.str());
	}

	bool operator >=(const String& lhs, const String::value_type* rhs)
	{
		return (lhs.str() >= rhs);
	}
#endif

	String operator +(const String::value_type lhs, const String& rhs)
	{
		String result;
		result.reserve(1 + rhs.size());
		result.append(lhs);
		result.append(rhs);
		return result;
	}

	String operator +(const String::value_type lhs, String&& rhs)
	{
		rhs.push_front(lhs);
		return std::move(rhs);
	}

	String operator +(const String::value_type* lhs, const String& rhs)
	{
		const size_t len = std::char_traits<String::value_type>::length(lhs);
		String result;
		result.reserve(len + rhs.size());
		result.append(lhs, len);
		result.append(rhs);
		return result;
	}

	String operator +(const String::value_type* lhs, String&& rhs)
	{
		return std::move(rhs.insert(0, lhs));
	}

	String operator +(const StringView lhs, const String& rhs)
	{
		String result;
		result.reserve(lhs.size() + rhs.size());
		result.append(lhs);
		result.append(rhs);
		return result;
	}

	String operator +(const StringView lhs, String&& rhs)
	{
		return std::move(rhs.insert(0, lhs));
	}

	String operator +(const String& lhs, const String::value_type rhs)
	{
		String result;
		result.reserve(lhs.size() + 1);
		result.append(lhs);
		result.append(rhs);
		return result;
	}

	String operator +(const String& lhs, const String::value_type* rhs)
	{
		const size_t len = std::char_traits<String::value_type>::length(rhs);
		String result;
		result.reserve(lhs.size() + len);
		result.append(lhs);
		result.append(rhs, len);
		return result;
	}

	String operator +(const String& lhs, const StringView rhs)
	{
		String result;
		result.reserve(lhs.size() + rhs.size());
		result.append(lhs);
		result.append(rhs);
		return result;
	}

	String operator +(const String& lhs, const String& rhs)
	{
		String result;
		result.reserve(lhs.size() + rhs.size());
		result.append(lhs);
		result.append(rhs);
		return result;
	}

	String operator +(const String& lhs, String&& rhs)
	{
		return std::move(rhs.insert(0, lhs));
	}

	String operator +(String&& lhs, const String::value_type rhs)
	{
		return std::move(lhs << rhs);
	}

	String operator +(String&& lhs, const String::value_type* rhs)
	{
		return std::move(lhs.append(rhs));
	}

	String operator +(String&& lhs, const StringView rhs)
	{
		return std::move(lhs.append(rhs));
	}

	String operator +(String&& lhs, const String& rhs)
	{
		return std::move(lhs.append(rhs));
	}

	String operator +(String&& lhs, String&& rhs)
	{
		if (rhs.size() <= lhs.capacity() - lhs.size() || rhs.capacity() - rhs.size() < lhs.size())
		{
			return std::move(lhs.append(rhs));
		}
		else
		{
			return std::move(rhs.insert(0, lhs));
		}
	}

	String operator +(const String::value_type lhs, StringView rhs)
	{
		String result;
		result.reserve(1 + rhs.size());
		result.append(lhs);
		result.append(rhs);
		return result;
	}

	String operator +(const String::value_type* lhs, StringView rhs)
	{
		const size_t len = std::char_traits<String::value_type>::length(lhs);
		String result;
		result.reserve(len + rhs.size());
		result.append(lhs, len);
		result.append(rhs);
		return result;
	}

	String operator +(StringView lhs, const String::value_type* rhs)
	{
		const size_t len = std::char_traits<String::value_type>::length(rhs);
		String result;
		result.reserve(lhs.size() + len);
		result.append(lhs);
		result.append(rhs, len);
		return result;
	}

	String operator +(StringView lhs, StringView rhs)
	{
		String result;
		result.reserve(lhs.size() + rhs.size());
		result.append(lhs);
		result.append(rhs);
		return result;
	}

	String operator +(StringView lhs, const String::value_type rhs)
	{
		String result;
		result.reserve(lhs.size() + 1);
		result.append(lhs);
		result.append(rhs);
		return result;
	}

	std::ostream& operator <<(std::ostream& output, const String& value)
	{
		return (output << value.narrow());
	}

	std::wostream& operator <<(std::wostream& output, const String& value)
	{
		return (output << value.toWstr());
	}

	std::basic_ostream<char32>& operator <<(std::basic_ostream<char32>& output, const String& value)
	{
		return output.write(value.data(), value.size());
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

		value = Unicode::FromWstring(s);

		return input;
	}

	void Formatter(FormatData& formatData, const String& s)
	{
		formatData.string.append(s);
	}
}
