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
# include "Fwd.hpp"
# include "String.hpp"
# include "StringView.hpp"

namespace s3d
{
	//
	// https://github.com/Siv3D/OpenSiv3D/wiki/Emoji-list
	// https://www.google.com/get/noto/help/emoji/
	//
	struct Emoji
	{
		String codePoints;

		explicit Emoji(StringView emoji) noexcept
			: codePoints(emoji) {}

		static Image LoadImage(StringView emoji);

		static Image LoadSilhouette(StringView emoji);
	};
}

