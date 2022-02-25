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
# include <cassert>
# include <stdexcept>
# include <algorithm>
# include "../Utility.hpp"

namespace s3d
{
	inline StringView::StringView(const std::u32string& s) noexcept
		: m_view{ s } {}

	inline constexpr StringView::StringView(const std::u32string_view s) noexcept
		: m_view{ s } {}

	inline constexpr StringView::StringView(const value_type* s, const size_type length) noexcept
		: m_view{ s, length } {}

	inline constexpr StringView::StringView(const value_type* s) noexcept
		: m_view{ s } {}

	inline constexpr StringView::const_iterator StringView::begin() const noexcept
	{
		return m_view.begin();
	}

	inline constexpr StringView::const_iterator StringView::end() const noexcept
	{
		return m_view.end();
	}

	inline constexpr StringView::const_iterator StringView::cbegin() const noexcept
	{
		return m_view.cbegin();
	}

	inline constexpr StringView::const_iterator StringView::cend() const noexcept
	{
		return m_view.cend();
	}

	inline constexpr StringView::const_reverse_iterator StringView::rbegin() const noexcept
	{
		return m_view.rbegin();
	}

	inline constexpr StringView::const_reverse_iterator StringView::rend() const noexcept
	{
		return m_view.rend();
	}

	inline constexpr StringView::const_reverse_iterator StringView::crbegin() const noexcept
	{
		return m_view.crbegin();
	}

	inline constexpr StringView::const_reverse_iterator StringView::crend() const noexcept
	{
		return m_view.crend();
	}

	inline constexpr StringView::const_reference StringView::operator[](const size_type index) const noexcept
	{
		return m_view[index];
	}

	inline constexpr StringView::const_reference StringView::at(const size_type index) const
	{
		if (index >= m_view.size())
		{
			throw std::out_of_range("StringView::at(): index out of range");
		}

		return m_view[index];
	}

	inline constexpr StringView::const_reference StringView::front() const noexcept
	{
		assert(not empty() && "cannot call StringView::front(): on empty StringView");

		return m_view[0];
	}

	inline constexpr StringView::const_reference StringView::back() const noexcept
	{
		assert(not empty() && "cannot call StringView::back() on empty StringView");

		return m_view[m_view.length() - 1];
	}

	inline constexpr StringView::const_pointer StringView::data() const noexcept
	{
		return m_view.data();
	}

	inline constexpr StringView::size_type StringView::size() const noexcept
	{
		return m_view.size();
	}

	inline constexpr StringView::size_type StringView::size_bytes() const noexcept
	{
		return (m_view.size() * sizeof(value_type));
	}

	inline constexpr StringView::size_type StringView::length() const noexcept
	{
		return m_view.length();
	}

	inline constexpr StringView::size_type StringView::max_size() const noexcept
	{
		return std::numeric_limits<size_type>::max();
	}

	inline constexpr bool StringView::empty() const noexcept
	{
		return m_view.empty();;
	}

	inline constexpr bool StringView::isEmpty() const noexcept
	{
		return m_view.empty();
	}

	inline constexpr StringView::operator bool() const noexcept
	{
		return (not m_view.empty());
	}

	constexpr void StringView::remove_prefix(const size_type n) noexcept
	{
		m_view.remove_prefix(n);
	}

	inline constexpr void StringView::remove_suffix(const size_type n) noexcept
	{
		m_view.remove_suffix(n);
	}

	inline constexpr void StringView::swap(StringView& other) noexcept
	{
		m_view.swap(other.m_view);
	}

	inline constexpr void StringView::clear() noexcept
	{
		*this = StringView();
	}

	inline StringView::size_type StringView::copy(value_type* dst, const size_type n, const size_type pos) const
	{
		return m_view.copy(dst, n, pos);
	}

	inline constexpr StringView StringView::substr(const size_type pos, const size_type n) const
	{
		if (pos > m_view.size())
		{
			throw std::out_of_range("StringView::substr(): index out of range");
		}

		return StringView(m_view.data() + pos, Min(n, m_view.size() - pos));
	}

	inline constexpr int32 StringView::compare(const StringView s) const noexcept
	{
		return m_view.compare(s.m_view);
	}

	inline constexpr int32 StringView::compare(const size_type pos1, const size_type n1, const StringView s) const noexcept
	{
		return m_view.compare(pos1, n1, s.m_view);
	}

	inline constexpr int32 StringView::compare(const size_type pos1, const size_type n1, const StringView s, const size_type pos2, const size_type n2) const noexcept
	{
		return m_view.compare(pos1, n1, s.m_view, pos2, n2);
	}

	inline constexpr int32 StringView::compare(const value_type* s) const noexcept
	{
		return m_view.compare(s);
	}

	inline constexpr int32 StringView::compare(const size_type pos1, const size_type n1, const value_type* s) const noexcept
	{
		return m_view.compare(pos1, n1, s);
	}

