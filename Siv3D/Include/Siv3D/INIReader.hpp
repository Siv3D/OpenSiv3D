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

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "Parse.hpp"
# include "IteratorRange.hpp"

namespace s3d
{
	struct INIKey
	{
		String section;

		String name;

		String value;
	};

	class INIReader
	{
	public:

		using Section = String;

		using Name = String;

	private:

		class CINIReader;

		std::shared_ptr<CINIReader> pImpl;

		static std::pair<Section, Name> Split(const String& section_and_name);

		Optional<String> getValue(const Section& section, const Name& name) const;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		INIReader();

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		explicit INIReader(const FilePath& path, bool trackFile = true)
			: INIReader()
		{
			open(path, trackFile);
		}

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		template <class Reader, std::enable_if_t<std::is_base_of<IReader, Reader>::value>* = nullptr>
		explicit INIReader(Reader&& reader)
			: INIReader()
		{
			open(std::move(reader));
		}

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		explicit INIReader(const std::shared_ptr<IReader>& reader)
			: INIReader()
		{
			open(reader);
		}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~INIReader();

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path, bool trackFile = true);

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		template <class Reader, std::enable_if_t<std::is_base_of<IReader, Reader>::value>* = nullptr>
		bool open(Reader&& reader)
		{
			return open(std::make_shared<Reader>(std::move(reader)));
		}

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const std::shared_ptr<IReader>& reader);

		/// <summary>
		/// INI ファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close();

		/// <summary>
		/// INI ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const;

		/// <summary>
		/// INI ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// INI ファイルの内容が変更されたかを返します。
		/// </summary>
		/// <remarks>
		/// ファイルの内容が変更された場合、reload() を呼ぶまで true を返します。
		/// </remarks>
		/// <returns>
		/// INI ファイルの内容が変更された場合 true, それ以外の場合は false
		/// </returns>
		bool hasChanged() const;

		/// <summary>
		/// INI ファイルが変更された場合、データの内容を更新します。
		/// </summary>
		/// <returns>
		/// 更新に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool reload();

		/// <summary>
		/// INI ファイルのパスを返します。
		/// </summary>
		const FilePath& path() const;

		CharacterEncoding encoding() const;

		Array<INIKey>::const_iterator begin() const
		{
			return keys().begin();
		}

		Array<INIKey>::const_iterator end() const
		{
			return keys().end();
		}

		const Array<INIKey>& keys() const;

		const Array<Section>& sections() const;

		bool hasSection(const Section& section) const;

		IteratorRange<Array<INIKey>::const_iterator> getSectionKeys(const Section& section) const;

		IteratorRange<Array<INIKey>::const_iterator> operator [](const Section& section) const
		{
			return getSectionKeys(section);
		}

		bool hasKey(const Section& section, const Name& name) const;

		bool hasKey(const String& section_and_name) const
		{
			const auto sn = Split(section_and_name);

			return hasKey(sn.first, sn.second);
		}

		template <class Type>
		Type get(const Section& section, const Name& name) const
		{
			if (const auto opt = getOpt<Type>(section, name))
			{
				return opt.value();
			}

			return Type();
		}

		template <class Type>
		Type get(const String& section_and_name) const
		{
			const auto sn = Split(section_and_name);

			return get<Type>(sn.first, sn.second);
		}

		template <class Type>
		Type getOr(const Section& section, const Name& name, Type&& defaultValue) const
		{
			return getOpt<Type>(section, name).value_or(std::forward<Type>(defaultValue));
		}

		template <class Type>
		Type getOr(const String& section_and_name, Type&& defaultValue) const
		{
			const auto sn = Split(section_and_name);

			return getOr<Type>(sn.first, sn.second, std::forward<Type>(defaultValue));
		}

		template <class Type>
		Optional<Type> getOpt(const Section& section, const Name& name) const
		{
			if (const auto value = getValue(section, name))
			{
				return ParseOpt<Type>(value.value());
			}

			return none;
		}

		template <class Type>
		Optional<Type> getOpt(const String& section_and_name) const
		{
			const auto sn = Split(section_and_name);

			return getOpt<Type>(sn.first, sn.second);
		}
	};
}
