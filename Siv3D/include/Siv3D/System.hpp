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
# include "Duration.hpp"
# include "EngineOptions.hpp"
# include "HashTable.hpp"
# include "AsyncTask.hpp"
# include "Optional.hpp"

namespace s3d
{
	namespace System
	{
		/// @brief 描画や入力情報など、フレームを更新します。
		/// @remarkアプリケーション終了トリガーが発生するか、内部で回復不能なエラーが発生した場合に false を返します。この関数が false を返したらプログラムを終了させるべきです。
		/// @return プログラムの続行の可否
		bool Update();

		/// @brief プログラムを終了させるために、この直後の `System::Update()` が false を返すように設定します。
		/// @remark この関数自体は終了処理を行わないため、この関数の呼び出しは必須ではありません。
		void Exit() noexcept;

		/// @brief アプリケーション終了トリガーに設定するユーザアクションを設定します。
		/// @param userActionFlags アプリケーション終了トリガーに設定するユーザアクションのフラグ
		/// @remark フラグには `UserAction` の値の組み合わせを使います。
		void SetTerminationTriggers(uint32 userActionFlags) noexcept;

		/// @brief アプリケーション終了トリガーに設定したユーザアクションのフラグの現在の設定を返します。
		/// @remark フラグには `UserAction` の値の組み合わせが使われています。
		/// @return プリケーション終了トリガーに設定したユーザアクションのフラグの組み合わせ
		[[nodiscard]]
		uint32 GetTerminationTriggers() noexcept;

		/// @brief 前回のフレームで発生したユーザアクションを返します。
		/// @remarkフラグには `UserAction` の値の組み合わせが使われています。
		/// @return 前のフレームで発生したユーザアクションのフラグの組み合わせ
		[[nodiscard]]
		uint32 GetUserActions() noexcept;

		/// @brief 現在のスレッドの実行を指定した時間だけ停止します。
		/// @param milliseconds スリープする時間（ミリ秒）
		void Sleep(int32 milliseconds);

		/// @brief 現在のスレッドの実行を指定した時間だけ停止します。
		/// @param duration スリープする時間
		void Sleep(const Duration& duration);

		/// @brief 指定した URL をデフォルトの Web ブラウザでオープンします。
		/// @param url URL
		/// @return オープンに成功した場合 true, それ以外の場合は false
		bool LaunchBrowser(FilePathView url);

		/// @brief ファイルパスをファイルマネージャー上で表示します。
		/// @param path ファイルパス
		/// @return ファイルマネージャー上での表示に成功した場合 true, それ以外の場合は false
		bool ShowInFileManager(FilePathView path);

		/// @brief レンダラーの設定を返します。
		/// @return レンダラーの設定
		[[nodiscard]]
		EngineOption::Renderer GetRendererType();
	}

# if SIV3D_PLATFORM(WEB)

	namespace Platform::Web::System
	{
		/// @brief ゲームループごとに呼ばれる関数を登録します
		[[noreturn]] 
		void SetMainLoop(std::function<void()> mainLoop);

		/// @brief 現在のページのクエリ文字列を取得します
		/// @return 現在のページのクエリ文字列
		[[nodiscard]]
		HashTable<String, String> GetURLParameters();

		/// @brief 指定した AsyncTask の準備ができるまで待機します
		template<class Type>
		Optional<Type> WaitForFutureResolved(AsyncTask<Type>& task);
	}

# endif
}

# include "detail/System.ipp"
