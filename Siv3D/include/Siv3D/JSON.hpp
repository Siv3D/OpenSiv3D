﻿//-----------------------------------------------
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
# include "Array.hpp"
# include "Optional.hpp"
# include "String.hpp"
# include "IReader.hpp"
# include "Blob.hpp"
# include "PredefinedYesNo.hpp"
# include "detail/JSONFwd.ipp"

# include <variant>

namespace s3d
{
	enum class JSONValueType : uint8
	{
		Empty,

		Null,

		Object,

		Array,

		String,

		Number,

		Bool,
	};

	class JSONIterator
	{
	public:

		friend JSONConstIterator;

		using value_type = JSONItem;

		using difference_type = ptrdiff_t;

		using iterator_concept = std::bidirectional_iterator_tag;

		SIV3D_NODISCARD_CXX20
		JSONIterator() = default;

		SIV3D_NODISCARD_CXX20
		JSONIterator(const JSONIterator&);

		SIV3D_NODISCARD_CXX20
		explicit JSONIterator(JSON* parent, difference_type index, const detail::JSONIteratorDetail&);

		JSONIterator& operator =(const JSONIterator& rhs);

		JSONIterator& operator ++();

		JSONIterator operator ++(int);

		JSONIterator& operator --();

		JSONIterator operator --(int);

		[[nodiscard]]
		JSONIterator operator +(difference_type index) const;

		[[nodiscard]]
		JSONItem operator *() const;

		[[nodiscard]]
		String key() const;

		[[nodiscard]]
		JSON value() const;

		[[nodiscard]]
		bool operator ==(const JSONIterator& other) const noexcept;

		[[nodiscard]]
		bool operator !=(const JSONIterator& other) const noexcept;

	private:

		JSON* m_parent = nullptr;

		difference_type m_index = -1;

		std::shared_ptr<detail::JSONIteratorDetail> m_detail;
	};

	class JSONConstIterator
	{
	public:

		using value_type = const JSONItem;

		using difference_type = ptrdiff_t;

		using iterator_concept = std::bidirectional_iterator_tag;

		SIV3D_NODISCARD_CXX20
		JSONConstIterator() = default;

		SIV3D_NODISCARD_CXX20
		JSONConstIterator(const JSONIterator&);

		SIV3D_NODISCARD_CXX20
		JSONConstIterator(const JSONConstIterator&);

		SIV3D_NODISCARD_CXX20
		explicit JSONConstIterator(const JSON* parent, difference_type index, const detail::JSONConstIteratorDetail&);

		JSONConstIterator& operator =(const JSONIterator& rhs);

		JSONConstIterator& operator =(const JSONConstIterator& rhs);

		JSONConstIterator& operator ++();

		JSONConstIterator operator ++(int);

		JSONConstIterator& operator --();

		JSONConstIterator operator --(int);

		[[nodiscard]]
		JSONConstIterator operator +(difference_type index) const;

		[[nodiscard]]
		const JSONItem operator *() const;

		[[nodiscard]]
		String key() const;

		[[nodiscard]]
		const JSON value() const;

		[[nodiscard]]
		bool operator ==(const JSONConstIterator& other) const noexcept;

		[[nodiscard]]
		bool operator !=(const JSONConstIterator& other) const noexcept;

	private:

		const JSON* m_parent = nullptr;

		difference_type m_index = -1;

		std::shared_ptr<detail::JSONConstIteratorDetail> m_detail;
	};

	class JSONIterationProxy
	{
	public:

		using value_type = JSON;

		using difference_type = ptrdiff_t;

		using iterator_concept = std::input_iterator_tag;

		SIV3D_NODISCARD_CXX20
		JSONIterationProxy() = delete;

		SIV3D_NODISCARD_CXX20
		JSONIterationProxy(const JSONIterationProxy&);

		SIV3D_NODISCARD_CXX20
		explicit JSONIterationProxy(const detail::JSONIterationProxyDetail&);

