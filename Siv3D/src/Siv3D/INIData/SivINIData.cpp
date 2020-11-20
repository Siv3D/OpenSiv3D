//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/INIData.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/TextWriter.hpp>

namespace s3d
{
	namespace detail
	{
		static void WriteNewLine(TextWriter& writer)
		{
			writer.writeUTF8("\r\n");
		}

		static void WriteSection(TextWriter& writer, const INIData::Section& section)
		{
			writer.writeUTF8("[");
			writer.write(section);
			writer.writeUTF8("]");
			WriteNewLine(writer);
		}

		static void WriteValue(TextWriter& writer, const INIData::Name& name, const INIData::Value& value)
		{
			writer.write(name);
			writer.writeUTF8(" = ");
			writer.write(value);
			WriteNewLine(writer);
		}
	}

	bool INIData::load(const FilePathView path, const Optional<TextEncoding>& encoding)
	{
		TextReader textReader(path, encoding);

		if (not loadFromTextReader(textReader))
		{
			clear();

			return false;
		}

		return true;
	}

	bool INIData::load(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding)
	{
		TextReader textReader(std::move(reader), encoding);

		if (not loadFromTextReader(textReader))
		{
			clear();

			return false;
		}

		return true;
	}

	void INIData::addSection(const SectionView section)
	{
		if (hasSection(section))
		{
			return;
		}

		m_sections.push_back(INISection(String{ section }, {}));

		const size_t sectionIndex = m_sections.size() - 1;

		m_keyIndices.emplace(String{ section }, std::pair<size_t, HashTable<Name, size_t>>{ sectionIndex, {}});
	}

	void INIData::removeSection(const SectionView section)
	{
		if (auto itSection = m_keyIndices.find(section);
			itSection != m_keyIndices.end())
		{
			const size_t removedSectionIndex = itSection->second.first;

			m_keyIndices.erase(itSection);

			m_sections.remove_at(removedSectionIndex);

			for (auto it = m_keyIndices.begin(); it != m_keyIndices.end(); ++it)
			{
				if (const size_t sectionIndex = it->second.first; sectionIndex > removedSectionIndex)
				{
					--it->second.first;
				}
			}
		}
	}

	void INIData::write(const SectionView section, const NameView name, const Value& value)
	{
		getValue(section, name) = value;
	}

	void INIData::writeGlobal(const NameView name, const Value& value)
	{
		write(SectionView{}, name, value);
	}

	bool INIData::save(const FilePathView path) const
	{
		TextWriter writer(path);

		if (!writer)
		{
			return false;
		}

		if (auto itGlobalSection = m_keyIndices.find(SectionView{});
			itGlobalSection != m_keyIndices.end())
		{
			const size_t sectionIndex = itGlobalSection->second.first;

			for (const auto& key : m_sections[sectionIndex].keys)
			{
				detail::WriteValue(writer, key.name, key.value);
			}

			detail::WriteNewLine(writer);
		}

		for (const auto& sectionData : m_sections)
		{
			if (!sectionData.section)
			{
				// skip global section
				continue;
			}

			detail::WriteSection(writer, sectionData.section);

			for (const auto& key : sectionData.keys)
			{
				detail::WriteValue(writer, key.name, key.value);
			}

			detail::WriteNewLine(writer);
		}

		return true;
	}

	bool INIData::loadFromTextReader(TextReader& reader)
	{
		if (!reader)
		{
			return false;
		}

		const char32 semicolon = U';';
		const char32 hash = U'#';
		const char32 lbracket = U'[';
		const char32 rbracket = U']';

		String currentSection;
		String line;

		for (size_t currentLine = 1; reader.readLine(line); ++currentLine)
		{
			line.trim();

			if (line.isEmpty())
			{
				continue;
			}

			// Comment
			if ((line[0] == semicolon)
				|| (line[0] == hash))
			{
				continue;
			}

			if (line[0] == lbracket)
			{
				const size_t end = line.indexOf(rbracket);

				if (end == String::npos)
				{
					// error: unmatched '['
					return false;
				}

				const Section section = line.substr(1, end - 1).trim();

				if (auto itSection = m_keyIndices.find(section); itSection == m_keyIndices.end())
				{
					addSection(section);

					currentSection = section;
				}
				else
				{
					// duplicate section name
					return false;
				}
			}
			else
			{
				const size_t eqpos = line.indexOf(U'=');

				if (eqpos == String::npos)
				{
					// error: '=' character not found in line
					return false;
				}

				if (eqpos == 0)
				{
					// error: key expected
					return false;
				}

				// add global section
				if (currentSection.isEmpty() && m_sections.isEmpty())
				{
					addSection(SectionView{});
				}

				auto itSection = m_keyIndices.find(currentSection);

				assert(itSection != m_keyIndices.end());

				Name name = line.substr(0, eqpos).trim();

				if (auto itKey = itSection->second.second.find(name);
					itKey != itSection->second.second.end())
				{
					// error: duplicate key name
					return false;
				}

				auto& keys = m_sections[itSection->second.first].keys;

				itSection->second.second.emplace(name, keys.size());

				keys.emplace_back(std::move(name), line.substr(eqpos + 1).trim());
			}
		}

		return true;
	}

	String& INIData::getValue(const SectionView section, const NameView name)
	{
		auto itSection = m_keyIndices.find(section);

		if (itSection != m_keyIndices.end()) // Section が存在
		{
			auto& value = itSection->second.second;
			const size_t sectionIndex = itSection->second.first;

			auto itKey = value.find(name);

			if (itKey != value.end()) // Key が存在
			{
				const size_t keyIndex = itKey->second;

				return m_sections[sectionIndex].keys[keyIndex].value;
			}
			else // Key が存在しない
			{
				const String name_(name);

				m_sections[sectionIndex].keys.emplace_back(name_, String{});

				const size_t keyIndex = m_sections[sectionIndex].keys.size() - 1;

				value.emplace(name_, keyIndex);

				return m_sections[sectionIndex].keys[keyIndex].value;
			}
		}
		else // Section が存在しない
		{
			m_sections.emplace_back(INISection(String{ section }, {}));

			const size_t sectionIndex = m_sections.size() - 1;

			const String name_(name);

			m_sections.back().keys.emplace_back(name_, String{});

			const size_t keyIndex = 0;

			m_keyIndices.emplace(section, std::pair<size_t, HashTable<Name, size_t>>{ sectionIndex, { { name_, keyIndex } }});

			return m_sections[sectionIndex].keys[keyIndex].value;
		}
	}

	Optional<String> INIData::getValueOpt(const SectionView section, const NameView name) const
	{
		if (auto itSection = m_keyIndices.find(section);
			itSection != m_keyIndices.end()) // Section が存在
		{
			const auto& value = itSection->second;
			const size_t sectionIndex = value.first;

			if (auto itKey = value.second.find(name);
				itKey != value.second.end()) // Key が存在
			{
				const size_t keyIndex = itKey->second;

				return m_sections[sectionIndex].keys[keyIndex].value;
			}
		}

		return none;
	}
}
