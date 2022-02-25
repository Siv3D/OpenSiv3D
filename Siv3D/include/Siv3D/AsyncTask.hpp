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
# ifndef SIV3D_NO_CONCURRENT_API

# include <future>
# include <type_traits>
# include "Platform.hpp"

namespace s3d
{
	/// @brief 非同期処理クラス
	/// @tparam Type 非同期処理のタスクで実行する関数の戻り値の型
	template <class Type>
	class AsyncTask
	{
	public:

		using base_type = std::future<Type>;

		/// @brief デフォルトコンストラクタ
		/// @remark 何もしません
		SIV3D_NODISCARD_CXX20
		AsyncTask() = default;

		SIV3D_NODISCARD_CXX20
		AsyncTask(base_type&& other) noexcept;

		SIV3D_NODISCARD_CXX20
		AsyncTask(AsyncTask&& other) noexcept;

		/// @brief 非同期処理のタスクを作成します
		/// @tparam Fty 非同期処理のタスクで実行する関数の型
		/// @tparam ...Args 非同期処理のタスクで実行する関数の引数の型
		/// @param f 非同期処理のタスクで実行する関数
		/// @param ...args 非同期処理のタスクで実行する関数の引数
		/// @remark 作成と同時にタスクが非同期で実行されます
		template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		explicit AsyncTask(Fty&& f, Args&&... args);

		~AsyncTask() = default;

		AsyncTask(const base_type&) = delete;
		
		AsyncTask(const AsyncTask&) = delete;
		
		AsyncTask& operator =(const base_type&) = delete;
		
		AsyncTask& operator =(const AsyncTask&) = delete;

		AsyncTask& operator =(base_type&& other) noexcept;
		
		AsyncTask& operator =(AsyncTask&& other) noexcept;

		/// @brief 非同期処理を持っているかを返します。
		/// @remark `get()` を呼ぶと、非同期処理を持たない状態に戻ります。
		/// @return 非同期処理を持っている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isValid() const noexcept;

		/// @brief タスクが完了した非同期処理を持っていて、結果をすぐに返せる状態であるかを返します。
		/// @remark `get()` を呼ぶと、非同期処理を持たない状態に戻ります。
		/// @return タスクが完了した非同期処理を持っていて、結果をすぐに返せる状態である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isReady() const;

		/// @brief タスクが完了した非同期処理の結果を返します。
		/// @remark タスクが完了していない場合は、完了まで待機します。
		/// @return タスクが完了した非同期処理の結果
		Type get();

		/// @brief 非同期処理のタスク完了を待ちます。
		void wait() const;

		template <class Rep, class Period>
		std::future_status wait_for(const std::chrono::duration<Rep, Period>& relTime) const;

		template <class Clock, class Duration>
		std::future_status wait_until(const std::chrono::time_point<Clock, Duration>& absTime) const;

		[[nodiscard]]
		std::shared_future<Type> share() noexcept;

	private:

		base_type m_data;
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
	inline auto Async(Fty&& f, Args&&... args);
}

# include "detail/AsyncTask.ipp"

# endif // SIV3D_NO_CONCURRENT_API
