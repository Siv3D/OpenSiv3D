//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "ByteArray.hpp"

namespace s3d
{
	namespace Compression
	{
		constexpr int32 DefaultCompressionLevel = 11;

		constexpr int32 MinCompressionLevel = 1;

		constexpr int32 MaxCompressionLevel = 22;


		ByteArray Compress(ByteArrayView view, int32 compressionLevel = DefaultCompressionLevel);

		inline ByteArray Compress(const ByteArray& data, const int32 compressionLevel = DefaultCompressionLevel)
		{
			return Compress(data.getView(), compressionLevel);
		}

		ByteArray CompressFile(const FilePath& path, int32 compressionLevel = DefaultCompressionLevel);


		bool CompressToFile(ByteArrayView view, const FilePath& outputPath, int32 compressionLevel = DefaultCompressionLevel);

		inline bool CompressToFile(const ByteArray& data, const FilePath& outputPath, const int32 compressionLevel = DefaultCompressionLevel)
		{
			return CompressToFile(data.getView(), outputPath, compressionLevel);
		}

		bool CompressFileToFile(const FilePath& inputPath, const FilePath& outputPath, int32 compressionLevel = DefaultCompressionLevel);


		ByteArray Decompress(ByteArrayView view);

		inline ByteArray Decompress(const ByteArray& data)
		{
			return Decompress(data.getView());
		}

		ByteArray DecompressFile(const FilePath& path);

		bool DecompressToFile(ByteArrayView view, const FilePath& outputPath);

		inline bool DecompressToFile(const ByteArray& data, const FilePath& outputPath)
		{
			return DecompressToFile(data.getView(), outputPath);
		}

		bool DecompressFileToFile(const FilePath& inputPath, const FilePath& outputPath);
	}
}
