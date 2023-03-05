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

			/// @brief ����� Validation ���s��������Ԃ�
			/// @return �G���[��񂪖������ true, �G���[��񂪂���� false
			[[nodiscard]]
			bool isOK() const noexcept;

			/// @brief ����� Validation ���s��������Ԃ�
			/// @return �G���[��񂪂���� true, �G���[��񂪖������ false
			[[nodiscard]]
			bool isError() const noexcept;

			/// @brief ����� Validation ���s��������Ԃ�
			/// @return �G���[��񂪖������ true, �G���[��񂪂���� false
			[[nodiscard]]
			explicit operator bool() const noexcept;

			/// @brief �G���[������������
			void reset();

			/// @brief �G���[���b�Z�[�W���擾����
			/// @return �G���[���b�Z�[�W������ւ̎Q��
			[[nodiscard]]
			const String& message() const noexcept;

			/// @brief �G���[���N�����ꏊ������ JSON Pointer ���擾����
			/// @return �G���[���N�����ꏊ������ JSON Pointer �ւ̎Q��
			/// @remark Root document �͋󕶎���ŕ\�����Ƃ���A�����ŃG���[���N����� JSON Pointer �͋�B
			[[nodiscard]] 
			const JSONPointer& pointer() const noexcept;

			/// @brief �G���[���N���� JSON �I�u�W�F�N�g���擾����
			/// @return �G���[���N���� JSON �I�u�W�F�N�g�̃R�s�[�ւ̎Q��
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

		/// @remark �R�s�[�s��
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
		/// @return �o���f�[�V�������p�X������ true, ����ȊO�̏ꍇ�� false
		[[nodiscard]]
		bool validate(const JSON& json, ValidationError& status) const noexcept;

		/// @brief assert �`���� validation ���s���֐�
		/// @param [in] json validation �������� JSON
		/// @return ������ json
		/// @exception ValidationError validation �Ɏ��s�����瑗�o
		void validationAssert(const JSON& json) const;

		[[nodiscard]]
		static JSONValidator Invalid();

		/// @brief JSON Schema �t�@�C�����p�[�X���� JSONValidator �I�u�W�F�N�g��Ԃ��܂��B
		/// @param [in] path �t�@�C���p�X
		/// @param [in] allowExceptions ��O�𔭐������邩
		/// @return JSONValidator �I�u�W�F�N�g
		[[nodiscard]]
		static JSONValidator Load(FilePathView path, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief JSON Schema �t�@�C�����p�[�X���� JSONValidator �I�u�W�F�N�g��Ԃ��܂��B
		/// @param [in] path JSON Schema �t�@�C���ւ̃t�@�C���p�X
		/// @param [in] allowExceptions ��O�𔭐������邩
		/// @return JSONValidator �I�u�W�F�N�g
		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>* = nullptr>
		[[nodiscard]]
		static JSONValidator Load(Reader&& reader, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief JSON Schema ������� IReader ����擾���ăp�[�X���� JSONValidator �I�u�W�F�N�g��Ԃ��܂��B
		/// @param [in] reader JSON Schema �������񋟂��� IReader
		/// @param [in] allowExceptions ��O�𔭐������邩
		/// @return JSONValidator �I�u�W�F�N�g
		[[nodiscard]]
		static JSONValidator Load(std::unique_ptr<IReader>&& reader, AllowExceptions allowExceptions = AllowExceptions::No);
		
		/// @brief JSON Schema ��������p�[�X���� JSONValidator �I�u�W�F�N�g��Ԃ��܂��B
		/// @param [in] str JSON Schema ������
		/// @param [in] allowExceptions ��O�𔭐������邩
		/// @return JSONValidator �I�u�W�F�N�g
		[[nodiscard]]
		static JSONValidator Parse(StringView str, AllowExceptions allowExceptions = AllowExceptions::No);

		/// @brief ���� JSON �Ƃ��ēǂݍ��܂�Ă��� JSON Schema �I�u�W�F�N�g���g���� JSONValidator �I�u�W�F�N�g��Ԃ��܂��B
		/// @param [in] schema JSON Schema ��ǂݍ���ł��� JSON �I�u�W�F�N�g
		/// @param [in] allowExceptions ��O�𔭐������邩
		/// @return JSONValidator �I�u�W�F�N�g
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
			/// @brief �^����ꂽ��������p�[�X���� JSONValidator �I�u�W�F�N�g��Ԃ�
			/// @remark �ϐ��ŗ^�������ꍇ�ɂ� JSONValidator::Load/Parse ���g�p���邱��
			inline JSONValidator operator""_jsonValidator(const char32_t* str, size_t length);
		}
	}
}

# include "detail/JSONValidator.ipp"