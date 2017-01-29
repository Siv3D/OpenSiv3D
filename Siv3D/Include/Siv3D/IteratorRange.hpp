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
	template <class IteratorType>
	class IteratorRange
	{
	private:

		IteratorType m_begin, m_end;

	public:

		using value_type		= typename IteratorType::value_type;
		using difference_type	= typename IteratorType::difference_type;
		using reference			= typename IteratorType::reference;
		using size_type			= size_t;
		using const_iterator	= IteratorType;
		using iterator			= IteratorType;

		constexpr IteratorRange(iterator Begin, iterator End)
			: m_begin(Begin)
			, m_end(End) {}

		constexpr iterator begin() const
		{
			return m_begin;
		}

		constexpr iterator end() const
		{
			return m_end;
		}

		constexpr size_type size() const
		{
			return std::distance(m_begin, m_end);
		}

		constexpr bool empty() const
		{
			return m_begin == m_end;
		}

		constexpr explicit operator bool() const
		{
			return !empty();
		}

		constexpr bool equal(const IteratorRange& r) const
		{
			return m_begin == r.m_begin && m_end == r.m_end;
		}
	};
}
