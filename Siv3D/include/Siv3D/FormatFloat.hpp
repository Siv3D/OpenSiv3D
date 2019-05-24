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
# include "Fwd.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]] String FormatFloat(double value, int32 decimalPlace, bool fixed);

		[[nodiscard]] size_t FormatFloat(char32(&dst)[384], double value, int32 decimalPlace, bool fixed);
	}

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
	[[nodiscard]] String ToString(const float value, const int32 decimalPlace = 3);

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
	[[nodiscard]] String ToString(const double value, const int32 decimalPlace = 3);

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
	[[nodiscard]] String ToString(const long double value, const int32 decimalPlace = 3);

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
	[[nodiscard]] String ToFixed(const float value, const int32 decimalPlace = 3);

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
	[[nodiscard]] String ToFixed(const double value, const int32 decimalPlace = 3);

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
	[[nodiscard]] String ToFixed(const long double value, const int32 decimalPlace = 3);

	////////////////////////////////////////////////////////////////
	//
	//		AsUint
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 浮動小数点数値のビット列を整数として解釈します。
	/// </summary>
	/// <param name="value">
	/// 浮動小数点数値
	/// </param>
	/// <returns>
	/// ビット列を整数として解釈した値
	/// </returns>
	[[nodiscard]] uint32 AsUint(const float value) noexcept;

	/// <summary>
	/// 浮動小数点数値のビット列を整数として解釈します。
	/// </summary>
	/// <param name="value">
	/// 浮動小数点数値
	/// </param>
	/// <returns>
	/// ビット列を整数として解釈した値
	/// </returns>
	[[nodiscard]] uint64 AsUint(const double value) noexcept;

	/// <summary>
	/// 浮動小数点数のビット表現を 2 進数の文字列で表します。
	/// </summary
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToBinary(const float value);

	/// <summary>
	/// 浮動小数点数のビット表現を 2 進数の文字列で表します。
	/// </summary
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToBinary(const double value);

	/// <summary>
	/// 浮動小数点数のビット表現を 8 進数の文字列で表します。
	/// </summary
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToOctal(const float value);

	/// <summary>
	/// 浮動小数点数のビット表現を 8 進数の文字列で表します。
	/// </summary
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToOctal(const double value);

	/// <summary>
	/// 浮動小数点数のビット表現を 16 進数の文字列で表します。
	/// </summary
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToHex(const float value);

	/// <summary>
	/// 浮動小数点数のビット表現を 16 進数の文字列で表します。
	/// </summary
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToHex(const double value);
}
