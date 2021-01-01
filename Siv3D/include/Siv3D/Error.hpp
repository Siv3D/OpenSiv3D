//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
	protected:

		String m_what;

	public:

		SIV3D_NODISCARD_CXX20
		Error() = default;

		SIV3D_NODISCARD_CXX20
		explicit Error(const char32* what)
			: m_what(what) {}

		SIV3D_NODISCARD_CXX20
		explicit Error(StringView what)
			: m_what(what) {}

		SIV3D_NODISCARD_CXX20
		explicit Error(const String& what)
			: m_what(what) {}

		SIV3D_NODISCARD_CXX20
		explicit Error(String&& what) noexcept
			: m_what(std::move(what)) {}

		virtual ~Error() = default;

		[[nodiscard]]
		const String& what() const noexcept
		{
			return m_what;
		}

		[[nodiscard]]
		virtual StringView type() const noexcept
		{
			return StringView(U"Error");
		}

		friend std::ostream& operator <<(std::ostream& output, const Error& value)
		{
			return (output << '[' << value.type() << "] " << value.what().narrow());
		}

		friend std::wostream& operator <<(std::wostream& output, const Error& value)
		{
			return (output << L'[' << value.type() << L"] " << value.what().toWstr());
		}

		friend std::basic_ostream<char32>& operator <<(std::basic_ostream<char32>& output, const Error& value)
		{
			return output << (U'[' + value.type() + U"] " + value.what());
		}
	};

	/// @brief パースエラーを表現する型
	class ParseError final : public Error
	{
	public:

		using Error::Error;

		[[nodiscard]]
		StringView type() const noexcept override
		{
			return StringView(U"ParseError");
		}
	};

	/// @brief 値を持たない Optional へのアクセスによるエラーを表現する型
	class BadOptionalAccess final : public Error
	{
	public:

		using Error::Error;

		[[nodiscard]]
		StringView type() const noexcept override
		{
			return StringView(U"Bad optional access");
		}
	};

	/// @brief エンジン内部のエラーを表現する型
	class EngineError final : public Error
	{
	public:

		using Error::Error;

		[[nodiscard]]
		StringView type() const noexcept override
		{
			return StringView(U"EngineError");
		}
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	/// @brief エラーをフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param value エラーの値
	void Formatter(FormatData& formatData, const Error& value);
}
