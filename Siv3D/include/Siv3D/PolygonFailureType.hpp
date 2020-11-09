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

namespace s3d
{
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
