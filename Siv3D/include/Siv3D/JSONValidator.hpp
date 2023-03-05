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

			/// @brief ���킩�ǂ�����Ԃ�
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

			// what �̕��� message ��ݒ肷��̂� m_message �͎����Ȃ�
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

		// Load �� Parse �Ɏ��s�����Ƃ��̂� true
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief validation ���s���֐�
		/// @param [in] json validation �������� JSON
		/// @return �o���f�[�V�������p�X������ true, ����ȊO�̏ꍇ�� false
		bool validate(const JSON& json) const noexcept;

		/// @brief validation ���s���֐��i�Ԃ�l���G���[�ɂ��Ă̏ڂ������������Ă���Łj
		/// @param [in] json validation �������� JSON
		/// @param [out] status validation �̌��ʂƃG���[�Ȃ�G���[�����܂�
		[[nodiscard]]
		bool validate(const JSON& json, ValidationError& status) const noexcept;

		/// @brief assert �`���� validation ���s���֐�
		/// @param [in] json validation �������� JSON
		/// @return ������ json
		/// @exception ValidationError validation �Ɏ��s�����瑗�o
		void validationAssert(const JSON& json) const;

		[[nodiscard]]
		static JSONValidator Invalid();

		/// @brief JSONSchema �t�@�C�����p�[�X���� JSONSchema �I�u�W�F�N�g��Ԃ��܂��B
		/// @param path �t�@�C���p�X
		/// @param allowExceptions ��O�𔭐������邩
		/// @return JSONSchema �I�u�W�F�N�g
		[[nodiscard]]
		static JSONValidator Load(FilePathView path, AllowExceptions allowExceptions = AllowExceptions::No);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>* = nullptr>
		[[nodiscard]]
		static JSONValidator Load(Reader&& reader, AllowExceptions allowExceptions = AllowExceptions::No);

		[[nodiscard]]
		static JSONValidator Load(std::unique_ptr<IReader>&& reader, AllowExceptions allowExceptions = AllowExceptions::No);
		
		/// @brief JSONSchema ��������p�[�X���� JSONSchema �I�u�W�F�N�g��Ԃ��܂��B
		/// @param str ������
		/// @param allowExceptions ��O�𔭐������邩
		/// @return JSONSchema �I�u�W�F�N�g
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