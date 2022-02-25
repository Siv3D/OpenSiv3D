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
# include "Optional.hpp"
# include "SIMD_Float4.hpp"

namespace s3d
{
	struct Ray;

	struct InfinitePlane
	{
		SIMD_Float4 value;

		SIV3D_NODISCARD_CXX20
		InfinitePlane() = default;

		SIV3D_NODISCARD_CXX20
		InfinitePlane(const InfinitePlane&) = default;

		SIV3D_NODISCARD_CXX20
		InfinitePlane(const Float3& point, const Float3& normal) noexcept;

		SIV3D_NODISCARD_CXX20
		InfinitePlane(const Float3& p0, const Float3& p1, const Float3& p2) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit InfinitePlane(Float4 _vec) noexcept;

		SIV3D_NODISCARD_CXX20
		InfinitePlane(aligned_float4 _vec) noexcept;

		InfinitePlane& operator =(const InfinitePlane&) = default;

		InfinitePlane& SIV3D_VECTOR_CALL operator =(aligned_float4 other) noexcept;

		InfinitePlane& SIV3D_VECTOR_CALL operator =(SIMD_Float4 other) noexcept;

		[[nodiscard]]
		SIV3D_VECTOR_CALL operator aligned_float4() const noexcept;

		[[nodiscard]]
		Float3 normal() const noexcept;


		[[nodiscard]]
		Optional<float> intersects(const Ray& ray) const noexcept;
	};
}

# include "detail/InfinitePlane.ipp"
