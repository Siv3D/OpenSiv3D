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
# include "Optional.hpp"

namespace s3d
{
	/// @brief 文字列をパースして bool 型に変換します。
	/// @param s 変換する文字列
	/// @throw ParseError パースに失敗した場合 | Thrown when a parsing error occurs
	/// @return 文字列から変換されたデータ
	[[nodiscard]]
	bool ParseBool(StringView s);

	/// @brief 文字列をパースして bool 型に変換します。
	/// @param s 変換する文字列
	/// @remark この関数はパースに失敗しても例外を投げません。
	/// @return 文字列から変換されたデータの Optional, 失敗した場合は none
	[[nodiscard]]
	Optional<bool> ParseBoolOpt(StringView s) noexcept;
}
