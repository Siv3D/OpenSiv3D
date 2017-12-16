﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Emoji.hpp>
# include <Siv3D/Image.hpp>
# include "../Siv3DEngine.hpp"
# include "../Font/IFont.hpp"

namespace s3d
{
	Image Emoji::LoadImage(const StringView emoji)
	{
		return Siv3DEngine::GetFont()->getColorEmoji(emoji);
	}

	Image Emoji::LoadSilhouette(StringView emoji)
	{
		return Siv3DEngine::GetFont()->getColorEmojiSilhouette(emoji);
	}

	//size_t CheckEmoji(Array<char32_t>::const_iterator it)
	//{
	//	return Siv3DEngine::GetFont()->checkEmoji(it);
	//}
}
