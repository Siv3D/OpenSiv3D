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

namespace s3d
{
	SIV3D_CONCEPT_URBG_
	inline double Random(URBG&& urbg) noexcept
	{
		if constexpr (std::is_same_v<std::decay_t<URBG>, DefaultRNG>)
		{
			return urbg.generateReal();
		}
		else
		{
			return RandomClosedOpen(0.0, 1.0, std::forward<URBG>(urbg));
		}
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Arithmetic Random(const Arithmetic min, const Arithmetic max)
	{
		return Random(min, max, GetDefaultRNG());
	}

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Arithmetic, class URBG, std::enable_if_t<std::conjunction_v<std::is_arithmetic<Arithmetic>, std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>*>
# endif
	[[nodiscard]]
	inline Arithmetic Random(const Arithmetic min, const Arithmetic max, URBG&& urbg)
	{
		if constexpr (std::is_integral_v<Arithmetic>)
		{
			return absl::Uniform(absl::IntervalClosed, std::forward<URBG>(urbg), min, max);
		}
		else
		{
			return absl::Uniform(absl::IntervalClosedOpen, std::forward<URBG>(urbg), min, max);
		}
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Arithmetic Random(const Arithmetic max)
	{
		return Random(max, GetDefaultRNG());
	}

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Arithmetic, class URBG, std::enable_if_t<std::conjunction_v<std::is_arithmetic<Arithmetic>, std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>*>
# endif
	[[nodiscard]]
	inline Arithmetic Random(const Arithmetic max, URBG&& urbg)
	{
		return Random<Arithmetic>(0, max, std::forward<URBG>(urbg));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Arithmetic RandomOpen(const Arithmetic min, const Arithmetic max)
	{
		return RandomOpen(min, max, GetDefaultRNG());
	}

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Arithmetic, class URBG, std::enable_if_t<std::conjunction_v<std::is_arithmetic<Arithmetic>, std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>*>
# endif
	[[nodiscard]]
	inline Arithmetic RandomOpen(const Arithmetic min, const Arithmetic max, URBG&& urbg)
	{
		return absl::Uniform(absl::IntervalOpen, std::forward<URBG>(urbg), min, max);
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Arithmetic RandomClosed(const Arithmetic min, const Arithmetic max)
	{
		return RandomClosed(min, max, GetDefaultRNG());
	}

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Arithmetic, class URBG, std::enable_if_t<std::conjunction_v<std::is_arithmetic<Arithmetic>, std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>*>
# endif
	[[nodiscard]]
	inline Arithmetic RandomClosed(const Arithmetic min, const Arithmetic max, URBG&& urbg)
	{
		return absl::Uniform(absl::IntervalClosed, std::forward<URBG>(urbg), min, max);
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Arithmetic RandomOpenClosed(const Arithmetic min, const Arithmetic max)
	{
		return RandomOpenClosed(min, max, GetDefaultRNG());
	}

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Arithmetic, class URBG, std::enable_if_t<std::conjunction_v<std::is_arithmetic<Arithmetic>, std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>*>
# endif
	[[nodiscard]]
	inline Arithmetic RandomOpenClosed(const Arithmetic min, const Arithmetic max, URBG&& urbg)
	{
		return absl::Uniform(absl::IntervalOpenClosed, std::forward<URBG>(urbg), min, max);
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Arithmetic RandomClosedOpen(const Arithmetic min, const Arithmetic max)
	{
		return RandomClosedOpen(min, max, GetDefaultRNG());
	}

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Arithmetic, class URBG, std::enable_if_t<std::conjunction_v<std::is_arithmetic<Arithmetic>, std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>*>
# endif
	[[nodiscard]]
	inline Arithmetic RandomClosedOpen(const Arithmetic min, const Arithmetic max, URBG&& urbg)
	{
		return absl::Uniform(absl::IntervalClosedOpen, std::forward<URBG>(urbg), min, max);
	}

	inline bool RandomBool(const double p) noexcept
	{
		return (GetDefaultRNG().generateReal() < p);
	}

	SIV3D_CONCEPT_URBG_
	inline bool RandomBool(double p, URBG&& urbg) noexcept
	{
		if constexpr (std::is_same_v<std::decay_t<URBG>, DefaultRNG>)
		{
			return (urbg.generateReal() < p);
		}
		else
		{
			return absl::Bernoulli(std::forward<URBG>(urbg), p);
		}
	}

	inline uint8 RandomUint8()
	{
		return RandomUint8(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline uint8 RandomUint8(URBG&& urbg)
	{
		return absl::Uniform<uint8>(std::forward<URBG>(urbg));
	}

	inline uint16 RandomUint16()
	{
		return RandomUint16(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline uint16 RandomUint16(URBG&& urbg)
	{
		return absl::Uniform<uint16>(std::forward<URBG>(urbg));
	}

	inline uint32 RandomUint32()
	{
		return RandomUint32(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline uint32 RandomUint32(URBG&& urbg)
	{
		return absl::Uniform<uint32>(std::forward<URBG>(urbg));
	}

	inline uint64 RandomUint64()
	{
		return RandomUint64(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline uint64 RandomUint64(URBG&& urbg)
	{
		return absl::Uniform<uint64>(std::forward<URBG>(urbg));
	}

	inline int8 RandomInt8()
	{
		return RandomInt8(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline int8 RandomInt8(URBG&& urbg)
	{
		return absl::Uniform(absl::IntervalOpenClosed, std::forward<URBG>(urbg), Smallest<int8>, Largest<int8>);
	}

	inline int16 RandomInt16()
	{
		return RandomInt16(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline int16 RandomInt16(URBG&& urbg)
	{
		return absl::Uniform(absl::IntervalOpenClosed, std::forward<URBG>(urbg), Smallest<int16>, Largest<int16>);
	}

	inline int32 RandomInt32()
	{
		return RandomInt32(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline int32 RandomInt32(URBG&& urbg)
	{
		return absl::Uniform(absl::IntervalOpenClosed, std::forward<URBG>(urbg), Smallest<int32>, Largest<int32>);
	}

	inline int64 RandomInt64()
	{
		return RandomInt64(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline int64 RandomInt64(URBG&& urbg)
	{
		return absl::Uniform(absl::IntervalOpenClosed, std::forward<URBG>(urbg), Smallest<int64>, Largest<int64>);
	}
}
