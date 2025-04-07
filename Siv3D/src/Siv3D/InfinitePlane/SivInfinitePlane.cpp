//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/InfinitePlane.hpp>
# include <Siv3D/Ray.hpp>

namespace s3d
{
	Optional<float> InfinitePlane::intersects(const Ray& ray) const noexcept
	{
		return ray.intersects(*this);
	}
}
