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
# include "AssetHandle.hpp"
# include "FontStyle.hpp"

namespace s3d
{
	class Font : public AssetHandle<Font>
	{
	public:

		SIV3D_NODISCARD_CXX20
		Font();

		//SIV3D_NODISCARD_CXX20
		//explicit Font(int32 fontSize, Typeface typeface = Typeface::Default, FontStyle style = FontStyle::Default);

		SIV3D_NODISCARD_CXX20
		Font(int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);

		virtual ~Font();

		[[nodiscard]]
		const String& getFamilyName() const;

		[[nodiscard]]
		const String& getStyleName() const;

		[[nodiscard]]
		FontStyle getStyle() const;

		[[nodiscard]]
		int32 getFontSize() const;

		[[nodiscard]]
		int32 getAscent() const;

		[[nodiscard]]
		int32 getDescent() const;
	};
}
