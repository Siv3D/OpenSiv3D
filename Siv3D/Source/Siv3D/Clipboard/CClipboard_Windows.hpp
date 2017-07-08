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
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include "IClipboard.hpp"
# include <Siv3D/Image.hpp>

namespace s3d
{
	class CClipboard_Windows : public ISiv3DClipboard
	{
	private:

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