	inline constexpr int32 StringView::compare(const size_type pos1, const size_type n1, const value_type* s, const size_type n2) const noexcept
	{
		return m_view.compare(pos1, n1, s, n2);
	}

	inline constexpr bool StringView::starts_with(const value_type ch) const noexcept
	{
		return (not empty()) && (front() == ch);
	}

	inline constexpr bool StringView::starts_with(const StringView s) const noexcept
	{
		return (m_view.size() >= s.size())
			&& (std::char_traits<value_type>::compare(m_view.data(), s.data(), s.size()) == 0);
	}

	inline bool StringView::ends_with(const value_type ch) const noexcept
	{
		return (not empty()) && (back() == ch);
	}

	inline constexpr bool StringView::ends_with(const StringView s) const noexcept
	{
		return (m_view.size() >= s.size())
			&& (std::char_traits<value_type>::compare(m_view.data() + m_view.size() - s.size(), s.data(), s.size()) == 0);
	}

	inline constexpr StringView::size_type StringView::indexOf(const StringView s, const size_type pos) const noexcept
	{
		return m_view.find(s.m_view, pos);
	}

	inline constexpr StringView::size_type StringView::indexOf(const value_type ch, const size_type pos) const noexcept
	{
		return m_view.find(ch, pos);
	}

	inline constexpr StringView::size_type StringView::indexOf(const value_type* s, const size_type pos, const size_type count) const noexcept
	{
		return m_view.find(s, pos, count);
	}

	inline constexpr StringView::size_type StringView::indexOf(const value_type* s, const size_type pos) const noexcept
	{
		return m_view.find(s, pos);
	}

	inline constexpr size_t StringView::indexOfNot(const value_type ch, const size_t pos) const noexcept
	{
		return m_view.find_first_not_of(ch, pos);
	}

	inline constexpr StringView::size_type StringView::lastIndexOf(const StringView s, const size_type pos) const noexcept
	{
		return m_view.rfind(s.m_view, pos);
	}

	inline constexpr StringView::size_type StringView::lastIndexOf(const value_type ch, const size_type pos) const noexcept
	{
		return m_view.rfind(ch, pos);
	}

	inline constexpr StringView::size_type StringView::lastIndexOf(const value_type* s, const size_type pos, const size_type count) const noexcept
	{
		return m_view.rfind(s, pos, count);
	}

	inline constexpr StringView::size_type StringView::lastIndexOf(const value_type* s, const size_type pos) const noexcept
	{
		return m_view.rfind(s, pos);
	}

	inline constexpr size_t StringView::lastIndexNotOf(const value_type ch, const size_t pos) const noexcept
	{
		return m_view.find_last_not_of(ch, pos);
	}

	inline constexpr size_t StringView::indexOfAny(const StringView anyof, const size_t pos) const noexcept
	{
		return m_view.find_first_of(anyof.m_view, pos);
	}

	inline constexpr size_t StringView::indexOfAny(const value_type* anyof, const size_t pos) const noexcept
	{
		return m_view.find_first_of(anyof, pos);
	}

	inline constexpr size_t StringView::lastIndexOfAny(const StringView anyof, const size_t pos) const noexcept
	{
		return m_view.find_last_of(anyof.m_view, pos);
	}

	inline constexpr size_t StringView::lastIndexOfAny(const value_type* anyof, const size_t pos) const noexcept
	{
		return m_view.find_last_of(anyof, pos);
	}

	inline constexpr size_t StringView::indexNotOfAny(const StringView anyof, const size_t pos) const noexcept
	{
		return m_view.find_first_not_of(anyof.m_view, pos);
	}

	inline constexpr size_t StringView::indexNotOfAny(const value_type* anyof, const size_t pos) const noexcept
	{
		return m_view.find_first_not_of(anyof, pos);
	}

	inline constexpr size_t StringView::lastIndexNotOfAny(const StringView anyof, const size_t pos) const noexcept
	{
		return m_view.find_last_not_of(anyof.m_view, pos);
	}

	inline constexpr size_t StringView::lastIndexNotOfAny(const value_type* anyof, const size_t pos) const noexcept
	{
		return m_view.find_last_not_of(anyof, pos);
	}

	inline constexpr bool StringView::includes(const value_type ch) const noexcept
	{
		return (indexOf(ch) != StringView::npos);
	}

	inline constexpr bool StringView::includes(const StringView s) const noexcept
	{
		return (indexOf(s) != StringView::npos);
	}

	inline void swap(StringView& a, StringView& b) noexcept
	{
		a.swap(b);
	}

	inline namespace Literals
	{
		inline namespace StringViewLiterals
		{
			inline constexpr StringView operator ""_sv(const char32_t* s, const size_t length) noexcept
			{
				return StringView(s, length);
			}
		}
	}
}

template <>
inline void std::swap(s3d::StringView& a, s3d::StringView& b) noexcept
{
	a.swap(b);
}