		JSONIterationProxy& operator =(const JSONIterationProxy& rhs);

		JSONIterationProxy& operator ++();

		JSONIterationProxy operator ++(int);

		[[nodiscard]]
		JSONIterationProxy operator +(size_t index) const;

		[[nodiscard]]
		JSON operator *() const;

		[[nodiscard]]
		bool operator ==(const JSONIterationProxy& other) const noexcept;

		[[nodiscard]]
		bool operator !=(const JSONIterationProxy& other) const noexcept;

	private:

		std::shared_ptr<detail::JSONIterationProxyDetail> m_detail;
	};

	class JSONArrayView
	{
	public:

		JSONArrayView(JSONIterationProxy begin, JSONIterationProxy end);

		[[nodiscard]]
		JSONIterationProxy begin() const;

		[[nodiscard]]
		JSONIterationProxy end() const;

		[[nodiscard]]
		JSON operator [](size_t index) const;

	private:

		JSONIterationProxy m_begin;

		JSONIterationProxy m_end;
	};

	/// @brief JSON 形式のデータの読み書き
	class JSON
	{
	public:

		using iterator = JSONIterator;

		using const_iterator = JSONConstIterator;

		SIV3D_NODISCARD_CXX20
		JSON();

		SIV3D_NODISCARD_CXX20
		JSON(std::shared_ptr<detail::JSONDetail>&& detail);

		SIV3D_NODISCARD_CXX20
		JSON(std::nullptr_t);

		SIV3D_NODISCARD_CXX20
		JSON(const JSON&) = default;

		SIV3D_NODISCARD_CXX20
		JSON(JSON&&) = default;

		SIV3D_NODISCARD_CXX20
		JSON(const std::initializer_list<std::pair<String, JSON>>& list);

		SIV3D_NODISCARD_CXX20
		JSON(const Array<JSON>& array);

		template <class Type, std::enable_if_t<!std::is_same_v<std::decay_t<Type>, JSON> && std::is_constructible_v<JSON, Type>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		JSON(const Array<Type>& arr);

		template <class Type, std::enable_if_t<std::is_constructible_v<JSON, Type>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		JSON(const std::initializer_list<Type>& list);

		SIV3D_NODISCARD_CXX20
		JSON(StringView value);

		template <class StringViewish, std::enable_if_t<std::is_constructible_v<StringView, StringViewish>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		JSON(const StringViewish& value);

		SIV3D_NODISCARD_CXX20
		JSON(int64 value);

		SIV3D_NODISCARD_CXX20
		JSON(uint64 value);

		SIV3D_NODISCARD_CXX20
		JSON(double value);

		SIV3D_NODISCARD_CXX20
		JSON(bool value);

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		SIV3D_NODISCARD_CXX20
		JSON(SignedInt value);

		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		SIV3D_NODISCARD_CXX20
		JSON(UnsignedInt value);

		SIV3D_CONCEPT_FLOATING_POINT
		SIV3D_NODISCARD_CXX20
		JSON(Float value);

		template <class Type, std::enable_if_t<!std::is_constructible_v<StringView, Type> && !std::is_arithmetic_v<Type>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		JSON(const Type& value);

		// JSONValueType::Null
		JSON& operator =(std::nullptr_t);

		// JSONValueType::Object
		JSON& operator =(const JSON& value);

		// JSONValueType::Object
		JSON& operator =(const std::initializer_list<std::pair<String, JSON>>& list);

		// JSONValueType::Array
		JSON& operator =(const Array<JSON>& array);

		// JSONValueType::Array
		template <class Type, std::enable_if_t<!std::is_same_v<std::decay_t<Type>, JSON>&& std::is_constructible_v<JSON, Type>>* = nullptr>
		JSON& operator =(const Array<Type>& arr);

		// JSONValueType::Array
		template <class Type, std::enable_if_t<std::is_constructible_v<JSON, Type>>* = nullptr>
		JSON& operator =(const std::initializer_list<Type>& list);

