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
	inline Triangle3D::Triangle3D(SIMD_Float4 _p0, SIMD_Float4 _p1, SIMD_Float4 _p2) noexcept
		: p0{ _p0 }
		, p1{ _p1 }
		, p2{ _p2 } {}

	inline Triangle3D::Triangle3D(const Float3& _p0, const Float3& _p1, const Float3& _p2) noexcept
		: p0{ _p0, 0.0f }
		, p1{ _p1, 0.0f }
		, p2{ _p2, 0.0f } {}

	inline Triangle3D& Triangle3D::set(const float x0, const float y0, const float z0, const float x1, const float y1, const float z1, const float x2, const float y2, const float z2) noexcept
	{
		p0.set(x0, y0, z0, 0.0f);
		p1.set(x1, y1, z1, 0.0f);
		p2.set(x2, y2, z2, 0.0f);
		return *this;
	}

	inline Triangle3D& Triangle3D::set(const Float3& _p0, const Float3& _p1, const Float3& _p2) noexcept
	{
		p0.set(_p0);
		p1.set(_p1);
		p2.set(_p2);
		return *this;
	}

	inline Triangle3D& Triangle3D::set(const SIMD_Float4 _p0, const SIMD_Float4 _p1, const SIMD_Float4 _p2) noexcept
	{
		p0 = _p0;
		p1 = _p1;
		p2 = _p2;
		return *this;
	}

	inline Triangle3D& Triangle3D::set(const Triangle3D& triangle) noexcept
	{
		return (*this = triangle);
	}


	inline Triangle3D Triangle3D::movedBy(const float x, const float y, const float z) const noexcept
	{
		const auto m = SIMD_Float4{ x, y, z, 0.0f };
		return{ (p0 + m), (p1 + m), (p2 + m) };
	}

	inline Triangle3D Triangle3D::movedBy(const Float3 v) const noexcept
	{
		const auto m = SIMD_Float4{ v, 0.0f };
		return{ (p0 + m), (p1 + m), (p2 + m) };
	}

	inline Triangle3D& Triangle3D::moveBy(const float x, const float y, const float z) noexcept
	{
		const auto m = SIMD_Float4{ x, y, z, 0.0f };
		p0 += m;
		p1 += m;
		p2 += m;
		return *this;
	}

	inline Triangle3D& Triangle3D::moveBy(const Float3 v) noexcept
	{
		const auto m = SIMD_Float4{ v, 0.0f };
		p0 += m;
		p1 += m;
		p2 += m;
		return *this;
	}


	inline Triangle3D Triangle3D::lerp(const Triangle3D& other, const double f) const noexcept
	{
		const float t = static_cast<float>(f);
		return{
			DirectX::XMVectorLerp(p0, other.p0, t),
			DirectX::XMVectorLerp(p1, other.p1, t),
			DirectX::XMVectorLerp(p2, other.p2, t)
		};
	}
}
