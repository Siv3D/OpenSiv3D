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

namespace s3d
{
	////////////////////////////////////////////////////////////////
	//
	//		AsUint
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 浮動小数点数値のビット列を整数として解釈します。
	/// </summary>
	/// <param name="value">
	///	浮動小数点数値
	/// </param>
	/// <returns>
	/// ビット列を整数として解釈した値
	/// </returns>
	{
		static_assert(sizeof(uint32) == sizeof(float), "");
		return *static_cast<const uint32*>(static_cast<const void*>(&value));
	}

	/// <summary>
	/// 浮動小数点数値のビット列を整数として解釈します。
	/// </summary>
	/// <param name="value">
	///	浮動小数点数値
	/// </param>
	/// <returns>
	/// ビット列を整数として解釈した値
	/// </returns>
	{
		static_assert(sizeof(uint64) == sizeof(double), "");
		return *static_cast<const uint64*>(static_cast<const void*>(&value));
	}

	/// <summary>
	/// 浮動小数点数値のビット列を整数として解釈します。
	/// </summary>
	/// <param name="value">
	///	浮動小数点数値
	/// </param>
	/// <returns>
	/// ビット列を整数として解釈した値
	/// </returns>
	{
		static_assert(sizeof(uint64) == sizeof(long double), "");
		return *static_cast<const uint64*>(static_cast<const void*>(&value));
	}

	/// <summary>
	/// 表現できる最大の数値を返します。
	/// </summary>
	/// <returns>
	/// 表現できる最大の数値
	/// </returns>
	template <class Type>
	inline constexpr Type Largest()
	{
		return std::numeric_limits<Type>::max();
	}

	/// <summary>
	/// 表現できる最小の数値を返します。
	/// </summary>
	/// <returns>
	/// 表現できる最小の数値
	/// </returns>
	template <class Type>
	inline constexpr Type Smallest()
	{
		return std::numeric_limits<Type>::lowest();
	}

	/// <summary>
	/// 正の無限大を返します。
	/// </summary>
	/// <returns>
	/// 正の無限大
	/// </returns>
	template<class Type>
	inline constexpr Type Infinity()
	{
		return std::numeric_limits<Type>::infinity();
	}
}
