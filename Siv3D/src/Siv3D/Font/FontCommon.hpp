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
# include <Siv3D/StringView.hpp>
# include <Siv3D/FontStyle.hpp>

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
	}
}
