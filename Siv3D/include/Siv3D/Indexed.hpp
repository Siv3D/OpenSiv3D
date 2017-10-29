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
# include <functional>

namespace s3d
{
	template <class Iterator>
	class IndexedIterator
	{
	private:

		size_t m_index = 0;

		Iterator m_it;

	public:

		using iterator_category	= typename std::iterator_traits<Iterator>::iterator_category;
		using value_type		= typename std::iterator_traits<Iterator>::value_type;
		using difference_type	= typename std::iterator_traits<Iterator>::difference_type;
		using pointer			= typename std::iterator_traits<Iterator>::pointer;
		using reference			= typename std::iterator_traits<Iterator>::reference;

		IndexedIterator(size_t index, Iterator it)
			: m_index(index)
			, m_it(it) {}

		IndexedIterator& operator ++()
		{
			++m_index;

			++m_it;
		
			return *this;
		}

		[[nodiscard]] auto operator *() const noexcept
		{
			if constexpr (std::is_lvalue_reference_v<decltype(*m_it)>)
			{
				return std::make_pair(m_index, std::ref(*m_it));
			}
			else
			{
				return std::make_pair(m_index, *m_it);
			}
		}

		[[nodiscard]] bool operator ==(const IndexedIterator& other) const
		{
			return m_it == other.m_it;
		}

		[[nodiscard]] bool operator !=(const IndexedIterator& other) const
		{
			return m_it != other.m_it;
		}
	};

	namespace detail
	{
		template <class Range>
		class Indexed_impl
		{
		private:

			const Range& m_range;

		public:

			Indexed_impl(const Range& range)
				: m_range(range) {}

			[[nodiscard]] auto begin() const
			{
				return IndexedIterator<decltype(std::begin(m_range))>(0, std::begin(m_range));
			}

			[[nodiscard]] auto end() const
			{
				return IndexedIterator<decltype(std::begin(m_range))>(std::size(m_range), std::end(m_range));
			}
		};
	}

	template <class Range>
	[[nodiscard]] inline detail::Indexed_impl<Range> Indexed(const Range& range)
	{
		return detail::Indexed_impl<Range>(range);
	}
}
