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
# include <ThirdParty/EnumBitmask/EnumBitmask.hpp>

namespace s3d
{
	enum class NormalComputation : uint32
	{
		/// @brief Compute normals using weight-by-angle
		WeightByAngle = 0x0,

		/// @brief Computes normals using weight-by-area
		WeightByArea = 0x1,

		/// @brief Compute normals with equal weights
		WeightEqual = 0x2,

		/// @brief Vertices are counter-clock-wise
		WindCCW = 0x4,

		Default = WeightByAngle,
	};
	DEFINE_BITMASK_OPERATORS(NormalComputation);
}
