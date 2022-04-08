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
	/// @brief Disjoint Set Union (Union-Find)
	/// @tparam IndexType インデックスの型
	template <class IndexType>
	class DisjointSet
	{
	public:

		/// @brief インデックスの型
		using index_type = IndexType;

		/// @brief 現在のインデックスの型で保持可能な最大の要素数
		/// @remark 例えば、インデックス型が uint8 の場合は 256 個です。
		static constexpr size_t MaxSize = (static_cast<size_t>(std::numeric_limits<index_type>::max()) + 1);

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		DisjointSet() = default;

		/// @brief 要素数を指定して Union-Find を作成します。
		/// @param n 要素数
		SIV3D_NODISCARD_CXX20
		explicit DisjointSet(size_t n);

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

		[[nodiscard]]
		size_t countSets() const noexcept;

		void reset() noexcept;

	private:

		Array<index_type> m_parents;

		Array<uint32> m_sizes;
	};
}

# include "detail/DisjointSet.ipp"
