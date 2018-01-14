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

namespace s3d
{
	namespace Hash
	{
		constexpr uint64 DefaultXXHSeed = 11111111;

		uint64 XXHash(ByteArrayView view, uint64 seed = DefaultXXHSeed);

		uint64 XXHashFromFile(const FilePath& path, uint64 seed = DefaultXXHSeed);
	}
}
