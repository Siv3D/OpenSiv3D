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
	/// @tparam Scalar 比較する値の型
	/// @param a 比較する値 | A value to compare
	/// @param b 比較する値 | Another value to compare
	/// @return 2 つの値のうち大きい方の値。等しい場合は a | The greater of a and b. If they are equivalent, returns a
	SIV3D_CONCEPT_SCALAR
	[[nodiscard]]
	inline constexpr Scalar Max(Scalar a, Scalar b) noexcept;

	/// @brief 2 つの値のうち大きい方の値を返します。 | Returns the greater of the two.
	/// @tparam Type 比較する値の型
	/// @param a 比較する値 | A value to compare
	/// @param b 比較する値 | Another value to compare
	/// @return 2 つの値のうち大きい方の値。等しい場合は a | The greater of a and b. If they are equivalent, returns a
# if __cpp_lib_concepts
	template <class Type> requires (not std::is_scalar_v<Type>)
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr const Type& Max(const Type& a, const Type& b) noexcept(noexcept(a < b));

	/// @brief 渡された初期化リストの中で最大の値を返します。 | Returns the greatest of the values in initializer list.
	/// @tparam Type 比較する値の型
	/// @param ilist 比較する値の初期化リスト | Initializer list with the values to compare 
	/// @return 初期化リストの中で最大の値。複数が等しい場合はその中で最も左の値 | The greatest value in ilist. If several values are equivalent to the greatest, returns the leftmost one
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

	/// @brief 2 つの値のうち小さい方の値を返します。 | Returns the lesser of the two.
	/// @tparam Scalar 比較する値の型
	/// @param a 比較する値 | A value to compare
	/// @param b 比較する値 | Another value to compare
	/// @return 2 つの値のうち小さい方の値。等しい場合は a | The lesser of a and b. If they are equivalent, returns a
	SIV3D_CONCEPT_SCALAR
	[[nodiscard]]
	inline constexpr Scalar Min(Scalar a, Scalar b) noexcept;

	/// @brief 2 つの値のうち小さい方の値を返します。 | Returns the lesser of the two.
	/// @tparam Type 比較する値の型
	/// @param a 比較する値 | A value to compare
	/// @param b 比較する値 | Another value to compare
	/// @return 2 つの値のうち小さい方の値。等しい場合は a | The lesser of a and b. If they are equivalent, returns a
# if __cpp_lib_concepts
	template <class Type> requires (not std::is_scalar_v<Type>)
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr const Type& Min(const Type& a, const Type& b) noexcept(noexcept(b < a));

	/// @brief 渡された初期化リストの中で最小の値を返します。 | Returns the least of the values in initializer list.
	/// @tparam Type 比較する値の型
	/// @param ilist 比較する値の初期化リスト | Initializer list with the values to compare 
	/// @return 初期化リストの中で最小大の値。複数が等しい場合はその中で最も左の値 | The least value in ilist. If several values are equivalent to the least, returns the leftmost one
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

	/// @brief 最小値と最大値の範囲にクランプした値を返します。 | Clamps the value to the specified minimum and maximum range.
	/// @tparam Scalar 比較する値の型
	/// @param v クランプする値 | A value to clamp
	/// @param min 範囲の最小値 | The specified minimum range
	/// @param max 範囲の最大値 | The specified maximum range
	/// @return v をクランプした値 | The clamped value for the v
	SIV3D_CONCEPT_SCALAR
	[[nodiscard]]
	inline constexpr Scalar Clamp(Scalar v, Scalar min, Scalar max) noexcept;

	/// @brief 最小値と最大値の範囲にクランプした値を返します。 | Clamps the value to the specified minimum and maximum range.
	/// @tparam Type 比較する値の型
	/// @param v クランプする値 | A value to clamp
	/// @param min 範囲の最小値 | The specified minimum range
	/// @param max 範囲の最大値 | The specified maximum range
	/// @return v をクランプした値 | The clamped value for the v
# if __cpp_lib_concepts
	template <class Type> requires (not std::is_scalar_v<Type>)
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

	/// @brief 値が閉区間 [min, max] にあるかを返します。 | Returns true if the value is in the closed interval [min, max].
	/// @tparam Scalar 比較する値の型
	/// @param v 比較する値 | A value to compare
	/// @param min 範囲の最小値 | The specified minimum range
	/// @param max 範囲の最大値 | The specified maximum range
	/// @return 閉区間 [min, max] にある場合 true, それ以外の場合は false | Returns true if the value is in the closed interval [min, max], false otherwise
	SIV3D_CONCEPT_SCALAR
	[[nodiscard]]
	inline constexpr bool InRange(Scalar v, Scalar min, Scalar max) noexcept;

	/// @brief 値が閉区間 [min, max] にあるかを返します。 | Returns true if the value is in the closed interval [min, max].
	/// @tparam Type 比較する値の型
	/// @param v 比較する値 | A value to compare
	/// @param min 範囲の最小値 | The specified minimum range
	/// @param max 範囲の最大値 | The specified maximum range
	/// @return 閉区間 [min, max] にある場合 true, それ以外の場合は false | Returns true if the value is in the closed interval [min, max], false otherwise
# if __cpp_lib_concepts
	template <class Type> requires (not std::is_scalar_v<Type>)
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

	/// @brief 値が開区間 (min, max) にあるかを返します。 | Returns true if the value is in the open interval (min, max).
	/// @tparam Scalar 比較する値の型
	/// @param v 比較する値 | A value to compare
	/// @param min 範囲の最小値 | The specified minimum range
	/// @param max 範囲の最大値 | The specified maximum range
	/// @return 開区間 (min, max) にある場合 true, それ以外の場合は false | Returns true if the value is in the open interval (min, max), false otherwise
	SIV3D_CONCEPT_SCALAR
	[[nodiscard]]
	inline constexpr bool InOpenRange(Scalar v, Scalar min, Scalar max) noexcept;

	/// @brief 値が開区間 (min, max) にあるかを返します。 | Returns true if the value is in the open interval (min, max).
	/// @tparam Type 比較する値の型
	/// @param v 比較する値 | A value to compare
	/// @param min 範囲の最小値 | The specified minimum range
	/// @param max 範囲の最大値 | The specified maximum range
	/// @return 開区間 (min, max) にある場合 true, それ以外の場合は false | Returns true if the value is in the open interval (min, max), false otherwise
# if __cpp_lib_concepts
	template <class Type> requires (not std::is_scalar_v<Type>)
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
	
	/// @brief 差の絶対値を返します。
	/// @tparam Arithmetic 値の型
	/// @param a 1 つ目の値
	/// @param b 2 つ目の値
	/// @return 2 つの値の差の絶対値
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

	template <class T, class U>
	[[nodiscard]]
	inline constexpr bool CmpEqual(T lhs, U rhs) noexcept;

	template <class T, class U>
	[[nodiscard]]
	inline constexpr bool CmpNotEqual(T lhs, U rhs) noexcept;

	template <class T, class U>
	[[nodiscard]]
	inline constexpr bool CmpLess(T lhs, U rhs) noexcept;
}

# include "detail/Utility.ipp"
