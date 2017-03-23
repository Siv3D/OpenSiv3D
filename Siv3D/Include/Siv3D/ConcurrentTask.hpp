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
# include <future>
# include "Fwd.hpp"

namespace s3d
{
	template <class Type>
	class ConcurrentTask : protected std::future<Type>
	{
	private:

		using base_type = std::future<Type>;

	public:

		using base_type::operator=;
		using base_type::get;
		using base_type::valid;
		using base_type::wait;
		using base_type::wait_for;
		using base_type::wait_until;
		using base_type::share;

		template <class Fty, class... Args>
		ConcurrentTask(Fty&& f, Args&&... args)
			: std::future<Type>(std::async(std::launch::async, std::forward<Fty>(f), std::forward<Args>(args)...)) {}

		bool is_done() const
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			return _Is_ready();

		# else

			return wait_for(std::chrono::seconds(0)) == std::future_status::ready;

		# endif	
		}
	};

	template <class Fty, class... Args>
	inline auto CreateConcurrentTask(Fty&& f, Args&&... args)
	{
		return ConcurrentTask<std::result_of_t<std::decay_t<Fty>(std::decay_t<Args>...)>>(std::forward<Fty>(f), std::forward<Args>(args)...);
	}
}
