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

# include <array>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Compression.hpp>
# include <Siv3D/Icon.hpp>
# include <Siv3D/CacheDirectory/CacheDirectory.hpp>
# include "FontCommon.hpp"

namespace s3d
{
	namespace detail
	{
		struct EngineFontResource
		{
			StringView path;

			bool required = false;

			bool compressed = true;
		};

		static constexpr std::array<EngineFontResource, 15> EngineFontResources =
		{ {
			{ U"min/siv3d-min.woff"_sv, true, false },
			{ U"noto-cjk/NotoSansCJK-Regular.ttc"_sv, false },
			{ U"noto-cjk/NotoSansJP-Regular.otf"_sv, false },
			{ U"noto-emoji/NotoEmoji-Regular.ttf"_sv, false },
			{ U"noto-emoji/NotoColorEmoji.ttf"_sv, false },
			{ U"mplus/mplus-1p-thin.ttf"_sv, false },
			{ U"mplus/mplus-1p-light.ttf"_sv, false },
			{ U"mplus/mplus-1p-regular.ttf"_sv, false },
			{ U"mplus/mplus-1p-medium.ttf"_sv, false },
			{ U"mplus/mplus-1p-bold.ttf"_sv, false },
			{ U"mplus/mplus-1p-heavy.ttf"_sv, false },
			{ U"mplus/mplus-1p-black.ttf"_sv, false },
			{ U"fontawesome/fontawesome-solid.otf"_sv, false },
			{ U"fontawesome/fontawesome-brands.otf"_sv, false },
			{ U"materialdesignicons/materialdesignicons-webfont.ttf"_sv, false },
		} };

		// 実行ファイルに同梱されている、圧縮済みフォントファイルをキャッシュフォルダに展開する。
		// キャッシュフォルダに展開済みのフォントがある場合はスキップ。
		bool ExtractEngineFonts()
		{
			LOG_SCOPED_TRACE(U"detail::ExtractEngineFonts()");

			const FilePath fontCacheDirectory = CacheDirectory::Engine() + U"font/";

			LOG_INFO(U"fontCacheDirectory: " + fontCacheDirectory);

			for (auto&&[name, required, compressed] : EngineFontResources)
			{
				const FilePath cachedFontPath = (fontCacheDirectory + name);
				const bool existsInCache = FileSystem::Exists(cachedFontPath);
				
				// 展開済みのフォントがある場合はスキップ
				if (existsInCache)
				{
					LOG_INFO(U"ℹ️ Engine font `{0}` found in the user cache directory"_fmt(name));
					continue;
				}

				const FilePath fontResourcePath = Resource(U"engine/font/" + name + (compressed ? U".zstdcmp" : U""));
				const bool existsInResource = FileSystem::Exists(fontResourcePath);

				if (not existsInResource)
				{
					// 必須のフォントがキャッシュフォルダにも実行ファイルにも見つからない場合エラー
					if (required)
					{
						LOG_ERROR(U"✖ Engine font `{0}` not found"_fmt(name));
						return false;
					}

					continue;
				}

				// フォントファイルの展開に失敗したらエラー
				if (compressed)
				{
					if (not Compression::DecompressFileToFile(fontResourcePath, cachedFontPath))
					{
						LOG_ERROR(U"✖ Engine font `{0}` decompression failed"_fmt(name));
						FileSystem::Remove(cachedFontPath);
						return false;
					}
				}
			}

			return true;
		}

		static const std::array<Array<TypefaceInfo>, 17> EngineTypefaceList =
		{ {
			{{ U"noto-cjk/NotoSansCJK-Regular.ttc", 0 }, { U"noto-cjk/NotoSansJP-Regular.otf", 0 }, { U"engine/font/min/siv3d-min.woff", 0, true }},
			{{ U"noto-cjk/NotoSansCJK-Regular.ttc", 1 }, { U"noto-cjk/NotoSansJP-Regular.otf", 0 }, { U"engine/font/min/siv3d-min.woff", 0, true }},
			{{ U"noto-cjk/NotoSansCJK-Regular.ttc", 2 }, { U"noto-cjk/NotoSansJP-Regular.otf", 0 }, { U"engine/font/min/siv3d-min.woff", 0, true }},
			{{ U"noto-cjk/NotoSansCJK-Regular.ttc", 3 }, { U"noto-cjk/NotoSansJP-Regular.otf", 0 }, { U"engine/font/min/siv3d-min.woff", 0, true }},
			{{ U"noto-cjk/NotoSansCJK-Regular.ttc", 4 }, { U"noto-cjk/NotoSansJP-Regular.otf", 0 }, { U"engine/font/min/siv3d-min.woff", 0, true }},
			{{ U"noto-emoji/NotoEmoji-Regular.ttf", 0 }, { U"noto-cjk/NotoSansJP-Regular.otf", 0 }, { U"engine/font/min/siv3d-min.woff", 0, true }},
			{{ U"noto-emoji/NotoColorEmoji.ttf", 0 }},
			{{ U"mplus/mplus-1p-thin.ttf", 0 }},
			{{ U"mplus/mplus-1p-light.ttf", 0}},
			{{ U"mplus/mplus-1p-regular.ttf", 0 }},
			{{ U"mplus/mplus-1p-medium.ttf", 0 }},
			{{ U"mplus/mplus-1p-bold.ttf", 0 }},
			{{ U"mplus/mplus-1p-heavy.ttf", 0 }},
			{{ U"mplus/mplus-1p-black.ttf", 0 }},
			{{ U"fontawesome/fontawesome-solid.otf", 0 }},
			{{ U"fontawesome/fontawesome-brands.otf", 0 }},
			{{ U"materialdesignicons/materialdesignicons-webfont.ttf", 0 }},
		} };

