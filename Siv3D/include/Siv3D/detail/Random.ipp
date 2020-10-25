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

namespace s3d
{
	SIV3D_CONCEPT_ARITHMETIC_
	inline Arithmetic Random(const Arithmetic min, const Arithmetic max)
	{
		if constexpr (std::is_integral_v<Arithmetic>)
		{
			return UniformIntDistribution<Arithmetic>(min, max)(GetDefaultRNG());
		}
		else
		{
			return UniformRealDistribution<Arithmetic>(min, max)(GetDefaultRNG());
		}
	}

	inline Duration Random(const Duration& min, const Duration& max) noexcept
	{
		return Duration{ Random(min.count(), max.count()) };
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Arithmetic Random(const Arithmetic max)
	{
		return Random<Arithmetic>(0, max);
	}

	inline Duration Random(const Duration& max) noexcept
	{
		return Duration{ Random(max.count()) };
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Arithmetic RandomOpen(const Arithmetic min, const Arithmetic max)
	{
		return absl::Uniform(absl::IntervalOpen, GetDefaultRNG(), min, max);
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Arithmetic RandomClosed(const Arithmetic min, const Arithmetic max)
	{
		return absl::Uniform(absl::IntervalClosed, GetDefaultRNG(), min, max);
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Arithmetic RandomOpenClosed(const Arithmetic min, const Arithmetic max)
	{
		return absl::Uniform(absl::IntervalOpenClosed, GetDefaultRNG(), min, max);
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Arithmetic RandomClosedOpen(const Arithmetic min, const Arithmetic max)
	{
		return absl::Uniform(absl::IntervalClosedOpen, GetDefaultRNG(), min, max);
	}

	inline bool RandomBool(const double p) noexcept
	{
		return (GetDefaultRNG().generateReal() < p);
	}

	inline uint8 RandomUint8()
	{
		return UniformIntDistribution<uint8>(0)(GetDefaultRNG());
	}

	inline uint16 RandomUint16()
	{
		return UniformIntDistribution<uint16>(0)(GetDefaultRNG());
	}

	inline uint32 RandomUint32()
	{
		return UniformIntDistribution<uint32>(0)(GetDefaultRNG());
	}

	inline uint64 RandomUint64()
	{
		return UniformIntDistribution<uint64>(0)(GetDefaultRNG());
	}

	inline int8 RandomInt8()
	{
		return UniformIntDistribution<int8>(0)(GetDefaultRNG());
	}

	inline int16 RandomInt16()
	{
		return UniformIntDistribution<int16>(0)(GetDefaultRNG());
	}

	inline int32 RandomInt32()
	{
		return UniformIntDistribution<int32>(0)(GetDefaultRNG());
	}

	inline int64 RandomInt64()
	{
		return UniformIntDistribution<int64>(0)(GetDefaultRNG());
	}

	template <class Container>
	inline void Shuffle(Container& c)
	{
		std::shuffle(std::begin(c), std::end(c), GetDefaultRNG());
	}

	template <class RandomIt>
	inline void Shuffle(RandomIt first, RandomIt last)
	{
		std::shuffle(first, last, GetDefaultRNG());
	}
}
