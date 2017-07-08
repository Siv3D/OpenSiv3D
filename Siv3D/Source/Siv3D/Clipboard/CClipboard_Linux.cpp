//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include "CClipboard_Linux.hpp"

namespace s3d
{
	CClipboard_Linux::CClipboard_Linux()
	{

	}

	CClipboard_Linux::~CClipboard_Linux()
	{

	}

	bool CClipboard_Linux::init()
	{
		// [Siv3D ToDo]
		return true;
	}

	bool CClipboard_Linux::hasChanged()
	{
		// [Siv3D ToDo]
		return false;
	}

	bool CClipboard_Linux::getText(String&)
	{
		// [Siv3D ToDo]
		return false;
	}

	bool CClipboard_Linux::getImage(Image&)
	{
		// [Siv3D ToDo]
		return false;
	}

	bool CClipboard_Linux::getFilePaths(Array<FilePath>&)
	{
		// [Siv3D ToDo]
		return false;
	}

	void CClipboard_Linux::setText(const String& text)
	{
		// [Siv3D ToDo]
	}

	void CClipboard_Linux::setImage(const Image& image)
	{
		// [Siv3D ToDo]
	}

	void CClipboard_Linux::clear()
	{
		// [Siv3D ToDo]
	}
}

# endif
