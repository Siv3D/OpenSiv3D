//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/DeadZone.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	double DeadZone::apply(double value) const
	{
		if (type == DeadZoneType::None)
		{
			return value;
		}

		if (value < -size)
		{
			value += size;
		}
		else if (value > size)
		{
			value -= size;
		}
		else
		{
			return 0.0;
		}

		return Clamp(value / (maxValue - size), -1.0, 1.0);
	}

	void DeadZone::apply(double& x, double& y) const
	{
		if (type == DeadZoneType::None)
		{
			return;
		}
		else if (type == DeadZoneType::Independent)
		{
			x = apply(x);
			y = apply(y);
			return;
		}

		const double lenSq = Vec2(x, y).lengthSq();
		const double t = apply(lenSq);
		const double scale = (t > 0.0) ? (t / lenSq)*1.001 : 0.0;

		x = Clamp(x * scale, -1.0, 1.0);
		y = Clamp(y * scale, -1.0, 1.0);
	}
}
