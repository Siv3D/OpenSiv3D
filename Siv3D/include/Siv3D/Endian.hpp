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

namespace s3d
{
	/// @brief エンディアンを変換します
	/// @param value エンディアンを変換する値
	/// @return エンディアン変換後の値
	[[nodiscard]]
	inline uint16 SwapEndian(uint16 value) noexcept;

	/// @brief エンディアンを変換します
	/// @param value エンディアンを変換する値
	/// @return エンディアン変換後の値
	[[nodiscard]]
	inline uint32 SwapEndian(uint32 value) noexcept;

	/// @brief エンディアンを変換します
	/// @param value エンディアンを変換する値
	/// @return エンディアン変換後の値
	[[nodiscard]]
	inline uint64 SwapEndian(uint64 value) noexcept;
}

# include "detail/Endian.ipp"
