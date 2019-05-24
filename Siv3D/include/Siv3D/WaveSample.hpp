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
# include <utility>
# include "Fwd.hpp"

namespace s3d
{
	struct WaveSampleS16
	{
		int16 left;

		int16 right;

		WaveSampleS16() = default;

		explicit constexpr WaveSampleS16(int16 mono) noexcept
			: left(mono)
			, right(mono) {}

		constexpr WaveSampleS16(int16 _left, int16 _right) noexcept
			: left(_left)
			, right(_right) {}

		[[nodiscard]] constexpr WaveSample asWaveSample() const noexcept;

		[[nodiscard]] static constexpr WaveSampleS16 Zero()
		{
			return{ 0, 0 };
		}
	};

	struct WaveSample
	{
		float left;

		float right;

		WaveSample() = default;

		explicit constexpr WaveSample(float mono) noexcept
			: left(mono)
			, right(mono) {}

		constexpr WaveSample(float _left, float _right) noexcept
			: left(_left)
			, right(_right) {}

		explicit constexpr WaveSample(const WaveSampleS16& sample) noexcept
			: left(sample.left / 32768.0f)
			, right(sample.right / 32768.0f) {}

		constexpr WaveSample& operator =(const WaveSample& sample) = default;

		constexpr WaveSample& operator =(float mono) noexcept
		{
			left = right = mono;
			return *this;
		}

		constexpr WaveSample& operator =(const WaveSampleS16& sample) noexcept
		{
			left = sample.left / 32768.0f;
			right = sample.right / 32768.0f;
			return *this;
		}

		constexpr WaveSample& set(float mono) noexcept
		{
			left = right = mono;
			return *this;
		}

		constexpr WaveSample& set(float _left, float _right) noexcept
		{
			left = _left;
			right = _right;
			return *this;
		}

		constexpr WaveSample& set(const WaveSample& sample) noexcept
		{
			return operator =(sample);
		}

		constexpr WaveSample& set(const WaveSampleS16& sample) noexcept
		{
			return operator =(sample);
		}

		void swapChannel() noexcept
		{
			std::swap(left, right);
		}

		[[nodiscard]] constexpr WaveSampleS16 asWaveSampleS16() const noexcept
		{
			return WaveSampleS16{ static_cast<int16>(left * 32767), static_cast<int16>(right * 32767) };
		}

		[[nodiscard]] static constexpr WaveSample Zero()
		{
			return{ 0.0f, 0.0f };
		}
	};

	inline constexpr WaveSample WaveSampleS16::asWaveSample() const noexcept
	{
		return WaveSample{ left / 32768.0f, right / 32768.0f };
	}
}
