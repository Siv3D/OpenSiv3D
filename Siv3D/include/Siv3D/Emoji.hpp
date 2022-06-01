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

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "Image.hpp"
# include "GlyphIndex.hpp"

namespace s3d
{
	/// @brief 絵文字
	struct Emoji
	{
		/// @brief OpenSiv3D 標準絵文字のサイズ（ピクセル）
		static constexpr Size ImageSize{ 136, 128 };

		static constexpr double HorizontalAspectRatio = ImageSize.horizontalAspectRatio();

		/// @brief 絵文字のコードポイント
		String codePoints;

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20 
		Emoji() = default;

		SIV3D_NODISCARD_CXX20
		explicit Emoji(const char32* emoji) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit Emoji(StringView emoji) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit Emoji(String emoji) noexcept;

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
			/// @brief 絵文字（コードポイント）を記述した文字列から Emoji オブジェクトを作成します。
			/// @param s 絵文字（コードポイント）を記述した文字列
			/// @param length 文字列の長さ
			/// @return Emoji オブジェクト
			[[nodiscard]] 
			Emoji operator ""_emoji(const char32* s, size_t length);
		}
	}
}

# include "detail/Emoji.ipp"
