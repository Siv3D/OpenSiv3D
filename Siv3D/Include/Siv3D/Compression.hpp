//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
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

		inline ByteArray Compress(const ByteArray& data, int32 compressionLevel = DefaultCompressionLevel)
		{
			return Compress(data.getView(), compressionLevel);
		}

		ByteArray CompressFile(const FilePath& path, int32 compressionLevel = DefaultCompressionLevel);


		bool SaveCompressed(ByteArrayView view, const FilePath& outputPath, int32 compressionLevel = DefaultCompressionLevel);

		inline bool SaveCompressed(const ByteArray& data, const FilePath& outputPath, int32 compressionLevel = DefaultCompressionLevel)
		{
			return SaveCompressed(data.getView(), outputPath, compressionLevel);
		}

		bool SaveCompressed(const FilePath& inputPath, const FilePath& outputPath, int32 compressionLevel = DefaultCompressionLevel);








	}
}
