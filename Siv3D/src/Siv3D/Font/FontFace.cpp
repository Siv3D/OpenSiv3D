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

# include "FontFace.hpp"

namespace s3d
{
	FontFace::~FontFace()
	{
		if (m_hbFont)
		{
			::hb_font_destroy(m_hbFont);
			m_hbFont = nullptr;
		}

		if (m_hbBuffer)
		{
			::hb_buffer_destroy(m_hbBuffer);
			m_hbBuffer = nullptr;
		}

		if (m_face)
		{
			::FT_Done_Face(m_face);
			m_face = nullptr;
		}
	}

	bool FontFace::load(const FT_Library library, const void* data, const size_t size)
	{
		if (const FT_Error error = ::FT_New_Memory_Face(library, static_cast<const FT_Byte*>(data), static_cast<FT_Long>(size), 0, &m_face))
		{
			if (error == FT_Err_Unknown_File_Format)
			{
				// unsupported format
			}
			else if (error)
			{
				// failed to open or load
			}

			return false;
		}

		return true;
	}

	bool FontFace::load(const FT_Library library, const FilePathView path)
	{
		if (const FT_Error error = ::FT_New_Face(library, path.narrow().c_str(), 0, &m_face))
		{
			if (error == FT_Err_Unknown_File_Format)
			{
				// unsupported format
			}
			else if (error)
			{
				// failed to open or load
			}

			return false;
		}

		return true;
	}
}
