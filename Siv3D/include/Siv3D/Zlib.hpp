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
	namespace Zlib
	{
		constexpr int32 DefaultCompressionLevel = 6;

		constexpr int32 MinCompressionLevel = 1;

		constexpr int32 MaxCompressionLevel = 9;

		[[nodiscard]] ByteArray Compress(ByteArrayViewAdapter view, int32 compressionLevel = DefaultCompressionLevel);

		[[nodiscard]] ByteArray Decompress(ByteArrayView view);
	}
}
