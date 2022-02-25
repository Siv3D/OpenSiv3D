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
# include "Common.hpp"

namespace s3d
{
	namespace Spline
	{
		template <class PointType>
		[[nodiscard]]
		inline constexpr PointType CalculateTangent(const PointType& p0, const PointType& p1, const PointType& p2, const double a = 0.0, const double b = 0.0) noexcept;

		template <class PointType>
		[[nodiscard]]
		inline constexpr PointType Hermite(const PointType& p0, const PointType& p1, const PointType& m0, const PointType& m1, const double t) noexcept;

		template <class PointType>
		[[nodiscard]]
		inline constexpr PointType CatmullRom(const PointType& p0, const PointType& p1, const PointType& p2, const PointType& p3, const double t) noexcept;
	}
}

# include "detail/Spline.ipp"
