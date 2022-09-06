//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/INI.hpp>
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

		static void WriteSection(TextWriter& writer, const INI::Section& section)
		{
			writer.writeUTF8("[");
			writer.write(section);
			writer.writeUTF8("]");
			WriteNewLine(writer);
		}

		static void WriteValue(TextWriter& writer, const INI::Name& name, const INI::Value& value)
		{
			writer.write(name);
			writer.writeUTF8(" = ");
			writer.write(value);
			WriteNewLine(writer);
		}
	}

	INI::INI() {}

	INI::INI(const FilePathView path, const Optional<TextEncoding>& encoding)
	{
		load(path, encoding);
	}

	INI::INI(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding)
	{
		load(std::move(reader), encoding);
	}

	bool INI::load(const FilePathView path, const Optional<TextEncoding>& encoding)
	{
		TextReader textReader(path, encoding);

		if (not loadFromTextReader(textReader))
		{
			clear();

			return false;
		}

		return true;
	}

	void INI::clear()
	{
		m_sections.clear();

		m_keyIndices.clear();
	}

	bool INI::load(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding)
	{
		TextReader textReader(std::move(reader), encoding);

		if (not loadFromTextReader(textReader))
		{
			clear();

			return false;
		}

		return true;
	}

	const INISection& INI::getSection(const SectionView section) const
	{
		if (auto it = m_keyIndices.find(section);
			it != m_keyIndices.end())
		{
			return m_sections[it->second.first];
		}
		else
		{
			return m_emptySection;
		}
	}

	bool INI::hasValue(const SectionView section, const NameView name) const
	{
		if (auto itSection = m_keyIndices.find(section);
			itSection != m_keyIndices.end()) // Section が存在
		{
			return itSection->second.second.contains(name);
		}

		return false;
	}

	const String& INI::getValue(const SectionView section, const NameView name) const
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

		return m_emptyValue;
	}

	void INI::addSection(const SectionView section)
	{
		if (hasSection(section))
		{
			return;
		}

		m_sections.push_back(INISection(String{ section }, {}));

		const size_t sectionIndex = m_sections.size() - 1;

		m_keyIndices.emplace(String{ section }, std::pair<size_t, HashTable<Name, size_t>>{ sectionIndex, {}});
	}

	void INI::removeSection(const SectionView section)
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

	void INI::write(const SectionView section, const NameView name, const Value& value)
	{
		getValue(section, name) = value;
	}

	void INI::writeGlobal(const NameView name, const Value& value)
	{
		write(SectionView{}, name, value);
	}

	bool INI::save(const FilePathView path) const
	{
		TextWriter writer{ path };

		if (not writer)
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
			if (not sectionData.section)
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

	bool INI::loadFromTextReader(TextReader& reader)
	{
		if (not reader)
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

	String& INI::getValue(const SectionView section, const NameView name)
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

	Optional<String> INI::getValueOpt(const SectionView section, const NameView name) const
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
