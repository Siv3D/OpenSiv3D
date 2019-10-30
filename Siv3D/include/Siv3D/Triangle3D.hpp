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
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "SIMD_Float4.hpp"

namespace s3d::experimental
{
	struct Triangle3D
	{
		Vec3 p0, p1, p2;

		Triangle3D() = default;

		Triangle3D(const Triangle3D&) = default;

		Triangle3D& operator=(const Triangle3D&) = default;

		Triangle3D(Triangle3D&&) = default;

		Triangle3D& operator=(Triangle3D&&) = default;

		constexpr Triangle3D(const Vec3& _p0, const Vec3& _p1, const Vec3& _p2) noexcept
			: p0(_p0)
			, p1(_p1)
			, p2(_p2) {}

		void draw(const Mat4x4& vp, const ColorF& color = Palette::White) const;
	};


	struct alignas(16) SIMD_Triangle3D
	{
		SIMD_Float4 vec[3];

		SIMD_Triangle3D() = default;

		SIMD_Triangle3D(const SIMD_Triangle3D&) = default;

		SIMD_Triangle3D& operator=(const SIMD_Triangle3D&) = default;

		SIMD_Triangle3D(SIMD_Triangle3D&&) = default;

		SIMD_Triangle3D& operator=(SIMD_Triangle3D&&) = default;

		constexpr SIMD_Triangle3D(SIMD_Float4 _p0, SIMD_Float4 _p1, SIMD_Float4 _p2) noexcept
			: vec{ _p0, _p1, _p2 } {}

		SIMD_Triangle3D(const Float3& _p0, const Float3& _p1, const Float3& _p2) noexcept
			: vec{ { _p0, 0.0f }, { _p1, 0.0f }, { _p2, 0.0f } } {}

		void draw(const Mat4x4& vp, const ColorF& color = Palette::White) const;
	};
}
