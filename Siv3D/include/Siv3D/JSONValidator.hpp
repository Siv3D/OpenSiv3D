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
# include "JSON.hpp"

namespace s3d
{
	struct JSONValidator
	{
		struct ValidationError final : public Error
		{
			SIV3D_NODISCARD_CXX20
			ValidationError() = default;

			SIV3D_NODISCARD_CXX20
			ValidationError(StringView message, const JSONPointer& pointer, const JSON& instance);

			SIV3D_NODISCARD_CXX20
			ValidationError(const ValidationError&) = default;

			SIV3D_NODISCARD_CXX20
			ValidationError(ValidationError&&) = default;

			ValidationError& operator =(const ValidationError&) = default;

			ValidationError& operator =(ValidationError&&) = default;

			/// @brief 正常に Validation を行えたかを返す
			/// @return エラー情報が無ければ true, エラー情報があれば false
			[[nodiscard]]
			bool isOK() const noexcept;

			/// @brief 正常に Validation を行えたかを返す
			/// @return エラー情報があれば true, エラー情報が無ければ false
			[[nodiscard]]
			bool isError() const noexcept;

			/// @brief 正常に Validation を行えたかを返す
			/// @return エラー情報が無ければ true, エラー情報があれば false
			[[nodiscard]]
			explicit operator bool() const noexcept;

			/// @brief エラー情報を消去する
			void reset();

			/// @brief エラーメッセージを取得する
			/// @return エラーメッセージ文字列への参照
			[[nodiscard]]
			const String& message() const noexcept;

			/// @brief エラーが起きた場所を示す JSON Pointer を取得する
			/// @return エラーが起きた場所を示す JSON Pointer への参照
			/// @remark Root document は空文字列で表すことから、そこでエラーが起きれば JSON Pointer は空。
			[[nodiscard]] 
			const JSONPointer& pointer() const noexcept;

			/// @brief エラーが起きた JSON オブジェクトを取得する
			/// @return エラーが起きた JSON オブジェクトのコピーへの参照
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
		JSONValidator();

		/// @remark コピー不可
		SIV3D_NODISCARD_CXX20
		JSONValidator(const JSONValidator&) = delete;

		SIV3D_NODISCARD_CXX20
		JSONValidator(JSONValidator&&) = default;

		SIV3D_NODISCARD_CXX20
		JSONValidator(std::shared_ptr<detail::JSONValidatorDetail>&& detail);

		JSONValidator& operator =(const JSONValidator&) = delete;

		JSONValidator& operator =(JSONValidator&&) = default;

		// Load や Parse に失敗したときのみ true
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief validation を行う関数
		/// @param [in] json validation をしたい JSON
		/// @return バリデーションをパスしたら true, それ以外の場合は false
		bool validate(const JSON& json) const noexcept;

		/// @brief validation を行う関数（返り値がエラーについての詳しい情報を持っている版）
		/// @param [in] json validation をしたい JSON
		/// @param [out] status validation の結果とエラーならエラー情報を含む
		/// @return バリデーションをパスしたら true, それ以外の場合は false
		[[nodiscard]]
		bool validate(const JSON& json, ValidationError& status) const noexcept;

		/// @brief assert 形式で validation を行う関数
		/// @param [in] json validation をしたい JSON
		/// @return 引数の json
		/// @exception ValidationError validation に失敗したら送出
		void validationAssert(const JSON& json) const;

		[[nodiscard]]
		static JSONValidator Invalid();

		/// @brief JSON Schema ファイルをパースして JSONValidator オブジェクトを返します。
		/// @param [in] path ファイルパス
		/// @param [in] allowExceptions 例外を発生させるか
		/// @return JSONValidator オブジェクト
		[[nodiscard]]
		static JSONValidator Load(FilePathView path, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief JSON Schema ファイルをパースして JSONValidator オブジェクトを返します。
		/// @param [in] path JSON Schema ファイルへのファイルパス
		/// @param [in] allowExceptions 例外を発生させるか
		/// @return JSONValidator オブジェクト
		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>* = nullptr>
		[[nodiscard]]
		static JSONValidator Load(Reader&& reader, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief JSON Schema 文字列を IReader から取得してパースして JSONValidator オブジェクトを返します。
		/// @param [in] reader JSON Schema 文字列を提供する IReader
		/// @param [in] allowExceptions 例外を発生させるか
		/// @return JSONValidator オブジェクト
		[[nodiscard]]
		static JSONValidator Load(std::unique_ptr<IReader>&& reader, AllowExceptions allowExceptions = AllowExceptions::No);
		
		/// @brief JSON Schema 文字列をパースして JSONValidator オブジェクトを返します。
		/// @param [in] str JSON Schema 文字列
		/// @param [in] allowExceptions 例外を発生させるか
		/// @return JSONValidator オブジェクト
		[[nodiscard]]
		static JSONValidator Parse(StringView str, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief 既に JSON として読み込まれている JSON Schema オブジェクトを使って JSONValidator オブジェクトを返します。
		/// @param [in] schema JSON Schema を読み込んである JSON オブジェクト
		/// @param [in] allowExceptions 例外を発生させるか
		/// @return JSONValidator オブジェクト
		[[nodiscard]]
		static JSONValidator Set(const JSON& schema, AllowExceptions allowExceptions = AllowExceptions::No);

	private:

		std::shared_ptr<detail::JSONValidatorDetail> m_detail;

		bool m_isValid = true;

		struct Invalid_ {};

		JSONValidator(Invalid_);
	};

	inline namespace Literals
	{
		inline namespace JSONLiterals
		{
			/// @brief 与えられた文字列をパースして JSONValidator オブジェクトを返す
			/// @remark 変数で与えたい場合には JSONValidator::Load/Parse を使用すること
			inline JSONValidator operator""_jsonValidator(const char32_t* str, size_t length);
		}
	}
}

# include "detail/JSONValidator.ipp"