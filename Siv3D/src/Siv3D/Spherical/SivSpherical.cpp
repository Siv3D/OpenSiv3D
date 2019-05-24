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

# include <Siv3D/Spherical.hpp>

namespace s3d
{
	Vec3 Spherical::operator +(const Vec3& v) const
	{
		return toVec3() + v;
	}

	Vec3 Spherical::operator -(const Vec3& v) const
	{
		return toVec3() - v;
	}

	void Formatter(FormatData& formatData, const Spherical& value)
	{
		Formatter(formatData, Vec3(value.r, value.theta, value.phi));
	}
}
