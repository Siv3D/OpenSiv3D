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

# include <Siv3D/JSONWriter.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/TextWriter.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(5054)
# define RAPIDJSON_SSE2
# define RAPIDJSON_HAS_STDSTRING 1
# include <../../Siv3D/src/ThirdParty/rapidjson/writer.h>
# include <../../Siv3D/src/ThirdParty/rapidjson/prettywriter.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	namespace detail
	{
		struct JSONWriterDetail
		{
			using StringBuffer = rapidjson::GenericStringBuffer<rapidjson::UTF32<char32>>;

			StringBuffer buffer;

			rapidjson::PrettyWriter<StringBuffer, rapidjson::UTF32<char32>, rapidjson::UTF32<char32>> writer;

			JSONWriterDetail()
				: writer(buffer) {}
		};
	}

	JSONWriter::JSONWriter()
		: pImpl(std::make_shared<detail::JSONWriterDetail>())
	{
		setIndent(U' ', 2);
	}


	JSONWriter& JSONWriter::setIndent(const char32 ch, const size_t count)
	{
		pImpl->writer.SetIndent(ch, static_cast<uint32>(count));

		return *this;
	}

	JSONWriter& JSONWriter::setMaxDecimalPlaces(const int32 maxDecimalPlaces)
	{
		pImpl->writer.SetMaxDecimalPlaces(maxDecimalPlaces);

		return *this;
	}

	void JSONWriter::startObject()
	{
		pImpl->writer.StartObject();
	}

	void JSONWriter::endObject()
	{
		pImpl->writer.EndObject();
	}

	void JSONWriter::startArray()
	{
		pImpl->writer.StartArray();
	}

	void JSONWriter::endArray()
	{
		pImpl->writer.EndArray();
	}

	JSONWriter& JSONWriter::key(const StringView key)
	{
		if (!pImpl->writer.Key(key.data(), static_cast<rapidjson::SizeType>(key.size())))
		{
			throw Error(U"JSONWriter::key({}): failed"_fmt(key));
		}

		return *this;
	}

	void JSONWriter::writeString(const StringView value)
	{
		if (!pImpl->writer.String(value.data(), static_cast<rapidjson::SizeType>(value.size())))
		{
			throw Error(U"JSONWriter::writeString({}): failed"_fmt(value));
		}
	}

	void JSONWriter::writeInt32(const int32 value)
	{
		if (!pImpl->writer.Int(value))
		{
			throw Error(U"JSONWriter::writeInt32({}): failed"_fmt(value));
		}
	}

	void JSONWriter::writeUint32(const uint32 value)
	{
		if (!pImpl->writer.Uint(value))
		{
			throw Error(U"JSONWriter::writeUint32({}): failed"_fmt(value));
		}
	}

	void JSONWriter::writeInt64(const int64 value)
	{
		if (!pImpl->writer.Int64(value))
		{
			throw Error(U"JSONWriter::writeInt64({}): failed"_fmt(value));
		}
	}

	void JSONWriter::writeUint64(const uint64 value)
	{
		if (!pImpl->writer.Uint64(value))
		{
			throw Error(U"JSONWriter::writeUint64({}): failed"_fmt(value));
		}
	}

	void JSONWriter::writeDouble(const double value)
	{
		if (!pImpl->writer.Double(value))
		{
			throw Error(U"JSONWriter::writeDouble({}): failed"_fmt(value));
		}
	}

	void JSONWriter::writeBool(const bool value)
	{
		if (!pImpl->writer.Bool(value))
		{
			throw Error(U"JSONWriter::writeBool({}): failed"_fmt(value));
		}
	}

	void JSONWriter::writeNull()
	{
		if (!pImpl->writer.Null())
		{
			throw Error(U"JSONWriter::writeNull(): failed");
		}
	}

	void JSONWriter::write(const int8 value)
	{
		writeInt32(value);
	}

	void JSONWriter::write(const uint8 value)
	{
		writeUint32(value);
	}

	void JSONWriter::write(const int16 value)
	{
		writeInt32(value);
	}

	void JSONWriter::write(const uint16 value)
	{
		writeUint32(value);
	}

	void JSONWriter::write(const int32 value)
	{
		writeInt32(value);
	}

	void JSONWriter::write(const uint32 value)
	{
		writeUint32(value);
	}

	void JSONWriter::write(const int64 value)
	{
		writeInt64(value);
	}

	void JSONWriter::write(const uint64 value)
	{
		writeUint64(value);
	}

	void JSONWriter::write(const float value)
	{
		writeDouble(value);
	}

	void JSONWriter::write(const double value)
	{
		writeDouble(value);
	}

	void JSONWriter::write(const StringView value)
	{
		writeString(value);
	}

	void JSONWriter::write(const String& value)
	{
		writeString(value);
	}

	void JSONWriter::write(const char32* value)
	{
		if (!value)
		{
			return writeNull();
		}

		writeString(value);
	}

	void JSONWriter::write(const char32 value)
	{
		if (!value)
		{
			return writeNull();
		}

		writeString(StringView(&value, 1));
	}

	bool JSONWriter::isComplete() const
	{
		return pImpl->writer.IsComplete();
	}

	String JSONWriter::get() const
	{
		if (!isComplete())
		{
			return String();
		}

		return String(pImpl->buffer.GetString(), pImpl->buffer.GetLength());
	}

	bool JSONWriter::save(const FilePathView path)
	{
		if (!isComplete())
		{
			return false;
		}

		TextWriter writer(path);

		if (!writer)
		{
			return false;
		}

		writer.writeln(get());

		return true;
	}
}
