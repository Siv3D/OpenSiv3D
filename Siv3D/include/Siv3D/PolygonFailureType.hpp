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
	/// @brief Polygon の入力頂点の検証結果
	enum class PolygonFailureType : uint8
	{
		/// @brief 問題なし
		OK,
		
		/// @brief 頂点の数が少ない
		FewPoints,
		
		WrongTopologicalDimension,
		
		/// @brief スパイクがある
		Spikes,
		
		/// @brief 重複する頂点がある
		DuplicatePoints,
		
		NotClosed,
		
		/// @brief 自己交差がある
		SelfIntersections,
		
		/// @brief 時計回りでない
		WrongOrientation,
		
		/// @brief 穴が外部にはみ出している
		InteriorRingsOutside,
		
		/// @brief 複数の穴が重なっている
		NestedInteriorRings,
		
		DisconnectedInterior,
		
		IntersectingInteriors,
		
		WrongCornerOrder,
		
		InvalidCoordinate,
		
		Unknown,
	};
}
