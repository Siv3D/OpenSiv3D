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
# include "Optional.hpp"

namespace s3d
{
	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	[[nodiscard]]
	bool ParseBool(StringView s);

	[[nodiscard]]
	Optional<bool> ParseBoolOpt(StringView s) noexcept;
}
