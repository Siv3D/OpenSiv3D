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
# include "StringView.hpp"
# include "AssetHandle.hpp"
# include "FontStyle.hpp"

namespace s3d
{
	class Font : public AssetHandle<Font>
	{
	public:

		Font();

		//explicit Font(int32 fontSize, Typeface typeface = Typeface::Default, FontStyle style = FontStyle::Default);

		Font(int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);

		virtual ~Font();
	};
}
