//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/Resource.hpp>
# include <EngineDirectory/EngineDirectory.hpp>
# include "CSDFFont.hpp"

namespace s3d
{
	namespace detail
	{
		enum class StandardFont
		{
			MPlusThin,
			MPlusLight,
			MPlusRegular,
			MPlusMedium,
			MPlusBold,
			MPlusHeavy,
			MPlusBlack,
			NotoEmojiRegular,
			NotoColorEmoji,
			AwesomeSolid,
			AwesomeBrands,
		};

		static constexpr std::array<FilePathView, 11> StandardFontNames =
		{
			U"mplus/mplus-1p-thin.ttf"_sv,
			U"mplus/mplus-1p-light.ttf"_sv,
			U"mplus/mplus-1p-regular.ttf"_sv,
			U"mplus/mplus-1p-medium.ttf"_sv,
			U"mplus/mplus-1p-bold.ttf"_sv,
			U"mplus/mplus-1p-heavy.ttf"_sv,
			U"mplus/mplus-1p-black.ttf"_sv,
			U"noto/NotoEmoji-Regular.ttf"_sv,
			U"noto/NotoColorEmoji.ttf"_sv,
			U"fontawesome/fontawesome-solid.otf"_sv,
			U"fontawesome/fontawesome-brands.otf"_sv,
		};

		FilePath GetEngineFontPath(const Typeface typeface);

		[[nodiscard]] static FilePath GetEngineFontDirectory()
		{
			return EngineDirectory::CurrectVersionCommon() + U"font/";
		}
	}

	CSDFFont::CSDFFont()
	{

	}

	CSDFFont::~CSDFFont()
	{
		LOG_TRACE(U"CSDFFont::~CSDFFont()");

		m_fonts.destroy();

		if (m_freeType)
		{
			::FT_Done_FreeType(m_freeType);
		}
	}

	void CSDFFont::init()
	{
		LOG_TRACE(U"CSDFFont::init()");

		// FreeType インスタンスの作成（CFont とは独立）
		if (const FT_Error error = ::FT_Init_FreeType(&m_freeType))
		{
			throw EngineError(U"FT_Init_FreeType() faild");
		}

		// Null SDFFont のセット
		{
			auto nullFont = std::make_unique<SDFFontData>(SDFFontData::Null{}, m_freeType);

			if (!nullFont->isInitialized())
			{
				throw EngineError(U"Null SDFFont initialization failed");
			}

			m_fonts.setNullData(std::move(nullFont));
		}

		LOG_INFO(U"ℹ️ CSDFFont initialized");
	}

	SDFFontID CSDFFont::create(const Typeface typeface, const int32 baseSize, const FontStyle style)
	{
		return create(detail::GetEngineFontPath(typeface), baseSize, style);
	}

	SDFFontID CSDFFont::create(const FilePath& path, const int32 baseSize, const FontStyle style)
	{
		const FilePath emojiPath = detail::GetEngineFontDirectory()
			+ detail::StandardFontNames[FromEnum(detail::StandardFont::NotoEmojiRegular)];

		auto font = std::make_unique<SDFFontData>(m_freeType, path, emojiPath, baseSize, style);

		if (!font->isInitialized())
		{
			return SDFFontID::NullAsset();
		}

		const String info = U"(`{0} {1}` baseSize: {2})"_fmt(font->getProperty().familyName, font->getProperty().styleName, baseSize);

		return m_fonts.add(std::move(font), info);
	}

	void CSDFFont::release(const SDFFontID handleID)
	{
		m_fonts.erase(handleID);
	}

	const String& CSDFFont::getFamilyName(const SDFFontID handleID)
	{
		return m_fonts[handleID]->getProperty().familyName;
	}

	const String& CSDFFont::getStyleName(const SDFFontID handleID)
	{
		return m_fonts[handleID]->getProperty().styleName;
	}

	int32 CSDFFont::getBaseSize(const SDFFontID handleID)
	{
		return m_fonts[handleID]->getProperty().baseSize;
	}

	int32 CSDFFont::getAscent(const SDFFontID handleID)
	{
		return m_fonts[handleID]->getProperty().ascender;
	}

	int32 CSDFFont::getDescent(const SDFFontID handleID)
	{
		return m_fonts[handleID]->getProperty().descender;
	}

	int32 CSDFFont::getHeight(const SDFFontID handleID)
	{
		return m_fonts[handleID]->getProperty().height;
	}

	Array<Glyph> CSDFFont::getGlyphs(const SDFFontID handleID, const StringView codePoints)
	{
		return m_fonts[handleID]->getGlyphs(codePoints);
	}

	const Texture& CSDFFont::getTexture(const SDFFontID handleID)
	{
		return m_fonts[handleID]->getTexture();
	}
}
