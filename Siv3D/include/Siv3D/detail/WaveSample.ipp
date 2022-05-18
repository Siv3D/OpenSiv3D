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
		auto t	= left;
		left	= right;
		right	= t;
	}

	inline constexpr WaveSample WaveSampleS16::asWaveSample() const noexcept
	{
		return{ (left / 32768.0f), (right / 32768.0f) };
	}

	inline constexpr WaveSampleS16 WaveSampleS16::FromFloat32(const float mono) noexcept
	{
		return WaveSampleS16{ static_cast<int16>(Clamp(static_cast<int32>(mono * 32768), -32768, 32767)) };
	}

	inline constexpr WaveSampleS16 WaveSampleS16::FromFloat32(const float _left, const float _right) noexcept
	{
		return{ static_cast<int16>(Clamp(static_cast<int32>(_left * 32768), -32768, 32767)), static_cast<int16>(Clamp(static_cast<int32>(_right * 32768), -32768, 32767)) };
	}
	
	inline constexpr WaveSampleS16 WaveSampleS16::Zero() noexcept
	{
		return{ 0, 0 };
	}

	inline constexpr WaveSampleS16 WaveSampleS16::Min() noexcept
	{
		return{ Smallest<int16>, Smallest<int16> };
	}

	inline constexpr WaveSampleS16 WaveSampleS16::Max() noexcept
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
		: left{ (sample.left / 32768.0f) }
		, right{ (sample.right / 32768.0f) } {}

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

	inline constexpr WaveSample WaveSample::operator *(const float s) const noexcept
	{
		return{ (left * s), (right * s) };
	}

	inline constexpr WaveSample& WaveSample::operator *=(const float s) noexcept
	{
		left *= s;
		right *= s;
		return *this;
	}

	constexpr void WaveSample::clear() noexcept
	{
		left	= 0.0f;
		right	= 0.0f;
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
		auto t	= left;
		left	= right;
		right	= t;
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	constexpr WaveSample WaveSample::lerp(const WaveSample other, const Float f) const noexcept
	{
		return{ (left + (other.left - left) * static_cast<float>(f)), (right + (other.right - right) * static_cast<float>(f)) };
	}

	inline constexpr WaveSampleS16 WaveSample::asWaveSampleS16() const noexcept
	{
		return WaveSampleS16::FromFloat32(left, right);
	}

	inline constexpr WaveSample WaveSample::FromInt16(const int16 mono) noexcept
	{
		return WaveSample(mono / 32768.0f);
	}

	inline constexpr WaveSample WaveSample::FromInt16(const int16 _left, const int16 _right) noexcept
	{
		return{ (_left / 32768.0f), (_right / 32768.0f) };
	}

	inline constexpr WaveSample WaveSample::Zero() noexcept
	{
		return{ 0.0f, 0.0f };
	}

	inline constexpr WaveSample WaveSample::Min() noexcept
	{
		return{ -1.0f, -1.0f };
	}

	inline constexpr WaveSample WaveSample::Max() noexcept
	{
		return{ 1.0f, 1.0f };
	}
}
