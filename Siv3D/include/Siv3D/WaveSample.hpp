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

namespace s3d
{
	struct WaveSampleS16;
	struct WaveSample;

	struct WaveSampleS16
	{
		int16 left;

		int16 right;

		SIV3D_NODISCARD_CXX20
		WaveSampleS16() = default;

		SIV3D_NODISCARD_CXX20
		WaveSampleS16(const WaveSampleS16&) = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr WaveSampleS16(int16 mono) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr WaveSampleS16(int16 _left, int16 _right) noexcept;

		constexpr WaveSampleS16& operator =(const WaveSampleS16& sample) = default;

		constexpr WaveSampleS16& set(int16 mono) noexcept;

		constexpr WaveSampleS16& set(int16 _left, int16 _right) noexcept;

		constexpr WaveSampleS16& set(WaveSampleS16 sample) noexcept;

		constexpr void swapChannel() noexcept;

		[[nodiscard]]
		constexpr WaveSample asWaveSample() const noexcept;

		[[nodiscard]]
		static constexpr WaveSampleS16 FromFloat32(float mono) noexcept;

		[[nodiscard]]
		static constexpr WaveSampleS16 FromFloat32(float _left, float _right) noexcept;

		[[nodiscard]]
		static constexpr WaveSampleS16 Zero() noexcept;

		[[nodiscard]]
		static constexpr WaveSampleS16 Min() noexcept;

		[[nodiscard]]
		static constexpr WaveSampleS16 Max() noexcept;
	};

	struct WaveSample
	{
		float left;

		float right;

		SIV3D_NODISCARD_CXX20
		WaveSample() = default;

		SIV3D_NODISCARD_CXX20
		WaveSample(const WaveSample&) = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr WaveSample(float mono) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr WaveSample(float _left, float _right) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr WaveSample(WaveSampleS16 sample) noexcept;

		constexpr WaveSample& operator =(const WaveSample& sample) = default;

		constexpr WaveSample& operator =(float mono) noexcept;

		constexpr WaveSample& operator =(WaveSampleS16 sample) noexcept;

		[[nodiscard]]
		constexpr WaveSample operator *(float s) const noexcept;

		SIV3D_CONCEPT_FLOATING_POINT
		[[nodiscard]]
		friend constexpr WaveSample operator *(Float s, WaveSample v) noexcept
		{
			return (v * static_cast<float>(s));
		}

		constexpr WaveSample& operator *=(float s) noexcept;

		constexpr void clear() noexcept;

		constexpr WaveSample& set(float mono) noexcept;

		constexpr WaveSample& set(float _left, float _right) noexcept;

		constexpr WaveSample& set(WaveSample sample) noexcept;

		constexpr WaveSample& set(WaveSampleS16 sample) noexcept;

		constexpr void swapChannel() noexcept;

		SIV3D_CONCEPT_FLOATING_POINT
		[[nodiscard]]
		constexpr WaveSample lerp(WaveSample other, Float f) const noexcept;

		[[nodiscard]]
		constexpr WaveSampleS16 asWaveSampleS16() const noexcept;
		
		[[nodiscard]]
		static constexpr WaveSample FromInt16(int16 mono) noexcept;

		[[nodiscard]]
		static constexpr WaveSample FromInt16(int16 _left, int16 _right) noexcept;

		[[nodiscard]]
		static constexpr WaveSample Zero() noexcept;

		[[nodiscard]]
		static constexpr WaveSample Min() noexcept;

		[[nodiscard]]
		static constexpr WaveSample Max() noexcept;
	};

	static_assert(sizeof(WaveSampleS16) == 4);
	static_assert(sizeof(WaveSample) == 8);
}

# include "detail/WaveSample.ipp"