		// JSONValueType::String
		JSON& operator =(StringView value);

		// JSONValueType::String
		template <class StringViewish, std::enable_if_t<std::is_constructible_v<StringView, StringViewish>>* = nullptr>
		JSON& operator =(const StringViewish& value);

		// JSONValueType::Number
		JSON& operator =(int64 value);

		// JSONValueType::Number
		JSON& operator =(uint64 value);

		// JSONValueType::Number
		JSON& operator =(double value);

		// JSONValueType::Bool
		JSON& operator =(bool value);

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		JSON& operator =(SignedInt value);

		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		JSON& operator =(UnsignedInt value);

		SIV3D_CONCEPT_FLOATING_POINT
		JSON& operator =(Float value);

		template <class Type,
			std::enable_if_t<!std::is_constructible_v<StringView, Type> && !std::is_arithmetic_v<Type>>* = nullptr,
			class = decltype(Formatter(std::declval<FormatData&>(), std::declval<Type>()))>
		JSON& operator =(const Type& value);

		[[nodiscard]]
		bool operator ==(const JSON& other) const;

		[[nodiscard]]
		bool operator !=(const JSON& other) const;

		// Load や Parse に失敗したときのみ true
		[[nodiscard]]
		bool isEmpty() const;

		[[nodiscard]]
		explicit operator bool() const;

		[[nodiscard]]
		bool isNull() const;

		[[nodiscard]]
		bool isBool() const;

		[[nodiscard]]
		bool isNumber() const;

		[[nodiscard]]
		bool isInteger() const;

		[[nodiscard]]
		bool isUnsigned() const;

		[[nodiscard]]
		bool isFloat() const;

		[[nodiscard]]
		bool isString() const;

		[[nodiscard]]
		bool isArray() const;

		[[nodiscard]]
		bool isObject() const;

		[[nodiscard]]
		JSONValueType getType() const;

		[[nodiscard]]
		bool hasElement(StringView name) const;

		[[nodiscard]]
		String getString() const;

		template <class Type>
		[[nodiscard]]
		Type get() const;

		template <class Type, class U>
		[[nodiscard]]
		Type getOr(U&& defaultValue) const;

		template <class Type>
		[[nodiscard]]
		Optional<Type> getOpt() const;

		JSON operator [](StringView name);

		const JSON operator [](StringView name) const;

		JSON operator [](size_t index);

		const JSON operator [](size_t index) const;

		JSON access(StringView jsonPointer);

		const JSON access(StringView jsonPointer) const;

		void push_back(const JSON& value);

		void clear() const;

		void erase(StringView name);

		void erase(size_t index);

		// [Siv3D ToDo]
		// void erase(???); 他のオーバーロード

		// [Siv3D ToDo]
		//[[nodiscard]] iterator find(const StringView name)

		// [Siv3D ToDo]
		//[[nodiscard]] const_iterator find(const StringView name)

		[[nodiscard]]
		iterator begin();

		[[nodiscard]]
		const_iterator begin() const;

		[[nodiscard]]
		iterator end();

		[[nodiscard]]
		const_iterator end() const;

		[[nodiscard]]
		JSONArrayView arrayView() const;

		[[nodiscard]]
		size_t size() const;

		/// @brief JSON データを文字列にフォーマットした結果を返します。
		/// @param space インデントの文字
		/// @param spaceCount インデントの文字数
		/// @return フォーマットした結果
		[[nodiscard]]
		String format(char32 space = U' ', size_t spaceCount = 2) const;

		[[nodiscard]]
		String formatMinimum() const;

		[[nodiscard]]
		std::string formatUTF8(char32 space = U' ', size_t spaceCount = 2) const;

		[[nodiscard]]
		std::string formatUTF8Minimum() const;

		/// @brief JSON データをファイルに保存します。
		/// @param path ファイルパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(FilePathView path) const;

