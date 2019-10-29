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
# include "Quaternion.hpp"

namespace s3d::experimental
{
	struct OBB
	{
		Vec3 center;

		Vec3 size;

		Quaternion orientation;

		OBB() = default;

		OBB(const OBB&) = default;

		OBB& operator=(const OBB&) = default;

		OBB(OBB&&) = default;

		OBB& operator=(OBB&&) = default;

		constexpr OBB(const Vec3& _center, const Vec3& _size) noexcept
			: center(_center)
			, size(_size)
			, orientation(Quaternion::Identity()) {}

		constexpr OBB(const Vec3& _center, const Vec3& _size, const Quaternion& _orientation) noexcept
			: center(_center)
			, size(_size)
			, orientation(_orientation) {}

		void getCorners(std::array<Float3, 8>& corners) const;

		void draw(const Mat4x4& vp, const ColorF& color) const;
	};
}

