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
# include <iosfwd>

namespace s3d
{
//////////////////////////////////////////////////
//
//	Integer Types
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
//	Character Types
//
//////////////////////////////////////////////////

	/// <summary>
	/// UTF-8 character representation
	/// </summary>
	using char8 = char;

	/// <summary>
	/// UTF-16 character representation
	/// </summary>
	using char16 = char16_t;

	/// <summary>
	/// UTF-32 character representation
	/// </summary>
	using char32 = char32_t;


//////////////////////////////////////////////////
//
//	Input Stream
//
//////////////////////////////////////////////////

	using CIStream = std::istream;

	using WIStream = std::wistream;

	using IStream = std::basic_istream<char32>;


//////////////////////////////////////////////////
//
//	Output Stream
//
//////////////////////////////////////////////////

	using COStream = std::ostream;

	using WOStream = std::wostream;

	using OStream = std::basic_ostream<char32>;
}
