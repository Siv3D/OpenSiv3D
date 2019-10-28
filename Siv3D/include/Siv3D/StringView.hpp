//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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
# include "TypeTraits.hpp"

namespace s3d
{
	class StringView
	{
	public:

		using string_view_type			= std::u32string_view;
		using traits_type				= typename string_view_type::traits_type;
		using value_type				= typename string_view_type::value_type;
		using pointer					= typename string_view_type::pointer;
		using const_pointer				= typename string_view_type::const_pointer;
		using reference					= typename string_view_type::reference;
		using const_reference			= typename string_view_type::const_reference;
		using const_iterator			= typename string_view_type::const_iterator;
		using iterator					= typename string_view_type::iterator;
		using const_reverse_iterator	= typename string_view_type::const_reverse_iterator;
		using reverse_iterator			= typename string_view_type::reverse_iterator;
		using size_type					= typename string_view_type::size_type;
		using difference_type			= typename string_view_type::difference_type;

	private:

		string_view_type m_view;

	public:

		static constexpr size_type npos = size_type{ static_cast<size_type>(-1) };

		constexpr StringView() noexcept = default;

		constexpr StringView(const StringView&) noexcept = default;

		StringView(const std::u32string& text) noexcept
			: m_view(text) {}

		constexpr StringView(std::u32string_view sv) noexcept
			: m_view(sv) {}

		constexpr StringView(const value_type* text, const size_type count)
			: m_view(text, count) {}

		constexpr StringView(const value_type* text)
			: m_view(text) {}

		constexpr StringView& operator =(const StringView&) noexcept = default;

		[[nodiscard]] constexpr const_iterator begin() const noexcept
		{
			return m_view.begin();
		}

		[[nodiscard]] constexpr const_iterator end() const noexcept
		{
			return m_view.end();
		}

		[[nodiscard]] constexpr const_iterator cbegin() const noexcept
		{
			return m_view.cbegin();
		}

		[[nodiscard]] constexpr const_iterator cend() const noexcept
		{
			return m_view.cend();
		}

		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept
		{
			return m_view.rbegin();
		}

		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept
		{
			return m_view.rend();
		}

		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept
		{
			return m_view.crbegin();
		}

		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept
		{
			return m_view.crend();
		}

		[[nodiscard]] constexpr const_reference operator[](const size_type index) const
		{
			return m_view[index];
		}

		[[nodiscard]] constexpr const_reference at(const size_type index) const
		{
			if (index >= m_view.size())
			{
				throw std::out_of_range("StringView::at() index out of range");
			}

			return m_view[index];
		}

		[[nodiscard]] constexpr const_reference front() const
		{
			assert(!empty() && "cannot call StringView::front() on empty StringView");

			return m_view[0];
		}

		[[nodiscard]] constexpr const_reference back() const
		{
			assert(!empty() && "cannot call StringView::back() on empty StringView");

			return m_view[m_view.length() - 1];
		}

		[[nodiscard]] constexpr const_pointer data() const noexcept
		{
			return m_view.data();
		}

		[[nodiscard]] constexpr size_type size() const noexcept
		{
			return m_view.size();
		}

		[[nodiscard]] constexpr size_type size_bytes() const noexcept
		{
			return m_view.size() * sizeof(value_type);
		}

		[[nodiscard]] constexpr size_type length() const noexcept
		{
			return m_view.length();
		}

		[[nodiscard]] constexpr size_type max_size() const noexcept
		{
			return std::numeric_limits<size_type>::max();
		}

		[[nodiscard]] constexpr bool empty() const noexcept
		{
			return m_view.empty();;
		}

		[[nodiscard]] constexpr bool isEmpty() const noexcept
		{
			return m_view.empty();
		}

		[[nodiscard]] explicit constexpr operator bool() const noexcept
		{
			return (!m_view.empty());
		}

		constexpr void remove_prefix(const size_type n) noexcept
		{
			m_view.remove_prefix(n);
		}

		constexpr void remove_suffix(const size_type n) noexcept
		{
			m_view.remove_suffix(n);
		}

		constexpr void swap(StringView& other) noexcept
		{
			m_view.swap(other.m_view);
		}

		constexpr void clear() noexcept
		{
			*this = StringView();
		}

		size_type copy(value_type* dst, const size_type n, const size_type pos = 0) const
		{
			return m_view.copy(dst, n, pos);
		}

		[[nodiscard]] constexpr StringView substr(const size_type pos = 0, const size_type n = npos) const
		{
			if (pos > m_view.size())
			{
				throw std::out_of_range("StringView::substr()");
			}

			return StringView(m_view.data() + pos, std::min(n, m_view.size() - pos));
		}

		[[nodiscard]] constexpr int32 compare(const StringView sv) const noexcept
		{
			return m_view.compare(sv.m_view);
		}

		[[nodiscard]] constexpr int32 compare(const size_type pos1, const size_type n1, const StringView sv) const noexcept
		{
			return m_view.compare(pos1, n1, sv.m_view);
		}

		[[nodiscard]] constexpr int32 compare(const size_type pos1, const size_type n1, const StringView sv, const size_type pos2, const size_type n2) const noexcept
		{
			return m_view.compare(pos1, n1, sv.m_view, pos2, n2);
		}

