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

# include <Siv3D/INIWriter.hpp>

namespace s3d
{
	INIWriter::Value& INIWriter::getValueRef(const Section& section, const Name& name)
	{
		auto itSection = m_keyIndices.find(section);

		if (itSection != m_keyIndices.end()) // Section が存在
		{		
			const size_t sectionIndex = itSection->second.first;

			auto itKey = itSection->second.second.find(name);

			if (itKey != itSection->second.second.end()) // Key が存在
			{	
				const size_t keyIndex = itKey->second;

				return m_sectionData[sectionIndex].keys[keyIndex].value;
			}
			else // Key が存在しない
			{	
				m_sectionData[sectionIndex].keys.emplace_back(name, String());

				const size_t keyIndex = m_sectionData[sectionIndex].keys.size() - 1;

				itSection.value().second.emplace(name, keyIndex);

				return m_sectionData[sectionIndex].keys[keyIndex].value;
			}
		}
		else // Section が存在しない
		{
			

			m_sectionData.emplace_back(SectionData{ section });

			const size_t sectionIndex = m_sectionData.size() - 1;

			m_sectionData.back().keys.emplace_back(name, String());

			const size_t keyIndex = 0;

			m_keyIndices.emplace(section, std::pair<size_t, HashTable<Name, size_t>>{ sectionIndex, { { name, keyIndex} }});

			return m_sectionData[sectionIndex].keys[keyIndex].value;
		}
	}
}
