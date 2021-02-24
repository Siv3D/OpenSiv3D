//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "Image.hpp"
# include "GlyphIndex.hpp"

namespace s3d
{
	struct Emoji
	{
		static constexpr Size ImageSize{ 136, 128 };

		String codePoints;

		SIV3D_NODISCARD_CXX20
		Emoji() = default;

		SIV3D_NODISCARD_CXX20
		explicit Emoji(String&& emoji) noexcept;

		[[nodiscard]]
		static bool HasGlyph(StringView emoji);

		[[nodiscard]]
		static GlyphIndex GetGlyphIndex(StringView emoji);

		[[nodiscard]]
		static Image CreateImage(StringView emoji);

		[[nodiscard]]
		static Image CreateImageByGlyphIndex(GlyphIndex glyphIndex);

		[[nodiscard]]
		static Image CreateSilhouetteImage(StringView emoji);

		[[nodiscard]]
		static Image CreateSilhouetteImageByGlyphIndex(GlyphIndex glyphIndex);
	};

	inline namespace Literals
	{
		inline namespace EmojiLiterals
		{
			[[nodiscard]]
			Emoji operator ""_emoji(const char32* s, size_t length);
		}
	}
}

# include "detail/Emoji.ipp"
