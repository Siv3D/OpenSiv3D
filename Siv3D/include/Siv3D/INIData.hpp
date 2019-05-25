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
# include "HashTable.hpp"
# include "Parse.hpp"

namespace s3d
{
	struct INIKey
	{
		String name;

		String value;

		INIKey() = default;

		INIKey(const String& _name, const String& _value)
			: name(_name)
			, value(_value) {}
	};

	struct INISection
	{
		String section;

		Array<INIKey> keys;

		INISection();

		INISection(const String& _section, const Array<INIKey>& _keys);
	};

	class INIValueWrapper
	{
	private:

		String& m_ref;

	public:

		explicit INIValueWrapper(String& ref)
			: m_ref(ref) {}

		template <class Type>
		void operator =(const Type& value) &&
		{
			m_ref = Format(value);
		}
	};

	class INIData
	{
	public:

		using Section = String;

		using Name = String;

		using Value = String;

	private:

		using SectionIndex = size_t;

		using KeyIndex = size_t;

		Array<INISection> m_sections;

		HashTable<Section, std::pair<SectionIndex, HashTable<Name, KeyIndex>>> m_keyIndices;

		const INISection m_dummySection;

		const Value m_dummyValue;

		String& getValue(const Section& section, const Name& name);

		Optional<String> getValueOpt(const Section& section, const Name& name) const;
		
		bool loadFromTextReader(TextReader& reader);

		static std::pair<Section, Name> Split(const String& section_and_name);

	public:

		INIData();

		explicit INIData(const FilePath& path);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>* = nullptr>
		explicit INIData(Reader&& reader)
		{
			load(std::move(reader));
		}

		explicit INIData(const std::shared_ptr<IReader>& reader);

		bool load(const FilePath& path);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>* = nullptr>
		bool load(Reader&& reader)
		{
			return load(std::make_shared<Reader>(std::move(reader)));
		}

		bool load(const std::shared_ptr<IReader>& reader);

		void clear();

		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] explicit operator bool() const { return isEmpty(); }

		[[nodiscard]] bool hasSection(const Section& section) const;

		[[nodiscard]] bool hasValue(const Section& section, const Name& name) const;

		[[nodiscard]] bool hasGlobalValue(const Name& name) const;

		[[nodiscard]] const Array<INISection>& sections() const;

		[[nodiscard]] const INISection& getSection(const Section& section) const;

		[[nodiscard]] const String& getValue(const Section& section, const Name& name) const;

		[[nodiscard]] const String& getGlobalVaue(const Name& name);

		[[nodiscard]] const Value& operator [](const String& section_and_name) const;

		[[nodiscard]] INIValueWrapper operator [](const String& section_and_name);

		template <class Type>
		[[nodiscard]] Type get(const Section& section, const Name& name) const
		{
			if (const auto opt = getOpt<Type>(section, name))
			{
				return opt.value();
			}

			return Type();
		}

		template <class Type>
		[[nodiscard]] Type get(const String& section_and_name) const
		{
			const auto[section, name] = Split(section_and_name);

			return get<Type>(section, name);
		}

		template <class Type, class U>
		[[nodiscard]] Type getOr(const Section& section, const Name& name, U&& defaultValue) const
		{
			return getOpt<Type>(section, name).value_or(std::forward<U>(defaultValue));
		}

		template <class Type, class U>
		[[nodiscard]] Type getOr(const String& section_and_name, U&& defaultValue) const
		{
			const auto[section, name] = Split(section_and_name);

			return getOpt<Type>(section, name).value_or(std::forward<U>(defaultValue));
		}

		template <class Type>
		[[nodiscard]] Optional<Type> getOpt(const Section& section, const Name& name) const
		{
			if (const auto value = getValueOpt(section, name))
			{
				return ParseOpt<Type>(value.value());
			}

			return none;
		}

		template <class Type>
		[[nodiscard]] Optional<Type> getOpt(const String& section_and_name) const
		{
			const auto[section, name] = Split(section_and_name);

			return getOpt<Type>(section, name);
		}

		void addSection(const Section& section);

		void removeSection(const Section& section);

		void write(const Section& section, const Name& name, const Value& value);

		void writeGlobal(const Name& name, const Value& value);

		template <class Type>
		void write(const Section& section, const Name& name, const Type& value)
		{
			write(section, name, Format(value));
		}

		template <class Type>
		void writeGlobal(const Name& name, const Type& value)
		{
			write(Section(), name, value);
		}

		bool save(const FilePath& path) const;
	};
}
