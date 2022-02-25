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
# include "Math.hpp"

namespace s3d
{
	/// @brief ナビメッシュの設定
	struct NavMeshConfig
	{
		double cellSize	= 1.0;

		double cellHeight = 0.2;

		double agentMaxSlope = Math::ToRadians(45);

		double agentHeight = 2.0;

		double agentMaxClimb = 0.9;

		/// @brief エージェントの半径
		/// @remark これより狭い経路を通過できません
		double agentRadius = 0.25;
	};
}
