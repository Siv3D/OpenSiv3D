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

		/// @brief INI 形式のデータをファイルからロードして作成します。
		/// @param path ファイルパス
		/// @param encoding テキストエンコーディング
		/// @remark ファイルのすべての内容を読み取り、以降はファイルには一切アクセスしません。
		explicit INI(FilePathView path, const Optional<TextEncoding>& encoding = unspecified);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		explicit INI(Reader&& reader, const Optional<TextEncoding>& encoding = unspecified);

		explicit INI(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding = unspecified);

		/// @brief INI 形式のデータをファイルからロードします。
		/// @param path ファイルパス
		/// @param encoding テキストエンコーディング
		/// @remark ファイルのすべての内容を読み取り、以降はファイルには一切アクセスしません。
		/// @return ロードに成功した場合 true, それ以外の場合は false
		bool load(FilePathView path, const Optional<TextEncoding>& encoding = unspecified);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool load(Reader&& reader, const Optional<TextEncoding>& encoding = unspecified);

		bool load(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding = unspecified);

		/// @brief 保持しているデータを消去します。
		void clear();

		/// @brief データが空であるかを返します。
		/// @return データが空である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief データが空でないかを返します。
		/// @return データが空でない場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief セクションの一覧を返します。
		/// @return セクションの一覧
		[[nodiscard]]
		const Array<INISection>& sections() const noexcept;

		/// @brief 指定したセクションが存在するかを返します。
		/// @param section セクション名
		/// @return 指定したセクションが存在する場合 true, それ以外の場合は false
		[[nodiscard]]
		bool hasSection(SectionView section) const;

		/// @brief 指定したセクションを返します。
		/// @param section セクション名
		/// @return セクション
		[[nodiscard]]
		const INISection& getSection(SectionView section) const;

		/// @brief プロパティが存在するかを返します。
		/// @param section セクション名
		/// @param name プロパティ名
		/// @return プロパティが存在する場合 true, それ以外の場合は false
		[[nodiscard]]
		bool hasValue(SectionView section, NameView name) const;

		/// @brief プロパティの値を返します。
		/// @param section セクション名
		/// @param name プロパティ名
		/// @return プロパティの値
		[[nodiscard]]
		const String& getValue(SectionView section, NameView name) const;

		/// @brief セクションに属さないグローバルプロパティが存在するかを返します。
		/// @param name プロパティ名
		/// @return グローバルプロパティが存在する場合 true, それ以外の場合は false
		[[nodiscard]]
		bool hasGlobalValue(NameView name) const;

		/// @brief セクションに属さないグローバルプロパティの値を返します。
		/// @param name プロパティ名
		/// @return グローバルプロパティの値
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

		/// @brief INI 形式のデータをファイルに保存します。
		/// @param path ファイルパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
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
