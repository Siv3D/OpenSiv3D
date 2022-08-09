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
# include "FormatData.hpp"

namespace s3d
{
	/// @brief エラーを表現する型
	class Error
	{
	public:

		SIV3D_NODISCARD_CXX20
		Error() = default;

		SIV3D_NODISCARD_CXX20
		explicit Error(const char32* what);

		SIV3D_NODISCARD_CXX20
		explicit Error(StringView what);

		SIV3D_NODISCARD_CXX20
		explicit Error(const String& what);

		SIV3D_NODISCARD_CXX20
		explicit Error(String&& what) noexcept;

		virtual ~Error() = default;

		[[nodiscard]]
		const String& what() const noexcept;

		[[nodiscard]]
		virtual StringView type() const noexcept;

		friend std::ostream& operator <<(std::ostream& output, const Error& value);

		friend std::wostream& operator <<(std::wostream& output, const Error& value);

		friend std::basic_ostream<char32>& operator <<(std::basic_ostream<char32>& output, const Error& value);

		friend void Formatter(FormatData& formatData, const Error& value);

	protected:

		String m_what;
	};

	/// @brief パースエラーを表現する型
	class ParseError final : public Error
	{
	public:

		using Error::Error;

		[[nodiscard]]
		StringView type() const noexcept override;
	};

	/// @brief 値を持たない Optional へのアクセスによるエラーを表現する型
	class BadOptionalAccess final : public Error
	{
	public:

		using Error::Error;

		[[nodiscard]]
		StringView type() const noexcept override;
	};

	/// @brief 未実装の機能を使用したエラーを表現する型
	class NotImplementedError final : public Error
	{
	public:

		using Error::Error;

		[[nodiscard]]
		StringView type() const noexcept override;
	};

	/// @brief エンジン内部のエラーを表現する型
	class EngineError final : public Error
	{
	public:

		using Error::Error;

		[[nodiscard]]
		StringView type() const noexcept override;
	};
}

# include "detail/Error.ipp"
