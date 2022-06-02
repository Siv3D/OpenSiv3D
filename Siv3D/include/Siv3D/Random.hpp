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
# include "Concepts.hpp"
# include "SFMT.hpp"
# include "Distribution.hpp"

namespace s3d
{
	/// @brief デフォルトの乱数エンジンの種類 (PRNG::SFMT19937_64)
	using DefaultRNG = PRNG::SFMT19937_64;

	/// @brief 現在のスレッドの乱数エンジンの参照を返します。
	/// @return 現在のスレッドの乱数エンジン
	[[nodiscard]]
	DefaultRNG& GetDefaultRNG() noexcept;

	/// @brief 現在のスレッドの乱数エンジンのシード値を設定します。 
	/// @param seed シード値
	void Reseed(uint64 seed) noexcept;

	/// @brief 現在のスレッドの乱数エンジンのシード値配列を設定します。 
	/// @param seeds シード値配列
	void Reseed(const std::array<uint64, 16>& seeds) noexcept;

	/// @brief [0, 1) の範囲の乱数を返します。
	/// @remark グローバルな乱数エンジンを使用します。
	/// @return [0, 1) の範囲の乱数
	double Random() noexcept;

	/// @brief [0, 1) の範囲の乱数を返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param urbg 乱数エンジン
	/// @return [0, 1) の範囲の乱数
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline double Random(URBG&& urbg) noexcept;

	/// @brief 現在のスレッドの乱数エンジンを用いて、min 以上 max 以下の範囲の乱数を生成して返します。
	/// @tparam Arithmetic 生成する乱数の型
	/// @param min 生成する乱数の最小値
	/// @param max 生成する乱数の最大値
	/// @return 生成された乱数
	SIV3D_CONCEPT_ARITHMETIC
	[[nodiscard]]
	inline Arithmetic Random(Arithmetic min, Arithmetic max);

