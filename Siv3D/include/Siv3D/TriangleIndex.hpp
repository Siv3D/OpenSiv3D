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
# include "Vertex2D.hpp"

namespace s3d
{
	/// @brief 三角形を構成する頂点インデックス
	struct alignas(alignof(Vertex2D::IndexType)) TriangleIndex
	{
		using value_type = Vertex2D::IndexType;

		/// @brief 頂点 0
		value_type i0;

		/// @brief 頂点 1
		value_type i1;

		/// @brief 頂点 2
		value_type i2;

		/// @brief すべてのインデックス値が 0 の TriangleIndex を返します。
		/// @return すべてのインデックス値が 0 の TriangleIndex
		[[nodiscard]] 
		static constexpr TriangleIndex Zero() noexcept;
	};

	/// @brief 三角形を構成する頂点インデックス
	struct TriangleIndex32
	{
		using value_type = uint32;

		/// @brief 頂点 0
		value_type i0;

		/// @brief 頂点 1
		value_type i1;

		/// @brief 頂点 2
		value_type i2;

		/// @brief すべてのインデックス値が 0 の TriangleIndex を返します。
		/// @return すべてのインデックス値が 0 の TriangleIndex
		[[nodiscard]]
		static constexpr TriangleIndex32 Zero() noexcept;
	};
}

# include "detail/TriangleIndex.ipp"
