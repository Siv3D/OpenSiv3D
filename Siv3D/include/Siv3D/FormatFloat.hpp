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
# include "PredefinedYesNo.hpp"

namespace s3d
{
	/// @brief 浮動小数点数を文字列に変換します。
	/// @param value 変換する数値
	/// @param decimalPlace 小数点以下の最大桁数
	/// @remark 小数点以下の末尾の 0 は省略されます。
	/// @return 変換後の文字列
	[[nodiscard]]
	inline String ToString(float value, int32 decimalPlace = 3);

	/// @brief 浮動小数点数を文字列に変換します。
	/// @param value 変換する数値
	/// @param decimalPlace 小数点以下の最大桁数
	/// @remark 小数点以下の末尾の 0 は省略されます。
	/// @return 変換後の文字列
	[[nodiscard]]
	inline String ToString(double value, int32 decimalPlace = 3);

	/// @brief 浮動小数点数を文字列に変換します。
	/// @param value 変換する数値
	/// @param decimalPlace 小数点以下の最大桁数
	/// @remark 小数点以下の末尾の 0 は省略されます。
	/// @return 変換後の文字列
	[[nodiscard]]
	inline String ToString(long double value, int32 decimalPlace = 3);

	/// @brief 浮動小数点数を文字列に変換します（表示桁数固定）。
	/// @param value 変換する数値
	/// @param decimalPlace 小数点以下の最大桁数
	/// @return 変換後の文字列
	[[nodiscard]]
	inline String ToFixed(float value, int32 decimalPlace = 3);

	/// @brief 浮動小数点数を文字列に変換します（表示桁数固定）。
	/// @param value 変換する数値
	/// @param decimalPlace 小数点以下の最大桁数
	/// @return 変換後の文字列
	[[nodiscard]]
	inline String ToFixed(double value, int32 decimalPlace = 3);

	/// @brief 浮動小数点数を文字列に変換します（表示桁数固定）。
	/// @param value 変換する数値
	/// @param decimalPlace 小数点以下の最大桁数
	/// @return 変換後の文字列
	[[nodiscard]]
	inline String ToFixed(long double value, int32 decimalPlace = 3);

	/// @brief 浮動小数点数のビット表現を 2 進数の文字列で表します。
	/// @param value 変換する数値
	/// @return 変換後の文字列
	[[nodiscard]]
	String ToBinary(float value);

	/// @brief 浮動小数点数のビット表現を 2 進数の文字列で表します。
	/// @param value 変換する数値
	/// @return 変換後の文字列
	[[nodiscard]]
	String ToBinary(double value);

	/// @brief 浮動小数点数のビット表現を 8 進数の文字列で表します。
	/// @param value 変換する数値
	/// @return 変換後の文字列
	[[nodiscard]]
	String ToOctal(float value);

	/// @brief 浮動小数点数のビット表現を 8 進数の文字列で表します。
	/// @param value 変換する数値
	/// @return 変換後の文字列
	[[nodiscard]]
	String ToOctal(double value);

	/// @brief 浮動小数点数のビット表現を 16 進数の文字列で表します。
	/// @param value 変換する数値
	/// @return 変換後の文字列
	[[nodiscard]]
	String ToHex(float value);

	/// @brief 浮動小数点数のビット表現を 16 進数の文字列で表します。
	/// @param value 変換する数値
	/// @return 変換後の文字列
	[[nodiscard]]
	String ToHex(double value);
}

# include "detail/FormatFloat.ipp"
