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

# include <Siv3D/Zlib.hpp>
# include <ThirdParty/zlib/zlib.h>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		::Bytef* ToBytef(void* p) noexcept
		{
			return static_cast<::Bytef*>(p);
		}

		[[nodiscard]]
		::Bytef* ToBytef(const void* p) noexcept
		{
			return const_cast<::Bytef*>(static_cast<const ::Bytef*>(p));
		}
	}

	namespace Zlib
	{
		Blob Compress(const void* data, const size_t size, const int32 compressionLevel)
		{
			Blob blob;

			if (Compress(data, size, blob, compressionLevel))
			{
				return blob;
			}
			else
			{
				return{};
			}
		}

		bool Compress(const void* data, const size_t size, Blob& dst, const int32 _compressionLevel)
		{
			dst.clear();

			const int32 compressionLevel = Clamp(_compressionLevel, MinCompressionLevel, MaxCompressionLevel);
			constexpr uint32 BufferSize = 2048;
			Byte buffer[BufferSize];

			z_stream z;
			z.zalloc = Z_NULL;
			z.zfree = Z_NULL;
			z.opaque = Z_NULL;
			z.next_in = detail::ToBytef(data);
			z.avail_in = static_cast<uint32>(size);
			z.next_out = detail::ToBytef(buffer);
			z.avail_out = BufferSize;

			if (deflateInit(&z, compressionLevel) != Z_OK)
			{
				return{};
			}

			for (;;)
			{
				const int32 r = deflate(&z, Z_FINISH);

				if (r == Z_STREAM_END)
				{
					break;
				}

				if (r != Z_OK)
				{
					deflateEnd(&z);
					return{};
				}

				if (z.avail_out == 0)
				{
					dst.append(buffer, sizeof(buffer));
					z.next_out = detail::ToBytef(buffer);
					z.avail_out = BufferSize;
				}
			}

			if (const size_t writeSize = (BufferSize - z.avail_out);
				writeSize > 0)
			{
				dst.append(buffer, writeSize);
			}

			if (deflateEnd(&z) != Z_OK)
			{
				return{};
			}

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

		Blob Decompress(const void* data, const size_t size)
		{
			Blob blob;

			if (Decompress(data, size, blob))
			{
				return blob;
			}
			else
			{
				return{};
			}
		}

		bool Decompress(const void* data, const size_t size, Blob& dst)
		{
			dst.clear();

			constexpr uint32 BufferSize = 2048;
			Byte buffer[BufferSize];

			z_stream z;
			z.zalloc = Z_NULL;
			z.zfree = Z_NULL;
			z.opaque = Z_NULL;
			z.next_in = detail::ToBytef(data);
			z.avail_in = static_cast<uint32>(size);
			z.next_out = detail::ToBytef(buffer);
			z.avail_out = BufferSize;

			if (inflateInit(&z) != Z_OK)
			{
				return{};
			}

			int32 r = Z_OK;

			while (r != Z_STREAM_END)
			{
				r = inflate(&z, Z_NO_FLUSH);

				if (r == Z_STREAM_END)
				{
					break;
				}
				else if (r != Z_OK)
				{
					inflateEnd(&z);
					return{};
				}

				if (z.avail_out == 0)
				{
					dst.append(buffer, sizeof(buffer));
					z.next_out = detail::ToBytef(buffer);
					z.avail_out = BufferSize;
				}
			}

			if (const size_t writeSize = (BufferSize - z.avail_out);
				writeSize > 0)
			{
				dst.append(buffer, writeSize);
			}

			if (inflateEnd(&z) != Z_OK)
			{
				return{};
			}

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
	}
}
