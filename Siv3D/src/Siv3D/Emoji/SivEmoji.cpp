//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Emoji.hpp>
# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	Emoji::Emoji(const char32* emoji) noexcept
		: codePoints{ emoji } {}

	Emoji::Emoji(const StringView emoji) noexcept
		: codePoints{ emoji } {}

	Emoji::Emoji(String emoji) noexcept
		: codePoints{ std::move(emoji) } {}

	bool Emoji::HasGlyph(const StringView emoji)
	{
		return SIV3D_ENGINE(Font)->hasEmoji(emoji);
	}

	GlyphIndex Emoji::GetGlyphIndex(const StringView emoji)
	{
		return SIV3D_ENGINE(Font)->getEmojiGlyphIndex(emoji);
	}

	Image Emoji::CreateImage(const StringView emoji)
	{
		const GlyphIndex glyphIndex = SIV3D_ENGINE(Font)->getEmojiGlyphIndex(emoji);

		return CreateImageByGlyphIndex(glyphIndex);
	}

	Image Emoji::CreateImageByGlyphIndex(const GlyphIndex glyphIndex)
	{
		if (glyphIndex == 0)
		{
			return{};
		}

		return SIV3D_ENGINE(Font)->renderEmojiBitmap(glyphIndex);
	}

	Image Emoji::CreateSilhouetteImage(const StringView emoji)
	{
		const GlyphIndex glyphIndex = SIV3D_ENGINE(Font)->getEmojiGlyphIndex(emoji);

		return CreateSilhouetteImageByGlyphIndex(glyphIndex);
	}

	Image Emoji::CreateSilhouetteImageByGlyphIndex(const GlyphIndex glyphIndex)
	{
		Image image = CreateImageByGlyphIndex(glyphIndex);

		for (auto& pixel : image)
		{
			pixel.setRGB(255, 255, 255);
		}

		return image;
	}

	inline namespace Literals
	{
		inline namespace EmojiLiterals
		{
			Emoji operator ""_emoji(const char32* s, const size_t length)
			{
				return Emoji{ String(s, length) };
			}
		}
	}
}
