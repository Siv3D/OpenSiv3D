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
# include "HashTable.hpp"
# include "URLView.hpp"
# include "HTTPResponse.hpp"
# include "AsyncHTTPTask.hpp"

namespace s3d
{
	class MemoryWriter;
	class IWriter;

	namespace SimpleHTTP
	{
		/// @brief 指定した URL からファイルをダウンロードし、HTTP レスポンスを返します。
		/// @param url URL
		/// @param filePath ダウンロードしたファイルを保存するパス
		/// @remark この関数は失敗するかダウンロードが終了するまで制御を返しません。非同期でダウンロードする場合は `SimpleHTTP::SaveAsync()` を使います。
		/// @return HTTP レスポンス
		HTTPResponse Save(URLView url, FilePathView filePath);

		/// @brief 指定した URL からファイルをダウンロードし、HTTP レスポンスを返します。
		/// @param url URL
		/// @param writer ダウンロードしたデータの格納先
		/// @remark この関数は失敗するかダウンロードが終了するまで制御を返しません。
		/// @return HTTP レスポンス
		HTTPResponse Load(URLView url, MemoryWriter& writer);

		/// @brief 指定した URL からファイルをダウンロードし、HTTP レスポンスを返します。
		/// @param url URL
		/// @param writer ダウンロードしたデータの格納先の IWriter インタフェース
		/// @remark この関数は失敗するかダウンロードが終了するまで制御を返しません。
		/// @return HTTP レスポンス
		HTTPResponse Load(URLView url, IWriter& writer);

		/// @brief GET メソッドで Web サーバにリクエストを送ります。
		/// @param url URL
		/// @param headers ヘッダ
		/// @param filePath ダウンロードしたファイルを保存するパス
		/// @remark この関数は、失敗するかレスポンスを受け取るまで制御を返しません。
		/// @return HTTP レスポンス
		HTTPResponse Get(URLView url, const HashTable<String, String>& headers, FilePathView filePath);

		/// @brief GET メソッドで Web サーバにリクエストを送ります。
		/// @param url URL
		/// @param headers ヘッダ
		/// @param writer ダウンロードしたデータの格納先
		/// @remark この関数は、失敗するかレスポンスを受け取るまで制御を返しません。
		/// @return HTTP レスポンス
		HTTPResponse Get(URLView url, const HashTable<String, String>& headers, MemoryWriter& writer);

		/// @brief GET メソッドで Web サーバにリクエストを送ります。
		/// @param url URL
		/// @param headers ヘッダ
		/// @param writer ダウンロードしたデータの格納先の IWriter インタフェース
		/// @remark この関数は、失敗するかレスポンスを受け取るまで制御を返しません。
		/// @return HTTP レスポンス
		HTTPResponse Get(URLView url, const HashTable<String, String>& headers, IWriter& writer);

		/// @brief POST メソッドで Web サーバにリクエストを送ります。
		/// @param url URL
		/// @param headers ヘッダ
		/// @param src 送信するデータの先頭ポインタ
		/// @param size 送信するデータのサイズ
		/// @param filePath ダウンロードしたファイルを保存するパス
		/// @remark この関数は、失敗するかレスポンスを受け取るまで制御を返しません。
		/// @return HTTP レスポンス
		HTTPResponse Post(URLView url, const HashTable<String, String>& headers, const void* src, size_t size, FilePathView filePath);

		/// @brief POST メソッドで Web サーバにリクエストを送ります。
		/// @param url URL
		/// @param headers ヘッダ
		/// @param src 送信するデータの先頭ポインタ
		/// @param size 送信するデータのサイズ
		/// @param writer ダウンロードしたデータの格納先
		/// @remark この関数は、失敗するかレスポンスを受け取るまで制御を返しません。
		/// @return HTTP レスポンス
		HTTPResponse Post(URLView url, const HashTable<String, String>& headers, const void* src, size_t size, MemoryWriter& writer);

		/// @brief OST メソッドで Web サーバにリクエストを送ります。
		/// @param url URL
		/// @param headers ヘッダ
		/// @param src 送信するデータの先頭ポインタ
		/// @param size 送信するデータのサイズ
		/// @param writer ダウンロードしたデータの格納先の IWriter インタフェース
		/// @remark この関数は、失敗するかレスポンスを受け取るまで制御を返しません。
		/// @return HTTP レスポンス
		HTTPResponse Post(URLView url, const HashTable<String, String>& headers, const void* src, size_t size, IWriter& writer);

		/// @brief 指定した URL からファイルをダウンロードします。
		/// @param url URL
		/// @param filePath ダウンロードしたファイルを保存するパス
		/// @return 非同期ダウンロードを管理するオブジェクト
		[[nodiscard]]
		AsyncHTTPTask SaveAsync(URLView url, FilePathView filePath);
	}
}