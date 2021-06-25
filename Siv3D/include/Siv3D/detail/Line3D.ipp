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
	inline constexpr Line3D::Line3D(const double bx, const double by, const double bz, const double ex, const double ey, const double ez) noexcept
		: begin{ bx, by, bz }
		, end{ ex, ey, ez } {}

	inline constexpr Line3D::Line3D(const Vec3& _begin, const double ex, const double ey, const double ez) noexcept
		: begin{ _begin }
		, end{ ex, ey, ez } {}

	inline constexpr Line3D::Line3D(const double bx, const double by, const double bz, const Vec3& _end) noexcept
		: begin{ bx, by, bz }
		, end{ _end } {}

	inline constexpr Line3D::Line3D(const Vec3& _begin, const Vec3& _end) noexcept
		: begin{ _begin }
		, end{ _end } {}

	inline constexpr Line Line3D::asLine() const noexcept
	{
		return{ begin.xy(), end.xy() };
	}
}
