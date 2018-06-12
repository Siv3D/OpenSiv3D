//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Windows.hpp>
# include "IClipboard.hpp"
# include <Siv3D/Image.hpp>

namespace s3d
{
	class CClipboard_Windows : public ISiv3DClipboard
	{
	private:

		HWND m_hWnd = nullptr;

		uint32 m_sequenceNumber = 0;

	public:

		CClipboard_Windows();

		~CClipboard_Windows() override;

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
