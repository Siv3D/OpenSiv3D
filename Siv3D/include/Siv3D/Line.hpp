//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// @brief 線分
	struct Line
	{
		using position_type	= Vec2;

		using value_type	= position_type::value_type;

		/// @brief 線分の開始位置
		position_type begin;

		/// @brief 線分の終点位置
		position_type end;

		SIV3D_NODISCARD_CXX20
		Line() = default;
	};
}

# include "detail/Line.ipp"
