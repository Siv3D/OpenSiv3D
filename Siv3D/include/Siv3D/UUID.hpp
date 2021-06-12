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
# include <array>
# include "Common.hpp"
# include "StringView.hpp"
# include "Optional.hpp"

namespace s3d
{
	struct UUID
	{
		std::array<uint8, 16> data{};

		[[nodiscard]]
		static UUID Generate();

		[[nodiscard]]
		static UUID FromRNG();

		[[nodiscard]]
		static Optional<UUID> Parse(StringView uuid);
	};
}
