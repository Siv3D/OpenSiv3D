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
# include <Siv3D/Common.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FontStyle.hpp>

namespace s3d
{
	struct FontFaceProperty
	{
		String familiyName;

		String styleName;

		bool hasColor = false;

		int32 fontPixelSize = 0;

		double spaceWidth = 0;

		FontStyle style = FontStyle::Default;

		int16 ascender = 0;

		int16 descender = 0;
	};
}