		TypefaceInfo GetTypefaceInfo(const Typeface typeface)
		{
			const FilePath fontCacheDirectory = (CacheDirectory::Engine() + U"font/");

			TypefaceInfo info;

			for (const auto& font : EngineTypefaceList[FromEnum(typeface)])
			{
				info = font;

				if (info.inResource)
				{
					info.path = Resource(info.path);
				}
				else
				{
					info.path.insert(0, fontCacheDirectory);
				}

				if (FileSystem::Exists(info.path))
				{
					break;
				}
			}

			return info;
		}

		bool IsAvailable(const Typeface typeface)
		{
			return FileSystem::Exists(GetTypefaceInfo(typeface).path);
		}

		std::unique_ptr<EmojiData> CreateDefaultEmoji(const FT_Library library)
		{
			const TypefaceInfo info = GetTypefaceInfo(Typeface::ColorEmoji);

			return std::make_unique<EmojiData>(library, info.path, info.faceIndex);
		}

		std::unique_ptr<IconData> CreateDefaultIcon(const FT_Library library, const Typeface typeface)
		{
			const TypefaceInfo info = GetTypefaceInfo(typeface);

			return std::make_unique<IconData>(library, info.path, info.faceIndex);
		}
	}

	namespace detail
	{
		bool HasIcon(const Array<std::unique_ptr<IconData>>& defaultIcons, const Icon::Type iconType, const char32 codePoint)
		{
			if (iconType == Icon::Type::Awesome)
			{
				return defaultIcons[0]->hasGlyph(codePoint)
					|| defaultIcons[1]->hasGlyph(codePoint);
			}
			else
			{
				return defaultIcons[2]->hasGlyph(codePoint);
			}
		}

		GlyphIndex GetIconGlyphIndex(const Array<std::unique_ptr<IconData>>& defaultIcons, const Icon::Type iconType, const char32 codePoint)
		{
			if (iconType == Icon::Type::Awesome)
			{
				GlyphIndex glyphIndex = defaultIcons[0]->getGlyphIndex(codePoint);

				if (glyphIndex == 0)
				{
					glyphIndex = defaultIcons[1]->getGlyphIndex(codePoint);
				}

				return glyphIndex;
			}
			else
			{
				return defaultIcons[2]->getGlyphIndex(codePoint);
			}
		}

		static Image RanderIcon(const FontMethod method, const GlyphIndex glyphIndex, const int32 fontPixelSize, int32 buffer, IconData& iconData)
		{
			if (method == FontMethod::Bitmap)
			{
				return iconData.renderBitmap(glyphIndex, fontPixelSize).image;
			}
			else if (method == FontMethod::SDF)
			{
				return iconData.renderSDF(glyphIndex, fontPixelSize, buffer).image;
			}
			else
			{
				return iconData.renderMSDF(glyphIndex, fontPixelSize, buffer).image;
			}
		}

		static Image RenderIcon(const FontMethod method, const Array<std::unique_ptr<IconData>>& defaultIcons, const Icon::Type iconType, const char32 codePoint, const int32 fontPixelSize, const int32 buffer)
		{
			if (iconType == Icon::Type::Awesome)
			{
				for (size_t i = 0; i < 2; ++i)
				{
					auto& iconData = defaultIcons[i];

					if (GlyphIndex glyphIndex = iconData->getGlyphIndex(codePoint))
					{
						return RanderIcon(method, glyphIndex, fontPixelSize, buffer, *iconData);
					}
				}
			}
			else
			{
				auto& iconData = defaultIcons[2];

				if (GlyphIndex glyphIndex = iconData->getGlyphIndex(codePoint))
				{
					return RanderIcon(method, glyphIndex, fontPixelSize, buffer, *iconData);
				}
			}

			return{};
		}

		Image RenderIconBitmap(const Array<std::unique_ptr<IconData>>& defaultIcons, const Icon::Type iconType, const char32 codePoint, const int32 fontPixelSize)
		{
			return RenderIcon(FontMethod::Bitmap, defaultIcons, iconType, codePoint, fontPixelSize, 0);
		}

		Image RenderIconSDF(const Array<std::unique_ptr<IconData>>& defaultIcons, const Icon::Type iconType, const char32 codePoint, const int32 fontPixelSize, const int32 buffer)
		{
			return RenderIcon(FontMethod::SDF, defaultIcons, iconType, codePoint, fontPixelSize, buffer);
		}

		Image RenderIconMSDF(const Array<std::unique_ptr<IconData>>& defaultIcons, const Icon::Type iconType, const char32 codePoint, const int32 fontPixelSize, const int32 buffer)
		{
			return RenderIcon(FontMethod::MSDF, defaultIcons, iconType, codePoint, fontPixelSize, buffer);
		}
	}
}