		/// @brief JSON データを、不要なスペースを消したコンパクトな形式でファイルに保存します。
		/// @param path ファイルパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool saveMinimum(FilePathView path) const;

		/// @brief BSON 形式にシリアライズした結果を返します。
		/// @return BSON データ
		[[nodiscard]]
		Blob toBSON() const;

		/// @brief CBOR 形式にシリアライズした結果を返します。
		/// @return CBOR データ
		[[nodiscard]]
		Blob toCBOR() const;

		/// @brief MessagePack 形式にシリアライズした結果を返します。
		/// @return MessagePack データ
		[[nodiscard]]
		Blob toMessagePack() const;

		[[nodiscard]]
		static JSON Invalid();

		/// @brief JSON ファイルをパースして JSON オブジェクトを返します。
		/// @param path ファイルパス
		/// @param allowExceptions 例外を発生させるか
		/// @return JSON オブジェクト
		[[nodiscard]]
		static JSON Load(FilePathView path, AllowExceptions allowExceptions = AllowExceptions::No);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>* = nullptr>
		[[nodiscard]]
		static JSON Load(Reader&& reader, AllowExceptions allowExceptions = AllowExceptions::No);

		[[nodiscard]]
		static JSON Load(std::unique_ptr<IReader>&& reader, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief JSON 文字列をパースして JSON オブジェクトを返します。
		/// @param str 文字列
		/// @param allowExceptions 例外を発生させるか
		/// @return JSON オブジェクト
		[[nodiscard]]
		static JSON Parse(StringView str, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief BSON 形式のデータから JSON オブジェクトをデシリアライズします。
		/// @param bson BSON データ
		/// @param allowExceptions 例外を発生させるか
		/// @return JSON オブジェクト
		[[nodiscard]]
		static JSON FromBSON(const Blob& bson, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief CBOR 形式のデータから JSON オブジェクトをデシリアライズします。
		/// @param cbor CBOR データ
		/// @param allowExceptions 例外を発生させるか
		/// @return JSON オブジェクト
		[[nodiscard]]
		static JSON FromCBOR(const Blob& cbor, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief MessagePack 形式のデータから JSON オブジェクトをデシリアライズします。
		/// @param msgpack MessagePack データ
		/// @param allowExceptions 例外を発生させるか
		/// @return JSON オブジェクト
		[[nodiscard]]
		static JSON FromMessagePack(const Blob& msgpack, AllowExceptions allowExceptions = AllowExceptions::No);

		friend void Formatter(FormatData& formatData, const JSON& value);

	private:

		std::shared_ptr<detail::JSONDetail> m_detail;

		bool m_isValid = true;

		struct Invalid_ {};

		JSON(Invalid_);

		SIV3D_CONCEPT_INTEGRAL
		Optional<Int> getOpt_() const;

		SIV3D_CONCEPT_FLOATING_POINT
		Optional<Float> getOpt_() const;

		template <class Type, std::enable_if_t<!std::is_arithmetic_v<Type>>* = nullptr>
		Optional<Type> getOpt_() const;

		Optional<String> getOptString() const;

		Optional<int64> getOptInt64() const;

		Optional<double> getOptDouble() const;

		Optional<bool> getOptBool() const;

		friend JSONSchema;
	};

	struct JSONItem
	{
		String key;

		JSON value;
	};

	struct JSONPointer
	{
		SIV3D_NODISCARD_CXX20
		explicit JSONPointer(const String& jsonPointer = U"");

		SIV3D_NODISCARD_CXX20
		JSONPointer(const JSONPointer& other);

		SIV3D_NODISCARD_CXX20
		JSONPointer(JSONPointer&&) = default;

		SIV3D_NODISCARD_CXX20
		JSONPointer(std::shared_ptr<detail::JSONPointerDetail>&& detail);

		JSONPointer& operator =(const JSONPointer& other);

		JSONPointer& operator =(JSONPointer&&) = default;

		[[nodiscard]] 
		String format() const;

		// operator != は導出により利用可能
		friend bool operator ==(const JSONPointer& lhs, const JSONPointer& rhs) noexcept;

		JSONPointer& operator /=(const JSONPointer& rhs);

		JSONPointer& operator /=(const String& unescapedToken);
 
		JSONPointer& operator /=(size_t index);

		[[nodiscard]] 
		JSONPointer operator /(const JSONPointer& rhs) const;

		[[nodiscard]] 
		JSONPointer operator /(const String& unescapedToken) const;

		[[nodiscard]] 
		JSONPointer operator /(size_t index) const;

		[[nodiscard]] 
		JSONPointer parent() const;

		[[nodiscard]] 
		String back() const;

		void pop_back();

		void push_back(const String& unescapedToken);

		void push_back(size_t index);

		// pointer が root document を指しているかを返す
		[[nodiscard]] 
		bool isEmpty() const noexcept;

		friend void Formatter(FormatData& formatData, const JSONPointer& value);

		/// @brief ~ -> ~0, / -> ~1 の escape を行う関数
		/// /abc/xyz のような JSONPointer パスを処理するわけではなく、abc や xyz の部分の処理に使用する
		[[nodiscard]] 
		static String Escape(const String& unescapedToken);

		/// @brief ~0 -> ~, ~1 -> / の unescape を行う関数
		/// /abc/xyz のような JSONPointer パスを処理するわけではなく、abc や xyz の部分の処理に使用する
		[[nodiscard]] 
		static String Unescape(const String& escapedToken);

	private:

		std::shared_ptr<detail::JSONPointerDetail> m_detail;
	};

	struct JSONSchema
	{
		struct ErrorDetails
		{
			String      message;
			JSONPointer pointer;
			JSON        instance;

			friend void Formatter(FormatData& formatData, const ErrorDetails& value);
		};

		struct ValidationStatus
		{
			SIV3D_NODISCARD_CXX20
			ValidationStatus(const ValidationStatus&) = default;

			SIV3D_NODISCARD_CXX20
			ValidationStatus(ValidationStatus&&) = default;

			SIV3D_NODISCARD_CXX20
			ValidationStatus(const JSON& json);

			SIV3D_NODISCARD_CXX20
			ValidationStatus(JSON&& json);

			SIV3D_NODISCARD_CXX20
			ValidationStatus(const ErrorDetails& details);

			SIV3D_NODISCARD_CXX20
			ValidationStatus(ErrorDetails&& details);
			
			[[nodiscard]]
			ValidationStatus& operator =(const ValidationStatus&) = default;

			[[nodiscard]]
			ValidationStatus& operator =(ValidationStatus&&) = default;

			[[nodiscard]] 
			bool isOK() const noexcept;

			[[nodiscard]] 
			bool isError() const noexcept;

			/// @brief 正常かどうかを返す
			[[nodiscard]] 
			explicit operator bool() const noexcept;

			[[nodiscard]] 
			JSON& value() & noexcept;

			[[nodiscard]] 
			JSON&& value() && noexcept;

			[[nodiscard]] 
			const JSON& value() const & noexcept;

			[[nodiscard]] 
			const ErrorDetails& error() const noexcept;

			[[nodiscard]] 
			const JSONPointer& pointer() const noexcept;

			[[nodiscard]] 
			const JSON& instance() const noexcept;

			[[nodiscard]] 
			const String& message() const noexcept;

			friend void Formatter(FormatData& formatData, const ValidationStatus& value);

		private:

			std::variant<JSON, ErrorDetails> m_data;

			static inline constexpr size_t OK = 0;

			static inline constexpr size_t Error = 1;
		};

		struct ValidationError final : public Error
		{
			SIV3D_NODISCARD_CXX20
			ValidationError() = default;

			SIV3D_NODISCARD_CXX20
			explicit ValidationError(StringView message, const JSONPointer& pointer, const JSON& instance);

			[[nodiscard]] 
			const JSONPointer& pointer() const noexcept;

			[[nodiscard]] 
			const JSON& instance() const noexcept;

			[[nodiscard]]
			virtual StringView type() const noexcept override;

			friend std::ostream& operator<<(std::ostream& output, const ValidationError& value);

			friend std::wostream& operator<<(std::wostream& output, const ValidationError& value);

			friend std::basic_ostream<char32>& operator<<(std::basic_ostream<char32>& output, const ValidationError& value);

			friend void Formatter(FormatData& formatData, const ValidationError& value);

		private:

			// what の方に message を設定するので m_message は持たない
			JSONPointer m_pointer;
			JSON        m_instance;
		};

		SIV3D_NODISCARD_CXX20
		JSONSchema();

		SIV3D_NODISCARD_CXX20
		JSONSchema(const JSONSchema&) = delete;

		SIV3D_NODISCARD_CXX20
		JSONSchema(JSONSchema&&) = default;

		SIV3D_NODISCARD_CXX20
		JSONSchema(std::shared_ptr<detail::JSONSchemaDetail>&& detail);

		[[nodiscard]]
		JSONSchema& operator =(const JSONSchema&) = delete;

		[[nodiscard]]
		JSONSchema& operator =(JSONSchema&&) = default;

		// Load や Parse に失敗したときのみ true
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief validation を行う関数
		/// @param [in] json validation をしたい JSON
		/// @return 成功不成功を含有した JSON
		/// @retval json validation に成功した時
		/// @retval JSON::Invalid() validation に失敗した時
		JSON validate(const JSON& json) const noexcept;

		JSON validate(JSON&& json) const noexcept;

		/// @brief validation を行う関数（返り値がエラーについての詳しい情報を持っている版）
		/// @param [in] json validation をしたい JSON
		/// @return 成功不成功を表すオブジェクト ValidationStatus
		[[nodiscard]]
		ValidationStatus validateWithDetails(const JSON& json) const noexcept;
		
		[[nodiscard]]
		ValidationStatus validateWithDetails(JSON&& json) const noexcept;

		/// @brief assert 形式で validation を行う関数
		/// @param [in] json validation をしたい JSON
		/// @return 引数の json
		/// @exception ValidationError validation に失敗したら送出
		JSON validationAssert(const JSON& json) const;

		JSON validationAssert(JSON&& json) const;

		[[nodiscard]]
		static JSONSchema Invalid();

		/// @brief JSONSchema ファイルをパースして JSONSchema オブジェクトを返します。
		/// @param path ファイルパス
		/// @param allowExceptions 例外を発生させるか
		/// @return JSONSchema オブジェクト
		[[nodiscard]]
		static JSONSchema Load(FilePathView path, AllowExceptions allowExceptions = AllowExceptions::No);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>* = nullptr>
		[[nodiscard]]
		static JSONSchema Load(Reader&& reader, AllowExceptions allowExceptions = AllowExceptions::No);

		[[nodiscard]]
		static JSONSchema Load(std::unique_ptr<IReader>&& reader, AllowExceptions allowExceptions = AllowExceptions::No);
		
		/// @brief JSONSchema 文字列をパースして JSONSchema オブジェクトを返します。
		/// @param str 文字列
		/// @param allowExceptions 例外を発生させるか
		/// @return JSONSchema オブジェクト
		[[nodiscard]]
		static JSONSchema Parse(StringView str, AllowExceptions allowExceptions = AllowExceptions::No);

		[[nodiscard]]
		static JSONSchema Set(const JSON& schema, AllowExceptions allowExceptions = AllowExceptions::No);

	private:

		std::shared_ptr<detail::JSONSchemaDetail> m_detail;

		bool m_isValid = true;

		struct Invalid_ {};

		JSONSchema(Invalid_);
	};
}

# include "detail/JSON.ipp"
