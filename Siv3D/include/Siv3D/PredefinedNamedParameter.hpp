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
# include "NamedParameter.hpp"

namespace s3d::Arg
{
	SIV3D_NAMED_PARAMETER(radix);				// ToString
	SIV3D_NAMED_PARAMETER(generator);			// Array, Image
	SIV3D_NAMED_PARAMETER(indexedGenerator);	// Array
	SIV3D_NAMED_PARAMETER(reserve);				// Array
	SIV3D_NAMED_PARAMETER(generator0_1);		// Image


	SIV3D_NAMED_PARAMETER(r);					// Circular
	SIV3D_NAMED_PARAMETER(theta);				// Circular

	SIV3D_NAMED_PARAMETER(angle);				// Line
	SIV3D_NAMED_PARAMETER(direction);			// Line

	SIV3D_NAMED_PARAMETER(center);				// Rectangle, Circle
	SIV3D_NAMED_PARAMETER(topLeft);				// Rectangle, Circle
	SIV3D_NAMED_PARAMETER(topRight);			// Rectangle, Circle
	SIV3D_NAMED_PARAMETER(bottomLeft);			// Rectangle, Circle
	SIV3D_NAMED_PARAMETER(bottomRight);			// Rectangle, Circle
	SIV3D_NAMED_PARAMETER(topCenter);			// Rectangle, Circle
	SIV3D_NAMED_PARAMETER(bottomCenter);		// Rectangle, Circle
	SIV3D_NAMED_PARAMETER(leftCenter);			// Rectangle, Circle
	SIV3D_NAMED_PARAMETER(rightCenter);			// Rectangle, Circle
	SIV3D_NAMED_PARAMETER(top);					// Rectangle
	SIV3D_NAMED_PARAMETER(bottom);				// Rectangle
	SIV3D_NAMED_PARAMETER(left);				// Rectangle
	SIV3D_NAMED_PARAMETER(right);				// Rectangle
}
