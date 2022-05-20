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
	template <class IndexType>
	inline DisjointSet<IndexType>::DisjointSet(const size_t n)
		: m_parents(n)
		, m_sizes(n, 1u)
	{
		assert(n <= MaxSize);

		std::iota(m_parents.begin(), m_parents.end(), static_cast<index_type>(0));
	}

	template <class IndexType>
	inline DisjointSet<IndexType>::operator bool() const noexcept
	{
		return isEmpty();
	}

	template <class IndexType>
	inline bool DisjointSet<IndexType>::isEmpty() const noexcept
	{
		return m_parents.empty();
	}

	template <class IndexType>
	inline size_t DisjointSet<IndexType>::size() const noexcept
	{
		return m_parents.size();
	}

	template <class IndexType>
	inline typename DisjointSet<IndexType>::index_type DisjointSet<IndexType>::find(index_type i) noexcept
	{
		assert(static_cast<size_t>(i) < size());

		// Path halving
		while (m_parents[i] != i)
		{
			i = m_parents[i] = m_parents[m_parents[i]];
		}

		return i;
	}

	template <class IndexType>
	inline bool DisjointSet<IndexType>::connected(const index_type i, const index_type k) noexcept
	{
		return (find(i) == find(k));
	}

	template <class IndexType>
	inline bool DisjointSet<IndexType>::merge(index_type i, index_type k) noexcept
	{
		i = find(i);
		k = find(k);

		if (i == k) // i and k are already in the same set
		{
			return false;
		}

		if (m_sizes[i] < m_sizes[k])
		{
			using std::swap;
			swap(i, k);
		}

		m_sizes[i] += m_sizes[k];
		m_parents[k] = i;

		return true;
	}

	template <class IndexType>
	inline size_t DisjointSet<IndexType>::size(const index_type i) noexcept
	{
		assert(static_cast<size_t>(i) < size());

		return m_sizes[find(i)];
	}

	template <class IndexType>
	inline size_t DisjointSet<IndexType>::countSets() const noexcept
	{
		size_t count = 0;

		const size_t size = m_parents.size();

		for (size_t i = 0; i < size; ++i)
		{
			if (static_cast<index_type>(i) == m_parents[i])
			{
				++count;
			}
		}

		return count;
	}

	template <class IndexType>
	inline void DisjointSet<IndexType>::reset() noexcept
	{
		std::iota(m_parents.begin(), m_parents.end(), static_cast<index_type>(0));

		std::fill(m_sizes.begin(), m_sizes.end(), 1u);
	}
}
