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

# include "../../ThirdParty/zstd/zstd.h"
# include <Siv3D/Compression.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	namespace Compression
	{
		ByteArray Compress(const ByteArrayView view, const int32 compressionLevel)
		{
			const size_t bufferSize = ZSTD_compressBound(view.size());

			Array<uint8> buffer(bufferSize);

			const size_t result = ZSTD_compress(buffer.data(), buffer.size(), view.data(), view.size(), compressionLevel);

			if (ZSTD_isError(result))
			{
				return ByteArray();
			}

			buffer.resize(result);

			buffer.shrink_to_fit();

			return ByteArray(std::move(buffer));
		}

		ByteArray CompressFile(const FilePath& path, const int32 compressionLevel)
		{
			BinaryReader reader(path);

			if (!reader)
			{
				return ByteArray();
			}

			const size_t inputBufferSize = ZSTD_CStreamInSize();
			const auto pInputBuffer = std::make_unique<uint8[]>(inputBufferSize);

			const size_t outputBufferSize = ZSTD_CStreamOutSize();
			const auto pOutputBuffer = std::make_unique<uint8[]>(outputBufferSize);

			ZSTD_CStream* const cStream = ZSTD_createCStream();

			if (!cStream)
			{
				return ByteArray();
			}

			const size_t initResult = ZSTD_initCStream(cStream, compressionLevel);

			if (ZSTD_isError(initResult))
			{
				return ByteArray();
			}

			size_t toRead = inputBufferSize;

			Array<uint8> buffer;

			while (const size_t read = static_cast<size_t>(reader.read(pInputBuffer.get(), toRead)))
			{
				ZSTD_inBuffer input = { pInputBuffer.get(), read, 0 };

				while (input.pos < input.size)
				{
					ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };
					
					toRead = ZSTD_compressStream(cStream, &output, &input);
					
					if (ZSTD_isError(toRead))
					{
						return ByteArray();
					}

					if (toRead > inputBufferSize)
					{
						toRead = inputBufferSize;
					}

					buffer.insert(buffer.end(), pOutputBuffer.get(), pOutputBuffer.get() + output.pos);
				}
			}

			ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };

			const size_t remainingToFlush = ZSTD_endStream(cStream, &output);

			if (remainingToFlush)
			{
				return ByteArray();
			}

			buffer.insert(buffer.end(), pOutputBuffer.get(), pOutputBuffer.get() + output.pos);

			return ByteArray(std::move(buffer));
		}

		//bool CompressToFile(ByteArrayView view, const FilePath& outputPath, const int32 compressionLevel)
		//{

		//}

		bool CompressFileToFile(const FilePath& inputPath, const FilePath& outputPath, const int32 compressionLevel)
		{
			BinaryReader reader(inputPath);
			
			if (!reader)
			{
				return false;
			}

			const size_t inputBufferSize = ZSTD_CStreamInSize();
			const auto pInputBuffer = std::make_unique<uint8[]>(inputBufferSize);

			const size_t outputBufferSize = ZSTD_CStreamOutSize();
			const auto pOutputBuffer = std::make_unique<uint8[]>(outputBufferSize);

			ZSTD_CStream* const cStream = ZSTD_createCStream();

			if (!cStream)
			{
				return false;
			}

			const size_t initResult = ZSTD_initCStream(cStream, compressionLevel);

			if (ZSTD_isError(initResult))
			{
				return false;
			}

			size_t toRead = inputBufferSize;

			BinaryWriter writer(outputPath);

			if (!writer)
			{
				return false;
			}

			while (const size_t read = static_cast<size_t>(reader.read(pInputBuffer.get(), toRead)))
			{
				ZSTD_inBuffer input = { pInputBuffer.get(), read, 0 };

				while (input.pos < input.size)
				{
					ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };

					toRead = ZSTD_compressStream(cStream, &output, &input);

					if (ZSTD_isError(toRead))
					{
						writer.clear();

						return false;
					}

					if (toRead > inputBufferSize)
					{
						toRead = inputBufferSize;
					}

					writer.write(pOutputBuffer.get(), output.pos);
				}
			}

			ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };

			const size_t remainingToFlush = ZSTD_endStream(cStream, &output);

			if (remainingToFlush)
			{
				writer.clear();

				return false;
			}

			writer.write(pOutputBuffer.get(), output.pos);

			return true;
		}
	}
}
