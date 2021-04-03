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
	inline constexpr double DeadZone::operator ()(double value) const noexcept
	{
		if (type == DeadZoneType::_None)
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

	inline constexpr Vec2 DeadZone::operator ()(double x, double y) const noexcept
	{
		if (type == DeadZoneType::_None)
		{
			return{ x, y };
		}
		else if (type == DeadZoneType::Independent)
		{
			x = operator()(x);
			y = operator()(y);
			return{ x, y };
		}

		const double lenSq = Vec2{ x, y }.lengthSq();
		const double t = operator()(lenSq);
		const double scale = (t > 0.0) ? (t / lenSq) * 1.001 : 0.0;

		x = Clamp(x * scale, -1.0, 1.0);
		y = Clamp(y * scale, -1.0, 1.0);

		return{ x, y };
	}

	inline constexpr Vec2 DeadZone::operator ()(const Vec2 value) const noexcept
	{
		return operator()(value.x, value.y);
	}
}
