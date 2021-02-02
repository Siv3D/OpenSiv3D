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
# include <Siv3D/StringView.hpp>

extern "C"
{
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
}

namespace s3d
{
	class FontFace
	{
	public:

		FontFace() = default;

		~FontFace();

		bool load(const FT_Library library, const void* data, size_t size);

		bool load(const FT_Library library, FilePathView path);

	private:

		FT_Face m_face = nullptr;
	};
}
