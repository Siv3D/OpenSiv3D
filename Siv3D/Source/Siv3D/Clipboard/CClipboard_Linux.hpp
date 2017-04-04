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

namespace s3d
{
	class CClipboard_Linux : public ISiv3DClipboard
	{
	private:

		bool m_hasChanged = false;

		String m_text;

		Image m_image;

		Array<FilePath> m_filePaths;

	public:

		CClipboard_Linux();

		~CClipboard_Linux() override;

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
