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
	inline UnionFind<IndexType>::UnionFind(const size_t n)
		: m_parents(n)
		, m_sizes(n, 1u)
	{
		assert(n <= MaxSize);

		std::iota(m_parents.begin(), m_parents.end(), static_cast<index_type>(0));
	}

	template <class IndexType>
	inline UnionFind<IndexType>::operator bool() const noexcept
	{
		return isEmpty();
	}

	template <class IndexType>
	inline bool UnionFind<IndexType>::isEmpty() const noexcept
	{
		return m_parents.empty();
	}

	template <class IndexType>
	inline size_t UnionFind<IndexType>::size() const noexcept
	{
		return m_parents.size();
	}

	template <class IndexType>
	inline typename UnionFind<IndexType>::index_type UnionFind<IndexType>::find(index_type i) noexcept
	{
		assert(i < size());

		// Path halving
		while (m_parents[i] != i)
		{
			i = m_parents[i] = m_parents[m_parents[i]];
		}

		return i;
	}

	template <class IndexType>
	inline bool UnionFind<IndexType>::connected(const index_type i, const index_type k) noexcept
	{
		return (find(i) == find(k));
	}

	template <class IndexType>
	inline bool UnionFind<IndexType>::merge(index_type i, index_type k) noexcept
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
	inline size_t UnionFind<IndexType>::size(const index_type i) noexcept
	{
		assert(i < size());

		return m_sizes[find(i)];
	}

	template <class IndexType>
	inline void UnionFind<IndexType>::reset() noexcept
	{
		std::iota(m_parents.begin(), m_parents.end(), static_cast<index_type>(0));

		std::fill(m_sizes.begin(), m_sizes.end(), 1u);
	}
}
