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
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "PointVector.hpp"
# include "StringView.hpp"

namespace s3d
{
	//
	// https://github.com/Siv3D/OpenSiv3D/wiki/Emoji-list
	// https://www.google.com/get/noto/help/emoji/
	//
	struct Emoji
	{
		static constexpr Size ImageSize = { 136, 128 };

		String codePoints;

		Emoji() = default;

		explicit Emoji(StringView emoji) noexcept
			: codePoints(emoji) {}

		[[nodiscard]] static Image LoadImage(StringView emoji);

		[[nodiscard]] static Image LoadSilhouette(StringView emoji);
	};

	struct Character
	{
		union
		{
			char32_t codePoint;

			uint32 emojiIndex;
		};

		//bool isEmoji() const;
	};

	//size_t CheckEmoji(Array<char32_t>::const_iterator it);
}

