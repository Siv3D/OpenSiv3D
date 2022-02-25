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
	inline InfinitePlane::InfinitePlane(const Float4 _vec) noexcept
		: value{ _vec } {}

	inline InfinitePlane::InfinitePlane(const aligned_float4 _vec) noexcept
		: value{ _vec } {}

	inline InfinitePlane::InfinitePlane(const Float3& point, const Float3& normal) noexcept
	{
		value = DirectX::XMPlaneFromPointNormal(SIMD_Float4{ point, 0.0f }, SIMD_Float4{ normal, 0.0f });
	}

	inline InfinitePlane::InfinitePlane(const Float3& p0, const Float3& p1, const Float3& p2) noexcept
	{
		value = DirectX::XMPlaneFromPoints(
			SIMD_Float4{ p0, 0.0f }, SIMD_Float4{ p1, 0.0f }, SIMD_Float4{ p2, 0.0f });
	}

	inline InfinitePlane& InfinitePlane::operator =(const aligned_float4 other) noexcept
	{
		value = other;
		return *this;
	}

	inline InfinitePlane& InfinitePlane::operator =(const SIMD_Float4 other) noexcept
	{
		value = other;
		return *this;
	}

	inline InfinitePlane::operator aligned_float4() const noexcept
	{
		return value.vec;
	}

	inline Float3 InfinitePlane::normal() const noexcept
	{
		return value.xyz();
	}
}
