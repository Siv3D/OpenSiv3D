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
		bool ClipboardGetText_macOS(String& text);
		
		bool ClipboardGetImage_macOS(Image& image);
		
		bool ClipboardGetFilePaths_macOS(Array<FilePath>& filePaths);
		
		
		void ClipboardSetText_macOS(const String& text);

		void ClipboardSetImage_macOS(const Image& image);
		
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

	bool CClipboard_macOS::hasChanged()
	{
		const uint64 currentChangeCount = detail::ClipboardGetChangeCount_macOS();
		
		m_hasChanged = (currentChangeCount != m_changeCount);
		
		m_changeCount = currentChangeCount;
		
		return m_hasChanged;
	}

	bool CClipboard_macOS::getText(String& text)
	{
		return detail::ClipboardGetText_macOS(text);
	}
	
	bool CClipboard_macOS::getImage(Image& image)
	{
		return detail::ClipboardGetImage_macOS(image);
	}
	
	bool CClipboard_macOS::getFilePaths(Array<FilePath>& paths)
	{
		return detail::ClipboardGetFilePaths_macOS(paths);
	}

	void CClipboard_macOS::setText(const String& text)
	{
		detail::ClipboardSetText_macOS(text);

		m_changeCount = detail::ClipboardGetChangeCount_macOS();
		m_hasChanged = true;
	}

	void CClipboard_macOS::setImage(const Image& image)
	{
		detail::ClipboardSetImage_macOS(image);

		m_changeCount = detail::ClipboardGetChangeCount_macOS();
		m_hasChanged = true;
	}

	void CClipboard_macOS::clear()
	{
		detail::ClipboardClear_macOS();
		
		m_changeCount = detail::ClipboardGetChangeCount_macOS();
		m_hasChanged = false;
	}
}

# endif
