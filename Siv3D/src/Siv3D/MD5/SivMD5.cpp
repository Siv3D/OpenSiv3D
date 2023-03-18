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

# include <Siv3D/MD5.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <ThirdParty/RFC1321/RFC1321.hpp>

namespace s3d
{
	namespace MD5
	{
		MD5Value FromBinary(const void* const data, size_t size)
		{
			MD5_CTX ctx;
			MD5Value result;

			MD5_Init(&ctx);
			MD5_Update(&ctx, data, static_cast<unsigned long>(size));
			MD5_Final(result.value.data(), &ctx);

			return result;
		}

		MD5Value FromBinary(const Blob& blob)
		{
			return FromBinary(blob.data(), blob.size());
		}

		MD5Value FromText(const StringView view)
		{
			return FromBinary(view.data(), view.size_bytes());
		}

		MD5Value FromText(const std::string_view view)
		{
			return FromBinary(view.data(), (view.size() * sizeof(char)));
		}

		MD5Value FromFile(const FilePathView path)
		{
			MD5_CTX ctx;
			MD5Value result;

			MD5_Init(&ctx);

			BinaryReader reader{ path };

			uint8 buffer[4096];

			while (int64 readSize = reader.read(buffer, sizeof(buffer)))
			{
				MD5_Update(&ctx, buffer, static_cast<uint32>(readSize));
			}

			MD5_Final(result.value.data(), &ctx);

			return result;
		}
	}
}
