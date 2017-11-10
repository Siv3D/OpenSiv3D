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
# include "Fwd.hpp"
# include "HashTable.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "TextWriter.hpp"

namespace s3d
{
	class INIWriterHelper
	{
	private:

		String & m_ref;

	public:

		explicit INIWriterHelper(String& ref)
			: m_ref(ref) {}

		template <class Type>
		void operator =(const Type& value) &&
		{
			m_ref = Format(value);
		}
	};

	/// <summary>
	/// INI ファイルの書き出し
	/// </summary>
	class INIWriter
	{
	public:

		using Section = String;

		using Name = String;

		using Value = String;

	private:

		struct Key
		{
			Name name;

			Value value;

			Key(const Name& _name, const Value& _value)
				: name(_name)
				, value(_value) {}

			bool operator <(const Key& other) const
			{
				if (const int32 r = name.case_insensitive_compare(other.name))
				{
					return r < 0;
				}

				return name < other.name;
			}
		};

		TextWriter m_writer;

		struct SectionData
		{
			Section sectionName;

			Array<Key> keys;
		};

		Array<SectionData> m_sectionData;

		HashTable<Section, std::pair<size_t, HashTable<Name, size_t>>> m_keyIndices;

		void writeNewLine()
		{
			m_writer.writeUTF8(u8"\r\n");
		}

		void writeSection(const Section& section)
		{
			m_writer.writeUTF8(u8"[");
			m_writer.write(section);
			m_writer.writeUTF8(u8"]");
			writeNewLine();
		}

		void writeValue(const Name& name, const Value& value)
		{
			m_writer.write(name);
			m_writer.writeUTF8(u8" = ");
			m_writer.write(value);
			writeNewLine();
		}

		void flushGlobalSection()
		{
			auto itGlobalSection = m_keyIndices.find(Section());

			if (itGlobalSection == m_keyIndices.end())
			{
				return;
			}

			const size_t sectionIndex = itGlobalSection->second.first;

			for (const auto& key : m_sectionData[sectionIndex].keys)
			{
				writeValue(key.name, key.value);
			}

			writeNewLine();
		}

		void flushNamedSection()
		{
			for (const auto& sectionData : m_sectionData)
			{
				if (!sectionData.sectionName)
				{
					// skip global section
					continue;
				}

				writeSection(sectionData.sectionName);

				for (const auto& key : sectionData.keys)
				{
					writeValue(key.name, key.value);
				}

				writeNewLine();
			}
		}

		void flush()
		{
			flushGlobalSection();

			flushNamedSection();

			clear();
		}

		Value& getValueRef(const Section& section, const Name& name);

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		INIWriter() = default;

		/// <summary>
		/// 書き出し用のファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		INIWriter(const FilePath& path)
			: m_writer(path) {}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~INIWriter()
		{
			close();
		}

		/// <summary>
		/// 書き出し用のファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path)
		{
			close();

			return m_writer.open(path);
		}

		/// <summary>
		/// INI データを書き出し、ファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close()
		{
			if (m_writer)
			{
				flush();
			}

			m_writer.close();
		}

		/// <summary>
		/// 書き出し用ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool isOpened() const
		{
			return m_writer.isOpened();
		}

		/// <summary>
		/// 書き出し用ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// 書き出したデータをすべて削除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void clear()
		{
			m_sectionData.clear();

			m_keyIndices.clear();
		}

		/// <summary>
		/// プロパティを書き込みます。
		/// </summary>
		/// <param name="name">
		/// 値の名前
		/// </param>
		/// <param name="value">
		/// 値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Type>
		void write(const Name& name, const Type& value)
		{
			write(Section(), name, value);
		}

		/// <summary>
		/// プロパティを書き込みます。
		/// </summary>
		/// <param name="section">
		/// セクション
		/// </param>
		/// <param name="name">
		/// 値の名前
		/// </param>
		/// <param name="value">
		/// 値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Type>
		void write(const Section& section, const Name& name, const Type& value)
		{
			getValueRef(section, name) = Format(value);
		}

		/// <summary>
		/// プロパティへの参照を返します。
		/// </summary>
		/// <param name="key">
		/// キー（L"PARAMETER" または L"SECTION.PARAMETER" といった形式）
		/// </param>
		/// <returns>
		/// プロパティへの参照
		/// </returns>
		[[nodiscard]] INIWriterHelper operator[](const String& key)
		{
			const auto sep = key.indexOf(U'.');

			if (sep == String::npos)
			{
				return INIWriterHelper(getValueRef(Section(), key));
			}

			return INIWriterHelper(getValueRef(key.substr(0, sep), key.substr(sep + 1)));
		}

		/// <summary>
		/// オープンしているファイルのパスを示します。
		/// </summary>
		/// <remarks>
		/// クローズしている場合は空の文字列です。
		/// </remarks>
		[[nodiscard]] const FilePath& path() const
		{
			return m_writer.path();
		}
	};
}
