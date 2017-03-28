//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Triangle.hpp>
# include <Siv3D/Circular.hpp>

namespace s3d
{
	Triangle::Triangle(const value_type sides, const value_type angle) noexcept
		: p0(Circular(1.0 / detail::Sqrt3 * sides, angle))
		, p1(Circular(1.0 / detail::Sqrt3 * sides, 2.0 * Math::OneThirdPi + angle))
		, p2(Circular(1.0 / detail::Sqrt3 * sides, 4.0 * Math::OneThirdPi + angle))
	{

	}
}
