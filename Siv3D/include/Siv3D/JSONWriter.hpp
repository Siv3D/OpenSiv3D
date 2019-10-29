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

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "Array.hpp"

namespace s3d
{
	namespace detail
	{
		struct JSONWriterDetail;
	};

	class JSONWriter
	{
	private:

		std::shared_ptr<detail::JSONWriterDetail> pImpl;

	public:

		JSONWriter();

		JSONWriter& setIndent(char32 ch, size_t count);

		JSONWriter& setMaxDecimalPlaces(int32 maxDecimalPlaces);

		void startObject();

		void endObject();

		void startArray();

		void endArray();

		JSONWriter& key(StringView key);

		void writeString(StringView value);

		void writeInt32(int32 value);

		void writeUint32(uint32 value);

		void writeInt64(int64 value);

		void writeUint64(uint64 value);

		void writeDouble(double value);

		void writeBool(bool value);

		void writeNull();

		template <class Type>
		void writeArray(std::initializer_list<Type> ilist)
		{
			startArray();

			for (const auto& value : ilist)
			{
				write(value);
			}

			endArray();
		}

		template <class Type, size_t Size>
		void writeArray(const std::array<Type, Size>& values)
		{
			startArray();

			for (const auto& value : values)
			{
				write(value);
			}

			endArray();
		}

		template <class Type>
		void writeArray(const Array<Type>& values)
		{
			startArray();

			for (const auto& value : values)
			{
				write(value);
			}

			endArray();
		}

		void write(int8 value);

		void write(uint8 value);

		void write(int16 value);

		void write(uint16 value);

		void write(int32 value);

		void write(uint32 value);

		void write(int64 value);

		void write(uint64 value);

		void write(float value);

		void write(double value);

		void write(StringView value);

		void write(const String& value);

		void write(const char32* value);

		void write(char32 value);

		template <class Bool, std::enable_if_t<std::is_same_v<Bool, bool>> * = nullptr>
		void write(bool value)
		{
			writeBool(value);
		}

		template <class Type, class = decltype(Formatter(std::declval<FormatData&>(), std::declval<Type>()))>
		void write(const Type& value)
		{
			writeString(Format(value));
		}

		[[nodiscard]] bool isComplete() const;

		[[nodiscard]] String get() const;

		bool save(FilePathView path);
	};
}
