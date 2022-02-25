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

namespace s3d
{
	template <class Type>
	inline AsyncTask<Type>::AsyncTask(base_type&& other) noexcept
		: m_data{ std::move(other) } {}

	template <class Type>
	inline AsyncTask<Type>::AsyncTask(AsyncTask&& other) noexcept
		: m_data{ std::move(other.m_data) } {}

	template <class Type>
	template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>*>
	inline AsyncTask<Type>::AsyncTask(Fty&& f, Args&&... args)
		: m_data{ std::async(std::launch::async, std::forward<Fty>(f), std::forward<Args>(args)...) } {}

	template <class Type>
	inline AsyncTask<Type>& AsyncTask<Type>::operator =(base_type&& other) noexcept
	{
		m_data = std::move(other);

		return *this;
	}

	template <class Type>
	inline AsyncTask<Type>& AsyncTask<Type>::operator =(AsyncTask&& other) noexcept
	{
		m_data = std::move(other.m_data);

		return *this;
	}

	template <class Type>
	inline bool AsyncTask<Type>::isValid() const noexcept
	{
		return m_data.valid();
	}

	template <class Type>
	inline bool AsyncTask<Type>::isReady() const
	{
		return m_data.valid()
			&& (m_data.wait_for(std::chrono::seconds(0)) == std::future_status::ready);
	}

	template <class Type>
	inline Type AsyncTask<Type>::get()
	{
		return m_data.get();
	}

	template <class Type>
	inline void AsyncTask<Type>::wait() const
	{
		m_data.wait();
	}

	template <class Type>
	template <class Rep, class Period>
	inline std::future_status AsyncTask<Type>::wait_for(const std::chrono::duration<Rep, Period>& relTime) const
	{
		return m_data.wait_for(relTime);
	}

	template <class Type>
	template <class Clock, class Duration>
	inline std::future_status AsyncTask<Type>::wait_until(const std::chrono::time_point<Clock, Duration>& absTime) const
	{
		return m_data.wait_for(absTime);
	}

	template <class Type>
	inline std::shared_future<Type> AsyncTask<Type>::share() noexcept
	{
		return m_data.share();
	}

	template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>*>
	inline auto Async(Fty&& f, Args&&... args)
	{
		return AsyncTask<std::invoke_result_t<std::decay_t<Fty>, std::decay_t<Args>...>>{ std::forward<Fty>(f), std::forward<Args>(args)... };
	}
}
