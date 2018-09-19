//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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

		constexpr WaveSample& operator =(const WaveSample& sample) = default;

		constexpr WaveSample& operator =(float mono) noexcept
		{
			left = right = mono;
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

		void swapChannel() noexcept
		{
			std::swap(left, right);
		}

		[[nodiscard]] constexpr WaveSampleS16 asS16() const noexcept
		{
			return WaveSampleS16{ static_cast<int16>(left * 32767), static_cast<int16>(right * 32767) };
		}

		[[nodiscard]] static constexpr WaveSample Zero()
		{
			return{ 0.0f, 0.0f };
		}
	};
}
