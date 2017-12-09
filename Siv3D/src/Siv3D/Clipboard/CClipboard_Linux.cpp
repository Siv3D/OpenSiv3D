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

# include <GL/glew.h>
# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "../Siv3DEngine.hpp"
# include "CClipboard_Linux.hpp"
# include <Siv3D/Logger.hpp>

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
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();

		LOG_INFO(U"ℹ️ Clipboard initialized");

		return true;
	}

	bool CClipboard_Linux::hasChanged()
	{
		// [Siv3D ToDo]
		return false;
	}

	bool CClipboard_Linux::getText(String& text)
	{
		const char* glfwText = glfwGetClipboardString(m_glfwWindow);
		if (glfwText == nullptr)
			return false;
		else
		{
			text = Unicode::Widen(glfwText);
			return true;
		}
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
		glfwSetClipboardString(m_glfwWindow, text.narrow().c_str());
	}

	void CClipboard_Linux::setImage(const Image& image)
	{
		// [Siv3D ToDo]
	}

	void CClipboard_Linux::clear()
	{
		glfwSetClipboardString(m_glfwWindow, "");
	}
}

# endif