		[[nodiscard]] constexpr int32 compare(const value_type* str) const noexcept
		{
			return m_view.compare(str);
		}

		[[nodiscard]] constexpr int32 compare(const size_type pos1, const size_type n1, const value_type* str) const noexcept
		{
			return m_view.compare(pos1, n1, str);
		}

		[[nodiscard]] constexpr int32 compare(const size_type pos1, const size_type n1, const value_type* str, const size_type n2) const noexcept
		{
			return m_view.compare(pos1, n1, str, n2);
		}

		[[nodiscard]] constexpr bool starts_with(const value_type ch) const
		{
			return !empty() && front() == ch;
		}

		[[nodiscard]] constexpr bool starts_with(const StringView text) const
		{
			return m_view.size() >= text.size() && std::char_traits<value_type>::compare(m_view.data(), text.data(), text.size()) == 0;
		}

		[[nodiscard]] bool ends_with(const value_type ch) const
		{
			return !empty() && back() == ch;
		}

		[[nodiscard]] constexpr bool ends_with(const StringView text) const
		{
			return m_view.size() >= text.size() && std::char_traits<value_type>::compare(m_view.data() + m_view.size() - text.size(), text.data(), text.size()) == 0;
		}

		[[nodiscard]] constexpr size_type indexOf(const StringView str, const size_type pos = 0) const noexcept
		{
			return m_view.find(str.m_view, pos);
		}

		[[nodiscard]] constexpr size_type indexOf(const value_type ch, const size_type pos = 0) const noexcept
		{
			return m_view.find(ch, pos);
		}

		[[nodiscard]] constexpr size_type indexOf(const value_type* str, const size_type pos, const size_type count) const noexcept
		{
			return m_view.find(str, pos, count);
		}

		[[nodiscard]] constexpr size_type indexOf(const value_type* str, const size_type pos = 0) const noexcept
		{
			return m_view.find(str, pos);
		}

		[[nodiscard]] constexpr size_t indexOfNot(const value_type ch, const size_t pos = 0) const noexcept
		{
			return m_view.find_first_not_of(ch, pos);
		}

		[[nodiscard]] constexpr size_type lastIndexOf(const StringView str, const size_type pos = npos) const noexcept
		{
			return m_view.rfind(str.m_view, pos);
		}

		[[nodiscard]] constexpr size_type lastIndexOf(const value_type ch, const size_type pos = npos) const noexcept
		{
			return m_view.rfind(ch, pos);
		}

		[[nodiscard]] constexpr size_type lastIndexOf(const value_type* str, const size_type pos, const size_type count) const noexcept
		{
			return m_view.rfind(str, pos, count);
		}

		[[nodiscard]] constexpr size_type lastIndexOf(const value_type* str, const size_type pos = npos) const noexcept
		{
			return m_view.rfind(str, pos);
		}

		[[nodiscard]] constexpr size_t lastIndexNotOf(const value_type ch, const size_t pos = npos) const noexcept
		{
			return m_view.find_last_not_of(ch, pos);
		}

		[[nodiscard]] constexpr size_t indexOfAny(const StringView anyof, const size_t pos = 0) const noexcept
		{
			return m_view.find_first_of(anyof.m_view, pos);
		}

		[[nodiscard]] constexpr size_t indexOfAny(const value_type* anyof, const size_t pos = 0) const noexcept
		{
			return m_view.find_first_of(anyof, pos);
		}

		[[nodiscard]] constexpr size_t lastIndexOfAny(const StringView anyof, const size_t pos = 0) const noexcept
		{
			return m_view.find_last_of(anyof.m_view, pos);
		}

		[[nodiscard]] constexpr size_t lastIndexOfAny(const value_type* anyof, const size_t pos = 0) const noexcept
		{
			return m_view.find_last_of(anyof, pos);
		}

		[[nodiscard]] constexpr size_t indexNotOfAny(const StringView anyof, const size_t pos = 0) const noexcept
		{
			return m_view.find_first_not_of(anyof.m_view, pos);
		}

		[[nodiscard]] constexpr size_t indexNotOfAny(const value_type* anyof, const size_t pos = 0) const noexcept
		{
			return m_view.find_first_not_of(anyof, pos);
		}

		[[nodiscard]] constexpr size_t lastIndexNotOfAny(const StringView anyof, const size_t pos = 0) const noexcept
		{
			return m_view.find_last_not_of(anyof.m_view, pos);
		}

		[[nodiscard]] constexpr size_t lastIndexNotOfAny(const value_type* anyof, const size_t pos = 0) const noexcept
		{
			return m_view.find_last_not_of(anyof, pos);
		}
	};


	//////////////////////////////////////////////////
	//
	//	Literals
	//
	//////////////////////////////////////////////////

	inline namespace Literals
	{
		inline namespace StringViewLiterals
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

	using FilePathView = StringView;

	template <class E>
	struct IsMemoryContiguousContainer<std::basic_string_view<E>> : std::bool_constant<std::is_trivially_copyable_v<E>> {};

	template <>
	struct IsMemoryContiguousContainer<StringView> : std::true_type {};
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
			return s3d::Hash::FNV1a(value.data(), value.size_bytes());
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
	inline void swap(s3d::StringView& a, s3d::StringView& b) noexcept
	{
		a.swap(b);
	}
}
