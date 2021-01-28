//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Base64.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

		constexpr static uint8 decodeTable[256] =
		{
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xfe, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3e, 0xff, 0x3e, 0xff, 0x3f,
			0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
			0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xff, 0xff, 0xff, 0xff, 0x3f,
			0xff, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
			0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		};

		[[nodiscard]]
		inline constexpr size_t EncodeLength(const size_t srcLength) noexcept
		{
			return (srcLength / 3 + (srcLength % 3 ? 1 : 0)) * 4;
		}

		[[nodiscard]]
		static constexpr size_t DecodeLength(const StringView view) noexcept
		{
			size_t length = (view.length() / 4) * 3;

			if (view.length() % 4 == 0 && !view.isEmpty())
			{
				length -= (view[view.length() - 2] == U'=') ? 2
					: (view[view.length() - 1] == U'=') ? 1 : 0;
			}

			return length;
		}

		[[nodiscard]]
		static constexpr size_t DecodeLength(const std::string_view view) noexcept
		{
			size_t length = (view.length() / 4) * 3;

			if ((view.length() % 4 == 0) && (not view.empty()))
			{
				length -= (view[view.length() - 2] == '=') ? 2
					: (view[view.length() - 1] == '=') ? 1 : 0;
			}

			return length;
		}
	}

	namespace Base64
	{
		String Encode(const void* const data, const size_t size)
		{
			String result;
			
			Encode(data, size, result);
			
			return result;
		}

		void Encode(const void* data, size_t size, String& dst)
		{
			dst.clear();
			dst.resize(detail::EncodeLength(size), U'=');

			const size_t blocks = (size / 3);
			const size_t remain = (size % 3);
			const uint8* pSrc = static_cast<const uint8*>(data);
			const uint8* pSrcBlocksEnd = pSrc + 3 * blocks;
			char32* pDst = dst.data();

			while (pSrc != pSrcBlocksEnd)
			{
				const uint32 n = pSrc[0] << 16 | pSrc[1] << 8 | pSrc[2];
				*pDst++ = detail::chars[(n >> 18)];
				*pDst++ = detail::chars[(n >> 12) & 0x3f];
				*pDst++ = detail::chars[(n >> 6) & 0x3f];
				*pDst++ = detail::chars[(n >> 0) & 0x3f];
				pSrc += 3;
			}

			if (remain == 1)
			{
				const uint32 n = (pSrc[0] << 16);
				*pDst++ = detail::chars[(n >> 18)];
				*pDst++ = detail::chars[(n >> 12) & 0x3f];
			}
			else if (remain == 2)
			{
				const uint32 n = (pSrc[0] << 16) | (pSrc[1] << 8);
				*pDst++ = detail::chars[(n >> 18)];
				*pDst++ = detail::chars[(n >> 12) & 0x3f];
				*pDst++ = detail::chars[(n >> 6) & 0x3f];
			}
		}

		void Encode(const void* data, size_t size, std::string& dst)
		{
			dst.clear();
			dst.resize(detail::EncodeLength(size), '=');

			const size_t blocks = (size / 3);
			const size_t remain = (size % 3);
			const uint8* pSrc = static_cast<const uint8*>(data);
			const uint8* pSrcBlocksEnd = pSrc + 3 * blocks;
			char* pDst = dst.data();

			while (pSrc != pSrcBlocksEnd)
			{
				const uint32 n = pSrc[0] << 16 | pSrc[1] << 8 | pSrc[2];
				*pDst++ = detail::chars[(n >> 18)];
				*pDst++ = detail::chars[(n >> 12) & 0x3f];
				*pDst++ = detail::chars[(n >> 6) & 0x3f];
				*pDst++ = detail::chars[(n >> 0) & 0x3f];
				pSrc += 3;
			}

			if (remain == 1)
			{
				const uint32 n = (pSrc[0] << 16);
				*pDst++ = detail::chars[(n >> 18)];
				*pDst++ = detail::chars[(n >> 12) & 0x3f];
			}
			else if (remain == 2)
			{
				const uint32 n = (pSrc[0] << 16) | (pSrc[1] << 8);
				*pDst++ = detail::chars[(n >> 18)];
				*pDst++ = detail::chars[(n >> 12) & 0x3f];
				*pDst++ = detail::chars[(n >> 6) & 0x3f];
			}
		}

		Blob Decode(const StringView base64)
		{
			if (not base64)
			{
				return{};
			}

			Array<Byte> dst(detail::DecodeLength(base64));
			const size_t blocks = (base64.length() / 4);
			const size_t remain = (base64.length() % 4);
			const char32* pSrc = base64.data();
			Byte* pDst = dst.data();

			for (size_t i = 0; i < blocks; ++i)
			{
				const uint8 v1 = detail::decodeTable[*pSrc++ & 0xff];
				const uint8 v2 = detail::decodeTable[*pSrc++ & 0xff];

				*pDst++ = static_cast<Byte>(v1 << 2 | v2 >> 4);

				const uint8 v3 = detail::decodeTable[*pSrc++ & 0xff];

				if (v3 == 0xFF)
				{
					break;
				}

				*pDst++ = static_cast<Byte>((v2 << 4 | v3 >> 2) & 0xff);

				const uint8 v4 = detail::decodeTable[*pSrc++ & 0xff];

				if (v4 == 0xFF)
				{
					break;
				}

				*pDst++ = static_cast<Byte>((v3 << 6 | v4) & 0xff);
			}

			if (remain)
			{
				const uint8 v1 = detail::decodeTable[*pSrc++ & 0xff];
				const uint8 v2 = detail::decodeTable[*pSrc++ & 0xff];

				*pDst++ = static_cast<Byte>(v1 << 2 | v2 >> 4);

				if (remain == 3)
				{
					*pDst++ = static_cast<Byte>((v2 << 4 | detail::decodeTable[*pSrc++ & 0xff] >> 2) & 0xff);
				}
			}

			return Blob{ std::move(dst) };
		}

		Blob Decode(const std::string_view base64)
		{
			if (base64.empty())
			{
				return{};
			}

			Array<Byte> dst(detail::DecodeLength(base64));
			const size_t blocks = (base64.length() / 4);
			const size_t remain = (base64.length() % 4);
			const char* pSrc = base64.data();
			Byte* pDst = dst.data();

			for (size_t i = 0; i < blocks; ++i)
			{
				const uint8 v1 = detail::decodeTable[static_cast<uint8>(*pSrc++)];
				const uint8 v2 = detail::decodeTable[static_cast<uint8>(*pSrc++)];

				*pDst++ = static_cast<Byte>(v1 << 2 | v2 >> 4);

				const uint8 v3 = detail::decodeTable[*pSrc++ & 0xff];

				if (v3 == 0xFF)
				{
					break;
				}

				*pDst++ = static_cast<Byte>((v2 << 4 | v3 >> 2) & 0xff);

				const uint8 v4 = detail::decodeTable[static_cast<uint8>(*pSrc++)];

				if (v4 == 0xFF)
				{
					break;
				}

				*pDst++ = static_cast<Byte>((v3 << 6 | v4) & 0xff);
			}

			if (remain)
			{
				const uint8 v1 = detail::decodeTable[static_cast<uint8>(*pSrc++)];
				const uint8 v2 = detail::decodeTable[static_cast<uint8>(*pSrc++)];

				*pDst++ = static_cast<Byte>(v1 << 2 | v2 >> 4);

				if (remain == 3)
				{
					*pDst++ = static_cast<Byte>((v2 << 4 | detail::decodeTable[static_cast<uint8>(*pSrc++)] >> 2) & 0xff);
				}
			}

			return Blob{ std::move(dst) };
		}
	}
}
