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

namespace s3d::experimental
{
	struct AABB
	{
		Vec3 center;

		Vec3 size;

		AABB() = default;

		AABB(const AABB&) = default;

		AABB& operator=(const AABB&) = default;

		AABB(AABB&&) = default;

		AABB& operator=(AABB&&) = default;

		constexpr AABB(const Vec3& _center, const Vec3& _size) noexcept
			: center(_center)
			, size(_size) {}

		void draw(const Mat4x4& vp, const ColorF& color) const;
	};
}
