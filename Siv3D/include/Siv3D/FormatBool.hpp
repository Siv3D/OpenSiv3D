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
# include "Common.hpp"
# include "LetterCase.hpp"
# include "StringView.hpp"

namespace s3d
{
	/// @brief bool 型の値を文字列に変換します。
	/// @param value 値
	/// @param letterCase 大文字にするか小文字にするか
	/// @return 変換後の文字列
	[[nodiscard]]
	inline constexpr StringView ToString(bool value, LetterCase letterCase = LetterCase::Lower);
}

# include "detail/FormatBool.ipp"
