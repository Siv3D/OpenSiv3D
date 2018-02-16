//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Optional.hpp"

namespace s3d
{
	[[nodiscard]] bool ParseBool(StringView view);

	[[nodiscard]] Optional<bool> ParseBoolOpt(StringView view);
}
