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
# include "StringView.hpp"
# include "Blob.hpp"

namespace s3d
{
	namespace Compression
	{
		inline constexpr int32 MinLevel = 1;

		inline constexpr int32 DefaultLevel = 11;

		inline constexpr int32 MaxLevel = 22;

		[[nodiscard]]
		Blob Compress(const void* data, size_t size, int32 compressionLevel = DefaultLevel);

		bool Compress(const void* data, size_t size, Blob& dst, int32 compressionLevel = DefaultLevel);

		[[nodiscard]]
		Blob Compress(const Blob& blob, int32 compressionLevel = DefaultLevel);

		bool Compress(const Blob& blob, Blob& dst, int32 compressionLevel = DefaultLevel);

		[[nodiscard]]
		Blob CompressFile(FilePathView path, int32 compressionLevel = DefaultLevel);

		bool CompressFile(FilePathView path, Blob& dst, int32 compressionLevel = DefaultLevel);

		bool CompressToFile(const void* data, size_t size, FilePathView outputPath, int32 compressionLevel = DefaultLevel);

		bool CompressToFile(const Blob& blob, FilePathView outputPath, int32 compressionLevel = DefaultLevel);

		bool CompressFileToFile(FilePathView inputPath, FilePathView outputPath, int32 compressionLevel = DefaultLevel);

		[[nodiscard]]
		Blob Decompress(const void* data, size_t size);

		bool Decompress(const void* data, size_t size, Blob& dst);

		[[nodiscard]]
		Blob Decompress(const Blob& blob);

		bool Decompress(const Blob& blob, Blob& dst);

		[[nodiscard]]
		Blob DecompressFile(FilePathView path);

		bool DecompressFile(FilePathView path, Blob& dst);

		bool DecompressToFile(const void* data, size_t size, FilePathView outputPath);

		bool DecompressToFile(const Blob& blob, FilePathView outputPath);

		bool DecompressFileToFile(FilePathView inputPath, FilePathView outputPath);
	}
}
