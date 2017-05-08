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
# include <cstdint>
# include <cstddef>
# include "Platform.hpp"

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

	/// <summary>
	/// 文字プレフィックス
	/// </summary>
	# define S3DCHAR(x)      L ## x

	/// <summary>
	/// 文字列プレフィックス
	/// </summary>
	# define S3DSTR(x)      L ## x

	/// <summary>
	/// 文字列プレフィックス
	/// </summary>
	# define S3DWSTR(x)      L ## x
}
