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

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/SDFFont.hpp>

namespace s3d
{
	class ISiv3DSDFFont
	{
	public:

		static ISiv3DSDFFont* Create();

		virtual ~ISiv3DSDFFont() = default;

		virtual void init() = 0;

		virtual SDFFontID create(Typeface typeface, int32 baseSize, FontStyle style) = 0;

		virtual SDFFontID create(const FilePath& path, int32 baseSize, FontStyle style) = 0;

		virtual SDFFontID create(const std::pair<FilePath, FilePath>& prerenderedFiles, Typeface typeface, int32 baseSize, FontStyle style) = 0;

		virtual SDFFontID create(const std::pair<FilePath, FilePath>& prerenderedFiles, const FilePath& path, int32 baseSize, FontStyle style) = 0;

		virtual void release(SDFFontID handleID) = 0;

		virtual const String& getFamilyName(SDFFontID handleID) = 0;

		virtual const String& getStyleName(SDFFontID handleID) = 0;

		virtual int32 getBaseSize(SDFFontID handleID) = 0;

		virtual double getAscent(SDFFontID handleID) = 0;

		virtual double getDescent(SDFFontID handleID) = 0;

		virtual double getHeight(SDFFontID handleID) = 0;

		virtual void preload(SDFFontID handleID, StringView codePoints) = 0;

		virtual bool saveGlyphs(SDFFontID handleID, FilePathView imagePath, FilePathView jsonPath) = 0;

		virtual Array<GlyphF> getGlyphs(SDFFontID handleID, StringView codePoints) = 0;

		virtual const Texture& getTexture(SDFFontID handleID) = 0;

		virtual RectF getBoundingRect(SDFFontID handleID, double fontSize, StringView codePoints, double lineSpacingScale) = 0;

		virtual RectF getRegion(SDFFontID handleID, double fontSize, StringView codePoints, double lineSpacingScale) = 0;

		virtual Array<double> getXAdvances(SDFFontID handleID, double fontSize, StringView codePoints) = 0;

		virtual RectF draw(SDFFontID handleID, double fontSize, StringView codePoints, const Vec2& pos, const ColorF& color, double lineSpacingScale) = 0;
	};
}
