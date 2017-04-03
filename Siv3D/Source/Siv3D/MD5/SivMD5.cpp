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

# include "../../ThirdParty/md5/md5.h"
# include <Siv3D/MD5.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/FormatUtility.hpp>

namespace s3d
{
	String MD5Hash::asString() const
	{
		String s;
		s.reserve(32);

		for (const auto& v : value)
		{
			s.append(Pad(ToHex(v), { 2, L'0' }));
		}

		return s;
	}

	namespace Hash
	{
		MD5Hash MD5(const void* data, size_t size)
		{
			MD5_CTX ctx;
			MD5_Init(&ctx);

			MD5_Update(&ctx, data, static_cast<unsigned long>(size));

			MD5Hash result;
			MD5_Final(result.value, &ctx);

			return result;
		}
	
		MD5Hash MD5FromFile(const FilePath& path)
		{
			constexpr size_t bufferSize = 4096;

			BinaryReader reader(path);

			MD5_CTX ctx;
			MD5_Init(&ctx);

			if (int64 sizeToRead = reader.size())
			{
				Byte* const buffer = static_cast<Byte*>(::malloc(bufferSize));

				while (sizeToRead)
				{
					const int64 readSize = reader.read(buffer, bufferSize);

					MD5_Update(&ctx, buffer, static_cast<unsigned long>(readSize));

					sizeToRead -= readSize;
				}

				::free(buffer);
			}

			MD5Hash result;
			MD5_Final(result.value, &ctx);

			return result;
		}
	}
}
