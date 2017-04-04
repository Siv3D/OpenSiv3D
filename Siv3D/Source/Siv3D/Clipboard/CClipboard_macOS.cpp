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
	namespace detail
	{
		String ClipboardGetText_macOS();
		
		Image ClipboardGetImage_macOS();
		
		Array<FilePath> ClipboardGetFilePaths_macOS();
		
		void ClipboardClear_macOS();
		
		long ClipboardGetChangeCount_macOS();
	}
		
	CClipboard_macOS::CClipboard_macOS()
	{

	}

	CClipboard_macOS::~CClipboard_macOS()
	{

	}

	bool CClipboard_macOS::init()
	{
		m_changeCount = detail::ClipboardGetChangeCount_macOS();
		
		return true;
	}

	void CClipboard_macOS::update()
	{
		const uint64 currentChangeCount = detail::ClipboardGetChangeCount_macOS();
		
		m_hasChanged = (currentChangeCount != m_changeCount);
		
		m_changeCount = currentChangeCount;
		
		if (!m_hasChanged)
		{
			return;
		}

		m_text = detail::ClipboardGetText_macOS();

		m_image = detail::ClipboardGetImage_macOS();
		
		m_filePaths = detail::ClipboardGetFilePaths_macOS();
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
		detail::ClipboardClear_macOS();
		
		m_text.clear();
		m_image.clear();
		m_filePaths.clear();
	}
}

# endif
