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
	SIV3D_NAMED_PARAMETER(phi);					// Cylindrical
	SIV3D_NAMED_PARAMETER(y);					// Cylindrical

	SIV3D_NAMED_PARAMETER(angle);				// Line
	SIV3D_NAMED_PARAMETER(direction);			// Line

	SIV3D_NAMED_PARAMETER(center);				// Rect, RectF, Circle
	SIV3D_NAMED_PARAMETER(topLeft);				// Rect, RectF, Circle
	SIV3D_NAMED_PARAMETER(topRight);			// Rect, RectF, Circle
	SIV3D_NAMED_PARAMETER(bottomLeft);			// Rect, RectF, Circle
	SIV3D_NAMED_PARAMETER(bottomRight);			// Rect, RectF, Circle
	SIV3D_NAMED_PARAMETER(topCenter);			// Rect, RectF, Circle
	SIV3D_NAMED_PARAMETER(bottomCenter);		// Rect, RectF, Circle
	SIV3D_NAMED_PARAMETER(leftCenter);			// Rect, RectF, Circle
	SIV3D_NAMED_PARAMETER(rightCenter);			// Rect, RectF, Circle
	SIV3D_NAMED_PARAMETER(top);					// Rect, RectF
	SIV3D_NAMED_PARAMETER(bottom);				// Rect, RectF
	SIV3D_NAMED_PARAMETER(left);				// Rect, RectF
	SIV3D_NAMED_PARAMETER(right);				// Rect, RectF

	SIV3D_NAMED_PARAMETER(code);				// XMLReader

	SIV3D_NAMED_PARAMETER(sampleRate);			// Wave


	SIV3D_NAMED_PARAMETER(loopBegin);			// Audio
	SIV3D_NAMED_PARAMETER(loopEnd);				// Audio
}
