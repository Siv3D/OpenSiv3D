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
# include "HTTPProgress.hpp"
# include "HTTPResponse.hpp"
# include "URLView.hpp"
# include "AsyncTask.hpp"

namespace s3d
{
	class AsyncHTTPTask;
	class AsyncHTTPTaskDetail;

	namespace SimpleHTTP
	{
		AsyncHTTPTask SaveAsync(URLView url, FilePathView filePath);
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

	private:

		AsyncHTTPTask(URLView url, FilePathView path);

		friend AsyncHTTPTask SimpleHTTP::SaveAsync(URLView url, FilePathView filePath);

	# if SIV3D_PLATFORM(WEB)
		friend AsyncTask<HTTPResponse> Platform::Web::SimpleHTTP::CreateAsyncTask(AsyncHTTPTask& httpTask);
	# endif

		std::shared_ptr<AsyncHTTPTaskDetail> pImpl;
	};
}