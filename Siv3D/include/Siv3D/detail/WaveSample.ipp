//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline constexpr WaveSampleS16::WaveSampleS16(const int16 mono) noexcept
		: left{ mono }
		, right{ mono } {}

	inline constexpr WaveSampleS16::WaveSampleS16(const int16 _left, const int16 _right) noexcept
		: left{ _left }
		, right{ _right } {}

	inline constexpr WaveSampleS16& WaveSampleS16::set(const int16 mono) noexcept
	{
		left	= mono;
		right	= mono;
		return *this;
	}

	inline constexpr WaveSampleS16& WaveSampleS16::set(const int16 _left, const int16 _right) noexcept
	{
		left	= _left;
		right	= _right;
		return *this;
	}

	inline constexpr WaveSampleS16& WaveSampleS16::set(const WaveSampleS16 sample) noexcept
	{
		left	= sample.left;
		right	= sample.right;
		return *this;
	}

	inline constexpr void WaveSampleS16::swapChannel() noexcept
	{
		std::swap(left, right);
	}

	inline constexpr WaveSample WaveSampleS16::asWaveSample() const noexcept
	{
		return{ (left / 32768.0f), (right / 32768.0f) };
	}

	inline constexpr WaveSampleS16 WaveSampleS16::FromFloat32(const float mono)
	{
		return WaveSampleS16{ static_cast<int16>(mono * 32767) };
	}

	inline constexpr WaveSampleS16 WaveSampleS16::FromFloat32(const float _left, const float _right)
	{
		return{ static_cast<int16>(_left * 32767), static_cast<int16>(_right * 32767) };
	}
	
	inline constexpr WaveSampleS16 WaveSampleS16::Zero()
	{
		return{ 0, 0 };
	}

	inline constexpr WaveSampleS16 WaveSampleS16::Min()
	{
		return{ Smallest<int16>, Smallest<int16> };
	}

	inline constexpr WaveSampleS16 WaveSampleS16::Max()
	{
		return{ Largest<int16>, Largest<int16> };
	}

	inline constexpr WaveSample::WaveSample(const float mono) noexcept
		: left{ mono }
		, right{ mono } {}

	inline constexpr WaveSample::WaveSample(const float _left, const float _right) noexcept
		: left{ _left }
		, right{ _right } {}

	inline constexpr WaveSample::WaveSample(const WaveSampleS16 sample) noexcept
		: WaveSample{ sample.asWaveSample() } {}

	inline constexpr WaveSample& WaveSample::operator =(const float mono) noexcept
	{
		left	= mono;
		right	= mono;
		return *this;
	}

	inline constexpr WaveSample& WaveSample::operator =(const WaveSampleS16 sample) noexcept
	{
		return (*this = sample.asWaveSample());
	}

	inline constexpr WaveSample& WaveSample::set(const float mono) noexcept
	{
		left	= mono;
		right	= mono;
		return *this;
	}

	inline constexpr WaveSample& WaveSample::set(const float _left, const float _right) noexcept
	{
		left	= _left;
		right	= _right;
		return *this;
	}

	inline constexpr WaveSample& WaveSample::set(const WaveSample sample) noexcept
	{
		left	= sample.left;
		right	= sample.right;
		return *this;
	}

	inline constexpr WaveSample& WaveSample::set(const WaveSampleS16 sample) noexcept
	{
		return (*this = sample.asWaveSample());
	}

	inline constexpr void WaveSample::swapChannel() noexcept
	{
		std::swap(left, right);
	}

	inline constexpr WaveSampleS16 WaveSample::asWaveSampleS16() const noexcept
	{
		return WaveSampleS16::FromFloat32(left, right);
	}

	inline constexpr WaveSample WaveSample::FromInt16(const int16 mono)
	{
		return WaveSample(mono / 32768.0f);
	}

	inline constexpr WaveSample WaveSample::FromInt16(const int16 _left, const int16 _right)
	{
		return{ (_left / 32768.0f), (_right / 32768.0f) };
	}

	inline constexpr WaveSample WaveSample::Zero()
	{
		return{ 0.0f, 0.0f };
	}

	inline constexpr WaveSample WaveSample::Min()
	{
		return{ -1.0f, -1.0f };
	}

	inline constexpr WaveSample WaveSample::Max()
	{
		return{ 1.0f, 1.0f };
	}
}
