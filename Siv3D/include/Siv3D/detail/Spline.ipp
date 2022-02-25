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
	namespace Spline
	{
		template <class PointType>
		inline constexpr PointType CalculateTangent(const PointType& p0, const PointType& p1, const PointType& p2, const double a, const double b) noexcept
		{
			return ((1 - a) * (1 + b)) / 2 * (p1 - p0) + ((1 - a) * (1 - b)) / 2 * (p2 - p1);
		}

		template <class PointType>
		inline constexpr PointType Hermite(const PointType& p0, const PointType& p1, const PointType& m0, const PointType& m1, const double t) noexcept
		{
			return (2 * (t * t * t) - 3 * (t * t) + 1) * p0 + ((t * t * t) - 2 * (t * t) + t) * m0 + ((t * t * t) - (t * t)) * m1 + (-2 * (t * t * t) + 3 * (t * t)) * p1;
		}

		template <class PointType>
		inline constexpr PointType CatmullRom(const PointType& p0, const PointType& p1, const PointType& p2, const PointType& p3, const double t) noexcept
		{
			return Hermite(p1, p2, CalculateTangent(p0, p1, p2), CalculateTangent(p1, p2, p3), t);
		}
	}
}
