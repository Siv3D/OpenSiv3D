//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "HTTPProgress.hpp"
# include "HTTPResponse.hpp"
# include "URLView.hpp"
# include "AsyncTask.hpp"
# include "HashTable.hpp"

namespace s3d
{
	class AsyncHTTPTask;
	class AsyncHTTPTaskDetail;
	class Blob;
	class MemoryViewReader;
	class JSON;

	namespace SimpleHTTP
	{
		AsyncHTTPTask GetAsync(URLView url, const HashTable<String, String>& headers, FilePathView filePath);

		AsyncHTTPTask GetAsync(URLView url, const HashTable<String, String>& headers);

		AsyncHTTPTask PostAsync(URLView url, const HashTable<String, String>& headers, const void* src, size_t size, FilePathView filePath);

		AsyncHTTPTask PostAsync(URLView url, const HashTable<String, String>& headers, const void* src, size_t size);
	}

# if SIV3D_PLATFORM(WEB)

	namespace Platform::Web::SimpleHTTP
	{
		AsyncTask<HTTPResponse> CreateAsyncTask(AsyncHTTPTask& httpTask);
	}

# endif

	/// @brief 非同期ダウンロードを管理するクラス
	class AsyncHTTPTask
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		AsyncHTTPTask();

		/// @brief 管理するダウンロードが無いかを返します。
		/// @return 管理するダウンロードが無い場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const;

		/// @brief 管理するダウンロードがあるかを返します。
		/// @return 管理するダウンロードがある場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const;

		/// @brief ダウンロードが終了したときに 1 度だけ true を返します。
		/// @return ダウンロードが終了した場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isReady() const;

		/// @brief ダウンロードを中断します。
		void cancel();

		/// @brief ダウンロードの進行状況を返します。
		/// @return ダウンロードの進行状況
		[[nodiscard]]
		HTTPAsyncStatus getStatus() const;

		/// @brief ダウンロードの進捗を返します。
		/// @return ダウンロードの進捗
		[[nodiscard]]
		HTTPProgress getProgress() const;

		/// @brief ダウンロードが進行中であるかを返します。
		/// @remark `getStatus() == HTTPAsyncStatus::Downloading` と同じです。
		/// @return ダウンロードが進行中である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isDownloading() const;

		/// @brief ダウンロードが失敗したかを返します。
		/// @remark `getStatus() == HTTPAsyncStatus::Failed` と同じです。
		/// @return ダウンロードが失敗した場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isFailed() const;

		/// @brief ダウンロードが中断されたかを返します。
		/// @remark `getStatus() == HTTPAsyncStatus::Canceled` と同じです。
		/// @return ダウンロードが中断された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isCanceled() const;

		/// @brief ダウンロードが成功したかを返します。
		/// @remark `getStatus() == HTTPAsyncStatus::Succeeded` と同じです。
		/// @return ダウンロードが成功した場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isSucceeded() const;

		/// @brief HTTP レスポンスを返します。
		/// @return HTTP レスポンス
		[[nodiscard]]
		const HTTPResponse& getResponse();

		/// @brief ダウンロード先がファイルであるかを返します。
		/// @return ダウンロード先がファイルの場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isFile() const;

		/// @brief ダウンロード先がメモリであるかを返します。
		/// @return ダウンロード先がメモリの場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isBlob() const;

		/// @brief ダウンロード先のファイルパスを返します。
		/// @return ダウンロード内容を保存したファイルパス。メモリへのダウンロードの場合は空の文字列。
		[[nodiscard]]
		const FilePath& getFilePath() const;

		/// @brief ダウンロードしたデータを返します。
		/// @return ダウンロード内容を保存したバイナリデータ。ファイルへのダウンロードの場合は空のバイナリデータ。
		[[nodiscard]]
		const Blob& getBlob() const;

		/// @brief ダウンロードしたデータを読み込む MemoryViewReader を返します。
		/// @return ダウンロード内容を保存したバイナリデータに対する MemoryViewReader, ファイルへのダウンロードの場合は空の MemoryViewReader.
		[[nodiscard]]
		MemoryViewReader getBlobReader() const;

		/// @brief ダウンロードしたデータを JSON としてパースした結果を返します。
		/// @return ダウンロード内容を JSON と解釈した結果
		/// @remark ダウンロード先がファイルであっても、メモリであっても使用できます。
		[[nodiscard]]
		JSON getAsJSON() const;

	private:

		AsyncHTTPTask(URLView url, const HashTable<String, String>& headers, FilePathView path);

		AsyncHTTPTask(URLView url, const HashTable<String, String>& headers);

		AsyncHTTPTask(URLView url, const HashTable<String, String>& headers, const void* src, size_t size, FilePathView path);

		AsyncHTTPTask(URLView url, const HashTable<String, String>& headers, const void* src, size_t size);

		friend AsyncHTTPTask SimpleHTTP::GetAsync(URLView url, const HashTable<String, String>& headers, FilePathView filePath);

		friend AsyncHTTPTask SimpleHTTP::GetAsync(URLView url, const HashTable<String, String>& headers);

		friend AsyncHTTPTask SimpleHTTP::PostAsync(URLView url, const HashTable<String, String>& headers, const void* src, size_t size, FilePathView filePath);

		friend AsyncHTTPTask SimpleHTTP::PostAsync(URLView url, const HashTable<String, String>& headers, const void* src, size_t size);

	# if SIV3D_PLATFORM(WEB)
		friend AsyncTask<HTTPResponse> Platform::Web::SimpleHTTP::CreateAsyncTask(AsyncHTTPTask& httpTask);
	# endif

		std::shared_ptr<AsyncHTTPTaskDetail> pImpl;
	};
}
