//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/INIReader.hpp>
# include "CINIReader.hpp"

namespace s3d
{
	static bool operator <(const INIKey&a, const INIKey& b)
	{
		const auto c = a.section.compare(b.section);

		if (c == -1)
		{
			return true;
		}
		else if (c == 1)
		{
			return false;
		}

		return a.name < b.name;
	}

	INIReader::INIReader()
		: pImpl(std::make_shared<CINIReader>())
	{

	}

	INIReader::~INIReader()
	{

	}

	bool INIReader::open(const FilePath& path, bool trackFile)
	{
		return pImpl->open(path, trackFile);
	}

	bool INIReader::open(const std::shared_ptr<IReader>& reader)
	{
		return pImpl->open(reader);
	}

	void INIReader::close()
	{
		pImpl->close();
	}

	bool INIReader::isOpened() const
	{
		return pImpl->isOpened();
	}

	const FilePath& INIReader::path() const
	{
		return pImpl->path();
	}

	CharacterEncoding INIReader::encoding() const
	{
		return pImpl->encoding();
	}

	const Array<INIKey>& INIReader::keys() const
	{
		return pImpl->getKeys();
	}

	const Array<INIReader::Section>& INIReader::sections() const
	{
		return pImpl->getSections();
	}

	bool INIReader::hasSection(const Section& section) const
	{
		const auto& sections = pImpl->getSections();

		return std::binary_search(sections.begin(), sections.end(), section);
	}

	IteratorRange<Array<INIKey>::const_iterator> INIReader::getSectionKeys(const Section& section) const
	{
		const auto& keys = pImpl->getKeys();
		auto first = keys.begin(), last = keys.end();
		auto count = std::distance(first, last);

		decltype(first) it;
		decltype(count) step;

		// Binary search
		while (count > 0)
		{
			it = first;
			step = count / 2;
			std::advance(it, step);

			if (it->section < section)
			{
				first = ++it;
				count -= step + 1;
			}
			else
			{
				count = step;
			}
		}

		auto itEnd = first;

		while (itEnd != last)
		{
			if (itEnd->section == section)
			{
				++itEnd;
			}
			else
			{
				break;
			}
		}

		return IteratorRange<Array<INIKey>::const_iterator>(first, itEnd);
	}

	bool INIReader::hasKey(const INIReader::Section& section, const INIReader::Name& name) const
	{
		const auto& keys = pImpl->getKeys();

		return std::binary_search(keys.begin(), keys.end(), INIKey{ section, name, String() });
	}

	std::pair<INIReader::Section, INIReader::Name> INIReader::Split(const String& section_and_name)
	{
		const size_t dot = section_and_name.indexOf(L'.');

		if (dot == String::npos)
		{
			return{ String(), section_and_name };
		}
		else
		{
			return{ String(section_and_name.begin(), section_and_name.begin() + dot),
				String(section_and_name.begin() + dot + 1, section_and_name.end()) };
		}
	}

	Optional<String> INIReader::getValue(const INIReader::Section& section, const INIReader::Name& name) const
	{
		const auto& keys = pImpl->getKeys();

		const auto it = std::lower_bound(keys.begin(), keys.end(), INIKey{ section, name, String() });

		if (it == keys.end() || (it->section != section || it->name != name))
		{
			return none;
		}

		return it->value;
	}
}
