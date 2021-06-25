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
# include "Common.hpp"
# include "PointVector.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	struct Mat4x4;

	struct Line3D
	{
		Vec3 begin;

		Vec3 end;

		SIV3D_NODISCARD_CXX20
		Line3D() = default;

		SIV3D_NODISCARD_CXX20
		Line3D(const Line3D&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(double bx, double by, double bz, double ex, double ey, double ez) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(const Vec3& _begin, double ex, double ey, double ez) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(double bx, double by, double bz, const Vec3& _end) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Line3D(const Vec3& _begin, const Vec3& _end) noexcept;

		[[nodiscard]]
		Line3D toScreen(const Mat4x4& vp) const noexcept;

		[[nodiscard]]
		Line toScreenLine(const Mat4x4& vp) const noexcept;

		[[nodiscard]]
		constexpr Line asLine() const noexcept;
	};
}

# include "detail/Line3D.ipp"
