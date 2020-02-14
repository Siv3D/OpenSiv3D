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

# include <Siv3D/Zlib.hpp>
# include <Siv3D/ByteArray.hpp>
# include <zlib/zlib.h>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]] ::Bytef* ToBytef(Byte* p)
		{
			return static_cast<::Bytef*>(static_cast<void*>(p));
		}

		[[nodiscard]] ::Bytef* ToBytef(const Byte* p)
		{
			return const_cast<::Bytef*>(static_cast<const ::Bytef*>(static_cast<const void*>(p)));
		}
	}

	namespace Zlib
	{
		ByteArray Compress(const ByteArrayViewAdapter view, const int32 _compressionLevel)
		{
			const int32 compressionLevel = Clamp(_compressionLevel, MinCompressionLevel, MaxCompressionLevel);
			constexpr uint32 BufferSize = 2048;
			Byte buffer[BufferSize];

			z_stream z;
			z.zalloc	= Z_NULL;
			z.zfree		= Z_NULL;
			z.opaque	= Z_NULL;
			z.next_in	= detail::ToBytef(view.data());
			z.avail_in	= static_cast<uint32>(view.size());
			z.next_out	= detail::ToBytef(buffer);
			z.avail_out = BufferSize;

			if (deflateInit(&z, compressionLevel) != Z_OK)
			{
				return{};
			}

			Array<Byte> result;

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
					result.insert(result.end(), std::begin(buffer), std::end(buffer));
					z.next_out	= detail::ToBytef(buffer);
					z.avail_out	= BufferSize;
				}
			}

			if (const size_t writeSize = (BufferSize - z.avail_out);
				writeSize > 0)
			{
				result.insert(result.end(), std::begin(buffer), std::begin(buffer) + writeSize);
			}

			if (deflateEnd(&z) != Z_OK)
			{
				return{};
			}

			return ByteArray(std::move(result));
		}

		ByteArray Decompress(const ByteArrayView view)
		{
			constexpr uint32 BufferSize = 2048;
			Byte buffer[BufferSize];

			z_stream z;
			z.zalloc	= Z_NULL;
			z.zfree		= Z_NULL;
			z.opaque	= Z_NULL;
			z.next_in	= detail::ToBytef(view.data());
			z.avail_in	= static_cast<uint32>(view.size());
			z.next_out	= detail::ToBytef(buffer);
			z.avail_out = BufferSize;

			if (inflateInit(&z) != Z_OK)
			{
				return{};
			}

			Array<Byte> result;
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
					result.insert(result.end(), std::begin(buffer), std::end(buffer));
					z.next_out = detail::ToBytef(buffer);
					z.avail_out = BufferSize;
				}
			}

			if (const size_t writeSize = (BufferSize - z.avail_out);
				writeSize > 0)
			{
				result.insert(result.end(), std::begin(buffer), std::begin(buffer) + writeSize);
			}

			if (inflateEnd(&z) != Z_OK)
			{
				return{};
			}

			return ByteArray(std::move(result));
		}
	}
}
