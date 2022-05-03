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
# include "Common.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "HashTable.hpp"
# include "Optional.hpp"
# include "IReader.hpp"
# include "TextEncoding.hpp"
# include "Unspecified.hpp"
# include "Format.hpp"
# include "Parse.hpp"

namespace s3d
{
	class TextReader;

	struct INIKey
	{
		String name;

		String value;

		INIKey() = default;

		INIKey(String _name, String _value)
			: name(std::move(_name))
			, value(std::move(_value)) {}
	};

	struct INISection
	{
		String section;

		Array<INIKey> keys;

		INISection() = default;

		INISection(String _section, Array<INIKey> _keys)
			: section(std::move(_section))
			, keys(std::move(_keys)) {}
	};

	class INIValueWrapper
	{
	public:

		explicit INIValueWrapper(String& ref)
			: m_ref(ref) {}

		template <class Type>
		void operator =(const Type& value)&&
		{
			m_ref = Format(value);
		}

		operator StringView() const noexcept
		{
			return m_ref;
		}

	private:

		String& m_ref;
	};

	/// @brief INI 形式のデータの読み書き
	class INI
	{
	public:

		using Section = String;
		using SectionView = StringView;

		using Name = String;
		using NameView = StringView;

		using Section_Dot_Name = String;
		using Section_Dot_NameView = StringView;

		using Value = String;
		using SectionIndex = size_t;
		using KeyIndex = size_t;

		INI();

		explicit INI(FilePathView path, const Optional<TextEncoding>& encoding = unspecified);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		explicit INI(Reader&& reader, const Optional<TextEncoding>& encoding = unspecified);

		explicit INI(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding = unspecified);

		bool load(FilePathView path, const Optional<TextEncoding>& encoding = unspecified);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool load(Reader&& reader, const Optional<TextEncoding>& encoding = unspecified);

		bool load(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding = unspecified);

		void clear();

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		const Array<INISection>& sections() const noexcept;

		[[nodiscard]]
		bool hasSection(SectionView section) const;

		[[nodiscard]]
		const INISection& getSection(SectionView section) const;

		[[nodiscard]]
		bool hasValue(SectionView section, NameView name) const;

		[[nodiscard]]
		const String& getValue(SectionView section, NameView name) const;

		[[nodiscard]]
		bool hasGlobalValue(NameView name) const;

		[[nodiscard]]
		const String& getGlobalValue(NameView name) const;

		[[nodiscard]]
		const Value& operator [](Section_Dot_NameView section_dot_name) const;

		[[nodiscard]]
		INIValueWrapper operator [](Section_Dot_NameView section_dot_name);

		template <class Type>
		[[nodiscard]]
		Type get(SectionView section, NameView name) const;

		template <class Type>
		[[nodiscard]]
		Type get(Section_Dot_NameView section_dot_name) const;

		template <class Type, class U>
		[[nodiscard]]
		Type getOr(SectionView section, NameView name, U&& defaultValue) const;

		template <class Type, class U>
		[[nodiscard]]
		Type getOr(Section_Dot_NameView section_dot_name, U&& defaultValue) const;

		template <class Type>
		[[nodiscard]]
		Optional<Type> getOpt(SectionView section, NameView name) const;

		template <class Type>
		[[nodiscard]]
		Optional<Type> getOpt(Section_Dot_NameView section_dot_name) const;

		void addSection(SectionView section);

		void removeSection(SectionView section);

		void write(SectionView section, NameView name, const Value& value);

		template <class Type>
		void write(SectionView section, NameView name, const Type& value);

		void writeGlobal(NameView name, const Value& value);

		template <class Type>
		void writeGlobal(NameView name, const Type& value);

		bool save(FilePathView path) const;

	private:

		Array<INISection> m_sections;

		HashTable<Section, std::pair<SectionIndex, HashTable<Name, KeyIndex>>> m_keyIndices;

		const INISection m_emptySection;

		const Value m_emptyValue;

		static constexpr std::pair<SectionView, NameView> Split(Section_Dot_NameView section_dot_name);

		bool loadFromTextReader(TextReader& reader);

		String& getValue(SectionView section, NameView name);

		Optional<String> getValueOpt(SectionView section, NameView name) const;
	};
}

# include "detail/INI.ipp"
