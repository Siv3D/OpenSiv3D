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

namespace s3d
{
	struct Line3D
	{
		Vec3 begin, end;

		Line3D() = default;

		Line3D(const Line3D&) = default;

		Line3D& operator=(const Line3D&) = default;

		Line3D(Line3D&&) = default;

		Line3D& operator=(Line3D&&) = default;

		constexpr Line3D(const Vec3& _begin, const Vec3& _end) noexcept
			: begin(_begin)
			, end(_end) {}

		void draw(const Mat4x4& vp, const ColorF& color = Palette::White) const;
	};


	struct alignas(16) SIMD_Line3D
	{
		SIMD_Float4 vec[2];

		SIMD_Line3D() = default;

		SIMD_Line3D(const SIMD_Line3D&) = default;

		SIMD_Line3D& operator=(const SIMD_Line3D&) = default;

		SIMD_Line3D(SIMD_Line3D&&) = default;

		SIMD_Line3D& operator=(SIMD_Line3D&&) = default;

		constexpr SIMD_Line3D(SIMD_Float4 _begin, SIMD_Float4 _end) noexcept
			: vec{ _begin, _end } {}

		SIMD_Line3D(const Float3& _begin, const Float3& _end) noexcept
			: vec{ { _begin, 0.0f }, { _end, 0.0f } } {}

		void draw(const Mat4x4& vp, const ColorF& color = Palette::White) const;
	};
}
