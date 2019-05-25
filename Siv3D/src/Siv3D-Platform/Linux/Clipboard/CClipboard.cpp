//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

//# include <X11/Xlib.h>

# include <Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Window/IWindow.hpp>
# include "CClipboard.hpp"

namespace s3d
{
	CClipboard::CClipboard()
	{
	}

	CClipboard::~CClipboard()
	{
		LOG_TRACE(U"CClipboard::~CClipboard()");
	}

	void CClipboard::init()
	{
		LOG_TRACE(U"CClipboard::init()");

		m_window = static_cast<GLFWwindow*>(Siv3DEngine::Get<ISiv3DWindow>()->getHandle());

		LOG_INFO(U"ℹ️ CClipboard initialized");
	}

	bool CClipboard::hasChanged()
	{
		return false;
	}

	bool CClipboard::getText(String& text)
	{
		text = Unicode::Widen(glfwGetClipboardString(m_window));
		return !text.isEmpty();
	}

	bool CClipboard::getImage(Image& image)
	{
		image.clear();
		return !image.isEmpty();
	}

	bool CClipboard::getFilePaths(Array<FilePath>& paths)
	{
		paths.clear();
		return !paths.isEmpty();
	}

	void CClipboard::setText(const String& text)
	{
		glfwSetClipboardString(m_window, Unicode::Narrow(text).c_str());
	}

	void CClipboard::setImage(const Image& image)
	{
	}

	void CClipboard::clear()
	{
	}
}
