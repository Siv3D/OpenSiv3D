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
# include "Blob.hpp"

namespace s3d
{
	namespace Zlib
	{
		inline constexpr int32 DefaultCompressionLevel = 6;

		inline constexpr int32 MinCompressionLevel = 1;

		inline constexpr int32 MaxCompressionLevel = 9;

		[[nodiscard]]
		Blob Compress(const void* data, size_t size, int32 compressionLevel = DefaultCompressionLevel);

		bool Compress(const void* data, size_t size, Blob& dst, int32 compressionLevel = DefaultCompressionLevel);

		[[nodiscard]]
		Blob Compress(const Blob& blob, int32 compressionLevel = DefaultCompressionLevel);

		bool Compress(const Blob& blob, Blob& dst, int32 compressionLevel = DefaultCompressionLevel);

		[[nodiscard]]
		Blob Decompress(const void* data, size_t size);

		bool Decompress(const void* data, size_t size, Blob& dst);

		[[nodiscard]]
		Blob Decompress(const Blob& blob);

		bool Decompress(const Blob& blob, Blob& dst);
	}
}
