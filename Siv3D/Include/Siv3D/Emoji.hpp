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

# define EMOJIDEF(NAME,CH) static constexpr Helper NAME = { CH };

namespace s3d
{
	struct Emoji
	{
	private:

		struct Helper
		{
			const char32_t* codePoint;
		};

	public:

		char32_t codePoint;

		explicit constexpr Emoji(char32_t _codePoint) noexcept
			: codePoint(_codePoint) {}

		constexpr Emoji(Helper helper) noexcept
			: codePoint(helper.codePoint[0]) {}

		static Image LoadImage(char32_t _codePoint);

		//
		// https://www.google.com/get/noto/help/emoji/
		//

		/// <summary>
		/// 🔥
		/// </summary>
		EMOJIDEF(Fire, U"🔥");

		/// <summary>
		/// ⚽
		/// </summary>
		EMOJIDEF(SoccerBall, U"⚽");

		/// <summary>
		/// 🐵
		/// </summary>
		EMOJIDEF(MonkeyFace, U"🐵");

		/// <summary>
		/// 🍔
		/// </summary>
		EMOJIDEF(Hamburger, U"🍔");
	};
}

# undef U32WIDEN
# undef EMOJIDEF
