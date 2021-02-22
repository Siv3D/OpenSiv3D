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

namespace s3d
{
	struct Emoji
	{
		String codePoints;

		SIV3D_NODISCARD_CXX20
		Emoji() = default;

		SIV3D_NODISCARD_CXX20
		explicit Emoji(String&& _codePoints) noexcept;
	};
}

# include "detail/Emoji.ipp"
