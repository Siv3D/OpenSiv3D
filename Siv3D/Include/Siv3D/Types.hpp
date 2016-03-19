//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cstdint>

namespace s3d
{
	/// <summary>
	/// 8 ビット符号付き整数
	/// </summary>
	using int8 = std::int8_t;

	/// <summary>
	/// 16 ビット符号付き整数
	/// </summary>
	using int16 = std::int16_t;

	/// <summary>
	/// 32 ビット符号付き整数
	/// </summary>
	using int32 = std::int32_t;

	/// <summary>
	/// 64 ビット符号付き整数
	/// </summary>
	using int64 = std::int64_t;

	/// <summary>
	/// 8 ビット符号なし整数
	/// </summary>
	using uint8 = std::uint8_t;

	/// <summary>
	/// 16 ビット符号なし整数
	/// </summary>
	using uint16 = std::uint16_t;

	/// <summary>
	/// 32 ビット符号なし整数
	/// </summary>
	using uint32 = std::uint32_t;

	/// <summary>
	/// 64 ビット符号なし整数
	/// </summary>
	using uint64 = std::uint64_t;

	/// <summary>
	/// 文字
	/// </summary>
	using wchar = wchar_t;
}
