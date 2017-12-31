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
	namespace Compression
	{
		constexpr int32 DefaultCompressionLevel = 11;

		constexpr int32 MinCompressionLevel = 1;

		constexpr int32 MaxCompressionLevel = 22;

		ByteArray Compress(ByteArrayView view, int32 compressionLevel = DefaultCompressionLevel);

		ByteArray CompressFile(const FilePath& path, int32 compressionLevel = DefaultCompressionLevel);

		bool CompressToFile(ByteArrayView view, const FilePath& outputPath, int32 compressionLevel = DefaultCompressionLevel);

		bool CompressFileToFile(const FilePath& inputPath, const FilePath& outputPath, int32 compressionLevel = DefaultCompressionLevel);

		ByteArray Decompress(ByteArrayView view);

		ByteArray DecompressFile(const FilePath& path);

		bool DecompressToFile(ByteArrayView view, const FilePath& outputPath);

		bool DecompressFileToFile(const FilePath& inputPath, const FilePath& outputPath);
	}
}
