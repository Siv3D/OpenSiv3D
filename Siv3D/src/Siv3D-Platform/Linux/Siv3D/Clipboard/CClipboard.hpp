﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Clipboard/IClipboard.hpp>
# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	class CClipboard final : public ISiv3DClipboard
	{
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

	private:

		GLFWwindow* m_window = nullptr;
	};
}
