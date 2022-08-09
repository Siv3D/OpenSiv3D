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
# include "String.hpp"
# include "Format.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	/// @brief 値を文字列に変換し、指定した文字数に満たない場合は埋め文字で埋めます。
	/// @tparam Type 変換する値の型
	/// @param value 変換する値
	/// @param padding 文字数と埋め文字のペア
	/// @return 変換した結果
	template <class Type>
	[[nodiscard]]
	inline String Pad(const Type& value, std::pair<int32, char32> padding);

	/// @brief 
	/// @param bytes 
	/// @return 
	[[nodiscard]]
	String FormatDataSize(int64 bytes);

	/// @brief 桁区切り記号を含めて、数値を文字列に変換した結果を返します。
	/// @tparam Int 整数型
	/// @param value 数値
	/// @param separator 桁区切り記号
	/// @return 変換した結果
	SIV3D_CONCEPT_INTEGRAL
	[[nodiscard]]
	inline String ThousandsSeparate(Int value, StringView separator = U","_sv);

	/// @brief 桁区切り記号を含めて、数値を文字列に変換した結果を返します。
	/// @tparam Float 浮動小数点数型
	/// @param value 数値
	/// @param decimalPlace 小数点数以下の桁数
	/// @param fixed 小数点数以下の桁数を固定する場合は `Fixed::Yes`, それ以外の場合は `Fixed::No`
	/// @param separator 桁区切り記号
	/// @return 変換した結果
	SIV3D_CONCEPT_FLOATING_POINT_
	[[nodiscard]]
	inline String ThousandsSeparate(Float value, int32 decimalPlace = 3, Fixed fixed = Fixed::No, StringView separator = U","_sv);

	/// @brief 文字列をパーセントエンコーディングした結果を返します。
	/// @param s 変換する文字列
	/// @return 変換した結果
	[[nodiscard]]
	String PercentEncode(StringView s);
}

# include "detail/FormatUtility.ipp"
