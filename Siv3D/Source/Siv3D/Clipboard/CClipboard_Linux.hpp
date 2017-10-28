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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include "IClipboard.hpp"
# include <Siv3D/Image.hpp>
# include "../Window/IWindow.hpp"

namespace s3d
{
	class CClipboard_Linux : public ISiv3DClipboard
	{
	private:
		WindowHandle m_glfwWindow = nullptr;

	public:

		CClipboard_Linux();

		~CClipboard_Linux() override;

		bool init() override;

		bool hasChanged() override;

		bool getText(String& text) override;

		bool getImage(Image& image) override;

		bool getFilePaths(Array<FilePath>& paths) override;

		void setText(const String& text) override;

		void setImage(const Image& image) override;

		void clear() override;
	};
}

# endif
