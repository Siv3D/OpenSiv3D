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
# include <iterator>

namespace s3d
{
	template <class Iterator>
	class RangeIterator
	{
	public:

		using value_type		= typename Iterator::value_type;
		using difference_type	= typename Iterator::difference_type;
		using reference			= typename Iterator::reference;
		using size_type			= size_t;
		using const_iterator	= Iterator;
		using iterator			= Iterator;

	private:

		iterator m_begin, m_end;

	public:

		constexpr RangeIterator(iterator begin, iterator end)
			: m_begin(begin)
			, m_end(end) {}

		[[nodiscard]] constexpr iterator begin() const
		{
			return m_begin;
		}

		[[nodiscard]] constexpr iterator end() const
		{
			return m_end;
		}

		[[nodiscard]] constexpr size_type size() const
		{
			return std::distance(m_begin, m_end);
		}

		[[nodiscard]] constexpr bool empty() const
		{
			return m_begin == m_end;
		}

		[[nodiscard]] constexpr explicit operator bool() const
		{
			return !empty();
		}

		[[nodiscard]] constexpr bool equal(const RangeIterator& other) const
		{
			return m_begin == other.m_begin && m_end == other.m_end;
		}
	};
}
