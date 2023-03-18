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

# include <Siv3D/CSV.hpp>
# include <Siv3D/TextWriter.hpp>
# include <boost/tokenizer.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline std::u32string ToU32String(const StringView view)
		{
			return std::u32string(view.begin(), view.end());
		}
	}

	CSV::CSV(const FilePathView path, const StringView separators, const StringView quotes, const StringView escapes)
	{
		load(path, separators, quotes, escapes);
	}

	CSV::CSV(std::unique_ptr<IReader>&& reader, const StringView separators, const StringView quotes, const StringView escapes)
	{
		load(std::move(reader), separators, quotes, escapes);
	}

	bool CSV::load(const FilePathView path, const StringView separators, const StringView quotes, const StringView escapes)
	{
		TextReader textReader{ path };

		if (not loadFromTextReader(textReader, separators, quotes, escapes))
		{
			clear();

			return false;
		}

		return true;
	}

	bool CSV::load(std::unique_ptr<IReader>&& reader, const StringView separators, const StringView quotes, const StringView escapes)
	{
		TextReader textReader{ std::move(reader) };

		if (not loadFromTextReader(textReader, separators, quotes, escapes))
		{
			clear();

			return false;
		}

		return true;
	}

	void CSV::clear() noexcept
	{
		m_data.clear();

		m_onHead = true;
	}

	bool CSV::isEmpty() const noexcept
	{
		return m_data.isEmpty();
	}

	size_t CSV::rows() const noexcept
	{
		return m_data.size();
	}

	size_t CSV::columns(const size_t row) const noexcept
	{
		if (m_data.size() <= row)
		{
			return 0;
		}

		return m_data[row].size();
	}

	const Array<Array<String>>& CSV::getData() const
	{
		return m_data;
	}

	const Array<String>& CSV::getRow(const size_t row) const
	{
		return m_data[row];
	}

	const Array<String>& CSV::operator [](const size_t row) const
	{
		return m_data[row];
	}

	Array<Array<String>>& CSV::getData()
	{
		return m_data;
	}

	Array<String>& CSV::getRow(const size_t row)
	{
		return m_data[row];
	}

	Array<String>& CSV::operator [](const size_t row)
	{
		return m_data[row];
	}

	void CSV::write(const String& record)
	{
		if (m_onHead)
		{
			m_data.emplace_back();

			m_onHead = false;
		}

		m_data.back().push_back(record);
	}

	void CSV::newLine()
	{
		if (m_onHead)
		{
			m_data.emplace_back();
		}

		m_onHead = true;
	}

	bool CSV::save(const FilePathView path, const char32 separator, const char32 quote, const char32 escape) const
	{
		TextWriter writer{ path };

		if (not writer)
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

				if (column.contains(quote))
				{
					column.replace(quoteStr, escapedQuote);
				}

				if (column.contains(separator))
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

	Optional<String> CSV::getItem(const size_t row, const size_t column) const
	{
		if (not inBounds(row, column))
		{
			return none;
		}

		return m_data[row][column];
	}

	bool CSV::inBounds(const size_t row, const size_t column) const
	{
		return (row < m_data.size()) && (column < m_data[row].size());
	}

	bool CSV::loadFromTextReader(TextReader& reader, const StringView separators, const StringView quotes, const StringView escapes)
	{
		if (not reader)
		{
			return false;
		}

		const boost::escaped_list_separator<char32> separator{ detail::ToU32String(escapes), detail::ToU32String(separators), detail::ToU32String(quotes) };

		String str;

		m_data.clear();

		while (reader.readLine(str))
		{
			try
			{
				const boost::tokenizer<boost::escaped_list_separator<char32>, String::const_iterator, String> tokens{ str, separator };

				m_data.emplace_back(tokens.begin(), tokens.end());
			}
			catch (boost::exception&)
			{
				str.replace(U"\\", U"\\\\");

				const boost::tokenizer<boost::escaped_list_separator<char32>, String::const_iterator, String> tokens{ str, separator };

				m_data.emplace_back(tokens.begin(), tokens.end());
			}
		}

		return true;
	}
}
