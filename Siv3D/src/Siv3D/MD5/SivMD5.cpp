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

# include <Siv3D/MD5.hpp>
# include <Siv3D/ByteArray.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/FormatUtility.hpp>
# include <RFC1321/RFC1321.hpp>

namespace s3d
{
	String MD5Value::asString() const
	{
		String s;
		s.reserve(32);

		for (const auto& v : value)
		{
			s.append(Pad(ToHex(v), { 2, U'0' }));
		}

		return s;
	}

	bool MD5Value::operator ==(const MD5Value& other) const noexcept
	{
		return ::memcmp(value.data(), other.value.data(), sizeof(value)) == 0;
	}

	bool MD5Value::operator !=(const MD5Value& other) const noexcept
	{
		return !(*this == other);
	}

	namespace MD5
	{
		MD5Value FromBinary(const void* const data, const size_t size)
		{
			MD5_CTX ctx;
			MD5Value result;

			MD5_Init(&ctx);
			MD5_Update(&ctx, data, static_cast<uint32>(size));
			MD5_Final(result.value.data(), &ctx);

			return result;
		}

		MD5Value FromBinary(const ByteArrayView view)
		{
			return FromBinary(view.data(), view.size_bytes());
		}

		MD5Value FromBinary(const ByteArrayViewAdapter view)
		{
			return FromBinary(view.data(), view.size_bytes());
		}

		MD5Value FromText(const StringView view)
		{
			return FromBinary(view.data(), view.size_bytes());
		}

		MD5Value FromText(const std::string_view view)
		{
			return FromBinary(view.data(), sizeof(char) * view.size());
		}

		MD5Value FromFile(const FilePath& path)
		{
			MD5_CTX ctx;
			MD5Value result;

			MD5_Init(&ctx);
			
			BinaryReader reader(path);

			uint8 buffer[4096];

			while (int64 readSize = reader.read(buffer, sizeof(buffer)))
			{
				MD5_Update(&ctx, buffer, static_cast<uint32>(readSize));
			}
			
			MD5_Final(result.value.data(), &ctx);

			return result;
		}
	}

	void Formatter(FormatData& formatData, const MD5Value& value)
	{
		formatData.string.append(value.asString());
	}
}
