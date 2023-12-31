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
# include "Array.hpp"
# include "Optional.hpp"
# include "String.hpp"
# include "IReader.hpp"
# include "Blob.hpp"
# include "PredefinedYesNo.hpp"
# include "detail/JSONFwd.ipp"

namespace s3d
{
	/// @brief JSON が持つ要素の値の種類を表す列挙体
	enum class JSONValueType : uint8
	{
		Empty,

		Null,

		Object,

		Array,

		String,

		Number,

		Bool,

		Binary,
	};

	/// @brief JSON が持つ要素を走査するために使用するイテレータ
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

	/// @brief JSON が持つ要素を走査するために使用する読み取り専用イテレータ
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

	/// @brief 配列を要素に持つ JSON において、その配列の要素を走査するために使用するイテレータ
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

	/// @brief 配列を要素に持つ JSON において、その配列の要素を走査するために使用するプロキシ型
	/// JSON::arrayView の返り値に使用されます。
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
		JSON(const JSON& other);

		SIV3D_NODISCARD_CXX20
		JSON(JSON&& other);

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

		JSON& operator =(JSON&& value) noexcept;

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

		JSON& assignUTF8String(std::string_view value);

		/// @brief 他の JSON オブジェクトと値が等しいかを調べます。
		/// @param [in] other 等しいか調べたい他の JSON オブジェクト
		[[nodiscard]]
		bool operator ==(const JSON& other) const;

		/// @brief 他の JSON オブジェクトと値が等しくないかを調べます。
		/// @param [in] other 等しくないか調べたい他の JSON オブジェクト
		[[nodiscard]]
		bool operator !=(const JSON& other) const;

		/// @brief 無効な状態であるかどうかを返します。 
		/// @remark Load や Parse に失敗したときのみ true になります。
		[[nodiscard]]
		bool isEmpty() const;

		/// @brief 有効な状態であるかどうかを返します。
		/// @remark Load や Parse に失敗したときのみ false になります。 
		[[nodiscard]]
		explicit operator bool() const;

		/// @brief 所有している値が null であるかを返します。 
		[[nodiscard]]
		bool isNull() const;

		/// @brief 所有している値が bool であるかを返します。 
		[[nodiscard]]
		bool isBool() const;

		/// @brief 所有している値が 数字 であるかを返します。 
		[[nodiscard]]
		bool isNumber() const;

		/// @brief 所有している値が 整数 であるかを返します。 
		[[nodiscard]]
		bool isInteger() const;

		/// @brief 所有している値が 非負整数 であるかを返します。 
		[[nodiscard]]
		bool isUnsigned() const;

		/// @brief 所有している値が 小数 であるかを返します。 
		[[nodiscard]]
		bool isFloat() const;

		/// @brief 所有している値が 文字列 であるかを返します。 
		[[nodiscard]]
		bool isString() const;

		/// @brief 所有している値が 配列 であるかを返します。 
		[[nodiscard]]
		bool isArray() const;

		/// @brief 所有している値が オブジェクト であるかを返します。 
		[[nodiscard]]
		bool isObject() const;

		/// @brief 所有している値が バイナリ であるかを返します。 
		[[nodiscard]]
		bool isBinary() const;

		/// @brief 所有している値の種類を取得します。
		/// @return 所有している値の種類を表す列挙体の値
		[[nodiscard]]
		JSONValueType getType() const;

		/// @brief 渡されたキーが指す要素が存在しているかを返します。
		/// @param [in] key キーを表す文字列
		[[nodiscard]]
		bool hasElement(StringView name) const;

		/// @brief 所有している値が文字列の場合に、その値を String として取得します。
		/// @return 取得した値
		[[nodiscard]]
		String getString() const;

		/// @brief 所有している値が文字列の場合に、その値を UTF-8 文字列 (std::string) として取得します。
		/// @return 取得した値
		[[nodiscard]]
		std::string getUTF8String() const;

		/// @brief 所有している値がバイナリである場合に、その値を配列として取得します。
		/// @return 取得した値
		[[nodiscard]]
		Array<uint8> getBinary() const;

