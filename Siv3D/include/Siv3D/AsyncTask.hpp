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
# ifndef SIV3D_NO_CONCURRENT_API

# include <future>
# include <type_traits>
# include "Platform.hpp"

namespace s3d
{
	/// @brief 非同期処理クラス
	/// @tparam Type 非同期処理のタスクで実行する関数の戻り値の型
	template <class Type>
	class AsyncTask : protected std::future<Type>
	{
		using base_type = std::future<Type>;

		using base_type::operator=;
		using base_type::get;
		using base_type::valid;
		using base_type::wait;
		using base_type::wait_for;
		using base_type::wait_until;
		using base_type::share;

		/// @brief デフォルトコンストラクタ
		/// @remark 何もしません
		SIV3D_NODISCARD_CXX20
		AsyncTask() = default;

		/// @brief 非同期処理のタスクを作成します
		/// @tparam Fty 非同期処理のタスクで実行する関数の型
		/// @tparam ...Args 非同期処理のタスクで実行する関数の引数の型
		/// @param f 非同期処理のタスクで実行する関数
		/// @param ...args 非同期処理のタスクで実行する関数の引数
		/// @remark 作成と同時にタスクが非同期で実行されます
		template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		explicit AsyncTask(Fty&& f, Args&&... args);

		/// @brief 非同期処理のタスクが完了しているかを返します。
		/// @return 非同期処理のタスクが完了している場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isReady() const;
	};

	template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>* = nullptr>
	AsyncTask(Fty, Args...)->AsyncTask<std::invoke_result_t<std::decay_t<Fty>, std::decay_t<Args>...>>;

	/// @brief 非同期処理のタスクを作成します
	/// @tparam Fty 非同期処理のタスクで実行する関数の型
	/// @tparam ...Args 非同期処理のタスクで実行する関数の引数の型
	/// @param f 非同期処理のタスクで実行する関数
	/// @param ...args 非同期処理のタスクで実行する関数の引数
	/// @remark 作成と同時にタスクが非同期で実行されます
	/// @return 作成された非同期処理のタスク
	template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>* = nullptr>
	[[nodiscard]]
	inline auto CreateAsyncTask(Fty&& f, Args&&... args);
}

# include "detail/AsyncTask.ipp"

# endif // SIV3D_NO_CONCURRENT_API
