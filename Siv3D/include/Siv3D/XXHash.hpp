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

namespace s3d
{
	namespace Hash
	{
		constexpr uint64 DefaultXXHSeed = 11111111;

		[[nodiscard]] uint64 XXHash(ByteArrayView view, uint64 seed = DefaultXXHSeed);

		[[nodiscard]] uint64 XXHash(ByteArrayViewAdapter view, uint64 seed = DefaultXXHSeed);

		[[nodiscard]] uint64 XXHashFromFile(const FilePath& path, uint64 seed = DefaultXXHSeed);
	}
}