		/// @brief 所有している値を Type の値として取得しようとし、失敗した場合は例外を投げます。
		/// @tparam Type 取得したい型 
		/// @return 取得した値
		/// @exception Type の値として取得するのに失敗した場合
		template <class Type>
		[[nodiscard]]
		Type get() const;

		/// @brief 所有している値を Type の値として取得しようとし、失敗した場合はデフォルト値を返します。
		/// @tparam Type 取得したい型
		/// @param [in] defaultValue 失敗した場合に返す値
		/// @return 成功した場合は取得したその値、失敗した場合はデフォルト値を返します。
		template <class Type, class U>
		[[nodiscard]]
		Type getOr(U&& defaultValue) const;

		/// @brief 所有している値を Type の値として取得しようとし、Optional で結果を返します。
		/// @tparam Type 取得したい型
		/// @return 成功した場合は取得したその値、失敗した場合は無効値を持つ Optional
		template <class Type>
		[[nodiscard]]
		Optional<Type> getOpt() const;

		/// @brief 渡されたキーが指す要素を取得します。
		/// @param [in] name キー
		/// @return キーが指す要素
		[[nodiscard]]
		JSON operator [](StringView name);

		/// @brief 渡されたキーが指す要素を取得します。
		/// @param [in] name キー
		/// @return キーが指す要素
		[[nodiscard]]
		const JSON operator [](StringView name) const;

		/// @brief 渡されたインデックスが指す要素を取得します。
		/// @param [in] index インデックス
		/// @return インデックスが指す要素
		[[nodiscard]]
		JSON operator [](size_t index);

		/// @brief 渡されたインデックスが指す要素を取得します。
		/// @param [in] index インデックス
		/// @return インデックスが指す要素
		[[nodiscard]]
		const JSON operator [](size_t index) const;

		/// @brief 渡された JSON Pointer が指す要素を取得します。
		/// @remark 実際の処理は access(JSONPointer) が行います。
		/// @param [in] JSONPointer JSONPointer
		/// @return JSONPointer が指す要素
		[[nodiscard]]
		JSON operator [](const JSONPointer& jsonPointer);

		/// @brief 渡された JSON Pointer が指す要素を取得します。
		/// @remark 実際の処理は access(JSONPointer) が行います。
		/// @param [in] JSONPointer JSONPointer
		/// @return JSONPointer が指す要素
		[[nodiscard]]
		const JSON operator [](const JSONPointer& jsonPointer) const;

		/// @brief 渡された JSON Pointer が指す要素を取得します。
		/// @param [in] jsonPointer JSONPointer
		/// @return JSONPointer が指す要素
		[[nodiscard]]
		JSON access(const JSONPointer& jsonPointer);

		/// @brief 渡された JSON Pointer が指す要素を取得します。
		/// @param [in] jsonPointer JSONPointer
		/// @return JSONPointer が指す要素
		[[nodiscard]]
		const JSON access(const JSONPointer& jsonPointer) const;

		/// @brief 渡された JSON Pointer の文字列が指す要素を取得します。
		/// @remark 実際の処理は access(JSONPointer) が行います。
		/// @param [in] JSONPointer 文字列で表現された JSON Pointer
		/// @return JSON Pointer が指す要素
		[[nodiscard]]
		JSON access(StringView jsonPointer);

		/// @brief 渡された JSON Pointer の文字列が指す要素を取得します。
		/// @remark 実際の処理は access(JSONPointer) が行います。
		/// @param [in] jsonPointer 文字列で表現された JSON Pointer
		/// @return JSON Pointer が指す要素
		[[nodiscard]]
		const JSON access(StringView jsonPointer) const;

		/// @brief 渡された JSON オブジェクトを所有しているデータに追加します。
		/// @param [in] value 追加する JSON オブジェクト
		void push_back(const JSON& value);

		/// @brief 所有しているデータを消去して空にします。
		void clear();

		/// @brief 渡されたキーが指す要素を削除します。
		/// @param [in] name キー
		void erase(StringView name);

		/// @brief 渡されたインデックスが指す要素を削除します。
		/// @param [in] index インデックス
		void erase(size_t index);

		/// @brief 渡されたキーが指す要素が存在しているかを返します。
		/// @param [in] key キーを表す文字列
		bool contains(StringView key) const noexcept;

