//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <type_traits>

namespace s3d
{
	template<typename Callback>
	class ScopeGuard
	{
	private:

		Callback m_callback;

		bool m_active = true;

	public:

		ScopeGuard() = delete;

		ScopeGuard(const ScopeGuard&) = delete;

		ScopeGuard(ScopeGuard&& other) noexcept(std::is_nothrow_constructible_v<Callback, Callback&&>)
			: m_callback(std::forward<Callback>(other.m_callback))
			, m_active(other.m_active)
		{
			other.m_active = false;
		}

		ScopeGuard(Callback&& callback) noexcept(std::is_nothrow_constructible_v<Callback, Callback&&>)
			: m_callback(std::forward<Callback>(callback)) {}

		~ScopeGuard() noexcept
		{
			if (m_active)
			{
				m_callback();
			}
		}

		ScopeGuard& operator =(const ScopeGuard&) = delete;

		void dismiss() noexcept
		{
			m_active = false;
		}
	};
}
