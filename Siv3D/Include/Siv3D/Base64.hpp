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

namespace s3d
{
	/// <summary>
	/// Base64
	/// </summary>
	/// <remarks>
	/// Base64 エンコード/デコードの機能を提供します。
	/// </remarks>
	namespace Base64
	{
		/// <summary>
		/// データを Base64 エンコードします。
		/// </summary>
		/// <param name="data">
		/// エンコードするデータの先頭ポインタ
		/// </param>
		/// <param name="size">
		/// エンコードするデータのサイズ（バイト）
		/// </param>
		/// <returns>
		/// エンコードされたテキストデータ、エンコードに失敗した場合空の文字列
		/// </returns>
		String Encode(const void* data, size_t size);

		/// <summary>
		/// データを Base64 エンコードします。
		/// </summary>
		/// <param name="view">
		/// エンコードするデータ
		/// </param>
		/// <returns>
		/// エンコードされたテキストデータ、エンコードに失敗した場合空の文字列
		/// </returns>
		inline String Encode(const ByteArrayView view)
		{
			return Encode(view.data(), view.size());
		}

		/// <summary>
		/// テキストを Base64 でデコードします。
		/// </summary>
		/// <param name="base64">
		/// デコードするテキスト
		/// </param>
		/// <returns>
		/// デコードされたバイナリデータ、デコードに失敗した場合空のバイナリデータ
		/// </returns>
		ByteArray Decode(const String& base64);
	};
}
