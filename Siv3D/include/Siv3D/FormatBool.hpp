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
# include "Fwd.hpp"
# include "LetterCase.hpp"
# include "StringView.hpp"

namespace s3d
{
	[[nodiscard]] inline constexpr StringView ToString(const bool value, const LetterCase letterCase = LetterCase::Lower)
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
