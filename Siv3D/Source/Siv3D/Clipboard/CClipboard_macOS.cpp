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
# if defined(SIV3D_TARGET_MACOS)

# include "CClipboard_macOS.hpp"

namespace s3d
{
	CClipboard_macOS::CClipboard_macOS()
	{

	}

	CClipboard_macOS::~CClipboard_macOS()
	{

	}

	bool CClipboard_macOS::init()
	{
		return true;
	}

	void CClipboard_macOS::update()
	{

	}

	bool CClipboard_macOS::hasChanged()
	{
		return m_hasChanged;
	}

	bool CClipboard_macOS::hasText()
	{
		return !m_text.isEmpty();
	}

	bool CClipboard_macOS::hasImage()
	{
		return !m_image.isEmpty();
	}

	bool CClipboard_macOS::hasFilePaths()
	{
		return !m_filePaths.isEmpty();
	}

	const String& CClipboard_macOS::getText()
	{
		return m_text;
	}

	const Image& CClipboard_macOS::getImage()
	{
		return m_image;
	}

	const Array<FilePath>& CClipboard_macOS::getFilePaths()
	{
		return m_filePaths;
	}

	void CClipboard_macOS::setText(const String& text)
	{
		// [Siv3D ToDo]
	}

	void CClipboard_macOS::setImage(const Image& image)
	{
		// [Siv3D ToDo]
	}

	void CClipboard_macOS::clear()
	{
		// [Siv3D ToDo]
	}
}

# endif
