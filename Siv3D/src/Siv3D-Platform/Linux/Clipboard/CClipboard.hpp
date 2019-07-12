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

# pragma once
# include <Siv3D/Image.hpp>
# include <Clipboard/IClipboard.hpp>
# include <GLFW/glfw3.h>

namespace s3d
{
	class CClipboard : public ISiv3DClipboard
	{
	private:

		GLFWwindow* m_window = nullptr;
		
		uint64 m_changeCount = 0;

	public:

		CClipboard();

		~CClipboard() override;

		void init() override;

		bool hasChanged() override;

		bool getText(String& text) override;

		bool getImage(Image& image) override;

		bool getFilePaths(Array<FilePath>& paths) override;

		void setText(const String& text) override;

		void setImage(const Image& image) override;

		void clear() override;
	};
}
