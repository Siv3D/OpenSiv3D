//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
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

		uint32 numGlyphs = 0;

		bool hasColor = false;

		int32 fontPixelSize = 0;

		double spaceWidth = 0;

		int32 indentSize = 8;

		FontStyle style = FontStyle::Default;

		int16 ascender = 0;

		int16 descender = 0;

		[[nodiscard]]
		int32 height() const noexcept
		{
			return (static_cast<int32>(ascender) + descender);
		}
	};
}
