//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FontStyle.hpp>
# include <Siv3D/Typeface.hpp>
# include "EmojiData.hpp"
# include "IconData.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		constexpr StringView ToString(const FontStyle style) noexcept
		{
			switch (style)
			{
			case FontStyle::Default:
				return U"Default";
			case FontStyle::Bold:
				return U"Bold";
			case FontStyle::Italic:
				return U"Italic";
			case FontStyle::BoldItalic:
				return U"BoldItalic";
			case FontStyle::Bitmap:
				return U"Bitmap";
			case FontStyle::BoldBitmap:
				return U"BoldBitmap";
			case FontStyle::ItalicBitmap:
				return U"ItalicBitmap";
			default:
				return U"BoldItalicBitmap";
			}
		}

		[[nodiscard]]
		bool ExtractEngineFonts();

		struct TypefaceInfo
		{
			String path;

			size_t faceIndex = 0;

			bool inResource = false;
		};

		[[nodiscard]]
		TypefaceInfo GetTypefaceInfo(Typeface typeface);

		[[nodiscard]]
		bool IsAvailable(Typeface typeface);

		[[nodiscard]]
		std::unique_ptr<EmojiData> CreateDefaultEmoji(FT_Library library);

		[[nodiscard]]
		std::unique_ptr<IconData> CreateDefaultIcon(FT_Library library, Typeface typeface);
	}

	namespace detail
	{
		[[nodiscard]]
		bool HasIcon(const Array<std::unique_ptr<IconData>>& defaultIcons, Icon::Type iconType, char32 codePoint);

		[[nodiscard]]
		GlyphIndex GetIconGlyphIndex(const Array<std::unique_ptr<IconData>>& defaultIcons, Icon::Type iconType, char32 codePoint);

		[[nodiscard]]
		Image RenderIconBitmap(const Array<std::unique_ptr<IconData>>& defaultIcons, Icon::Type iconType, char32 codePoint, int32 fontPixelSize);

		[[nodiscard]]
		Image RenderIconSDF(const Array<std::unique_ptr<IconData>>& defaultIcons, Icon::Type iconType, char32 codePoint, int32 fontPixelSize, int32 buffer);

		[[nodiscard]]
		Image RenderIconMSDF(const Array<std::unique_ptr<IconData>>& defaultIcons, Icon::Type iconType, char32 codePoint, int32 fontPixelSize, int32 buffer);
	}
}
