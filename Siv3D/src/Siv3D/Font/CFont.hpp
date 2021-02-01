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
# include <Siv3D/Font.hpp>
# include "IFont.hpp"

extern "C"
{
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
}

namespace s3d
{
	class CFont final : public ISiv3DFont
	{
	private:

		FT_Library m_freeType = nullptr;

	public:

		CFont();

		~CFont();

		void init() override;

	};
}
