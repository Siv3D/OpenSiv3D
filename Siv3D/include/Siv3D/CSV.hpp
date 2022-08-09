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
# include "Optional.hpp"
# include "Parse.hpp"
# include "IReader.hpp"
# include "TextReader.hpp"

namespace s3d
{
	/// @brief CSV 形式のデータの読み書き
	class CSV
	{
	public:

		SIV3D_NODISCARD_CXX20
		CSV() = default;

		SIV3D_NODISCARD_CXX20
		explicit CSV(FilePathView path, StringView separators = U",", StringView quotes = U"\"", StringView escapes = U"\\");

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		explicit CSV(Reader&& reader, StringView separators = U",", StringView quotes = U"\"", StringView escapes = U"\\");

		SIV3D_NODISCARD_CXX20
		explicit CSV(std::unique_ptr<IReader>&& reader, StringView separators = U",", StringView quotes = U"\"", StringView escapes = U"\\");

		bool load(FilePathView path, StringView separators = U",", StringView quotes = U"\"", StringView escapes = U"\\");

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool load(Reader&& reader, StringView separators = U",", StringView quotes = U"\"", StringView escapes = U"\\");

		bool load(std::unique_ptr<IReader>&& reader, StringView separators = U",", StringView quotes = U"\"", StringView escapes = U"\\");

		void clear() noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief 行数を返します。
		/// @return 行数
		[[nodiscard]]
		size_t rows() const noexcept;

		/// @brief 指定した行の列数を返します。
		/// @param row 行
		/// @return 指定した行の列数
		[[nodiscard]]
		size_t columns(size_t row) const noexcept;

		/// @brief 指定した位置の値を読み取ります。
		/// @tparam Type 読み取る値の型
		/// @param row 行
		/// @param column 列
		/// @return 読み取った値
		template <class Type = String>
		[[nodiscard]]
		Type get(size_t row, size_t column) const;

		/// @brief 指定した位置の値を読み取ります。失敗した場合は defaultValue を返します。
		/// @tparam Type 読み取る値の型
		/// @tparam U デフォルトの値の型
		/// @param row 行
		/// @param column 列
		/// @param defaultValue デフォルトの値
		/// @return 読み取った値。失敗した場合はデフォルトの値
		template <class Type, class U>
		[[nodiscard]]
		Type getOr(size_t row, size_t column, U&& defaultValue) const;

		/// @brief 指定した位置の値を読み取ります。失敗した場合は none を返します。
		/// @tparam Type 読み取る値の型
		/// @param row 行
		/// @param column 列
		/// @return 読み取った値。失敗した場合は none
		template <class Type>
		[[nodiscard]]
		Optional<Type> getOpt(size_t row, size_t column) const;

		[[nodiscard]]
		const Array<Array<String>>& getData() const;

		[[nodiscard]]
		const Array<String>& getRow(size_t row) const;

		[[nodiscard]]
		const Array<String>& operator [](size_t row) const;

		[[nodiscard]]
		Array<Array<String>>& getData();

		[[nodiscard]]
		Array<String>& getRow(size_t row);

		[[nodiscard]]
		Array<String>& operator [](size_t row);

		void write(const String& record);

		template <class Type>
		void write(const Type& value);

		template <class ... Args>
		void write(const Args& ... records);

		template <class ... Args>
		void writeRow(const Args& ... records);

		void newLine();

		/// @brief CSV データをファイルに保存します。
		/// @param path ファイルパス
		/// @param separator 要素のセパレータ
		/// @param quote クオーテーション記号
		/// @param escape エスケープ記号
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(FilePathView path, char32 separator = U',', char32 quote = U'\"', char32 escape = U'\\') const;

	private:

		Array<Array<String>> m_data;

		bool m_onHead = true;

		Optional<String> getItem(size_t row, size_t column) const;

		bool inBounds(size_t row, size_t column) const;

		bool loadFromTextReader(TextReader& reader, StringView separators, StringView quotes, StringView escapes);

		void _write();

		template <class Type, class ... Args>
		void _write(const Type& record, const Args& ... records);
	};
}

# include "detail/CSV.ipp"