		/// @brief 渡されたインデックスが指す要素が存在しているかを返します。
		/// @param [in] index インデックス
		bool contains(size_t index) const noexcept;

		/// @brief 渡された JSONPointer が指す要素が存在しているかを返します。
		/// @param [in] jsonPointer JSONPointer
		bool contains(const JSONPointer& jsonPointer) const noexcept;

		// [Siv3D ToDo]
		// void erase(???); 他のオーバーロード

		// [Siv3D ToDo]
		//[[nodiscard]] iterator find(const StringView name)

		// [Siv3D ToDo]
		//[[nodiscard]] const_iterator find(const StringView name)

		/// @brief 最初の要素を指すイテレータを返します。
		/// @return 最初の要素を指すイテレータ
		[[nodiscard]]
		iterator begin();

		/// @brief 最初の要素を指す読み取り専用イテレータを返します。
		/// @return 最初の要素を指す読み取り専用イテレータ
		[[nodiscard]]
		const_iterator begin() const;

		/// @brief 最後の要素の次を指すイテレータを返します。
		/// @return 最後の要素の次を指すイテレータ
		[[nodiscard]]
		iterator end();

		/// @brief 最後の要素の次を指す読み取り専用イテレータを返します。
		/// @return 最後の要素の次を指す読み取り専用イテレータ
		[[nodiscard]]
		const_iterator end() const;

		/// @brief 所有しているデータが配列である場合のイテレータを提供するプロキシを返します。
		/// @deprecated v0.6.7. におけるイテレータの改善の結果、使用する必要がなくなりました。
		[[nodiscard]]
		JSONArrayView arrayView() const;

		/// @brief 持っているデータの要素数を返します。
		/// @return 要素数
		[[nodiscard]]
		size_t size() const;

		/// @brief JSON データを文字列にフォーマットした結果を返します。
		/// @param [in] space インデントの文字
		/// @param [in] spaceCount インデントの文字数
		/// @return フォーマットした結果
		[[nodiscard]]
		String format(char32 space = U' ', size_t spaceCount = 2) const;

		/// @brief JSON データを、不要なスペースを消したコンパクトな形式で文字列にフォーマットした結果を返します。
		/// @return フォーマットした結果
		[[nodiscard]]
		String formatMinimum() const;

		/// @brief JSON データを UTF-8 エンコードの文字列にフォーマットした結果を返します。
		/// @param [in] space インデントの文字
		/// @param [in] spaceCount インデントの文字数
		/// @return フォーマットした結果
		[[nodiscard]]
		std::string formatUTF8(char32 space = U' ', size_t spaceCount = 2) const;

		/// @brief JSON データを、不要なスペースを消したコンパクトな形式で UTF-8 エンコードの文字列にフォーマットした結果を返します。
		/// @return フォーマットした結果
		[[nodiscard]]
		std::string formatUTF8Minimum() const;

		/// @brief JSON データをファイルに保存します。
		/// @param [in] path ファイルパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(FilePathView path) const;

		/// @brief JSON データを、不要なスペースを消したコンパクトな形式でファイルに保存します。
		/// @param [in] path ファイルパス
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

		/// @brief JSON オブジェクトを交換します。
		/// @param other 交換する JSON オブジェクト
		void swap(JSON& other) noexcept;

		/// @brief 2 つの JSON オブジェクトを交換します。
		/// @param lhs JSON オブジェクト
		/// @param rhs JSON オブジェクト
		friend void swap(JSON& lhs, JSON& rhs) noexcept
		{
			lhs.m_detail.swap(rhs.m_detail);
			std::swap(lhs.m_isValid, rhs.m_isValid);
		}

		// @brief 無効な JSON オブジェクトを返します。
		// @return 無効な JSON オブジェクト
		[[nodiscard]]
		static JSON Invalid();

		/// @brief JSON ファイルをパースして JSON オブジェクトを返します。
		/// @param [in] path ファイルパス
		/// @param [in] allowExceptions 例外を発生させるか
		/// @return JSON オブジェクト
		[[nodiscard]]
		static JSON Load(FilePathView path, AllowExceptions allowExceptions = AllowExceptions::No);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>* = nullptr>
		[[nodiscard]]
		static JSON Load(Reader&& reader, AllowExceptions allowExceptions = AllowExceptions::No);

