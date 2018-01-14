//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "String.hpp"
# include "Format.hpp"
# include "ByteArrayView.hpp"

namespace s3d
{
	/// <summary>
	/// MD5 ハッシュ値
	/// </summary>
	struct MD5Value
	{
		std::array<uint8, 16> value;

		String asString() const;

		bool operator == (const MD5Value& other) const noexcept;

		bool operator != (const MD5Value& other) const noexcept;
	};

	/// <summary>
	/// MD5
	/// </summary>
	/// <remarks>
	/// データから MD5 ハッシュ値を計算する機能を提供します。
	/// </remarks>
	namespace MD5
	{
		/// <summary>
		/// データから MD5 ハッシュ値を計算します。
		/// </summary>
		/// <param name="data">
		/// MD5 ハッシュ値を計算するデータの先頭ポインタ
		/// </param>
		/// <param name="size">
		/// MD5 ハッシュ値を計算するデータのサイズ
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		[[nodiscard]] MD5Value FromBinary(const void* const data, size_t size);

		/// <summary>
		/// データから MD5 ハッシュ値を計算します。
		/// </summary>
		/// <param name="view">
		/// MD5 ハッシュ値を計算するデータ
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		[[nodiscard]] MD5Value FromBinary(ByteArrayView view);

		/// <summary>
		/// 文字列データから MD5 ハッシュ値を計算します。
		/// </summary>
		/// <param name="str">
		/// MD5 ハッシュ値を計算する文字列データ
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		[[nodiscard]] MD5Value FromText(StringView view);

		/// <summary>
		/// 文字列から MD5 ハッシュを計算します。
		/// </summary>
		/// <param name="str">
		/// MD5 ハッシュ値を計算する文字列
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		[[nodiscard]] MD5Value FromText(std::string_view view);

		/// <summary>
		/// 指定したファイルの MD5 ハッシュ値を計算します。
		/// </summary>
		/// <param name="path">
		/// MD5 ハッシュ値を計算するファイルのパス
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		[[nodiscard]] MD5Value FromFile(const FilePath& path);
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	inline void Formatter(FormatData& formatData, const MD5Value& value)
	{
		formatData.string.append(value.asString());
	}

	template <class CharType>
	inline std::basic_ostream<CharType> & operator <<(std::basic_ostream<CharType> output, const MD5Value& value)
	{
		return output << value.asString();
	}
}
