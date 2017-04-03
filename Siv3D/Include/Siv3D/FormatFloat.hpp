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
# include "Fwd.hpp"
# include "FormatInt.hpp"

namespace s3d
{
	namespace detail
	{
		String FormatFloat(double value, int32 decimalPlace, bool fixed);

		size_t FormatFloat(wchar(&dst)[384], double value, int32 decimalPlace, bool fixed);
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
	inline String ToString(const float value, const int32 decimalPlace = 3)
	{
		return detail::FormatFloat(value, decimalPlace, false);
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
	inline String ToString(const double value, const int32 decimalPlace = 3)
	{
		return detail::FormatFloat(value, decimalPlace, false);
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
	inline String ToString(const long double value, const int32 decimalPlace = 3)
	{
		return detail::FormatFloat(static_cast<double>(value), decimalPlace, false);
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
	inline String ToFixed(const float value, const int32 decimalPlace = 3)
	{
		return detail::FormatFloat(value, decimalPlace, true);
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
	inline String ToFixed(const double value, const int32 decimalPlace = 3)
	{
		return detail::FormatFloat(value, decimalPlace, true);
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
	inline String ToFixed(const long double value, const int32 decimalPlace = 3)
	{
		return detail::FormatFloat(static_cast<double>(value), decimalPlace, true);
	}
    
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
    inline uint32 AsUint(const float value) noexcept
    {
        static_assert(sizeof(uint32) == sizeof(float));
        return *static_cast<const uint32*>(static_cast<const void*>(&value));
    }
    
    /// <summary>
    /// 浮動小数点数値のビット列を整数として解釈します。
    /// </summary>
    /// <param name="value">
    /// 浮動小数点数値
    /// </param>
    /// <returns>
    /// ビット列を整数として解釈した値
    /// </returns>
    inline uint64 AsUint(const double value) noexcept
    {
        static_assert(sizeof(uint64) == sizeof(double));
        return *static_cast<const uint64*>(static_cast<const void*>(&value));
    }
    
    /// <summary>
    /// 浮動小数点数のビット表現を 2 進数の文字列で表します。
    /// </summary
    /// <param name="value">
    /// 数値
    /// </param>
    /// <returns>
    /// 変換した文字列
    /// </returns>
    inline String ToBinary(const float value)
    {
        return ToBinary(AsUint(value));
    }
    
    /// <summary>
    /// 浮動小数点数のビット表現を 2 進数の文字列で表します。
    /// </summary
    /// <param name="value">
    /// 数値
    /// </param>
    /// <returns>
    /// 変換した文字列
    /// </returns>
    inline String ToBinary(const double value)
    {
        return ToBinary(AsUint(value));
    }
    
    /// <summary>
    /// 浮動小数点数のビット表現を 8 進数の文字列で表します。
    /// </summary
    /// <param name="value">
    /// 数値
    /// </param>
    /// <returns>
    /// 変換した文字列
    /// </returns>
    inline String ToOctal(const float value)
    {
        return ToOctal(AsUint(value));
    }
    
    /// <summary>
    /// 浮動小数点数のビット表現を 8 進数の文字列で表します。
    /// </summary
    /// <param name="value">
    /// 数値
    /// </param>
    /// <returns>
    /// 変換した文字列
    /// </returns>
    inline String ToOctal(const double value)
    {
        return ToOctal(AsUint(value));
    }
    
    /// <summary>
    /// 浮動小数点数のビット表現を 16 進数の文字列で表します。
    /// </summary
    /// <param name="value">
    /// 数値
    /// </param>
    /// <returns>
    /// 変換した文字列
    /// </returns>
    inline String ToHex(const float value)
    {
        return ToHex(AsUint(value));
    }
    
    /// <summary>
    /// 浮動小数点数のビット表現を 16 進数の文字列で表します。
    /// </summary
    /// <param name="value">
    /// 数値
    /// </param>
    /// <returns>
    /// 変換した文字列
    /// </returns>
    inline String ToHex(const double value)
    {
        return ToHex(AsUint(value));
    }
}
