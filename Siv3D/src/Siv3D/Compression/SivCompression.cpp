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

# include <zstd/zstd.h>
# include <Siv3D/Compression.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/ReaderView.hpp>

namespace s3d
{
	namespace Compression
	{
		ByteArray Compress(const ByteArrayViewAdapter view, const int32 compressionLevel)
		{
			const size_t bufferSize = ZSTD_compressBound(view.size());

			Array<Byte> buffer(bufferSize);

			const size_t result = ZSTD_compress(buffer.data(), buffer.size(), view.data(), view.size(), compressionLevel);

			if (ZSTD_isError(result))
			{
				return ByteArray();
			}

			buffer.resize(result);

			buffer.shrink_to_fit();

			return ByteArray(std::move(buffer));
		}

		ByteArray CompressFile(const FilePathView path, const int32 compressionLevel)
		{
			BinaryReader reader(path);

			if (!reader)
			{
				return ByteArray();
			}

			const size_t inputBufferSize = ZSTD_CStreamInSize();
			const auto pInputBuffer = std::make_unique<Byte[]>(inputBufferSize);

			const size_t outputBufferSize = ZSTD_CStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_CStream* const cStream = ZSTD_createCStream();

			if (!cStream)
			{
				return ByteArray();
			}

			const size_t initResult = ZSTD_initCStream(cStream, compressionLevel);

			if (ZSTD_isError(initResult))
			{
				ZSTD_freeCStream(cStream);
				return ByteArray();
			}

			size_t toRead = inputBufferSize;

			Array<Byte> buffer;

			while (const size_t read = static_cast<size_t>(reader.read(pInputBuffer.get(), toRead)))
			{
				ZSTD_inBuffer input = { pInputBuffer.get(), read, 0 };

				while (input.pos < input.size)
				{
					ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };
					
					toRead = ZSTD_compressStream(cStream, &output, &input);
					
					if (ZSTD_isError(toRead))
					{
						ZSTD_freeCStream(cStream);
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

			ZSTD_freeCStream(cStream);

			if (remainingToFlush)
			{
				return ByteArray();
			}

			buffer.insert(buffer.end(), pOutputBuffer.get(), pOutputBuffer.get() + output.pos);

			return ByteArray(std::move(buffer));
		}

		bool CompressToFile(const ByteArrayViewAdapter view, const FilePathView outputPath, const int32 compressionLevel)
		{
			const size_t inputBufferSize = ZSTD_CStreamInSize();
			const auto pInputBuffer = std::make_unique<Byte[]>(inputBufferSize);

			const size_t outputBufferSize = ZSTD_CStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_CStream* const cStream = ZSTD_createCStream();

			if (!cStream)
			{
				return false;
			}

			const size_t initResult = ZSTD_initCStream(cStream, compressionLevel);

			if (ZSTD_isError(initResult))
			{
				ZSTD_freeCStream(cStream);
				return false;
			}

			size_t toRead = inputBufferSize;

			BinaryWriter writer(outputPath);

			if (!writer)
			{
				ZSTD_freeCStream(cStream);
				return false;
			}

			ReaderView reader(view.data(), view.size());

			for (;;)
			{
				const size_t read = std::min<size_t>(toRead, view.size() - static_cast<size_t>(reader.getPos()));

				if (read == 0)
				{
					break;
				}

				reader.read(pInputBuffer.get(), read);

				ZSTD_inBuffer input = { pInputBuffer.get(), read, 0 };

				while (input.pos < input.size)
				{
					ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };

					toRead = ZSTD_compressStream(cStream, &output, &input);

					if (ZSTD_isError(toRead))
					{
						writer.clear();

						ZSTD_freeCStream(cStream);

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

			ZSTD_freeCStream(cStream);

			if (remainingToFlush)
			{
				writer.clear();

				return false;
			}

			writer.write(pOutputBuffer.get(), output.pos);

			return true;
		}

		bool CompressFileToFile(const FilePathView inputPath, const FilePathView outputPath, const int32 compressionLevel)
		{
			BinaryReader reader(inputPath);
			
			if (!reader)
			{
				return false;
			}

			const size_t inputBufferSize = ZSTD_CStreamInSize();
			const auto pInputBuffer = std::make_unique<Byte[]>(inputBufferSize);

			const size_t outputBufferSize = ZSTD_CStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_CStream* const cStream = ZSTD_createCStream();

			if (!cStream)
			{
				return false;
			}

			const size_t initResult = ZSTD_initCStream(cStream, compressionLevel);

			if (ZSTD_isError(initResult))
			{
				ZSTD_freeCStream(cStream);
				return false;
			}

			size_t toRead = inputBufferSize;

			BinaryWriter writer(outputPath);

			if (!writer)
			{
				ZSTD_freeCStream(cStream);
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

						ZSTD_freeCStream(cStream);

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

			ZSTD_freeCStream(cStream);

			if (remainingToFlush)
			{
				writer.clear();

				return false;
			}

			writer.write(pOutputBuffer.get(), output.pos);

			return true;
		}

		ByteArray Decompress(const ByteArrayView view)
		{
			const uint64 originalSize = ZSTD_getDecompressedSize(view.data(), view.size());

			if (originalSize == 0)
			{
				return ByteArray();
			}

			Array<Byte> outputBuffer(static_cast<size_t>(originalSize));

			const size_t decompressedSize = ZSTD_decompress(outputBuffer.data(), outputBuffer.size(), view.data(), view.size());

			if (originalSize != decompressedSize)
			{
				return ByteArray();
			}

			return ByteArray(std::move(outputBuffer));
		}

		ByteArray DecompressFile(const FilePathView path)
		{
			BinaryReader reader(path);

			if (!reader)
			{
				return ByteArray();
			}

			const size_t inputBufferSize = ZSTD_DStreamInSize();
			const auto pInputBuffer = std::make_unique<Byte[]>(inputBufferSize);

			const size_t outputBufferSize = ZSTD_DStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_DStream* const dStream = ZSTD_createDStream();

			if (!dStream)
			{
				return ByteArray();
			}

			const size_t initResult = ZSTD_initDStream(dStream);

			if (ZSTD_isError(initResult))
			{
				ZSTD_freeDStream(dStream);
				return ByteArray();
			}

			size_t toRead = initResult;

			Array<Byte> buffer;

			while (const size_t read = static_cast<size_t>(reader.read(pInputBuffer.get(), toRead)))
			{
				ZSTD_inBuffer input = { pInputBuffer.get(), read, 0 };

				while (input.pos < input.size)
				{
					ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };

					toRead = ZSTD_decompressStream(dStream, &output, &input);

					if (ZSTD_isError(toRead))
					{
						ZSTD_freeDStream(dStream);
						return ByteArray();
					}

					buffer.insert(buffer.end(), pOutputBuffer.get(), pOutputBuffer.get() + output.pos);
				}
			}

			ZSTD_freeDStream(dStream);

			return ByteArray(std::move(buffer));
		}

		bool DecompressToFile(const ByteArrayView view, const FilePathView outputPath)
		{
			const size_t inputBufferSize = ZSTD_DStreamInSize();
			const auto pInputBuffer = std::make_unique<Byte[]>(inputBufferSize);

			const size_t outputBufferSize = ZSTD_DStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_DStream* const dStream = ZSTD_createDStream();

			if (!dStream)
			{
				return false;
			}

			const size_t initResult = ZSTD_initDStream(dStream);

			if (ZSTD_isError(initResult))
			{
				ZSTD_freeDStream(dStream);
				return false;
			}

			size_t toRead = initResult;

			BinaryWriter writer(outputPath);

			if (!writer)
			{
				ZSTD_freeDStream(dStream);
				return false;
			}

			ReaderView reader(view.data(), view.size());

			for (;;)
			{
				const size_t read = std::min<size_t>(toRead, view.size() - static_cast<size_t>(reader.getPos()));

				if (read == 0)
				{
					break;
				}

				reader.read(pInputBuffer.get(), read);

				ZSTD_inBuffer input = { pInputBuffer.get(), read, 0 };

				while (input.pos < input.size)
				{
					ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };

					toRead = ZSTD_decompressStream(dStream, &output, &input);

					if (ZSTD_isError(toRead))
					{
						writer.clear();

						ZSTD_freeDStream(dStream);

						return false;
					}

					writer.write(pOutputBuffer.get(), output.pos);
				}
			}

			ZSTD_freeDStream(dStream);

			return true;
		}

		bool DecompressFileToFile(const FilePathView inputPath, const FilePathView outputPath)
		{
			BinaryReader reader(inputPath);

			if (!reader)
			{
				return false;
			}

			const size_t inputBufferSize = ZSTD_DStreamInSize();
			const auto pInputBuffer = std::make_unique<Byte[]>(inputBufferSize);

			const size_t outputBufferSize = ZSTD_DStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_DStream* const dStream = ZSTD_createDStream();

			if (!dStream)
			{
				return false;
			}

			const size_t initResult = ZSTD_initDStream(dStream);

			if (ZSTD_isError(initResult))
			{
				ZSTD_freeDStream(dStream);
				return false;
			}

			size_t toRead = initResult;

			BinaryWriter writer(outputPath);

			if (!writer)
			{
				ZSTD_freeDStream(dStream);
				return false;
			}

			while (const size_t read = static_cast<size_t>(reader.read(pInputBuffer.get(), toRead)))
			{
				ZSTD_inBuffer input = { pInputBuffer.get(), read, 0 };

				while (input.pos < input.size)
				{
					ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };

					toRead = ZSTD_decompressStream(dStream, &output, &input);

					if (ZSTD_isError(toRead))
					{
						writer.clear();

						ZSTD_freeDStream(dStream);

						return false;
					}

					writer.write(pOutputBuffer.get(), output.pos);
				}
			}

			ZSTD_freeDStream(dStream);

			return true;
		}
	}
}
