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
# include "Fwd.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "Optional.hpp"
# include "Parse.hpp"

namespace s3d
{
	class CSVData
	{
	private:

		Array<Array<String>> m_data;

		bool m_onHead = true;

		Optional<String> getItem(size_t row, size_t column) const;

		bool inBounds(size_t row, size_t column) const;

		bool loadFromTextReader(TextReader& reader, StringView separators, StringView quotes, StringView escapes);

		void _write()
		{
			return;
		}

		template <class Type, class ... Args>
		void _write(const Type& record, const Args& ... records)
		{
			write(Format(record));

			return _write(records...);
		}

	public:

		CSVData();

		explicit CSVData(const FilePath& path, StringView separators = U",", StringView quotes = U"\"", StringView escapes = U"\\");

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>* = nullptr>
		explicit CSVData(Reader&& reader, StringView separators = U",", StringView quotes = U"\"", StringView escapes = U"\\")
		{
			load(std::move(reader), separators, quotes, escapes);
		}

		explicit CSVData(const std::shared_ptr<IReader>& reader, StringView separators = U",", StringView quotes = U"\"", StringView escapes = U"\\");

		bool load(const FilePath& path, StringView separators = U",", StringView quotes = U"\"", StringView escapes = U"\\");

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>* = nullptr>
		bool load(Reader&& reader, StringView separators = U",", StringView quotes = U"\"", StringView escapes = U"\\")
		{
			return load(std::make_shared<Reader>(std::move(reader), separators, quotes, escapes));
		}

		bool load(const std::shared_ptr<IReader>& reader, StringView separators = U",", StringView quotes = U"\"", StringView escapes = U"\\");

		void clear();

		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] explicit operator bool() const { return isEmpty(); }

		[[nodiscard]] size_t rows() const;

		[[nodiscard]] size_t columns(size_t row) const;

		template <class Type = String>
		[[nodiscard]] Type get(size_t row, size_t column) const
		{
			if (const auto opt = getOpt<Type>(row, column))
			{
				return opt.value();
			}

			return Type();
		}

		template <class Type, class U>
		[[nodiscard]] Type getOr(size_t row, size_t column, U&& defaultValue) const
		{
			return getOpt<Type>(row, column).value_or(std::forward<U>(defaultValue));
		}

		template <class Type>
		[[nodiscard]] Optional<Type> getOpt(size_t row, size_t column) const
		{
			if (const auto item = getItem(row, column))
			{
				return ParseOpt<Type>(item.value());
			}

			return none;
		}

		[[nodiscard]] const Array<Array<String>>& getData() const;

		[[nodiscard]] const Array<String>& getRow(size_t row) const;

		[[nodiscard]] const Array<String>& operator [](size_t row) const;

		[[nodiscard]] Array<Array<String>>& getData();

		[[nodiscard]] Array<String>& getRow(size_t row);

		[[nodiscard]] Array<String>& operator [](size_t row);

		void write(const String& record);

		template <class Type>
		void write(const Type& value)
		{
			write(Format(value));
		}

		template <class ... Args>
		void write(const Args& ... records)
		{
			_write(records...);
		}

		template <class ... Args>
		void writeRow(const Args& ... records)
		{
			_write(records...);

			newLine();
		}

		void newLine();

		bool save(const FilePath& path, char32 separator = U',', char32 quote = U'\"', char32 escape = U'\\') const;
	};
}
