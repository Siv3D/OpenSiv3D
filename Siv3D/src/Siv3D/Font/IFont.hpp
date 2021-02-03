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
# include <Siv3D/Common.hpp>
# include <Siv3D/Font.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DFont
	{
	public:

		static ISiv3DFont* Create();

		virtual ~ISiv3DFont() = default;

		virtual void init() = 0;

		virtual Font::IDType create(FilePathView path, int32 fontSize, FontStyle style) = 0;

		virtual void release(Font::IDType handleID) = 0;

		virtual const String& getFamilyName(Font::IDType handleID) = 0;

		virtual const String& getStyleName(Font::IDType handleID) = 0;

		virtual FontStyle getStyle(Font::IDType handleID) = 0;

		virtual int32 getFontSize(Font::IDType handleID) = 0;

		virtual int32 getAscent(Font::IDType handleID) = 0;

		virtual int32 getDescent(Font::IDType handleID) = 0;
	};
}
