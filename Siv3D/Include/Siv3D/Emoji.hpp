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

# define EMOJIDEF(NAME,CH) static constexpr Helper NAME = { CH };

namespace s3d
{
	struct Emoji
	{
	private:

		struct Helper
		{
			const wchar_t* codePoints;
		};

	public:

		String codePoints;

		explicit Emoji(StringView emoji) noexcept
			: codePoints(emoji) {}

		Emoji(Helper helper) noexcept
			: codePoints(helper.codePoints) {}

		static Image LoadImage(StringView emoji);

		//
		// https://www.google.com/get/noto/help/emoji/
		//

		/// <summary>
		/// 🔥
		/// </summary>
		EMOJIDEF(Fire, L"🔥");

		/// <summary>
		/// ⚽
		/// </summary>
		EMOJIDEF(SoccerBall, L"⚽");

		/// <summary>
		/// 🐵
		/// </summary>
		EMOJIDEF(MonkeyFace, L"🐵");

		/// <summary>
		/// 🍔
		/// </summary>
		EMOJIDEF(Hamburger, L"🍔");
	};
}

# undef U32WIDEN
# undef EMOJIDEF
