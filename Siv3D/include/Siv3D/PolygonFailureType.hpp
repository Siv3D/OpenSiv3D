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
# include "Common.hpp"

namespace s3d
{
	/// @brief Polygon の入力頂点の検証結果
	enum class PolygonFailureType : uint32
	{
		OK,
		
		FewPoints,
		
		WrongTopologicalDimension,
		
		Spikes,
		
		DuplicatePoints,
		
		NotClosed,
		
		SelfIntersections,
		
		WrongOrientation,
		
		InteriorRingsOutside,
		
		NestedInteriorRings,
		
		DisconnectedInterior,
		
		IntersectingInteriors,
		
		WrongCornerOrder,
		
		InvalidCoordinate,
		
		Unknown,
	};
}
