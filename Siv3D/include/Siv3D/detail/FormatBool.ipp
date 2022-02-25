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

namespace s3d
{
	inline constexpr StringView ToString(const bool value, const LetterCase letterCase)
	{
		if (letterCase == LetterCase::Lower)
		{
			return value ? StringView(U"true") : StringView(U"false");
		}
		else
		{
			return value ? StringView(U"TRUE") : StringView(U"FALSE");
		}
	}
}
