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

# include <boost/tokenizer.hpp>
# include <Siv3D/CSVData.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/TextWriter.hpp>

namespace s3d
{
	namespace detail
	{
		std::u32string ToU32String(StringView view)
		{
			return std::u32string(view.begin(), view.end());
		}
	}

	Optional<String> CSVData::getItem(const size_t row, const size_t column) const
	{
		if (!inBounds(row, column))
		{
			return none;
		}

		return m_data[row][column];
	}

	bool CSVData::inBounds(const size_t row, const size_t column) const
	{
		return (row < m_data.size()) && (column < m_data[row].size());
	}

	bool CSVData::loadFromTextReader(TextReader& reader, const StringView separators, const StringView quotes, const StringView escapes)
	{
		if (!reader)
		{
			return false;
		}

		const boost::escaped_list_separator<char32> separator(detail::ToU32String(escapes), detail::ToU32String(separators), detail::ToU32String(quotes));

		String str;

		m_data.clear();

		while (reader.readLine(str))
		{
			try
			{
				const boost::tokenizer<boost::escaped_list_separator<char32>, String::const_iterator, String> tokens(str, separator);

				m_data.emplace_back(tokens.begin(), tokens.end());
			}
			catch (boost::exception&)
			{
				str.replace(U"\\", U"\\\\");

				const boost::tokenizer<boost::escaped_list_separator<char32>, String::const_iterator, String> tokens(str, separator);

				m_data.emplace_back(tokens.begin(), tokens.end());
			}
		}

		return true;
	}

	CSVData::CSVData()
	{

	}

	CSVData::CSVData(const FilePathView path, const StringView separators, const StringView quotes , const StringView escapes)
	{
		load(path, separators, quotes, escapes);
	}

	CSVData::CSVData(const std::shared_ptr<IReader>& reader, const StringView separators, const StringView quotes, const StringView escapes)
	{
		load(reader, separators, quotes, escapes);
	}

	bool CSVData::load(const FilePathView path, const StringView separators, const StringView quotes, const StringView escapes)
	{
		TextReader textReader(path);

		if (!loadFromTextReader(textReader, separators, quotes, escapes))
		{
			clear();

			return false;
		}

		return true;
	}

	bool CSVData::load(const std::shared_ptr<IReader>& reader, const StringView separators, const StringView quotes, const StringView escapes)
	{
		TextReader textReader(reader);

		if (!loadFromTextReader(textReader, separators, quotes, escapes))
		{
			clear();

			return false;
		}

		return true;
	}

	void CSVData::clear()
	{
		m_data.clear();
	}

	bool CSVData::isEmpty() const
	{
		return m_data.isEmpty();
	}

	size_t CSVData::rows() const
	{
		return m_data.size();
	}

	size_t CSVData::columns(const size_t row) const
	{
		if (row >= m_data.size())
		{
			return 0;
		}

		return m_data[row].size();
	}

	const Array<Array<String>>& CSVData::getData() const
	{
		return m_data;
	}

	const Array<String>& CSVData::getRow(const size_t row) const
	{
		return m_data[row];
	}

	const Array<String>& CSVData::operator [](const size_t row) const
	{
		return m_data[row];
	}

	Array<Array<String>>& CSVData::getData()
	{
		return m_data;
	}

	Array<String>& CSVData::getRow(const size_t row)
	{
		return m_data[row];
	}

	Array<String>& CSVData::operator [](const size_t row)
	{
		return m_data[row];
	}

	void CSVData::write(const String& record)
	{
		if (m_onHead)
		{
			m_data.emplace_back();

			m_onHead = false;
		}

		m_data.back().push_back(record);
	}

	void CSVData::newLine()
	{
		if (m_onHead)
		{
			m_data.emplace_back();
		}

		m_onHead = true;
	}

	bool CSVData::save(const FilePathView path, const char32 separator, const char32 quote, const char32 escape) const
	{
		TextWriter writer(path);

		if (!writer)
		{
			return false;
		}

		const String quoteStr(1, quote);
		const String escapedQuote = { escape, quote };

		for (const auto& row : m_data)
		{
			bool isHead = true;

			for (String column : row)
			{
				if (isHead)
				{
					isHead = false;
				}
				else
				{
					writer.write(separator);
				}

				if (column.includes(quote))
				{
					column.replace(quoteStr, escapedQuote);
				}

				if (column.includes(separator))
				{
					column.push_front(quote);

					column.push_back(quote);
				}

				writer.write(column);
			}

			writer.writeUTF8("\r\n");
		}

		return true;
	}
}
