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

namespace s3d
{
	inline constexpr double DeadZone::operator ()(double value) const noexcept
	{
		if (type == DeadZoneType::None_)
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

	inline Vec2 DeadZone::operator ()(double x, double y) const noexcept
	{
		if (type == DeadZoneType::None_)
		{
			return{ x, y };
		}
		else if (type == DeadZoneType::Independent)
		{
			return{ operator()(x), operator()(y) };
		}

		const double dist = Vec2{ x, y }.length();
		const double t = operator()(dist);
		const double scale = (t > 0.0) ? (t / dist) : 0.0;

		return{ Clamp(x * scale, -1.0, 1.0), Clamp(y * scale, -1.0, 1.0) };
	}

	inline Vec2 DeadZone::operator ()(const Vec2 value) const noexcept
	{
		return operator()(value.x, value.y);
	}
}
