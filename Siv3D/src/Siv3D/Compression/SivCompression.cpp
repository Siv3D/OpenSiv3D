//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Compression.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <ThirdParty/zstd/zstd.h>

# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace Compression
	{
		Blob Compress(const void* data, const size_t size, const int32 compressionLevel)
		{
			Blob blob;

			if (not Compress(data, size, blob, compressionLevel))
			{
				return{};
			}

			return blob;
		}

		bool Compress(const void* data, const size_t size, Blob& dst, const int32 compressionLevel)
		{
			const size_t bufferSize = ZSTD_compressBound(size);

			dst.resize(bufferSize);

			const size_t result = ZSTD_compress(dst.data(), dst.size(), data, size, compressionLevel);

			if (ZSTD_isError(result))
			{
				dst.clear();
				return false;
			}

			dst.resize(result);

			return true;
		}

		Blob Compress(const Blob& blob, const int32 compressionLevel)
		{
			return Compress(blob.data(), blob.size(), compressionLevel);
		}

		bool Compress(const Blob& blob, Blob& dst, const int32 compressionLevel)
		{
			return Compress(blob.data(), blob.size(), dst, compressionLevel);
		}

		Blob CompressFile(const FilePathView path, const int32 compressionLevel)
		{
			Blob blob;

			if (not CompressFile(path, blob, compressionLevel))
			{
				return{};
			}

			return blob;
		}

		bool CompressFile(const FilePathView path, Blob& dst, const int32 compressionLevel)
		{
			dst.clear();

			BinaryReader reader{ path };

			if (not reader)
			{
				return false;
			}

			const size_t inputBufferSize = ZSTD_CStreamInSize();
			const auto pInputBuffer = std::make_unique<Byte[]>(inputBufferSize);

			const size_t outputBufferSize = ZSTD_CStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_CStream* const cStream = ZSTD_createCStream();

			if (not cStream)
			{
				return false;
			}

			if (const size_t ret = ZSTD_initCStream(cStream, compressionLevel); 
				ZSTD_isError(ret))
			{
				ZSTD_freeCStream(cStream);
				return false;
			}

			size_t toRead = inputBufferSize;

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
						return false;
					}

					if (toRead > inputBufferSize)
					{
						toRead = inputBufferSize;
					}

					dst.append(pOutputBuffer.get(), output.pos);
				}
			}

			ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };

			const size_t remainingToFlush = ZSTD_endStream(cStream, &output);

			ZSTD_freeCStream(cStream);

			if (remainingToFlush)
			{
				return false;
			}

			dst.append(pOutputBuffer.get(), output.pos);

			return true;
		}

		bool CompressToFile(const void* data, const size_t size, const FilePathView outputPath, const int32 compressionLevel)
		{
			const size_t inputBufferSize = ZSTD_CStreamInSize();
			const size_t outputBufferSize = ZSTD_CStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_CStream* const cStream = ZSTD_createCStream();

			if (not cStream)
			{
				return false;
			}

			if (const size_t ret = ZSTD_initCStream(cStream, compressionLevel); 
				ZSTD_isError(ret))
			{
				ZSTD_freeCStream(cStream);
				return false;
			}

			size_t toRead = inputBufferSize;

			BinaryWriter writer{ outputPath };

			if (not writer)
			{
				ZSTD_freeCStream(cStream);
				return false;
			}

			size_t readPos = 0;

			for (;;)
			{
				const size_t read = Min(toRead, (size - readPos));

				if (read == 0)
				{
					break;
				}

				ZSTD_inBuffer input = { (static_cast<const Byte*>(data) + readPos), read, 0 };

				readPos += read;

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

		bool CompressToFile(const Blob& blob, const FilePathView outputPath, const int32 compressionLevel)
		{
			return CompressToFile(blob.data(), blob.size(), outputPath, compressionLevel);
		}

		bool CompressFileToFile(const FilePathView inputPath, const FilePathView outputPath, const int32 compressionLevel)
		{
			BinaryReader reader{ inputPath };

			if (not reader)
			{
				return false;
			}

			const size_t inputBufferSize = ZSTD_CStreamInSize();
			const auto pInputBuffer = std::make_unique<Byte[]>(inputBufferSize);

			const size_t outputBufferSize = ZSTD_CStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_CStream* const cStream = ZSTD_createCStream();

			if (not cStream)
			{
				return false;
			}

			if (const size_t ret = ZSTD_initCStream(cStream, compressionLevel); 
				ZSTD_isError(ret))
			{
				ZSTD_freeCStream(cStream);
				return false;
			}

			size_t toRead = inputBufferSize;

			BinaryWriter writer{ outputPath };

			if (not writer)
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

		Blob Decompress(const void* data, const size_t size)
		{
			Blob blob;

			if (not Decompress(data, size, blob))
			{
				return{};
			}

			return blob;
		}

		bool Decompress(const void* data, const size_t size, Blob& dst)
		{
			dst.clear();

			const size_t inputBufferSize = ZSTD_DStreamInSize();
			const size_t outputBufferSize = ZSTD_DStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_DStream* const dStream = ZSTD_createDStream();

			if (not dStream)
			{
				return false;
			}

			if (const size_t ret = ZSTD_initDStream(dStream); 
				ZSTD_isError(ret))
			{
				ZSTD_freeDStream(dStream);
				return false;
			}

			size_t readPos = 0;

			for (;;)
			{
				const size_t read = Min(inputBufferSize, (size - readPos));

				if (read == 0)
				{
					break;
				}

				ZSTD_inBuffer input = { (static_cast<const Byte*>(data) + readPos), read, 0 };

				readPos += read;

				while (input.pos < input.size)
				{
					ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };

					if (const size_t ret = ZSTD_decompressStream(dStream, &output, &input); 
						ZSTD_isError(ret))
					{
						dst.clear();

						ZSTD_freeDStream(dStream);

						return false;
					}

					dst.append(pOutputBuffer.get(), output.pos);
				}
			}

			ZSTD_freeDStream(dStream);

			return true;
		}

		Blob Decompress(const Blob& blob)
		{
			return Decompress(blob.data(), blob.size());
		}

		bool Decompress(const Blob& blob, Blob& dst)
		{
			return Decompress(blob.data(), blob.size(), dst);
		}

		Blob DecompressFile(const FilePathView path)
		{
			Blob blob;

			if (not DecompressFile(path, blob))
			{
				return{};
			}

			return blob;
		}

		bool DecompressFile(const FilePathView path, Blob& dst)
		{
			dst.clear();

			BinaryReader reader{ path };

			if (not reader)
			{
				return false;
			}

			const size_t inputBufferSize = ZSTD_DStreamInSize();
			const auto pInputBuffer = std::make_unique<Byte[]>(inputBufferSize);

			const size_t outputBufferSize = ZSTD_DStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_DStream* const dStream = ZSTD_createDStream();

			if (not dStream)
			{
				return false;
			}

			if (const size_t ret = ZSTD_initDStream(dStream); 
				ZSTD_isError(ret))
			{
				ZSTD_freeDStream(dStream);
				return false;
			}

			while (const size_t read = static_cast<size_t>(reader.read(pInputBuffer.get(), inputBufferSize)))
			{
				ZSTD_inBuffer input = { pInputBuffer.get(), read, 0 };

				while (input.pos < input.size)
				{
					ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };

					if (const size_t ret = ZSTD_decompressStream(dStream, &output, &input); 
						ZSTD_isError(ret))
					{
						ZSTD_freeDStream(dStream);
						return false;
					}

					dst.append(pOutputBuffer.get(), output.pos);
				}
			}

			ZSTD_freeDStream(dStream);

			return true;
		}

		bool DecompressToFile(const void* data, const size_t size, const FilePathView outputPath)
		{
			const size_t inputBufferSize = ZSTD_DStreamInSize();
			const size_t outputBufferSize = ZSTD_DStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_DStream* const dStream = ZSTD_createDStream();

			if (not dStream)
			{
				return false;
			}

			if (const size_t ret = ZSTD_initDStream(dStream); 
				ZSTD_isError(ret))
			{
				ZSTD_freeDStream(dStream);
				return false;
			}

			BinaryWriter writer{ outputPath };

			if (not writer)
			{
				ZSTD_freeDStream(dStream);
				return false;
			}

			size_t readPos = 0;

			for (;;)
			{
				const size_t read = Min<size_t>(inputBufferSize, (size - readPos));

				if (read == 0)
				{
					break;
				}

				ZSTD_inBuffer input = { (static_cast<const Byte*>(data) + readPos), read, 0 };

				readPos += read;

				while (input.pos < input.size)
				{
					ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };

					if (const size_t ret = ZSTD_decompressStream(dStream, &output, &input); 
						ZSTD_isError(ret))
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

		bool DecompressToFile(const Blob& blob, const FilePathView outputPath)
		{
			return DecompressToFile(blob.data(), blob.size(), outputPath);
		}

		bool DecompressFileToFile(const FilePathView inputPath, const FilePathView outputPath)
		{
			BinaryReader reader{ inputPath };

			if (not reader)
			{
				return false;
			}

			const size_t inputBufferSize = ZSTD_DStreamInSize();
			const auto pInputBuffer = std::make_unique<Byte[]>(inputBufferSize);

			const size_t outputBufferSize = ZSTD_DStreamOutSize();
			const auto pOutputBuffer = std::make_unique<Byte[]>(outputBufferSize);

			ZSTD_DStream* const dStream = ZSTD_createDStream();

			if (not dStream)
			{
				return false;
			}

			if (const size_t ret = ZSTD_initDStream(dStream);
				ZSTD_isError(ret))
			{
				ZSTD_freeDStream(dStream);
				return false;
			}

			BinaryWriter writer{ outputPath };

			if (not writer)
			{
				ZSTD_freeDStream(dStream);
				return false;
			}

			while (const size_t read = static_cast<size_t>(reader.read(pInputBuffer.get(), inputBufferSize)))
			{
				ZSTD_inBuffer input = { pInputBuffer.get(), read, 0 };

				while (input.pos < input.size)
				{
					ZSTD_outBuffer output = { pOutputBuffer.get(), outputBufferSize, 0 };

					if (const size_t ret = ZSTD_decompressStream(dStream, &output, &input); 
						ZSTD_isError(ret))
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
