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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Font.hpp>

namespace s3d
{
	class ISiv3DFont
	{
	public:

		static ISiv3DFont* Create();

		virtual ~ISiv3DFont() = default;

		virtual bool init() = 0;

		virtual Font::IDType create(const FilePath& path, int32 fontSize, FontStyle style) = 0;

		virtual void release(Font::IDType handleID) = 0;

		virtual int32 getAscender(Font::IDType handleID) = 0;

		virtual int32 getDescender(Font::IDType handleID) = 0;

		virtual RectF getBoundingRect(Font::IDType handleID, const String& text, double lineSpacingScale) = 0;

		virtual RectF getRegion(Font::IDType handleID, const String& text, double lineSpacingScale) = 0;

		virtual RectF draw(Font::IDType handleID, const String& text, const Vec2& pos, const ColorF& color, double lineSpacingScale) = 0;

		virtual Image getColorEmoji(uint32 codePoint) = 0;
	};
}
