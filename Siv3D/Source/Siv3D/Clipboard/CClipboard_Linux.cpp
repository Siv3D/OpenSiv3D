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
		return true;
	}

	void CClipboard_Linux::update()
	{

	}

	bool CClipboard_Linux::hasChanged()
	{
		return m_hasChanged;
	}

	bool CClipboard_Linux::hasText()
	{
		return !m_text.isEmpty();
	}

	bool CClipboard_Linux::hasImage()
	{
		return !m_image.isEmpty();
	}

	bool CClipboard_Linux::hasFilePaths()
	{
		return !m_filePaths.isEmpty();
	}

	const String& CClipboard_Linux::getText()
	{
		return m_text;
	}

	const Image& CClipboard_Linux::getImage()
	{
		return m_image;
	}

	const Array<FilePath>& CClipboard_Linux::getFilePaths()
	{
		return m_filePaths;
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
		m_hasChanged = false;
		m_text.clear();
		m_image.clear();
		m_filePaths.clear();
	}
}

# endif
