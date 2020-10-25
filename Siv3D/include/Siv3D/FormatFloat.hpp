//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// 数値を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 数値
	/// </param>
	/// <param name="decimalPlace">
	/// 小数点以下の最大桁数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]]
	inline String ToString(float value, int32 decimalPlace = 3);

	/// <summary>
	/// 数値を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 数値
	/// </param>
	/// <param name="decimalPlace">
	/// 小数点以下の最大桁数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]]
	inline String ToString(double value, int32 decimalPlace = 3);

	/// <summary>
	/// 数値を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 数値
	/// </param>
	/// <param name="decimalPlace">
	/// 小数点以下の最大桁数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]]
	inline String ToString(long double value, int32 decimalPlace = 3);

	/// <summary>
	/// 数値を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 数値
	/// </param>
	/// <param name="decimalPlace">
	/// 小数点以下の最大桁数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]]
	inline String ToFixed(float value, int32 decimalPlace = 3);

	/// <summary>
	/// 数値を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 数値
	/// </param>
	/// <param name="decimalPlace">
	/// 小数点以下の最大桁数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]]
	inline String ToFixed(double value, int32 decimalPlace = 3);

	/// <summary>
	/// 数値を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 数値
	/// </param>
	/// <param name="decimalPlace">
	/// 小数点以下の最大桁数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]]
	inline String ToFixed(long double value, int32 decimalPlace = 3);

	/// <summary>
	/// 浮動小数点数のビット表現を 2 進数の文字列で表します。
	/// </summary
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]]
	String ToBinary(float value);

	/// <summary>
	/// 浮動小数点数のビット表現を 2 進数の文字列で表します。
	/// </summary
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]]
	String ToBinary(double value);

	/// <summary>
	/// 浮動小数点数のビット表現を 8 進数の文字列で表します。
	/// </summary
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]]
	String ToOctal(float value);

	/// <summary>
	/// 浮動小数点数のビット表現を 8 進数の文字列で表します。
	/// </summary
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]]
	String ToOctal(double value);

	/// <summary>
	/// 浮動小数点数のビット表現を 16 進数の文字列で表します。
	/// </summary
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]]
	String ToHex(float value);

	/// <summary>
	/// 浮動小数点数のビット表現を 16 進数の文字列で表します。
	/// </summary
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]]
	String ToHex(double value);
}

# include "detail/FormatFloat.ipp"
