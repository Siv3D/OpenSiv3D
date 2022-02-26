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
# include "Common.hpp"
# include "Array.hpp"

namespace s3d
{
	template <class IndexType>
	class UnionFind
	{
	public:

		using index_type = IndexType;

		static constexpr size_t MaxSize = (static_cast<size_t>(std::numeric_limits<index_type>::max()) + 1);

		SIV3D_NODISCARD_CXX20
		UnionFind() = default;

		SIV3D_NODISCARD_CXX20
		explicit UnionFind(size_t n);

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		size_t size() const noexcept;

		[[nodiscard]]
		index_type find(index_type i) noexcept;

		[[nodiscard]]
		bool connected(index_type i, index_type k) noexcept;

		bool merge(index_type i, index_type k) noexcept;

		[[nodiscard]]
		size_t size(index_type i) noexcept;

		void reset() noexcept;

	private:

		Array<index_type> m_parents;

		Array<uint32> m_sizes;
	};
}

# include "detail/UnionFind.ipp"
