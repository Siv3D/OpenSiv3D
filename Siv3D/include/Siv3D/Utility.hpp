﻿//-----------------------------------------------
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
# include <algorithm>
# include <type_traits>
# include "Common.hpp"
# include "Concepts.hpp"
# include "PlaceHolder.hpp"
# include "detail/Utility_detail.ipp"

namespace s3d
{
	//////////////////////////////////////////////////
	//
	//	Max
	//
	//////////////////////////////////////////////////

	template <class Type>
	[[nodiscard]]
	inline constexpr auto Max(const Type& a, PlaceHolder_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr auto Max(PlaceHolder_t, const Type& b) noexcept;

	[[nodiscard]]
	inline constexpr auto Max(PlaceHolder_t, PlaceHolder_t) noexcept;

	/// @brief 2 つの値のうち大きい方の値を返します。 | Returns the greater of the two.
	/// @tparam Type 比較する値の型
	/// @param a 比較する値 | A value to compare
	/// @param b 比較する値 | Another value to compare
	/// @return 2 つの値のうち大きい方の値。等しい場合は a | The greater of a and b. If they are equivalent, returns a
# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr Type Max(Type a, Type b) noexcept;

	/// @brief 2 つの値のうち大きい方の値を返します。 | Returns the greater of the two.
	/// @tparam Type 比較する値の型
	/// @param a 比較する値 | A value to compare
	/// @param b 比較する値 | Another value to compare
	/// @return 2 つの値のうち大きい方の値。等しい場合は a | The greater of a and b. If they are equivalent, returns a
# if __cpp_lib_concepts
	template <class Type>
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr const Type& Max(const Type& a, const Type& b) noexcept(noexcept(a < b));

	/// <summary>
	/// 渡された初期化リストの中で最大の値を返します。
	/// Returns the greatest of the values in initializer list.
	/// </summary>
	/// <param name="ilist">
	/// 比較する値の初期化リスト
	/// Initializer list with the values to compare 
	/// </param>
	/// <returns>
	/// 初期化リストの中で最大の値。複数が等しい場合はその中で最も左の値
	/// The greatest value in ilist. If several values are equivalent to the greatest, returns the leftmost one
	/// </returns>
	template <class Type>
	[[nodiscard]]
	inline constexpr Type Max(std::initializer_list<Type> ilist);

	//////////////////////////////////////////////////
	//
	//	Min
	//
	//////////////////////////////////////////////////

	template <class Type>
	[[nodiscard]]
	inline constexpr auto Min(const Type& a, PlaceHolder_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr auto Min(PlaceHolder_t, const Type& b) noexcept;

	[[nodiscard]]
	inline constexpr auto Min(PlaceHolder_t, PlaceHolder_t) noexcept;

	/// <summary>
	/// 2 つの値のうち小さい方の値を返します。
	/// Returns the lesser of the two.
	/// </summary>
	/// <param name="a">
	/// 比較する値
	/// A value to compare
	/// </param>
	/// <param name="b">
	/// 比較する値
	/// Another value to compare
	/// </param>
	/// <returns>
	/// 2 つの値のうち小さい方の値。等しい場合は a
	/// The greater of a and b. If they are equivalent, returns a
	/// </returns>
# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr Type Min(Type a, Type b) noexcept;

	/// <summary>
	/// 2 つの値のうち小さい方の値を返します。
	/// Returns the lesser of the two.
	/// </summary>
	/// <param name="a">
	/// 比較する値
	/// A value to compare
	/// </param>
	/// <param name="b">
	/// 比較する値
	/// Another value to compare
	/// </param>
	/// <returns>
	/// 2 つの値のうち小さい方の値。等しい場合は a
	/// The greater of a and b. If they are equivalent, returns a
	/// </returns>
# if __cpp_lib_concepts
	template <class Type>
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr const Type& Min(const Type& a, const Type& b) noexcept(noexcept(b < a));

	/// <summary>
	/// 渡された初期化リストの中で最小の値を返します。
	/// Returns the least of the values in initializer list.
	/// </summary>
	/// <param name="ilist">
	/// 比較する値の初期化リスト
	/// Initializer list with the values to compare 
	/// </param>
	/// <returns>
	/// 初期化リストの中で最小大の値。複数が等しい場合はその中で最も左の値
	/// The least value in ilist. If several values are equivalent to the least, returns the leftmost one
	/// </returns>
	template <class Type>
	[[nodiscard]]
	inline constexpr Type Min(std::initializer_list<Type> ilist);

	//////////////////////////////////////////////////
	//
	//	Clamp
	//
	//////////////////////////////////////////////////

	template <class Type>
	[[nodiscard]]
	constexpr auto Clamp(PlaceHolder_t, const Type& min, const Type& max) noexcept;

	/// <summary>
	/// 最小値と最大値の範囲にクランプした値を返します。
	/// Clamps the value to the specified minimum and maximum range
	/// </summary>
	/// <param name="v">
	/// クランプする値
	/// A value to clamp
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// v をクランプした値
	/// The clamped value for the v
	/// </returns>
# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr Type Clamp(Type v, Type min, Type max) noexcept;

	/// <summary>
	/// 最小値と最大値の範囲にクランプした値を返します。
	/// Clamps the value to the specified minimum and maximum range
	/// </summary>
	/// <param name="v">
	/// クランプする値
	/// A value to clamp
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// v をクランプした値
	/// The clamped value for the v
	/// </returns>
# if __cpp_lib_concepts
	template <class Type>
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr const Type& Clamp(const Type& v, const Type& min, const Type& max) noexcept(noexcept(max < v) && noexcept(v < min));

	//////////////////////////////////////////////////
	//
	//	InRange
	//
	//////////////////////////////////////////////////

	template <class Type>
	[[nodiscard]]
	inline constexpr auto InRange(PlaceHolder_t, const Type& min, const Type& max) noexcept;

	/// <summary>
	/// 値が閉区間 [min, max] にあるかを返します。
	/// Returns true if the value is in the closed interval [min, max]
	/// </summary>
	/// <param name="v">
	/// 調べる値
	/// A value
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// 閉区間 [min, max] にある場合 true, それ以外の場合は false
	/// Returns true if the value is in the closed interval [min, max], false otherwise
	/// </returns>
# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr bool InRange(Type v, Type min, Type max) noexcept;

	/// <summary>
	/// 値が閉区間 [min, max] にあるかを返します。
	/// Returns true if the value is in the closed interval [min, max]
	/// </summary>
	/// <param name="v">
	/// 調べる値
	/// A value
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// 閉区間 [min, max] にある場合 true, それ以外の場合は false
	/// Returns true if the value is in the closed interval [min, max], false otherwise
	/// </returns>
# if __cpp_lib_concepts
	template <class Type>
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr bool InRange(const Type& v, const Type& min, const Type& max) noexcept(noexcept(v < min));

	//////////////////////////////////////////////////
	//
	//	InOpenRange
	//
	//////////////////////////////////////////////////

	template <class Type>
	[[nodiscard]]
	inline constexpr auto InOpenRange(PlaceHolder_t, const Type& min, const Type& max) noexcept;

	/// <summary>
	/// 値が開区間 (min, max) にあるかを返します。
	/// Returns true if the value is in the open interval (min, max)
	/// </summary>
	/// <param name="v">
	/// 調べる値
	/// A value
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// 開区間 (min, max) にある場合 true, それ以外の場合は false
	/// Returns true if the value is in the open interval (min, max), false otherwise
	/// </returns>
# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr bool InOpenRange(Type v, Type min, Type max) noexcept;

	/// <summary>
	/// 値が開区間 (min, max) にあるかを返します。
	/// Returns true if the value is in the open interval (min, max)
	/// </summary>
	/// <param name="v">
	/// 調べる値
	/// A value
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// 開区間 (min, max) にある場合 true, それ以外の場合は false
	/// Returns true if the value is in the open interval (min, max), false otherwise
	/// </returns>
# if __cpp_lib_concepts
	template <class Type>
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr bool InOpenRange(const Type& v, const Type& min, const Type& max) noexcept(noexcept(v < min));

	//////////////////////////////////////////////////
	//
	//	Abs
	//
	//////////////////////////////////////////////////

	/// @brief 絶対値を計算する関数オブジェクトです。
	inline constexpr auto Abs = detail::Abs_impl{};

	//////////////////////////////////////////////////
	//
	//	AbsDiff
	//
	//////////////////////////////////////////////////

	SIV3D_CONCEPT_ARITHMETIC
	[[nodiscard]]
	inline constexpr auto AbsDiff(Arithmetic a, PlaceHolder_t) noexcept;

	SIV3D_CONCEPT_ARITHMETIC
	[[nodiscard]]
	inline constexpr auto AbsDiff(PlaceHolder_t, Arithmetic b) noexcept;

	[[nodiscard]]
	inline constexpr auto AbsDiff(PlaceHolder_t, PlaceHolder_t) noexcept;

	SIV3D_CONCEPT_ARITHMETIC
	[[nodiscard]]
	inline constexpr auto AbsDiff(Arithmetic a, Arithmetic b) noexcept;

	//////////////////////////////////////////////////
	//
	//	FromEnum
	//
	//////////////////////////////////////////////////

	/// @brief 列挙型を整数型に変換する関数オブジェクトです。
	inline constexpr auto FromEnum = detail::FromEnum_impl{};

	//////////////////////////////////////////////////
	//
	//	ToEnum
	//
	//////////////////////////////////////////////////

	/// @brief 整数を列挙型の値に変換する関数オブジェクトです。
	/// @tparam Enum 変換先の列挙型
	SIV3D_CONCEPT_ENUM
	inline constexpr auto ToEnum = detail::ToEnum_impl<Enum>{};

	//////////////////////////////////////////////////
	//
	//	IsOdd
	//
	//////////////////////////////////////////////////

	/// @brief 数が奇数かを判定する関数オブジェクトです。
	inline constexpr auto IsOdd = detail::IsOdd_impl{};

	//////////////////////////////////////////////////
	//
	//	IsEven
	//
	//////////////////////////////////////////////////

	/// @brief 数が偶数かを判定する関数オブジェクトです。
	inline constexpr auto IsEven = detail::IsEven_impl{};

	//////////////////////////////////////////////////
	//
	//	Identity
	//
	//////////////////////////////////////////////////

	/// @brief 渡された値をそのまま返す関数オブジェクトです。
	inline constexpr auto Identity = detail::Identity_impl{};

	//////////////////////////////////////////////////
	//
	//	Utility
	//
	//////////////////////////////////////////////////

	/// @brief コンテナから条件を満たす要素を削除します。
	/// @tparam Container コンテナの型
	/// @tparam Pred 条件の型
	/// @param c コンテナ
	/// @param pred 条件
	template <class Container, class Pred>
	inline void Erase_if(Container& c, Pred pred);

	/// @brief コンテナから条件を満たす要素を削除します。
	/// @tparam Container コンテナの型
	/// @tparam Pred 条件の型
	/// @param c コンテナ
	/// @param pred 条件
	template <class Container, class Pred>
	inline void EraseNodes_if(Container& c, Pred pred);
}

# include "detail/Utility.ipp"
