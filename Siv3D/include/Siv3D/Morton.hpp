//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// @brief 32-bit にエンコードされたモートン順序
	using Morton32 = uint32;

	/// @brief 64-bit にエンコードされたモートン順序
	using Morton64 = uint64;

	namespace Morton
	{
		/// @brief 2D 座標を 32-bit のモートン順序にエンコードして返します。
		/// @param x X 座標
		/// @param y Y 座標
		/// @return モートン順序
		[[nodiscard]]
		Morton32 Encode2D32(uint16 x, uint16 y) noexcept;
		
		/// @brief 2D 座標を 64-bit のモートン順序にエンコードして返します。
		/// @param x X 座標
		/// @param y Y 座標
		/// @return モートン順序
		[[nodiscard]]
		Morton64 Encode2D64(uint32 x, uint32 y) noexcept;

		/// @brief 2D 座標を 32-bit のモートン順序にエンコードして返します。
		/// @param pos 座標
		/// @return モートン順序
		[[nodiscard]]
		Morton32 Encode2D32(Point pos) noexcept;

		/// @brief 2D 座標を 64-bit のモートン順序にエンコードして返します。
		/// @param pos 座標
		/// @return モートン順序
		[[nodiscard]]
		Morton64 Encode2D64(Point pos) noexcept;

		/// @brief 32-bit のモートン順序を 2D 座標にデコードして返します。
		/// @param morton モートン順序
		/// @return 2D 座標
		[[nodiscard]]
		Point Decode2D32(Morton32 morton) noexcept;

		/// @brief 64-bit のモートン順序を 2D 座標にデコードして返します。
		/// @param morton モートン順序
		/// @return 2D 座標
		[[nodiscard]]
		Point Decode2D64(Morton64 morton) noexcept;

		/// @brief 3D 座標を 32-bit のモートン順序にエンコードして返します。
		/// @param x X 座標
		/// @param y Y 座標
		/// @param z Z 座標
		/// @return モートン順序
		[[nodiscard]]
		Morton32 Encode3D32(uint16 x, uint16 y, uint16 z) noexcept;

		/// @brief 3D 座標を 64-bit のモートン順序にエンコードして返します。
		/// @param x X 座標
		/// @param y Y 座標
		/// @param z Z 座標
		/// @return モートン順序
		[[nodiscard]]
		Morton64 Encode3D64(uint32 x, uint32 y, uint32 z) noexcept;

		/// @brief 3D 座標を 32-bit のモートン順序にエンコードして返します。
		/// @param pos 座標
		/// @return モートン順序
		[[nodiscard]]
		Morton32 Encode3D32(Point3D pos) noexcept;

		/// @brief 3D 座標を 64-bit のモートン順序にエンコードして返します。
		/// @param pos 座標
		/// @return モートン順序
		[[nodiscard]]
		Morton64 Encode3D64(Point3D pos) noexcept;

		/// @brief 32-bit のモートン順序を 3D 座標にデコードして返します。
		/// @param morton モートン順序
		/// @return 3D 座標
		[[nodiscard]]
		Point3D Decode3D32(Morton32 morton) noexcept;

		/// @brief 64-bit のモートン順序を 3D 座標にデコードして返します。
		/// @param morton モートン順序
		/// @return 3D 座標
		[[nodiscard]]
		Point3D Decode3D64(Morton64 morton) noexcept;
	}
}
