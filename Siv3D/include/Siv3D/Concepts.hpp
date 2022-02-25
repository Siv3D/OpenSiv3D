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
# include <type_traits>
# if  __has_include(<concepts>)
#	include <concepts>
# endif

# if __cpp_lib_concepts

namespace s3d
{
	namespace Concept
	{
		/// @brief 整数型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept Integral = std::is_integral_v<Type>;
		
		/// @brief 符号付整数型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept SignedIntegral = std::integral<Type> && (Type(-1) < Type(0));

		/// @brief 符号なし整数型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept UnsignedIntegral = std::integral<Type> && !SignedIntegral<Type>;

		/// @brief 浮動小数点数型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept FloatingPoint = std::is_floating_point_v<Type>;

		/// @brief 符号付数値型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept Signed = std::is_signed_v<Type>;

		/// @brief スカラー型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept Scalar = std::is_scalar_v<Type>;

		/// @brief 数値型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept Arithmetic = std::is_arithmetic_v<Type>;

		/// @brief 列挙型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept Enum = std::is_enum_v<Type>;

		/// @brief トリビアルコピー可能型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept TriviallyCopyable = std::is_trivially_copyable_v<Type>;

		/// @brief 一様ランダムビットジェネレータ型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept UniformRandomBitGenerator = (std::invocable<Type&> && std::unsigned_integral<std::invoke_result_t<Type&>>);
	}
}

# endif

# if __cpp_lib_concepts

	# define SIV3D_CONCEPT_INTEGRAL				template <s3d::Concept::Integral Int>
	# define SIV3D_CONCEPT_INTEGRAL_			template <s3d::Concept::Integral Int>
	# define SIV3D_CONCEPT_SIGNED_INTEGRAL		template <s3d::Concept::SignedIntegral SignedInt>
	# define SIV3D_CONCEPT_SIGNED_INTEGRAL_		template <s3d::Concept::SignedIntegral SignedInt>
	# define SIV3D_CONCEPT_UNSIGNED_INTEGRAL	template <s3d::Concept::UnsignedIntegral UnsignedInt>
	# define SIV3D_CONCEPT_UNSIGNED_INTEGRAL_	template <s3d::Concept::UnsignedIntegral UnsignedInt>
	# define SIV3D_CONCEPT_FLOATING_POINT		template <s3d::Concept::FloatingPoint Float>
	# define SIV3D_CONCEPT_FLOATING_POINT_		template <s3d::Concept::FloatingPoint Float>
	# define SIV3D_CONCEPT_SCALAR				template <s3d::Concept::Scalar Scalar>
	# define SIV3D_CONCEPT_SCALAR_				template <s3d::Concept::Scalar Scalar>
	# define SIV3D_CONCEPT_ARITHMETIC			template <s3d::Concept::Arithmetic Arithmetic>
	# define SIV3D_CONCEPT_ARITHMETIC_			template <s3d::Concept::Arithmetic Arithmetic>
	# define SIV3D_CONCEPT_ENUM					template <s3d::Concept::Enum Enum>
	# define SIV3D_CONCEPT_ENUM_				template <s3d::Concept::Enum Enum>
	# define SIV3D_CONCEPT_TRIVIALLY_COPYABLE	template <s3d::Concept::TriviallyCopyable TriviallyCopyable>
	# define SIV3D_CONCEPT_TRIVIALLY_COPYABLE_	template <s3d::Concept::TriviallyCopyable TriviallyCopyable>
	# define SIV3D_CONCEPT_URBG					template <s3d::Concept::UniformRandomBitGenerator URBG>
	# define SIV3D_CONCEPT_URBG_				template <s3d::Concept::UniformRandomBitGenerator URBG>
	# define SIV3D_CONCEPT_FORMATTABLE_ARGS		template <s3d::Concept::Formattable... Args>
	# define SIV3D_CONCEPT_FORMATTABLE_ARGS_	template <s3d::Concept::Formattable... Args>
	# define SIV3D_CONCEPT_FORMATTABLE			template <s3d::Concept::Formattable Formattable>
	# define SIV3D_CONCEPT_FORMATTABLE_			template <s3d::Concept::Formattable Formattable>

# else

	# define SIV3D_CONCEPT_INTEGRAL				template <class Int, std::enable_if_t<std::is_integral_v<Int>>* = nullptr>
	# define SIV3D_CONCEPT_INTEGRAL_			template <class Int, std::enable_if_t<std::is_integral_v<Int>>*>
	# define SIV3D_CONCEPT_SIGNED_INTEGRAL		template <class SignedInt, std::enable_if_t<std::conjunction_v<std::is_integral<SignedInt>, std::is_signed<SignedInt>>>* = nullptr>
	# define SIV3D_CONCEPT_SIGNED_INTEGRAL_		template <class SignedInt, std::enable_if_t<std::conjunction_v<std::is_integral<SignedInt>, std::is_signed<SignedInt>>>*>
	# define SIV3D_CONCEPT_UNSIGNED_INTEGRAL	template <class UnsignedInt, std::enable_if_t<std::conjunction_v<std::is_integral<UnsignedInt>, std::negation<std::is_signed<UnsignedInt>>>>* = nullptr>
	# define SIV3D_CONCEPT_UNSIGNED_INTEGRAL_	template <class UnsignedInt, std::enable_if_t<std::conjunction_v<std::is_integral<UnsignedInt>, std::negation<std::is_signed<UnsignedInt>>>>*>
	# define SIV3D_CONCEPT_FLOATING_POINT		template <class Float, std::enable_if_t<std::is_floating_point_v<Float>>* = nullptr>
	# define SIV3D_CONCEPT_FLOATING_POINT_		template <class Float, std::enable_if_t<std::is_floating_point_v<Float>>*>
	# define SIV3D_CONCEPT_SCALAR				template <class Scalar, std::enable_if_t<std::is_scalar_v<Scalar>>* = nullptr>
	# define SIV3D_CONCEPT_SCALAR_				template <class Scalar, std::enable_if_t<std::is_scalar_v<Scalar>>*>
	# define SIV3D_CONCEPT_ARITHMETIC			template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>* = nullptr>
	# define SIV3D_CONCEPT_ARITHMETIC_			template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>*>
	# define SIV3D_CONCEPT_ENUM					template <class Enum, std::enable_if_t<std::is_enum_v<Enum>>* = nullptr>
	# define SIV3D_CONCEPT_ENUM_				template <class Enum, std::enable_if_t<std::is_enum_v<Enum>>*>
	# define SIV3D_CONCEPT_TRIVIALLY_COPYABLE	template <class TriviallyCopyable, std::enable_if_t<std::is_trivially_copyable_v<TriviallyCopyable>>* = nullptr>
	# define SIV3D_CONCEPT_TRIVIALLY_COPYABLE_	template <class TriviallyCopyable, std::enable_if_t<std::is_trivially_copyable_v<TriviallyCopyable>>*>
	# define SIV3D_CONCEPT_URBG					template <class URBG, std::enable_if_t<std::conjunction_v<std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
	# define SIV3D_CONCEPT_URBG_				template <class URBG, std::enable_if_t<std::conjunction_v<std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>*>
	# define SIV3D_CONCEPT_FORMATTABLE_ARGS		template <class... Args>
	# define SIV3D_CONCEPT_FORMATTABLE_ARGS_	template <class... Args>
	# define SIV3D_CONCEPT_FORMATTABLE			template <class Formattable, class = decltype(Formatter(std::declval<FormatData&>(), std::declval<Formattable>()))>
	# define SIV3D_CONCEPT_FORMATTABLE_			template <class Formattable, class>

# endif
