//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "Format.hpp"

namespace s3d
{
	/// @brief 
	/// @tparam Type 
	/// @param value 
	/// @param padding 
	/// @return 
	template <class Type>
	[[nodiscard]]
	inline String Pad(const Type& value, std::pair<int32, char32> padding);

	/// @brief 
	/// @param bytes 
	/// @return 
	[[nodiscard]]
	String FormatDataSize(int64 bytes);

	/// @brief 
	/// @tparam Int 
	/// @param value 
	/// @param separator 
	/// @return 
	SIV3D_CONCEPT_INTEGRAL
	[[nodiscard]]
	inline String ThousandsSeparate(Int value, StringView separator = U","_sv);

	/// @brief 
	/// @tparam Float
	/// @param value 
	/// @param decimalPlace 
	/// @param fixed 
	/// @param separator 
	/// @return 
	SIV3D_CONCEPT_FLOATING_POINT_
	[[nodiscard]]
	inline String ThousandsSeparate(Float value, int32 decimalPlace = 3, bool fixed = false, StringView separator = U","_sv);
}

# include "detail/FormatUtility.ipp"