	/// @brief min 以上 max 以下の範囲の乱数を生成して返します。
	/// @tparam Arithmetic 生成する乱数の型
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param min 生成する乱数の最小値
	/// @param max 生成する乱数の最大値
	/// @param urbg 乱数エンジン
	/// @return 生成された乱数
# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Arithmetic, class URBG, std::enable_if_t<std::conjunction_v<std::is_arithmetic<Arithmetic>, std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
# endif
	[[nodiscard]]
	inline Arithmetic Random(Arithmetic min, Arithmetic max, URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、0 以上 max 以下の範囲の乱数を生成して返します。
	/// @tparam Arithmetic 生成する乱数の型
	/// @param max 生成する乱数の最大値
	/// @return 生成された乱数
	SIV3D_CONCEPT_ARITHMETIC
	[[nodiscard]]
	inline Arithmetic Random(Arithmetic max);

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Arithmetic, class URBG, std::enable_if_t<std::conjunction_v<std::is_arithmetic<Arithmetic>, std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
# endif
	[[nodiscard]]
	inline Arithmetic Random(Arithmetic max, URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、min より大きく max 未満の範囲の乱数を生成して返します。
	/// @tparam Arithmetic 生成する乱数の型
	/// @param min 生成する乱数の範囲の基準となる値（これより大きい）
	/// @param max 生成する乱数の範囲の基準となる値（これ未満）
	/// @return 生成された乱数
	SIV3D_CONCEPT_ARITHMETIC
	[[nodiscard]]
	inline Arithmetic RandomOpen(Arithmetic min, Arithmetic max);

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Arithmetic, class URBG, std::enable_if_t<std::conjunction_v<std::is_arithmetic<Arithmetic>, std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
# endif
	[[nodiscard]]
	inline Arithmetic RandomOpen(Arithmetic min, Arithmetic max, URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、min 以上 max 以下の範囲の乱数を生成して返します。
	/// @tparam Arithmetic 生成する乱数の型
	/// @param min 生成する乱数の最小値
	/// @param max 生成する乱数の最大値
	/// @remark Random(min, max) と同じです。
	/// @return 生成された乱数
	SIV3D_CONCEPT_ARITHMETIC
	[[nodiscard]]
	inline Arithmetic RandomClosed(Arithmetic min, Arithmetic max);

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Arithmetic, class URBG, std::enable_if_t<std::conjunction_v<std::is_arithmetic<Arithmetic>, std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
# endif
	[[nodiscard]]
	inline Arithmetic RandomClosed(Arithmetic min, Arithmetic max, URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、min より大きく max 以下の範囲の乱数を生成して返します。
	/// @tparam Arithmetic 生成する乱数の型
	/// @param min 生成する乱数の範囲の基準となる値（これより大きい）
	/// @param max 生成する乱数の最大値
	/// @return 生成された乱数
	SIV3D_CONCEPT_ARITHMETIC
	[[nodiscard]]
	inline Arithmetic RandomOpenClosed(Arithmetic min, Arithmetic max);

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Arithmetic, class URBG, std::enable_if_t<std::conjunction_v<std::is_arithmetic<Arithmetic>, std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
# endif
	[[nodiscard]]
	inline Arithmetic RandomOpenClosed(Arithmetic min, Arithmetic max, URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、min 以上 max 未満の範囲の乱数を生成して返します。
	/// @tparam Arithmetic 生成する乱数の型
	/// @param min 生成する乱数の最小値
	/// @param max 生成する乱数の範囲の基準となる値（これ未満）
	/// @return 生成された乱数
	SIV3D_CONCEPT_ARITHMETIC
	[[nodiscard]]
	inline Arithmetic RandomClosedOpen(Arithmetic min, Arithmetic max);

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Arithmetic, class URBG, std::enable_if_t<std::conjunction_v<std::is_arithmetic<Arithmetic>, std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
# endif
	[[nodiscard]]
	inline Arithmetic RandomClosedOpen(Arithmetic min, Arithmetic max, URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、指定した確率で true を返します。
	/// @param p 確率
	/// @return p で指定した確率に基づき、true または false
	[[nodiscard]]
	inline bool RandomBool(double p = 0.5) noexcept;

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline bool RandomBool(double p, URBG&& urbg) noexcept;

	/// @brief 現在のスレッドの乱数エンジンを用いて、uint8 型で表現されるランダムな値を返します。
	/// @return uint8 型のランダムな値
	[[nodiscard]]
	inline uint8 RandomUint8();

	/// @brief 指定した乱数エンジンを用いて、uint8 型で表現されるランダムな値を返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param urbg 使用する乱数エンジン
	/// @return uint8 型のランダムな値
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline uint8 RandomUint8(URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、uint16 型で表現されるランダムな値を返します。
	/// @return uint16 型のランダムな値
	[[nodiscard]]
	inline uint16 RandomUint16();

	/// @brief 指定した乱数エンジンを用いて、uint16 型で表現されるランダムな値を返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param urbg 使用する乱数エンジン
	/// @return uint16 型のランダムな値
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline uint16 RandomUint16(URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、uint32 型で表現されるランダムな値を返します。
	/// @return uint32 型のランダムな値
	[[nodiscard]]
	inline uint32 RandomUint32();

	/// @brief 指定した乱数エンジンを用いて、uint32 型で表現されるランダムな値を返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param urbg 使用する乱数エンジン
	/// @return uint32 型のランダムな値
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline uint32 RandomUint32(URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、uint64 型で表現されるランダムな値を返します。
	/// @return uint64 型のランダムな値
	[[nodiscard]]
	inline uint64 RandomUint64();

	/// @brief 指定した乱数エンジンを用いて、uint64 型で表現されるランダムな値を返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param urbg 使用する乱数エンジン
	/// @return uint64 型のランダムな値
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline uint64 RandomUint64(URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、int8 型で表現されるランダムな値を返します。
	/// @return int8 型のランダムな値
	[[nodiscard]]
	inline int8 RandomInt8();

	/// @brief 指定した乱数エンジンを用いて、int8 型で表現されるランダムな値を返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param urbg 使用する乱数エンジン
	/// @return int8 型のランダムな値
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline int8 RandomInt8(URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、int16 型で表現されるランダムな値を返します。
	/// @return int16 型のランダムな値
	[[nodiscard]]
	inline int16 RandomInt16();

	/// @brief 指定した乱数エンジンを用いて、int16 型で表現されるランダムな値を返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param urbg 使用する乱数エンジン
	/// @return int16 型のランダムな値
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline int16 RandomInt16(URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、int32 型で表現されるランダムな値を返します。
	/// @return int32 型のランダムな値
	[[nodiscard]]
	inline int32 RandomInt32();

	/// @brief 指定した乱数エンジンを用いて、int32 型で表現されるランダムな値を返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param urbg 使用する乱数エンジン
	/// @return int32 型のランダムな値
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline int32 RandomInt32(URBG&& urbg);

	/// @brief 現在のスレッドの乱数エンジンを用いて、int64 型で表現されるランダムな値を返します。
	/// @return int64 型のランダムな値
	[[nodiscard]]
	inline int64 RandomInt64();

	/// @brief 指定した乱数エンジンを用いて、int64 型で表現されるランダムな値を返します。
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param urbg 使用する乱数エンジン
	/// @return int64 型のランダムな値
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline int64 RandomInt64(URBG&& urbg);
}

# include "detail/Random.ipp"
