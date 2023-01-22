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

			[[nodiscard]]
			bool isOK() const noexcept;

			[[nodiscard]]
			bool isError() const noexcept;

			/// @brief 正常かどうかを返す
			[[nodiscard]]
			explicit operator bool() const noexcept;

			void reset();

			[[nodiscard]]
			const String& message() const noexcept;

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
		JSONValidator();

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
		[[nodiscard]]
		bool validate(const JSON& json, ValidationError& status) const noexcept;

		/// @brief assert 形式で validation を行う関数
		/// @param [in] json validation をしたい JSON
		/// @return 引数の json
		/// @exception ValidationError validation に失敗したら送出
		void validationAssert(const JSON& json) const;

		[[nodiscard]]
		static JSONValidator Invalid();

		/// @brief JSONSchema ファイルをパースして JSONSchema オブジェクトを返します。
		/// @param path ファイルパス
		/// @param allowExceptions 例外を発生させるか
		/// @return JSONSchema オブジェクト
		[[nodiscard]]
		static JSONValidator Load(FilePathView path, AllowExceptions allowExceptions = AllowExceptions::No);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>* = nullptr>
		[[nodiscard]]
		static JSONValidator Load(Reader&& reader, AllowExceptions allowExceptions = AllowExceptions::No);

		[[nodiscard]]
		static JSONValidator Load(std::unique_ptr<IReader>&& reader, AllowExceptions allowExceptions = AllowExceptions::No);
		
		/// @brief JSONSchema 文字列をパースして JSONSchema オブジェクトを返します。
		/// @param str 文字列
		/// @param allowExceptions 例外を発生させるか
		/// @return JSONSchema オブジェクト
		[[nodiscard]]
		static JSONValidator Parse(StringView str, AllowExceptions allowExceptions = AllowExceptions::No);

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
			inline JSONValidator operator""_jsonValidator(const char32_t* str, size_t length);
		}
	}
}

# include "detail/JSONValidator.ipp"