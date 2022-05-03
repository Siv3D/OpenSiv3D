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

# pragma once

namespace s3d
{
	inline INI::INI() {}

	inline INI::INI(const FilePathView path, const Optional<TextEncoding>& encoding)
	{
		load(path, encoding);
	}

	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>*>
	inline INI::INI(Reader&& reader, const Optional<TextEncoding>& encoding)
	{
		load(std::move(reader), encoding);
	}

	inline INI::INI(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding)
	{
		load(std::move(reader), encoding);
	}

	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>*>
	inline bool INI::load(Reader&& reader, const Optional<TextEncoding>& encoding)
	{
		return load(std::make_shared<Reader>(std::move(reader)), encoding);
	}

	inline void INI::clear()
	{
		m_sections.clear();

		m_keyIndices.clear();
	}

	inline bool INI::isEmpty() const noexcept
	{
		return m_sections.isEmpty();
	}

	inline INI::operator bool() const noexcept
	{
		return (not m_sections.isEmpty());
	}

	inline const Array<INISection>& INI::sections() const noexcept
	{
		return m_sections;
	}

	inline bool INI::hasSection(const SectionView section) const
	{
		return m_keyIndices.contains(section);
	}

	inline bool INI::hasGlobalValue(const NameView name) const
	{
		return hasValue(SectionView{}, name);
	}

	inline const String& INI::getGlobalValue(const NameView name) const
	{
		return getValue(SectionView{}, name);
	}

	inline const INI::Value& INI::operator [](const Section_Dot_NameView section_dot_name) const
	{
		const auto [section, name] = Split(section_dot_name);

		return getValue(section, name);
	}

	inline INIValueWrapper INI::operator [](const Section_Dot_NameView section_dot_name)
	{
		const auto [section, name] = Split(section_dot_name);

		return INIValueWrapper(getValue(section, name));
	}

	template <class Type>
	inline Type INI::get(const SectionView section, const NameView name) const
	{
		if (const auto opt = getOpt<Type>(section, name))
		{
			return opt.value();
		}

		return{};
	}

	template <class Type>
	inline Type INI::get(const Section_Dot_NameView section_dot_name) const
	{
		const auto [section, name] = Split(section_dot_name);

		return get<Type>(section, name);
	}

	template <class Type, class U>
	inline Type INI::getOr(const SectionView section, const NameView name, U&& defaultValue) const
	{
		return getOpt<Type>(section, name)
			.value_or(std::forward<U>(defaultValue));
	}

	template <class Type, class U>
	inline Type INI::getOr(const Section_Dot_NameView section_dot_name, U&& defaultValue) const
	{
		const auto[section, name] = Split(section_dot_name);

		return getOr<Type>(section, name, std::forward<U>(defaultValue));
	}

	template <class Type>
	inline Optional<Type> INI::getOpt(const SectionView section, const NameView name) const
	{
		if (const auto value = getValueOpt(section, name))
		{
			return ParseOpt<Type>(*value);
		}

		return none;
	}

	template <class Type>
	inline Optional<Type> INI::getOpt(const Section_Dot_NameView section_dot_name) const
	{
		const auto [section, name] = Split(section_dot_name);

		return getOpt<Type>(section, name);
	}

	template <class Type>
	void INI::write(const SectionView section, const NameView name, const Type& value)
	{
		write(section, name, Format(value));
	}

	template <class Type>
	void INI::writeGlobal(const NameView name, const Type& value)
	{
		write(SectionView{}, name, value);
	}

	inline constexpr std::pair<INI::SectionView, INI::NameView> INI::Split(const Section_Dot_NameView section_dot_name)
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
