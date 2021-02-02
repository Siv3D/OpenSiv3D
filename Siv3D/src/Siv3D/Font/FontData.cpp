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

# include "FontData.hpp"

namespace s3d
{
	FontData::FontData(Null, const FT_Library library)
	{
		m_initialized = true;
	}

	FontData::FontData(const FT_Library library, const FilePathView filePath, const int32 fontSize, const FontStyle style)
	{




		m_initialized = true;
	}

	FontData::~FontData()
	{

	}

	bool FontData::isInitialized() const noexcept
	{
		return m_initialized;
	}
}
