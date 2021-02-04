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
# include "Image.hpp"

namespace s3d
{
	struct SDFGlyph
	{
		Image image;

		int32 buffer = 0;

		int32 left = 0;

		int32 top = 0;

		int32 width = 0;

		int32 height = 0;

		double xAdvance = 0.0;

		double yAdvance = 0.0;

		double ascent = 0.0;
	
		double descent = 0.0;
	};
}
