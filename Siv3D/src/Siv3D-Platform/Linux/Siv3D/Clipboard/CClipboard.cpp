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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "CClipboard.hpp"

namespace s3d
{
	CClipboard::CClipboard() {}

	CClipboard::~CClipboard()
	{
		LOG_SCOPED_TRACE(U"CClipboard::~CClipboard()");
	}

	void CClipboard::init()
	{
		LOG_SCOPED_TRACE(U"CClipboard::init()");

		m_window = static_cast<GLFWwindow*>(SIV3D_ENGINE(Window)->getHandle());
	}

	bool CClipboard::hasChanged()
	{
		// [Siv3D ToDo]
		return false;
	}

	bool CClipboard::getText(String& text)
	{
		if (m_window)
		{
			text = Unicode::Widen(::glfwGetClipboardString(m_window));
		}
		else
		{
			text.clear();
		}
		
		return (not text.isEmpty());
	}

	bool CClipboard::getImage(Image& image)
	{
		image.clear();

		// [Siv3D ToDo]

		return (not image.isEmpty());
	}

	bool CClipboard::getFilePaths(Array<FilePath>& paths)
	{
		paths.clear();

		// [Siv3D ToDo]

		return (not paths.isEmpty());
	}

	void CClipboard::setText(const String& text)
	{
		::glfwSetClipboardString(m_window, text.narrow().c_str());
	}

	void CClipboard::setImage(const Image&)
	{
		// [Siv3D ToDo]
	}

	void CClipboard::clear()
	{
		// [Siv3D ToDo]
	}
}