		[[nodiscard]]
		static JSON Load(std::unique_ptr<IReader>&& reader, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief JSON 文字列をパースして JSON オブジェクトを返します。
		/// @param [in] str 文字列
		/// @param [in] allowExceptions 例外を発生させるか
		/// @return JSON オブジェクト
		[[nodiscard]]
		static JSON Parse(StringView str, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief BSON 形式のデータから JSON オブジェクトをデシリアライズします。
		/// @param [in] bson BSON データ
		/// @param [in] allowExceptions 例外を発生させるか
		/// @return JSON オブジェクト
		[[nodiscard]]
		static JSON FromBSON(const Blob& bson, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief CBOR 形式のデータから JSON オブジェクトをデシリアライズします。
		/// @param [in] cbor CBOR データ
		/// @param [in] allowExceptions 例外を発生させるか
		/// @return JSON オブジェクト
		[[nodiscard]]
		static JSON FromCBOR(const Blob& cbor, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief MessagePack 形式のデータから JSON オブジェクトをデシリアライズします。
		/// @param [in] msgpack MessagePack データ
		/// @param [in] allowExceptions 例外を発生させるか
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

		friend JSONValidator;
	};

	struct JSONItem
	{
		String key;

		JSON value;
	};

	struct JSONPointer
	{
		/// @brief JSONPointer オブジェクトを作成します。
		/// @param [in] jsonPointer JSON Pointer を表す文字列
		/// @remark 空の文字列の場合は Root document を指すようになります。
		/// 空の文字列ではない場合、"/" から始まる必要があります。
		/// トークン（区切り文字ではない Object キーや Array インデックス）の中においては、
		/// "~" は "~0" へ、"/" は "~1" へとエスケープされる必要があります。
		SIV3D_NODISCARD_CXX20
		explicit JSONPointer(StringView jsonPointer = U"");

		SIV3D_NODISCARD_CXX20
		JSONPointer(const JSONPointer& other);

		SIV3D_NODISCARD_CXX20
		JSONPointer(JSONPointer&&) = default;

		SIV3D_NODISCARD_CXX20
		JSONPointer(std::shared_ptr<detail::JSONPointerDetail>&& detail);

		JSONPointer& operator =(const JSONPointer& other);

		JSONPointer& operator =(JSONPointer&&) = default;

		/// @brief 保持しているパスを文字列として取得します。
		/// @return 保持しているパスを JSON Pointer を表す文字列として返します。
		/// @remark 返される文字列はエスケープされたままであることに留意してください。
		[[nodiscard]] 
		String format() const;

		/// @brief 同じパスを指しているかを調べます。
		/// @return 同じパスを指しているなら true, そうでなければ false
		/// @remark operator != は自動導出によって利用可能になります。
		friend bool operator ==(const JSONPointer& lhs, const JSONPointer& rhs) noexcept;

		/// @brief JSONPointer を末尾に追加します。
		/// @param [in] rhs JSONPointer
		/// @return *this
		JSONPointer& operator /=(const JSONPointer& rhs);

		/// @brief トークン（Object キーまたは Array インデックス）を末尾に追加します。
		/// @param [in] unescapedToken キーを表す文字列（エスケープされていないトークン）
		/// @return *this
		JSONPointer& operator /=(StringView unescapedToken);
 
		/// @brief JSON の Array インデックスを末尾に追加します。
		/// @param [in] index インデックス
		/// @return *this
		JSONPointer& operator /=(size_t index);

		/// @brief JSONPointer を末尾に追加した JSONPointer を作成します。
		/// @param [in] rhs JSONPointer
		/// @return 受け取った JSONPointer を末尾に追加して作成された JSONPointer
		[[nodiscard]] 
		JSONPointer operator /(const JSONPointer& rhs) const;

		/// @brief トークン（Object キーまたは Array インデックス）を末尾に追加した JSONPointer を作成します。
		/// @param [in] unescapedToken キーを表す文字列（エスケープされていないトークン）
		/// @return 受け取ったトークンを末尾に追加して作成された JSONPointer
		[[nodiscard]] 
		JSONPointer operator /(StringView unescapedToken) const;

		/// @brief Array インデックスを末尾に追加した JSONPointer を作成します。
		/// @param [in] index インデックス
		/// @return 受け取った Array インデックスを末尾に追加して作成された JSONPointer
		[[nodiscard]] 
		JSONPointer operator /(size_t index) const;

		/// @brief 親パスを返り値で取得します。
		/// @return 親パスを持った JSONPointer
		/// @remark 親パスとは、pop_back をした状態と同じパスのことを指しています。
		[[nodiscard]] 
		JSONPointer parent() const;

		/// @brief 末尾のトークン（Object キーまたは Array インデックス）を取得します。
		/// @return 末尾のトークンの文字列
		[[nodiscard]] 
		String back() const;

		/// @brief 末尾から1つトークン（Object キーまたは Array インデックス）を削除します。
		/// @param [in] n 削除する個数
		/// @remark n が持っているトークンの個数よりも多い場合は全てのトークンを削除します。
		void pop_back();

		/// @brief 末尾から指定された個数のトークン（Object キーまたは Array インデックス）を削除します。
		/// @param [in] n 削除する個数
		/// @remark n が持っているトークンの個数よりも多い場合は全てのトークンを削除します。
		void pop_back_N(size_t n);

		/// @brief JSONPointer を末尾に追加します。
		/// @param [in] rhs JSONPointer
		void push_back(const JSONPointer& rhs);

		/// @brief トークン（Object キーまたは Array インデックス）を末尾に追加します。
		/// @param [in] unescapedToken キーを表す文字列（エスケープされていないトークン）
		void push_back(StringView unescapedToken);

		/// @brief JSON の Array インデックスを末尾に追加します。
		/// @param [in] index インデックス
		void push_back(size_t index);

		/// @brief Root document を指しているかを返します。
		/// @return Root document を指していれば true, そうでなければ false
		[[nodiscard]] 
		bool isEmpty() const noexcept;

		/// @brief Root document を指しているかを返します。
		/// @return Root document を指していれば true, そうでなければ false
		[[nodiscard]]
		bool empty() const noexcept;

		friend void Formatter(FormatData& formatData, const JSONPointer& value);

		/// @brief "~" -> "~0", "/" -> "~1" の escape を行います。
		/// @remark /abc/xyz のような JSON Pointer を処理するわけではなく、abc や xyz のトークン部分の処理に使用します。
		/// @param [in] unescapedToken エスケープされていないトークン
		/// @return エスケープされたトークン
		[[nodiscard]] 
		static String Escape(StringView unescapedToken);

		/// @brief "~0" -> "~", "~1" -> "/" の unescape を行います。
		/// @remark /abc/xyz のような JSON Pointer を処理するわけではなく、abc や xyz のトークン部分の処理に使用します。
		/// @param [in] escapedToken エスケープされているトークン
		/// @return エスケープされていないトークン
		[[nodiscard]] 
		static String Unescape(StringView escapedToken);

	private:

		std::shared_ptr<detail::JSONPointerDetail> m_detail;

		friend JSON;
	};

	inline namespace Literals
	{
		inline namespace JSONLiterals
		{
			/// @brief 与えられた文字列をパースして JSON オブジェクトを返します。
			/// @remark 文字列変数から JSON オブジェクトを作成する場合は JSON::Load/Parse を使用してください。
			inline JSON operator ""_json(const char32_t* str, size_t length);

			/// @brief 与えられた文字列をパースして JSONPointer オブジェクトを返します。
			/// @remark JSON Pointer を表す文字列の変数から JSONPointer オブジェクトを作成する場合は
			/// JSONPointer のコンストラクタを使用してください。
			inline JSONPointer operator ""_jsonPointer(const char32_t* str, size_t length);

			/// @brief 与えられた文字列をパースして JSONPointer オブジェクトを返します。
			/// @remark JSON Pointer を表す文字列の変数から JSONPointer オブジェクトを作成する場合は
			/// JSONPointer のコンストラクタを使用してください。
			inline JSONPointer operator ""_jsonPtr(const char32_t* str, size_t length);
		}
	}
}

# include "detail/JSON.ipp"
