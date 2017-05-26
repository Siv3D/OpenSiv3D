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

# define U32WIDEN(x) U ## x
# define EMOJIDEF(NAME,CH) static constexpr Helper NAME = { U32WIDEN(#CH) };

namespace s3d
{
	struct Emoji
	{
	private:

		struct Helper
		{
			char32_t* codePoint;
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
		EMOJIDEF(Fire, 🔥);

		/// <summary>
		/// ⚽
		/// </summary>
		EMOJIDEF(SoccerBall, ⚽);

		/// <summary>
		/// 🐵
		/// </summary>
		EMOJIDEF(MonkeyFace, 🐵);

		/// <summary>
		/// 🍔
		/// </summary>
		EMOJIDEF(Hamburger, 🍔);
	};
}

# undef U32WIDEN
# undef EMOJIDEF
