//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline INIData::INIData()
	{
	
	}

	inline INIData::INIData(const FilePathView path, const Optional<TextEncoding>& encoding)
	{
		load(path, encoding);
	}

	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>*>
	inline INIData::INIData(Reader&& reader, const Optional<TextEncoding>& encoding)
	{
		load(std::move(reader), encoding);
	}

	inline INIData::INIData(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding)
	{
		load(std::move(reader), encoding);
	}

	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>*>
	inline bool INIData::load(Reader&& reader, const Optional<TextEncoding>& encoding)
	{
		return load(std::make_shared<Reader>(std::move(reader)), encoding);
	}

	inline void INIData::clear()
	{
		m_sections.clear();

		m_keyIndices.clear();
	}

	inline bool INIData::isEmpty() const noexcept
	{
		return m_sections.isEmpty();
	}

	inline INIData::operator bool() const noexcept
	{
		return m_sections.isEmpty();
	}

	inline const Array<INISection>& INIData::sections() const noexcept
	{
		return m_sections;
	}

	inline bool INIData::hasSection(const SectionView section) const
	{
		return m_keyIndices.contains(section);
	}

	inline const INISection& INIData::getSection(const SectionView section) const
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

	inline bool INIData::hasValue(const SectionView section, const NameView name) const
	{
		if (auto itSection = m_keyIndices.find(section);
			itSection != m_keyIndices.end()) // Section が存在
		{
			return itSection->second.second.contains(name);
		}

		return false;
	}

	inline const String& INIData::getValue(const SectionView section, const NameView name) const
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

	inline bool INIData::hasGlobalValue(const NameView name) const
	{
		return hasValue(SectionView{}, name);
	}

	inline const String& INIData::getGlobalValue(const NameView name)
	{
		return getValue(SectionView(), name);
	}

	inline const INIData::Value& INIData::operator [](const Section_Dot_NameView section_dot_name) const
	{
		const auto [section, name] = Split(section_dot_name);

		return getValue(section, name);
	}

	inline INIValueWrapper INIData::operator [](const Section_Dot_NameView section_dot_name)
	{
		const auto [section, name] = Split(section_dot_name);

		return INIValueWrapper(getValue(section, name));
	}

	template <class Type>
	inline Type INIData::get(const SectionView section, const NameView name) const
	{
		if (const auto opt = getOpt<Type>(section, name))
		{
			return opt.value();
		}

		return{};
	}

	template <class Type>
	inline Type INIData::get(const Section_Dot_NameView section_dot_name) const
	{
		const auto [section, name] = Split(section_dot_name);

		return get<Type>(section, name);
	}

	template <class Type, class U>
	inline Type INIData::getOr(const SectionView section, const NameView name, U&& defaultValue) const
	{
		return getOpt<Type>(section, name)
			.value_or(std::forward<U>(defaultValue));
	}

	template <class Type, class U>
	inline Type INIData::getOr(const Section_Dot_NameView section_dot_name, U&& defaultValue) const
	{
		const auto[section, name] = Split(section_dot_name);

		return getOr<Type>(section, name, std::forward<U>(defaultValue));
	}

	template <class Type>
	inline Optional<Type> INIData::getOpt(const SectionView section, const NameView name) const
	{
		if (const auto value = getValueOpt(section, name))
		{
			return ParseOpt<Type>(value.value());
		}

		return none;
	}

	template <class Type>
	inline Optional<Type> INIData::getOpt(const Section_Dot_NameView section_dot_name) const
	{
		const auto [section, name] = Split(section_dot_name);

		return getOpt<Type>(section, name);
	}

	template <class Type>
	void INIData::write(const SectionView section, const NameView name, const Type& value)
	{
		write(section, name, Format(value));
	}

	template <class Type>
	void INIData::writeGlobal(const NameView name, const Type& value)
	{
		write(SectionView{}, name, value);
	}

	inline constexpr std::pair<INIData::SectionView, INIData::NameView> INIData::Split(const Section_Dot_NameView section_dot_name)
	{
		const size_t dot = section_dot_name.indexOf(U'.');

		if (dot == String::npos)
		{
			return{ SectionView(), section_dot_name };
		}
		else
		{
			return{
				SectionView(section_dot_name.data(), dot),
				NameView(section_dot_name.data() + dot + 1, (section_dot_name.size() - dot - 1))
			};
		}
	}
}
