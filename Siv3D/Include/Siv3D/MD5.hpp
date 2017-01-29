//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "String.hpp"
# include "ByteArrayView.hpp"
# include "Format.hpp"

namespace s3d
{
	/// <summary>
	/// MD5 ハッシュ値
	/// </summary>
	struct MD5Hash
	{
		uint8 value[16];

		String asString() const;

		bool operator ==(const MD5Hash& md5) const noexcept
		{
			return ::memcmp(value, md5.value, sizeof(value)) == 0;
		}

		bool operator !=(const MD5Hash& md5) const noexcept
		{
			return !(*this == md5);
		}
	};

	namespace Hash
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
		MD5Hash MD5(const void* data, size_t size);

		/// <summary>
		/// データから MD5 ハッシュ値を計算します。
		/// </summary>
		/// <param name="view">
		/// MD5 ハッシュ値を計算するデータ
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		inline MD5Hash MD5(const ByteArrayView view)
		{
			return MD5(view.data(), view.size());
		}

		/// <summary>
		/// 文字列データから MD5 ハッシュ値を計算します。
		/// </summary>
		/// <param name="str">
		/// MD5 ハッシュ値を計算する文字列データ
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		inline MD5Hash MD5FromString(StringView str)
		{
			return MD5(str.data(), str.size_bytes());
		}

		/// <summary>
		/// 文字列から MD5 ハッシュを計算します。
		/// </summary>
		/// <param name="str">
		/// MD5 ハッシュ値を計算する文字列
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		inline MD5Hash MD5FromString(const std::string& str)
		{
			return MD5(str.data(), str.size());
		}

		/// <summary>
		/// 指定したファイルの MD5 ハッシュ値を計算します。
		/// </summary>
		/// <param name="path">
		/// MD5 ハッシュ値を計算するファイルのパス
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		MD5Hash MD5FromFile(const FilePath& path);
	}
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting MD5Hash
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[ ] istream
//	[ ] wistream
//	[p] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	inline void Formatter(FormatData& formatData, const MD5Hash& md5)
	{
		formatData.string.append(md5.asString());
	}

	template <class CharType>
	inline std::basic_ostream<CharType> & operator <<(std::basic_ostream<CharType> os, const MD5Hash& md5)
	{
		return os << md5.asString();
	}
}
//
//////////////////////////////////////////////////////////////////////////////
