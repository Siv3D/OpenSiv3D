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
# if defined(SIV3D_TARGET_MACOS)

# include "IClipboard.hpp"
# include <Siv3D/Image.hpp>

namespace s3d
{
	class CClipboard_macOS : public ISiv3DClipboard
	{
	private:

		String m_text;

		Image m_image;

		Array<FilePath> m_filePaths;

		uint64 m_changeCount = 0;
		
		bool m_hasChanged = false;
		
	public:

		CClipboard_macOS();

		~CClipboard_macOS() override;

		bool init() override;

		void update() override;

		bool hasChanged() override;

		bool hasText() override;

		bool hasImage() override;

		bool hasFilePaths() override;

		const String& getText() override;

		const Image& getImage() override;

		const Array<FilePath>& getFilePaths() override;

		void setText(const String& text) override;

		void setImage(const Image& image) override;

		void clear() override;
	};
}

# endif
