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
# include <type_traits>
# include <utility>
# include <array>

namespace s3d
{
	//////////////////////////////////////////////////
	//
	//	IsPair
	//
	//////////////////////////////////////////////////

	template <class Type>
	struct IsPair : std::false_type {};

	template <class T, class U>
	struct IsPair<std::pair<T, U>> : std::true_type {};

	/// <summary>
	/// 型 Type が std::pair であれば true, それ以外の場合は false
	/// True if Type is a std::pair, false otherwise
	/// </summary>
	template <class Type> constexpr bool IsPair_v = IsPair<Type>::value;

	//////////////////////////////////////////////////
	//
	//	IsMemoryContiguousContainer
	//
	//////////////////////////////////////////////////

	template <class Type, class = void>
	struct IsMemoryContiguousContainer : std::false_type {};

	template <class E, size_t N>
	struct IsMemoryContiguousContainer<std::array<E, N>> : std::bool_constant<std::is_trivially_copyable_v<E>> {};

	/// <summary>
	/// 型 Type がオブジェクトをメモリに連続して保存するコンテナであれば true, それ以外の場合は false
	/// True if Type is a container that stores objects in contiguous memory locations, false otherwise
	/// </summary>
	template <class Type> constexpr bool IsMemoryContiguousContainer_v = IsMemoryContiguousContainer<Type>::value;

	//////////////////////////////////////////////////
	//
	//	IsConvertibleToByteArrayView
	//
	//////////////////////////////////////////////////

	template <class Type>
	struct IsConvertibleToByteArrayView
		: std::bool_constant<std::is_trivially_copyable_v<Type> || IsMemoryContiguousContainer_v<Type>> {};

	/// <summary>
	/// 型 Type が ByteArrayView に変換可能であれば true, それ以外の場合は false
	/// True if Type is convertible to ByteArrayView, false otherwise
	/// </summary>
	template <class Type> constexpr bool IsConvertibleToByteArrayView_v = IsConvertibleToByteArrayView<Type>::value;

	//////////////////////////////////////////////////
	//
	//	IsBigInt
	//
	//////////////////////////////////////////////////
	template <class Type>
	struct IsBigInt : std::false_type {};

	/// <summary>
	/// 型 Type が BigInt であれば true, それ以外の場合は false
	/// True if Type is BigInt, false otherwise
	/// </summary>
	template <class Type> constexpr bool IsBigInt_v = IsBigInt<Type>::value;

	//////////////////////////////////////////////////
	//
	//	IsBigFloat
	//
	//////////////////////////////////////////////////
	template <class Type>
	struct IsBigFloat : std::false_type {};

	/// <summary>
	/// 型 Type が BigFloat であれば true, それ以外の場合は false
	/// True if Type is BigFloat, false otherwise
	/// </summary>
	template <class Type> constexpr bool IsBigFloat_v = IsBigFloat<Type>::value;

	//////////////////////////////////////////////////
	//
	//	IsBigNumber
	//
	//////////////////////////////////////////////////
	template <class Type>
	struct IsBigNumber : std::false_type {};

	/// <summary>
	/// 型 Type が BigInt か BigFloat のどちらかであれば true, それ以外の場合は false
	/// True if Type is either BigInt or BigFloat, false otherwise
	/// </summary>
	template <class Type> constexpr bool IsBigNumber_v = IsBigNumber<Type>::value;

	//////////////////////////////////////////////////
	//
	//	CommonFloat
	//
	//////////////////////////////////////////////////

	template <class T, class U, std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<U>>* = nullptr>
	struct CommonFloat
	{
		using type = std::conditional_t<!std::is_floating_point_v<T> && !std::is_floating_point_v<U>, double, std::common_type_t<T, U>>;
	};

	/// <summary>
	/// 混合した精度の数値型の計算結果として使う浮動小数点数型
	/// </summary>
	template <class T, class U>
	using CommonFloat_t = typename CommonFloat<T, U>::type;
}
