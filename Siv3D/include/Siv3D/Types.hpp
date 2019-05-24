//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cstdint>

namespace s3d
{
//////////////////////////////////////////////////
//
// 整数型
// Integer Types
//
//////////////////////////////////////////////////

	/// <summary>
	/// Signed integer type with width of 8 bits
	/// </summary>
	using int8 = std::int8_t;

	/// <summary>
	/// Signed integer type with width of 16 bits
	/// </summary>
	using int16 = std::int16_t;

	/// <summary>
	/// Signed integer type with width of 32 bits
	/// </summary>
	using int32 = std::int32_t;

	/// <summary>
	/// Signed integer type with width of 64 bits
	/// </summary>
	using int64 = std::int64_t;

	/// <summary>
	/// Unsigned integer type with width of 8 bits
	/// </summary>
	using uint8 = std::uint8_t;

	/// <summary>
	/// Unsigned integer type with width of 16 bits
	/// </summary>
	using uint16 = std::uint16_t;

	/// <summary>
	/// Unsigned integer type with width of 32 bits
	/// </summary>
	using uint32 = std::uint32_t;

	/// <summary>
	/// Unsigned integer type with width of 64 bits
	/// </summary>
	using uint64 = std::uint64_t;

//////////////////////////////////////////////////
//
// 文字型
// Character Types
//
//////////////////////////////////////////////////

	/// <summary>
	/// UTF-8 character
	/// </summary>
	using char8 = char;

	/// <summary>
	/// UTF-16 character
	/// </summary>
	using char16 = char16_t;

	/// <summary>
	/// UTF-32 character
	/// </summary>
	using char32 = char32_t;
}
